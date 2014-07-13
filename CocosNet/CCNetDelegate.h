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
#ifndef __CCNET_NETDELEGATE_H__
#define __CCNET_NETDELEGATE_H__

#include "cocos2d.h"
#include "CCNetMacros.h"
#include "CCSocket.h"

NS_CC_BEGIN

/**
 * class  : CCNetDelegate
 * author : Jason lee
 * email  : jason.lee.c@foxmail.com
 * descpt : the net delegate, use it as connector
 */
class CCNetDelegate : public CCObject
{
public:
	CCNetDelegate();
	virtual ~CCNetDelegate();

public:
	// will calling when a package is coming
	virtual void onMessageReceived(CCBuffer& oBuffer) = 0;

	// when connected will calling
	virtual void onConnected(){}

	// when connect time out will calling
	virtual void onConnectTimeout(){}

	// on disconnected will call
	virtual void onDisconnected(){}

	// on exception
	virtual void onExceptionCaught(CCSocketStatus eStatus){}

public:
	// set target address
	void setInetAddress(const CCInetAddress& oInetAddress);

	// get target address
	const CCInetAddress& getInetAddress() const;
	
	// the time out of connecting
	void setSoTimeout(float fSoTimeout);

	// get the time out value
	float getSoTimeout() const;

	// send package to target address
	void send(char* pBuffer, unsigned int uLen);

	// send package to target address
	void send(CCBuffer* pBuffer);

	// check the net status
	bool isConnected();

	// close the socket
	void close();

	// connect to target address
	bool connect();

	// disconnect as close for now
	void disconnect();

private:
	// read data on every frame, if needed
	bool runRead();

	// send data on every frame, if needed
	bool runWrite();

	// frame call
	void runSchedule(float dt);
	
	// registe the function of frame called
	void registerScheduler();

	// unregiste the function of frame called
	void unregisterScheduler();

private:

	/**
	 * struct : _SENDBUFFER
	 * author : Jason lee
	 * email  : jason.lee.c@foxmail.com
	 * descpt : send data
	 */
	struct _SENDBUFFER
	{
		char* pBuffer;       // the data
		int nOffset;         // the send data offset
		int nLength;         // data's length
	};
	
private:
	bool                   m_bRunSchedule;
	float                  m_fConnectingDuration;
	float                  m_fSoTimeout;
	std::list<_SENDBUFFER> m_lSendBuffers;
	CCBuffer               m_oReadBuffer;
	CCInetAddress          m_oInetAddress;
	CCSocket               m_oSocket;
	char                   m_pReadBuffer[SOCKET_READ_BUFFER_SIZE];

protected:
	CCSocketStatus         m_eStatus;
};

NS_CC_END

#endif //__CCNET_NETDELEGATE_H__