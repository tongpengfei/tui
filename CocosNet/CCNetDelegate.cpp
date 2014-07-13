﻿/****************************************************************************
Copyright (c) 2014 Lijunlin - Jason lee

Created by Lijunlin - Jason lee on 2014

jason.lee.c@foxmail.com
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCNetDelegate.h"

NS_CC_BEGIN

CCNetDelegate::CCNetDelegate()
: m_fSoTimeout(SOCKET_SOTIMEOUT)
, m_eStatus(eSocketIoClosed)
, m_fConnectingDuration(0.0f)
, m_bRunSchedule(false)
{
	
}

CCNetDelegate::~CCNetDelegate()
{
	m_oSocket.ccClose();

	while(!m_lSendBuffers.empty())
	{
		CC_SAFE_DELETE_ARRAY(m_lSendBuffers.front().pBuffer);
		m_lSendBuffers.pop_front();
	}
}

void CCNetDelegate::setInetAddress(const CCInetAddress& oInetAddress)
{
	m_oInetAddress = oInetAddress;
}

const CCInetAddress& CCNetDelegate::getInetAddress() const
{
	return m_oInetAddress;
}

void CCNetDelegate::setSoTimeout(float fSoTimeout)
{
	m_fSoTimeout = fSoTimeout;
}

float CCNetDelegate::getSoTimeout() const
{
	return m_fSoTimeout;
}

void CCNetDelegate::send(char* pBuffer, unsigned int uLen)
{
	if( !pBuffer || uLen == 0 || !isConnected() )
		return;
	
#if USING_PACKAGE_HEAD_LENGTH
	CCBuffer* pBuf = new CCBuffer(pBuffer, uLen);
	pBuf->autorelease();
	send(pBuf);
#else
	char* pTemp = new char[uLen];
	memcpy(pTemp, pBuffer, uLen);

	_SENDBUFFER tBuf;
	tBuf.pBuffer = pTemp;
	tBuf.nLength = (int)uLen;
	tBuf.nOffset = 0;

	m_lSendBuffers.push_back(tBuf);
#endif
}

void CCNetDelegate::send(CCBuffer* pBuffer)
{
	if( pBuffer->empty() || !isConnected() )
		return;

#if USING_PACKAGE_HEAD_LENGTH
	unsigned int u_len = pBuffer->length();
	pBuffer->moveRight(sizeof(unsigned int));
	pBuffer->moveWriterIndexToFront();
	pBuffer->writeUInt(u_len);
#endif

	pBuffer->moveReaderIndexToFront();
	char* pData = pBuffer->readWholeData();
	int nLength = (int)pBuffer->length();
	pBuffer->moveReaderIndexToFront();

	_SENDBUFFER tBuf;
	tBuf.pBuffer = pData;
	tBuf.nLength = nLength;
	tBuf.nOffset = 0;

	m_lSendBuffers.push_back(tBuf);
}

bool CCNetDelegate::isConnected()
{
	return m_eStatus == eSocketConnected;
}

bool CCNetDelegate::connect()
{
	if( m_eStatus != eSocketConnected && m_eStatus != eSocketConnecting )
	{
		m_oSocket.setInetAddress(m_oInetAddress);
		if( m_oSocket.ccConnect() )
		{
			registerScheduler();
			m_eStatus = eSocketConnecting;
			return true;
		}
	}
	return false;
}

void CCNetDelegate::disconnect()
{
	if( m_eStatus == eSocketConnected )
	{
		unregisterScheduler();
		m_oSocket.ccDisconnect();
		m_eStatus = eSocketDisconnected;
		onDisconnected();
	}
}

void CCNetDelegate::close()
{
	if( m_eStatus == eSocketConnected )
	{
		unregisterScheduler();
		m_oSocket.ccClose();
		m_eStatus = eSocketIoClosed;
		onDisconnected();
	}
}

void CCNetDelegate::runSchedule(float dt)
{
	switch( m_eStatus )
	{
	case eSocketConnecting:
		{
			switch( m_oSocket.ccIsConnected() )
			{
			case eSocketConnected:
				{
					m_eStatus = eSocketConnected;
					onConnected();
				}
				break;
			case eSocketConnectFailed:
				{
					unregisterScheduler();
                    m_oSocket.ccClose();
					m_eStatus = eSocketConnectFailed;
					onExceptionCaught(eSocketConnectFailed);
				}
				break;
			case eSocketConnecting:
				{
					if( m_fConnectingDuration > m_fSoTimeout )
					{
						unregisterScheduler();
						m_oSocket.ccDisconnect();
						m_eStatus = eSocketDisconnected;
						onConnectTimeout();
						m_fConnectingDuration = 0.0f;
					}
					else
					{
						m_fConnectingDuration += dt;
					}
				}
				break;
			default:
				break;
			}
		}
		break;
	case eSocketConnected:
		{
#if HANDLE_ON_SINGLE_FRAME
			while( m_oSocket.ccIsReadable() )
#else
			if( m_oSocket.ccIsReadable() )
#endif
			{
				if( this->runRead() ) return;
			}

#if HANDLE_ON_SINGLE_FRAME
			while( m_oSocket.ccIsWritable() && !m_lSendBuffers.empty() )
#else
			if( m_oSocket.ccIsWritable() && !m_lSendBuffers.empty() )
#endif
			{
				if( this->runWrite() ) return;
			}
		}
		break;
	default:
		break;
	}	
}

bool CCNetDelegate::runRead()
{
	int nRet = m_oSocket.ccRead(m_pReadBuffer, SOCKET_READ_BUFFER_SIZE);
	if( nRet == eSocketIoError || nRet == eSocketIoClosed )
	{
		unregisterScheduler();
		m_oSocket.ccClose();
		m_eStatus = eSocketIoClosed;
		onDisconnected();
		return true;
	}
	else
	{
#if 1
		CCLOG("CCSOCKET READ %d", nRet);
#endif
		m_oReadBuffer.writeData(m_pReadBuffer, (unsigned int)nRet);
#if USING_PACKAGE_HEAD_LENGTH
		while( m_oReadBuffer.isReadable(sizeof(int)) )
		{
			m_oReadBuffer.moveReaderIndexToFront();
			int n_head_len = m_oReadBuffer.readInt();
			if( n_head_len <= 0 )
			{
				CCLOGERROR("invalidate head length");
				m_oReadBuffer.moveLeft(sizeof(int));
			}

			int n_content_len = (int)m_oReadBuffer.length();
			if( n_content_len - (int)(sizeof(int)) >= n_head_len )
			{
				m_oReadBuffer.moveLeft(sizeof(unsigned int));
				CCBuffer* pData = m_oReadBuffer.readData(n_head_len);
				m_oReadBuffer.moveLeft(n_head_len);
				m_oReadBuffer.moveReaderIndexToFront();
				m_oReadBuffer.moveWriterIndexToBack();

				onMessageReceived(*pData);
			}
		}
#else
		CCBuffer* pData = (CCBuffer*) m_oReadBuffer.copy();
		pData->autorelease();
		m_oReadBuffer.clear();
		
		onMessageReceived(*pData);
#endif
	}
	return false;
}

bool CCNetDelegate::runWrite()
{
	_SENDBUFFER& tBuffer = m_lSendBuffers.front();

	int nRet = m_oSocket.ccWrite(tBuffer.pBuffer + tBuffer.nOffset, tBuffer.nLength - tBuffer.nOffset);
#if 1
	CCLOG("CCSOCKET WRITE %d", nRet);
#endif
	if( nRet == eSocketIoError )
	{
		unregisterScheduler();
		m_oSocket.ccClose();
		m_eStatus = eSocketIoClosed;
		onDisconnected();
		return true;
	}
	else if( nRet == tBuffer.nLength - tBuffer.nOffset )
	{
		CC_SAFE_DELETE_ARRAY(tBuffer.pBuffer);
		m_lSendBuffers.pop_front();
	}
	else
	{
		tBuffer.nOffset += nRet;
	}
	return false;
}

void CCNetDelegate::registerScheduler()
{
	if( m_bRunSchedule )
		return;

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
		schedule_selector(CCNetDelegate::runSchedule), 
		this, 
		0.0f, 
		false
	);
	m_bRunSchedule = true;
}

void CCNetDelegate::unregisterScheduler()
{
	if( !m_bRunSchedule )
		return;

	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(
		schedule_selector(CCNetDelegate::runSchedule),
		this
	);
	m_bRunSchedule = false;
}



NS_CC_END