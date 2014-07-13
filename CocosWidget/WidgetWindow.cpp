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
#include "WidgetWindow.h"
#if USING_LUA
#include "CCLuaEngine.h"
#endif
#include "GUI/CCControlExtension/CCControl.h"
using namespace std;

NS_CC_WIDGET_BEGIN

CWidgetWindow::CWidgetWindow()
: m_bIsTouched(false)
, m_nTouchPriority(0)
, m_bModalable(false)
, m_bTouchEnabled(true)
, m_pSelectedWidget(NULL)
, m_fTouchedDuration(0.0f)
, m_pTouchMovedAfterLongClickListener(NULL)
, m_pTouchEndedAfterLongClickListener(NULL)
, m_pTouchCancelledAfterLongClickListener(NULL)
, m_pTouchMovedAfterLongClickHandler(NULL)
, m_pTouchEndedAfterLongClickHandler(NULL)
, m_pTouchCancelledAfterLongClickHandler(NULL)
, m_pLongClickedWidgetObject(NULL)
, m_bMultiTouchEnabled(false)
#if USING_LUA
, m_nTouchMovedAfterLongClickScriptHandler(0)
, m_nTouchEndedAfterLongClickScriptHandler(0)
, m_pTouchCancelledAfterLongClickScriptHandler(0)
#endif
{

}

CWidgetWindow::~CWidgetWindow()
{
#if USING_LUA
	removeOnTouchMovedAfterLongClickScriptHandler();
	removeOnTouchEndedAfterLongClickScriptHandler();
	removeOnTouchCancelledAfterLongClickScriptHandler();
#endif
}

int CWidgetWindow::getTouchPriority()
{
	return m_nTouchPriority;
}

CCObject* CWidgetWindow::findWidgetById(const char* id)
{
	CCAssert(id && strlen(id), "should not null");

	return find(m_pChildren, id);
}

CCObject* CWidgetWindow::find(CCArray* pChidren, const char* id)
{
	if( pChidren && pChidren->count() > 0 )
	{
		unsigned int nCount = pChidren->count();
		for(unsigned int i = 0; i < nCount; ++i)
		{
			CCObject* pObject = pChidren->objectAtIndex(i);
			CWidget* pWidget = dynamic_cast<CWidget*>(pObject);
			if( pWidget )
			{
				if( strcmp(pWidget->getId(), id) == 0 )
				{
					return pObject;
				}
				else
				{
					CCObject* pRet = find(dynamic_cast<CCNode*>(pObject)->getChildren(), id);
					if( pRet )
					{
						return pRet;
					}
				}
			}
		}
	}
	return NULL;
}

void CWidgetWindow::setLongClickTouchHandlerWidget(CCObject* pWidgetObject, int nTouchId)
{
	if( m_bMultiTouchEnabled && !m_mMultiTouchKeeper.empty() )
	{
		map<int, __ccMULTITOUCHTARGET>::iterator itr = m_mMultiTouchKeeper.find(nTouchId);
		if( itr != m_mMultiTouchKeeper.end() )
		{
			itr->second.pLongClickedWidgetObject = pWidgetObject;
		}
	}
	else
	{
		m_pLongClickedWidgetObject = pWidgetObject;
	}
}

void CWidgetWindow::setOnTouchMovedAfterLongClickListener(CCObject* pListener, SEL_AfterLongClickHandler pHandler)
{
	m_pTouchMovedAfterLongClickListener = pListener;
    m_pTouchMovedAfterLongClickHandler = pHandler;
}

void CWidgetWindow::setOnTouchEndedAfterLongClickListener(CCObject* pListener, SEL_AfterLongClickHandler pHandler)
{
	m_pTouchEndedAfterLongClickListener = pListener;
    m_pTouchEndedAfterLongClickHandler = pHandler;
}

void CWidgetWindow::setOnTouchCancelledAfterLongClickListener(CCObject* pListener, SEL_AfterLongClickHandler pHandler)
{
	m_pTouchCancelledAfterLongClickListener = pListener;
    m_pTouchCancelledAfterLongClickHandler = pHandler;
}

#if USING_LUA
void CWidgetWindow::setOnTouchMovedAfterLongClickScriptHandler(int nHandler)
{
	removeOnTouchMovedAfterLongClickScriptHandler();
	m_nTouchMovedAfterLongClickScriptHandler = nHandler;
}

void CWidgetWindow::setOnTouchEndedAfterLongClickScriptHandler(int nHandler)
{
	removeOnTouchEndedAfterLongClickScriptHandler();
	m_nTouchEndedAfterLongClickScriptHandler = nHandler;
}

void CWidgetWindow::setOnTouchCancelledAfterLongClickScriptHandler(int nHandler)
{
	removeOnTouchCancelledAfterLongClickScriptHandler();
	m_pTouchCancelledAfterLongClickScriptHandler = nHandler;
}

void CWidgetWindow::removeOnTouchMovedAfterLongClickScriptHandler()
{
	if( m_nTouchMovedAfterLongClickScriptHandler != 0 )
	{
		CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nTouchMovedAfterLongClickScriptHandler);
		m_nTouchMovedAfterLongClickScriptHandler = 0;
	}
}

void CWidgetWindow::removeOnTouchEndedAfterLongClickScriptHandler()
{
	if( m_nTouchEndedAfterLongClickScriptHandler != 0 )
	{
		CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nTouchEndedAfterLongClickScriptHandler);
		m_nTouchEndedAfterLongClickScriptHandler = 0;
	}
}

void CWidgetWindow::removeOnTouchCancelledAfterLongClickScriptHandler()
{
	if( m_pTouchCancelledAfterLongClickScriptHandler != 0 )
	{
		CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_pTouchCancelledAfterLongClickScriptHandler);
		m_pTouchCancelledAfterLongClickScriptHandler = 0;
	}
}
#endif

void CWidgetWindow::executeTouchMovedAfterLongClickHandler(CCObject* pSender, CCTouch *pTouch, float fDuration)
{
    if( m_pTouchMovedAfterLongClickListener && m_pTouchMovedAfterLongClickHandler )
    {
        (m_pTouchMovedAfterLongClickListener->*m_pTouchMovedAfterLongClickHandler)(pSender, pTouch, fDuration);
    }
#if USING_LUA
	else if( m_nTouchMovedAfterLongClickScriptHandler != 0 )
	{
		CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
		CCLuaStack* pStack = pEngine->getLuaStack();

		pStack->pushCCObject(pSender, "CCObject");
		pStack->pushCCObject(pTouch, "CCTouch");
		pStack->pushFloat(fDuration);

		int nRet = pStack->executeFunctionByHandler(m_nTouchMovedAfterLongClickScriptHandler, 3);
		pStack->clean();
	}
#endif
}

void CWidgetWindow::executeTouchEndedAfterLongClickHandler(CCObject* pSender, CCTouch *pTouch, float fDuration)
{
    if( m_pTouchEndedAfterLongClickListener && m_pTouchEndedAfterLongClickHandler )
    {
		(m_pTouchEndedAfterLongClickListener->*m_pTouchEndedAfterLongClickHandler)(pSender, pTouch, fDuration);
    }
#if USING_LUA
	else if( m_nTouchEndedAfterLongClickScriptHandler != 0 )
	{
		CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
		CCLuaStack* pStack = pEngine->getLuaStack();

		pStack->pushCCObject(pSender, "CCObject");
		pStack->pushCCObject(pTouch, "CCTouch");
		pStack->pushFloat(fDuration);

		int nRet = pStack->executeFunctionByHandler(m_nTouchEndedAfterLongClickScriptHandler, 3);
		pStack->clean();
	}
#endif
}

void CWidgetWindow::executeTouchCancelledAfterLongClickHandler(CCObject* pSender, CCTouch *pTouch, float fDuration)
{
    if( m_pTouchCancelledAfterLongClickListener && m_pTouchCancelledAfterLongClickHandler )
    {
		(m_pTouchCancelledAfterLongClickListener->*m_pTouchCancelledAfterLongClickHandler)(pSender, pTouch, fDuration);
    }
#if USING_LUA
	else if( m_pTouchCancelledAfterLongClickScriptHandler != 0 )
	{
		CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
		CCLuaStack* pStack = pEngine->getLuaStack();

		pStack->pushCCObject(pSender, "CCObject");
		pStack->pushCCObject(pTouch, "CCTouch");
		pStack->pushFloat(fDuration);

		int nRet = pStack->executeFunctionByHandler(m_pTouchCancelledAfterLongClickScriptHandler, 3);
		pStack->clean();
	}
#endif
}

void CWidgetWindow::setTouchPriority(int nTouchPriority)
{
	if( m_nTouchPriority != nTouchPriority )
	{
		m_nTouchPriority = nTouchPriority;
		if( m_bTouchEnabled && m_bRunning )
		{
			CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
			pDispatcher->setPriority(nTouchPriority, this);
		}
	}
}

bool CWidgetWindow::isMultiTouchEnabled() const
{
	return m_bMultiTouchEnabled;
}

void CWidgetWindow::setMultiTouchEnabled(bool bEnabled)
{
	if( m_bMultiTouchEnabled != bEnabled )
	{
		setTouchEnabled(false);
		m_bMultiTouchEnabled = bEnabled;
		setTouchEnabled(true);
	}
}

void CWidgetWindow::setModalable(bool bModalable, bool isRootContainer /* = false */)
{
	m_bModalable = bModalable;
	
	CCArray *arr = getChildren();
	for (int i = 0; i < arr->count();i++)
	{
		CWidgetWindow *pWindow = dynamic_cast<CWidgetWindow *>(arr->objectAtIndex(i));
		if (pWindow != nullptr) pWindow->setModalable(bModalable);
		//混用组件EidtBox等
		extension::CCControl *pControl = dynamic_cast<extension::CCControl*>(arr->objectAtIndex(i));
		if (pControl != nullptr) pControl->setEnabled(!bModalable);
	}
	if (isRootContainer){
		m_bModalable = false;
	}
}

bool CWidgetWindow::isModalable() const
{
	return m_bModalable;
}

bool CWidgetWindow::isTouchEnabled()
{
	return m_bTouchEnabled;
}

void CWidgetWindow::setTouchEnabled(bool bTouchEnabled)
{
	if( m_bTouchEnabled != bTouchEnabled )
	{
		m_bTouchEnabled = bTouchEnabled;
		if( m_bRunning )
		{
			if( bTouchEnabled )
			{
				if( m_bMultiTouchEnabled )
				{
					CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, m_nTouchPriority);
				}
				else
				{
					CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_nTouchPriority, true);
				}
			}
			else
			{
				CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			}
		}
	}
}

bool CWidgetWindow::init()
{
	if( CCNode::init() )
	{
		CCSize tWinSize = CCDirector::sharedDirector()->getWinSize();

		this->ignoreAnchorPointForPosition(true);
		this->setContentSize(tWinSize);
		this->setAnchorPoint(CCPointZero);
		this->setPosition(CCPointZero);

		return true;
	}
	return false;
}

void CWidgetWindow::visit()
{
	if( m_bIsTouched )
	{
		m_fTouchedDuration += CCDirector::sharedDirector()->getDeltaTime();
	}

	if( !m_mMultiTouchKeeper.empty() )
	{
		map<int, __ccMULTITOUCHTARGET>::iterator itr = m_mMultiTouchKeeper.begin();
		for(; itr != m_mMultiTouchKeeper.end(); ++itr)
		{
			itr->second.fTouchedDuration += CCDirector::sharedDirector()->getDeltaTime();
		}
	}

	CCNode::visit();
}

void CWidgetWindow::onEnter()
{
	if( m_bTouchEnabled )
	{
		if( m_bMultiTouchEnabled )
		{
			CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, m_nTouchPriority);
		}
		else
		{
			CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_nTouchPriority, true);
		}
	}
	CCNode::onEnter();
}

void CWidgetWindow::onExit()
{
	if( m_bTouchEnabled )
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
	CCNode::onExit();
}

bool CWidgetWindow::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bModalable) return true;
	if( m_bTouchEnabled && m_bVisible && m_pChildren && m_pChildren->count() > 0 )
	{
		CCPoint touchPointInView = convertToNodeSpace(pTouch->getLocation());
		if( m_pChildren && m_pChildren->count() > 0 )
		{
			CCObject* pObject = NULL;
			CCARRAY_FOREACH_REVERSE( m_pChildren, pObject )
			{
				CCNode* pNode = dynamic_cast<CCNode*>(pObject);
				CWidget* pWidget = dynamic_cast<CWidget*>(pObject);
				if( pWidget && pNode->isVisible() && pWidget->isEnabled() && pWidget->isTouchEnabled() )
				{
					if( pNode->boundingBox().containsPoint(touchPointInView) )
					{
						if( pWidget->executeTouchBeganHandler(pTouch) != eWidgetTouchNone )
						{
							m_pSelectedWidget = pWidget;
							m_bIsTouched = true;
							m_fTouchedDuration = 0.0f;
							return true;
						}
					}
				}
			}
			m_pSelectedWidget = NULL;
		}
	}
	return m_bModalable;
}

void CWidgetWindow::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if( m_pSelectedWidget )
	{
		if( m_pSelectedWidget->isTouchInterrupted() )
		{
			if( m_pLongClickedWidgetObject )
			{
				executeTouchMovedAfterLongClickHandler(m_pLongClickedWidgetObject, pTouch, m_fTouchedDuration);
			}
		}
		else
		{
			m_pSelectedWidget->executeTouchMovedHandler(pTouch, m_fTouchedDuration);
		}
	}
}

void CWidgetWindow::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if( m_pSelectedWidget )
	{
		if( m_pSelectedWidget->isTouchInterrupted() )
		{
			if( m_pLongClickedWidgetObject )
			{
				executeTouchEndedAfterLongClickHandler(m_pLongClickedWidgetObject, pTouch, m_fTouchedDuration);
			}
		}
		else
		{
			m_pSelectedWidget->executeTouchEndedHandler(pTouch, m_fTouchedDuration);
		}
	}
	m_bIsTouched = false;
    m_fTouchedDuration = 0.0f;
	m_pSelectedWidget = NULL;
	m_pLongClickedWidgetObject = NULL;
}

void CWidgetWindow::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	if( m_pSelectedWidget )
	{
		if( m_pSelectedWidget->isTouchInterrupted() )
		{
			if( m_pLongClickedWidgetObject )
			{
				executeTouchCancelledAfterLongClickHandler(m_pLongClickedWidgetObject, pTouch, m_fTouchedDuration);
			}
		}
		else
		{
			m_pSelectedWidget->interruptTouchCascade(pTouch, m_fTouchedDuration);
		}
	}
	m_bIsTouched = false;
    m_fTouchedDuration = 0.0f;
	m_pSelectedWidget = NULL;
	m_pLongClickedWidgetObject = NULL;
}

void CWidgetWindow::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator itr = pTouches->begin();
	for(; itr != pTouches->end(); ++itr)
	{
		CCTouch* pTouch = (CCTouch*)(*itr);
		if( m_bTouchEnabled && m_bMultiTouchEnabled && m_bVisible && m_pChildren && m_pChildren->count() > 0 )
		{
			CCPoint touchPointInView = convertToNodeSpace(pTouch->getLocation());
			if( m_pChildren && m_pChildren->count() > 0 )
			{
				CCObject* pObject = NULL;
				CCARRAY_FOREACH_REVERSE( m_pChildren, pObject )
				{
					CCNode* pNode = dynamic_cast<CCNode*>(pObject);
					CWidget* pWidget = dynamic_cast<CWidget*>(pObject);
					if( pWidget && pNode->isVisible() && pWidget->isEnabled() && pWidget->isTouchEnabled() )
					{
						bool bSameWidgetBreak = false;
						if( pNode->boundingBox().containsPoint(touchPointInView) )
						{
							//make sure it can not happened on the same widget
							map<int, __ccMULTITOUCHTARGET>::iterator mitr = m_mMultiTouchKeeper.begin();
							for(; mitr != m_mMultiTouchKeeper.end(); ++mitr)
							{
								if( mitr->second.pWidget == pWidget )
								{
									bSameWidgetBreak = true;
									break;
								}
							}

							if( bSameWidgetBreak )
							{
								break;
							}

							if( pWidget->executeTouchBeganHandler(pTouch) != eWidgetTouchNone )
							{
								__ccMULTITOUCHTARGET tKeeper;
								tKeeper.fTouchedDuration = 0.0f;
								tKeeper.pWidget = pWidget;
								tKeeper.pLongClickedWidgetObject = NULL;
								m_mMultiTouchKeeper[pTouch->getID()] = tKeeper;
								return;
							}
						}
					}
				}
			}

		}
	}
}

void CWidgetWindow::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator itr = pTouches->begin();
	for(; itr != pTouches->end(); ++itr)
	{
		CCTouch* pTouch = (CCTouch*)(*itr);
		map<int, __ccMULTITOUCHTARGET>::iterator mitr = m_mMultiTouchKeeper.find(pTouch->getID());
		if( mitr != m_mMultiTouchKeeper.end() )
		{
			if( mitr->second.pWidget->isTouchInterrupted() )
			{
				if( mitr->second.pLongClickedWidgetObject )
				{
					executeTouchMovedAfterLongClickHandler(mitr->second.pLongClickedWidgetObject, pTouch, mitr->second.fTouchedDuration);
				}
			}
			else
			{
				mitr->second.pWidget->executeTouchMovedHandler(pTouch, mitr->second.fTouchedDuration);
			}
		}
	}
}

void CWidgetWindow::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator itr = pTouches->begin();
	for(; itr != pTouches->end(); ++itr)
	{
		CCTouch* pTouch = (CCTouch*)(*itr);
		map<int, __ccMULTITOUCHTARGET>::iterator mitr = m_mMultiTouchKeeper.find(pTouch->getID());
		if( mitr != m_mMultiTouchKeeper.end() )
		{
			if( mitr->second.pWidget )
			{
				if( mitr->second.pWidget->isTouchInterrupted() )
				{
					if( mitr->second.pLongClickedWidgetObject )
					{
						executeTouchEndedAfterLongClickHandler(mitr->second.pLongClickedWidgetObject, pTouch, mitr->second.fTouchedDuration);
					}
				}
				else
				{
					mitr->second.pWidget->executeTouchEndedHandler(pTouch, mitr->second.fTouchedDuration);
				}
			}
			m_mMultiTouchKeeper.erase(mitr);
		}
	}
}

void CWidgetWindow::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator itr = pTouches->begin();
	for(; itr != pTouches->end(); ++itr)
	{
		CCTouch* pTouch = (CCTouch*)(*itr);
		map<int, __ccMULTITOUCHTARGET>::iterator mitr = m_mMultiTouchKeeper.find(pTouch->getID());
		if( mitr != m_mMultiTouchKeeper.end() )
		{
			if( mitr->second.pWidget )
			{
				if( mitr->second.pWidget->isTouchInterrupted() )
				{
					if( mitr->second.pLongClickedWidgetObject )
					{
						executeTouchCancelledAfterLongClickHandler(mitr->second.pLongClickedWidgetObject, pTouch, mitr->second.fTouchedDuration);
					}
				}
				else
				{
					mitr->second.pWidget->interruptTouchCascade(pTouch, mitr->second.fTouchedDuration);
				}
			}
			m_mMultiTouchKeeper.erase(mitr);
		}
	}
}

CWidgetWindow* CWidgetWindow::create()
{
	CWidgetWindow *pRet = new CWidgetWindow();
	if( pRet && pRet->init() )
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}


NS_CC_WIDGET_END