/****************************************************************************
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
#include "CCSceneExtension.h"
#include "CCSceneManager.h"
using namespace std;
#if USING_COCOSWIDGET
using namespace cocos2d::cocoswidget;
#endif


NS_CC_BEGIN

CCSceneExtension::CCSceneExtension()
: m_bCachable(false)
, m_pExtraObject(NULL)
, m_strClassName("")
, m_bLoaded(false)
, m_nLoadResourcesAsyncCount(0)
, m_nLoadResourcesAsyncIdx(0)
, m_bAutoRemoveUnusedTexture(false)
#if! USING_COCOSWIDGET
, m_nTouchPriority(0)
#endif
{
	setAnchorPoint(CCPointZero);
	setContentSize(CCDirector::sharedDirector()->getWinSize());
}

CCSceneExtension::~CCSceneExtension()
{
	CC_SAFE_RELEASE(m_pExtraObject);
#if COCOS2D_DEBUG >= 1
	if( !m_strClassName.empty() )
	{
		CCLOG("CocosBase [DEBUG] : destroy Scene %s", m_strClassName.c_str());
	}
#endif
	if( m_bAutoRemoveUnusedTexture )
	{
		removeAllChildrenWithCleanup(true);
		CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	}
}

void CCSceneExtension::onEnter()
{
#if USING_COCOSWIDGET
	setTouchPriority(CCSceneManager::sharedManager()->getTouchPriority());
	
	CCMsgManager::sharedManager()->registerMessageDelegate(this);
	onEnterScene();
	CWidgetWindow::onEnter();
#else
	m_nTouchPriority = CCSceneManager::sharedManager()->getTouchPriority();

	CCMsgManager::sharedManager()->registerMsgDelegate(this);
	onEnterScene();
	CCNode::onEnter();
#endif
}

void CCSceneExtension::onExit()
{
	CCMsgManager::sharedManager()->unregisterMsgDelegate(this);
#if USING_COCOSWIDGET
	onExitScene();
	CWidgetWindow::onExit();
#else
	onExitScene();
	CCNode::onExit();
#endif
}

bool CCSceneExtension::isAutoRemoveUnusedTexture() const
{
	return m_bAutoRemoveUnusedTexture;
}

void CCSceneExtension::setAutoRemoveUnusedTexture(bool bAuto)
{
	m_bAutoRemoveUnusedTexture = bAuto;
}

bool CCSceneExtension::isCachable() const
{
	return m_bCachable;
}

void CCSceneExtension::setCachable(bool bCachable)
{
	m_bCachable = bCachable;
}

CCObject* CCSceneExtension::getExtraObject() const
{
	return m_pExtraObject;
}

void CCSceneExtension::setExtraObject(CCObject* pExtraObject)
{
	CC_SAFE_RETAIN(pExtraObject);
	CC_SAFE_RELEASE(m_pExtraObject);
	m_pExtraObject = pExtraObject;
}

void CCSceneExtension::setClassName(const char* pClassName)
{
	m_strClassName = pClassName;
}

const char* CCSceneExtension::getClassName()
{
	return m_strClassName.c_str();
}

bool CCSceneExtension::isLoaded() const
{
	return m_bLoaded;
}

#if! USING_COCOSWIDGET
int CCSceneExtension::getTouchPriority() const
{
	return m_nTouchPriority;
}
#endif

void CCSceneExtension::setLoaded(bool bLoaded)
{
	m_bLoaded = bLoaded;
}

void CCSceneExtension::addImage(const char* pFile)
{
	CCAssert(pFile && strlen(pFile), "file path invalidate");
	m_vLoadImageFilesSync.push_back(pFile);
}

void CCSceneExtension::addImageAsync(const char* pFile)
{
	CCAssert(pFile && strlen(pFile), "file path invalidate");
	m_vLoadImageFilesAsync.push_back(pFile);
}

bool CCSceneExtension::isLoadingResourcesAsync()
{
	return !m_vLoadImageFilesAsync.empty();
}

void CCSceneExtension::loadResourcesSync()
{
	if( m_vLoadImageFilesSync.empty() )
		return;

	vector<string>::iterator itr = m_vLoadImageFilesSync.begin();
	vector<string>::iterator end = m_vLoadImageFilesSync.end();

	for(; itr != end; ++itr)
	{
		CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(itr->c_str());
		CCAssert(pTexture, "load image failed");
#if COCOS2D_DEBUG >= 1
		CCLOG("CocosBase [DEBUG] : Scene [%s] load image sync %s", m_strClassName.c_str(), itr->c_str());
#endif
	}

	m_vLoadImageFilesSync.clear();
}

void CCSceneExtension::loadResourcesAsync()
{
	CCAssert(!m_vLoadImageFilesAsync.empty(), "empty");

	CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(false);

	m_nLoadResourcesAsyncCount = m_vLoadImageFilesAsync.size();
	m_nLoadResourcesAsyncIdx = 0;

	vector<string>::iterator itr = m_vLoadImageFilesAsync.begin();
	vector<string>::iterator end = m_vLoadImageFilesAsync.end();

	for(; itr != end; ++itr)
	{
		CCTextureCache::sharedTextureCache()->addImageAsync(
			itr->c_str(), 
			this, 
			callfuncO_selector(CCSceneExtension::loadingResourcesCallBack));
#if COCOS2D_DEBUG >= 1
		CCLOG("CocosBase [DEBUG] : Scene [%s] load image async %s", m_strClassName.c_str(), itr->c_str());
#endif
	}

	m_vLoadImageFilesAsync.clear();
}

void CCSceneExtension::loadingResourcesCallBack(CCObject* pTextureObj)
{
	CCAssert(pTextureObj, "load resources async failed");

	m_nLoadResourcesAsyncIdx ++;

	if( m_nLoadResourcesAsyncIdx == m_nLoadResourcesAsyncCount )
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);

		m_nLoadResourcesAsyncCount = 0;
		m_nLoadResourcesAsyncIdx = 0;
		onLoadResourcesCompleted();
		onLoadScene();

		// there is execute just one
		CCSceneManager::sharedManager()->unlockSceneSwitch(m_strClassName.c_str());
		CCSceneManager::sharedManager()->unlockUISceneSwitch(m_strClassName.c_str());
	}
}


NS_CC_END