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
#include "CCSceneManager.h"
#include <algorithm>
using namespace std;

NS_CC_BEGIN

CCSceneManager::CCSceneManager()
: m_bSendCleanupToScene(false)
, m_bPopup(true)
, m_pRunningScene(NULL)
, m_pNextScene(NULL)
{
	m_pMsgManager = CCMsgManager::sharedManager();
}

CCSceneManager::~CCSceneManager()
{
	m_pMsgManager->release();

	if(!m_lSceneSwitchQueue.empty())
	{
		list<ccSCENESWITCH>::iterator itr = m_lSceneSwitchQueue.begin();
		list<ccSCENESWITCH>::iterator end = m_lSceneSwitchQueue.end();

		for(; itr != end; ++itr )
		{
			CC_SAFE_RELEASE(itr->pNextScene);
			CC_SAFE_RELEASE(itr->pExtra);
		}
	}
	m_lSceneSwitchQueue.clear();

	removeAllCachedScenes();

	if(!m_vRunningSceneStack.empty())
	{
		vector<CCSceneExtension*>::iterator itr = m_vRunningSceneStack.begin();
		vector<CCSceneExtension*>::iterator end = m_vRunningSceneStack.end();

		for(; itr != end; ++itr )
		{
			CC_SAFE_RELEASE(*itr);
		}
	}
	m_vRunningSceneStack.clear();

	if(!m_vRunningUIScenes.empty())
	{
		vector<CCSceneExtension*>::iterator itr = m_vRunningUIScenes.begin();
		vector<CCSceneExtension*>::iterator end = m_vRunningUIScenes.end();

		for(; itr != end; ++itr )
		{
			CC_SAFE_RELEASE(*itr);
		}
	}
	m_vRunningUIScenes.clear();
	m_mFnSceneCreatePointers.clear();

	CC_SAFE_RELEASE(m_pRunningScene);
}

CCSceneManager* CCSceneManager::sharedManager()
{
	static CCSceneManager* pInstance = NULL;
	if( pInstance == NULL ) {
		pInstance = new CCSceneManager();
		pInstance->init();
		CCDirector::sharedDirector()->runWithScene(pInstance);
		pInstance->release();
	}
	return pInstance;
}

void CCSceneManager::visit()
{
	mainLoop();
}

void CCSceneManager::mainLoop()
{
// << message

	m_pMsgManager->update();

// << switch

	do {
		CC_BREAK_IF(m_lSceneSwitchQueue.empty());
		ccSCENESWITCH& tSceneSwitch = m_lSceneSwitchQueue.front();
		
		CC_BREAK_IF(tSceneSwitch.bLockedSwitch);
		handleSceneSwitch(tSceneSwitch);
		m_lSceneSwitchQueue.pop_front();
	}
	while(0);
	
	do {
		CC_BREAK_IF(m_lUISceneSwitchQueue.empty());
		ccUISCENESWITCH& tSceneSwitch = m_lUISceneSwitchQueue.front();
		
		CC_BREAK_IF(tSceneSwitch.bLockedSwitch);
		handleUISceneSwitch(tSceneSwitch);
		m_lUISceneSwitchQueue.pop_front();
	}
	while(1);

// << draw scene

	if( m_pNextScene )
    {
        setNextScene();
    }

    if( m_pRunningScene )
    {
        m_pRunningScene->visit();
    }

// << draw ui scene

	visitUIScenes();
}

void CCSceneManager::runWithScene(CCSceneExtension* pScene, CCObject* pExtra)
{
	CCAssert(pScene != NULL, "This command can only be used to start the CCDirector. There is already a scene present.");
    CCAssert(m_pRunningScene == NULL, "m_pRunningScene should be null");

    pushScene(pScene, pExtra);
}

void CCSceneManager::pushScene(CCSceneExtension* pScene, CCObject* pExtra)
{
	CCAssert(pScene, "the scene should not null");

	if( isSceneRunning(getSceneClassName(pScene)) )
		return;

	ccSCENESWITCH tSceneSwitch;
	tSceneSwitch.pNextScene = pScene;
	tSceneSwitch.pExtra = NULL;
	tSceneSwitch.eType = eSceneSwitchPushScene;
	tSceneSwitch.bLockedSwitch = true;

	setExtraToScene(pScene, tSceneSwitch.pExtra);
	m_lSceneSwitchQueue.push_back(tSceneSwitch);
	
	CC_SAFE_RETAIN(pScene);

	if( !loadSceneResources(pScene) )
	{
		m_lSceneSwitchQueue.back().bLockedSwitch = false;
	}
}

void CCSceneManager::replaceScene(CCSceneExtension* pScene, CCObject* pExtra)
{
	CCAssert(m_pRunningScene, "Use runWithScene: instead to start the director");
	CCAssert(pScene != NULL, "the scene should not be null");

	if( isSceneRunning(getSceneClassName(pScene)) )
		return;

	ccSCENESWITCH tSceneSwitch;
	tSceneSwitch.pNextScene = pScene;
	tSceneSwitch.pExtra = pExtra;
	tSceneSwitch.eType = eSceneSwitchReplaceScene;
	tSceneSwitch.bLockedSwitch = true;

	setExtraToScene(pScene, tSceneSwitch.pExtra);
	m_lSceneSwitchQueue.push_back(tSceneSwitch);

	CC_SAFE_RETAIN(pScene);

	if( !loadSceneResources(pScene) )
	{
		m_lSceneSwitchQueue.back().bLockedSwitch = false;
	}
}

void CCSceneManager::popScene(CCObject* pExtra)
{
	CCAssert(m_pRunningScene != NULL, "running scene should not null");

	ccSCENESWITCH tSceneSwitch;
	tSceneSwitch.pNextScene = NULL;
	tSceneSwitch.pExtra = pExtra;
	tSceneSwitch.eType = eSceneSwitchPopScene;
	tSceneSwitch.bLockedSwitch = false;

	CC_SAFE_RETAIN(pExtra);

	m_lSceneSwitchQueue.push_back(tSceneSwitch);
}

void CCSceneManager::popToRootScene(CCObject* pExtra)
{
	popToSceneStackLevel(1, pExtra);
}

void CCSceneManager::popToSceneStackLevel(int nLevel, CCObject* pExtra)
{
    CCAssert(m_pRunningScene != NULL, "A running Scene is needed");

	ccSCENESWITCH tSceneSwitch;
	tSceneSwitch.pNextScene = NULL;
	tSceneSwitch.pExtra = pExtra;
	tSceneSwitch.eType = eSceneSwitchPopToSceneStackLevel;
	tSceneSwitch.nPopSceneStackLevel = nLevel;

	CC_SAFE_RETAIN(pExtra);

	m_lSceneSwitchQueue.push_back(tSceneSwitch);
}

void CCSceneManager::end()
{
	autorelease();
	CCDirector::sharedDirector()->end();
}

void CCSceneManager::runUIScene(CCSceneExtension* pScene, CCObject* pExtra /* = NULL */, bool isPopup /* = true */)
{
	CCAssert(pScene != NULL && !dynamic_cast<CCSceneExTransition*>(pScene), "should not null and not transition");

	if( isSceneRunning(getSceneClassName(pScene)) )
		return;

	ccUISCENESWITCH tSceneSwitch;
	tSceneSwitch.pScene = pScene;
	tSceneSwitch.eType = eUISceneSwitchRunScene;
	tSceneSwitch.bLockedSwitch = true;
	m_lUISceneSwitchQueue.push_back(tSceneSwitch);

	CC_SAFE_RETAIN(pScene);
	setExtraToScene(pScene, pExtra);

	if( !loadSceneResources(pScene) )
	{
		m_lUISceneSwitchQueue.back().bLockedSwitch = false;
	}

	m_bPopup = isPopup;
	if (m_bPopup)
	{
		vector<CCSceneExtension*>::iterator it;
		for (it = m_vRunningUIScenes.begin(); it != m_vRunningUIScenes.end(); ++it)
		{
			if (pScene != (*it))
				(*it)->setModalable(true,true);
		}
		m_pRunningScene->setModalable(true,true);
	}
}

void CCSceneManager::popUIScene(CCSceneExtension* pScene)
{
	CCAssert(pScene != NULL, "A running Scene is needed");

	if(!isSceneRunning(getSceneClassName(pScene)) )
		return;

	ccUISCENESWITCH tSceneSwitch;
	tSceneSwitch.pScene = pScene;
	tSceneSwitch.eType = eUISceneSwitchPopScene;
	tSceneSwitch.bLockedSwitch = false;
	m_lUISceneSwitchQueue.push_back(tSceneSwitch);

	if (m_bPopup)
	{
		if (m_vRunningUIScenes.size() >= 2){
			auto preUISceneIt = m_vRunningUIScenes.end() - 2;
			(*preUISceneIt)->setModalable(false);
		}
		if (m_vRunningUIScenes.size() == 1)
			m_pRunningScene->setModalable(false);
	}
}

void CCSceneManager::popAllUIScene()
{
	unsigned int i = 0;
	unsigned int c = m_vRunningUIScenes.size();

	for(; i < c; ++i )
	{
		ccUISCENESWITCH tSceneSwitch;
		tSceneSwitch.pScene = m_vRunningUIScenes[i];
		tSceneSwitch.eType = eUISceneSwitchPopScene;
		tSceneSwitch.bLockedSwitch = false;
		m_lUISceneSwitchQueue.push_back(tSceneSwitch);
	}

	if (m_bPopup)
	{
		for (; i < c; ++i)
		{
			m_vRunningUIScenes[i]->setModalable(false);
		}
		m_pRunningScene->setModalable(false);
	}
}

bool CCSceneManager::isSceneRunning(const char* pSceneName)
{
	vector<CCSceneExtension*>::iterator ritr = m_vRunningSceneStack.begin();
	vector<CCSceneExtension*>::iterator rend = m_vRunningSceneStack.end();
	for(; ritr != rend; ++ritr )
	{
		if( strcmp((*ritr)->getClassName(), pSceneName) == 0 )
		{
			return true;
		}
	}

	vector<CCSceneExtension*>::iterator uitr = m_vRunningUIScenes.begin();
	vector<CCSceneExtension*>::iterator uend = m_vRunningUIScenes.end();
	for(; uitr != uend; ++uitr )
	{
		if( strcmp((*uitr)->getClassName(), pSceneName) == 0 )
		{
			return true;
		}
	}

	return false;
}

CCSceneExtension* CCSceneManager::getRunningScene() const
{
	return m_pRunningScene;
}

void CCSceneManager::setNextScene()
{
	bool runningIsTransition = dynamic_cast<CCSceneExTransition*>(m_pRunningScene) != NULL;
	bool newIsTransition = dynamic_cast<CCSceneExTransition*>(m_pNextScene) != NULL;

	// If it is not a transition, call onExit/cleanup
	if (! newIsTransition)
	{
		if (m_pRunningScene)
		{
			m_pRunningScene->onExitTransitionDidStart();
			m_pRunningScene->onExit();
		}

		// issue #709. the root node (scene) should receive the cleanup message too
		// otherwise it might be leaked.
		if (m_bSendCleanupToScene && m_pRunningScene)
		{
			m_pRunningScene->cleanup();
		}
	}

	if (m_pRunningScene)
	{
		m_pRunningScene->release();
	}
	m_pRunningScene = m_pNextScene;
	m_pNextScene->retain();
	m_pNextScene = NULL;

	if ((! runningIsTransition) && m_pRunningScene)
	{
		m_pRunningScene->onEnter();
		m_pRunningScene->onEnterTransitionDidFinish();
	}
}

void CCSceneManager::handleSceneSwitch(ccSCENESWITCH& tSceneSwitch)
{
	switch( tSceneSwitch.eType )
	{
	case eSceneSwitchPushScene:
		{
			CCAssert(tSceneSwitch.pNextScene, "the scene should not null");
			CCSceneExtension* pScene = tSceneSwitch.pNextScene;
			pScene->autorelease();

			addCachableScene(pScene);

			m_bSendCleanupToScene = false;

			m_vRunningSceneStack.push_back(pScene);
			pScene->retain();
			m_pNextScene = pScene;

#if(COCOS2D_DEBUG >= 1)
			debugSceneSwitchInfo();
#endif
		}
		break;
	case eSceneSwitchReplaceScene:
		{
			CCAssert(m_pRunningScene, "Use runWithScene: instead to start the director");
			CCAssert(tSceneSwitch.pNextScene != NULL, "the scene should not be null");
			CCSceneExtension* pScene = tSceneSwitch.pNextScene;
			pScene->autorelease();

			addCachableScene(pScene);

			m_bSendCleanupToScene = true;
			m_vRunningSceneStack.back()->release();
			m_vRunningSceneStack.pop_back();
			m_vRunningSceneStack.push_back(pScene);
			pScene->retain();

			m_pNextScene = pScene;

#if(COCOS2D_DEBUG >= 1)
			debugSceneSwitchInfo();
#endif
		}
		break;
	case eSceneSwitchPopScene:
		{
			CCAssert(m_pRunningScene != NULL, "running scene should not null");

			m_vRunningSceneStack.back()->release();
			m_vRunningSceneStack.pop_back();
			unsigned int c = m_vRunningSceneStack.size();

			if (c == 0)
			{
				CC_SAFE_RELEASE(tSceneSwitch.pExtra);
				end();
			}
			else
			{
				setExtraToScene(m_vRunningSceneStack.back(), tSceneSwitch.pExtra);
				CC_SAFE_RELEASE(tSceneSwitch.pExtra);

				m_bSendCleanupToScene = true;
				m_pNextScene = m_vRunningSceneStack[c - 1];
			}

#if(COCOS2D_DEBUG >= 1)
			debugSceneSwitchInfo();
#endif
		}
		break;
	case eSceneSwitchPopToSceneStackLevel:
		{
			 CCAssert(m_pRunningScene != NULL, "A running Scene is needed");
			 int c = (int) m_vRunningSceneStack.size();
			 int level = tSceneSwitch.nPopSceneStackLevel;

			 // level 0? -> end
			 if (level == 0)
			 {
				 CC_SAFE_RELEASE(tSceneSwitch.pExtra);
				 end();
				 return;
			 }

			 // current level or lower -> nothing
			 if (level >= c)
			 {
				 CC_SAFE_RELEASE(tSceneSwitch.pExtra);
				 return;
			 }

			 // pop stack until reaching desired level
			 while (c > level)
			 {
				 CCSceneExtension* current = m_vRunningSceneStack.back();

				 if (current->isRunning())
				 {
					 current->onExitTransitionDidStart();
					 current->onExit();
				 }

				 current->cleanup();
				 m_vRunningSceneStack.back()->release();
				 m_vRunningSceneStack.pop_back();
				 c--;
			 }

			 setExtraToScene(m_vRunningSceneStack.back(), tSceneSwitch.pExtra);
			 CC_SAFE_RELEASE(tSceneSwitch.pExtra);

			 m_pNextScene = m_vRunningSceneStack.back();
			 m_bSendCleanupToScene = false;

#if(COCOS2D_DEBUG >= 1)
			debugSceneSwitchInfo();
#endif
		}
		break;
	}
}

void CCSceneManager::unlockSceneSwitch(const char* pClassName)
{
	if( m_lSceneSwitchQueue.empty() )
		return;

	list<ccSCENESWITCH>::iterator itr = m_lSceneSwitchQueue.begin();
	list<ccSCENESWITCH>::iterator end = m_lSceneSwitchQueue.end();

	for(; itr != end; ++itr )
	{
		CCSceneExTransition* pTransitionScene = dynamic_cast<CCSceneExTransition*>(itr->pNextScene);
		CCSceneExtension* pInScene = itr->pNextScene;

		if( pTransitionScene )
		{
			pInScene = pTransitionScene->getInScene();
		}

		if( strcmp(pInScene->getClassName(), pClassName) == 0 )
		{
			itr->bLockedSwitch = false;
			return;
		}
	}
}

void CCSceneManager::handleUISceneSwitch(ccUISCENESWITCH& tSceneSwitch)
{
	switch( tSceneSwitch.eType )
	{
	case eUISceneSwitchRunScene:
		{
			tSceneSwitch.pScene->autorelease();
			addCachableScene(tSceneSwitch.pScene);

			tSceneSwitch.pScene->retain();
			tSceneSwitch.pScene->onEnter();
			tSceneSwitch.pScene->onEnterTransitionDidFinish();
			m_vRunningUIScenes.push_back(tSceneSwitch.pScene);
		}
		break;
	case eUISceneSwitchPopScene:
		{
			vector<CCSceneExtension*>::iterator itr = std::find(m_vRunningUIScenes.begin(), m_vRunningUIScenes.end(), tSceneSwitch.pScene);
			if( itr != m_vRunningUIScenes.end() )
			{
				tSceneSwitch.pScene->onExitTransitionDidStart();
				tSceneSwitch.pScene->onExit();
				tSceneSwitch.pScene->release();
				m_vRunningUIScenes.erase(itr);
			}
		}
		break;
	}
}

void CCSceneManager::unlockUISceneSwitch(const char* pClassName)
{
	if( m_lUISceneSwitchQueue.empty() )
		return;

	list<ccUISCENESWITCH>::iterator itr = m_lUISceneSwitchQueue.begin();
	list<ccUISCENESWITCH>::iterator end = m_lUISceneSwitchQueue.end();

	for(; itr != end; ++itr )
	{
		if( strcmp(itr->pScene->getClassName(), pClassName) == 0 )
		{
			itr->bLockedSwitch = false;
			return;
		}
	}
}

void CCSceneManager::visitUIScenes()
{
	unsigned int i = 0;
	unsigned int c = m_vRunningUIScenes.size();

	for(; i < c; ++i )
	{
		m_vRunningUIScenes[i]->visit();
	}
}

void CCSceneManager::removeCachedScene(const char* pSceneName)
{
	map<string, CCSceneExtension*>::iterator itr = m_mSceneCachePool.find(pSceneName);
	if( itr != m_mSceneCachePool.end() )
	{
		itr->second->release();
		m_mSceneCachePool.erase(itr);
	}
}

void CCSceneManager::removeAllCachedScenes()
{
	if( m_mSceneCachePool.empty() )
		return;

	map<string, CCSceneExtension*>::iterator itr = m_mSceneCachePool.begin();
	for(; itr != m_mSceneCachePool.end(); ++itr)
	{
		itr->second->release();
	}
	m_mSceneCachePool.clear();
}

void CCSceneManager::removeUnusedCachedScenes()
{
	if( m_mSceneCachePool.empty() )
		return;

	vector<map<string, CCSceneExtension*>::iterator> removeStack;
	map<string, CCSceneExtension*>::iterator itr = m_mSceneCachePool.begin();
	map<string, CCSceneExtension*>::iterator end = m_mSceneCachePool.end();

	for(; itr != end; ++itr )
	{
		if( itr->second->isSingleReference() )
		{
			itr->second->release();
			removeStack.push_back(itr);
		}
	}

	unsigned int i = 0;
	unsigned int c = m_mSceneCachePool.size();

	for(; i < c; ++i )
	{
		m_mSceneCachePool.erase(removeStack[i]);
	}
}

void CCSceneManager::registerSceneClass(const char* pSceneName, Fn_CreateSceneExtension pFn)
{
	if( pFn && pSceneName && strlen(pSceneName) )
	{
		m_mFnSceneCreatePointers[pSceneName] = pFn;
	}
}

CCSceneExtension* CCSceneManager::loadScene(const char* pSceneName)
{
	CCAssert(pSceneName && strlen(pSceneName), "should not null");

	map<string, CCSceneExtension*>::iterator mitr = m_mSceneCachePool.find(pSceneName);
	if( mitr != m_mSceneCachePool.end() )
	{
		return mitr->second;
	}

	map<string, Fn_CreateSceneExtension>::iterator itr = m_mFnSceneCreatePointers.find(pSceneName);
	if( itr != m_mFnSceneCreatePointers.end() )
	{
		CCSceneExtension* pScene = (*itr->second)();
		pScene->setClassName(pSceneName);
		pScene->init();
		pScene->autorelease();
		return pScene;
	}

	return NULL;
}

CCSceneExtension* CCSceneManager::seekScene(const char* pSceneName)
{
	CCAssert(pSceneName && strlen(pSceneName), "should not null");

	vector<CCSceneExtension*>::iterator ritr = m_vRunningSceneStack.begin();
	vector<CCSceneExtension*>::iterator rend = m_vRunningSceneStack.end();
	for(; ritr != rend; ++ritr )
	{
		if( strcmp((*ritr)->getClassName(), pSceneName) == 0 )
		{
			return (*ritr);
		}
	}

	vector<CCSceneExtension*>::iterator uitr = m_vRunningUIScenes.begin();
	vector<CCSceneExtension*>::iterator uend = m_vRunningUIScenes.end();
	for(; uitr != uend; ++uitr )
	{
		if( strcmp((*uitr)->getClassName(), pSceneName) == 0 )
		{
			return (*uitr);
		}
	}

	map<string, CCSceneExtension*>::iterator mitr = m_mSceneCachePool.find(pSceneName);
	if( mitr != m_mSceneCachePool.end() )
	{
		return mitr->second;
	}

	return NULL;
}

bool CCSceneManager::loadSceneResources(CCSceneExtension* pScene)
{
	CCSceneExTransition* pTransitionScene = dynamic_cast<CCSceneExTransition*>(pScene);
	CCSceneExtension* pInScene = pScene;

	if( pTransitionScene )
	{
		pInScene = pTransitionScene->getInScene();
	}

	if( !pInScene->isLoaded() )
	{
		pInScene->onLoadResources();
		pInScene->loadResourcesSync();

		if( pInScene->isLoadingResourcesAsync() )
		{
			pInScene->loadResourcesAsync();
			pInScene->setLoaded(true);
			return true;
		}
		else
		{
			pInScene->onLoadResourcesCompleted();
			pInScene->onLoadScene();
		}

		pInScene->setLoaded(true);
	}

	return false;
}

void CCSceneManager::setExtraToScene(CCSceneExtension* pScene, CCObject* pExtra)
{
	CCSceneExTransition* pTransitionScene = dynamic_cast<CCSceneExTransition*>(pScene);
	CCSceneExtension* pInScene = pScene;

	if( pTransitionScene )
	{
		pInScene = pTransitionScene->getInScene();
	}

	if( pExtra )
	{
		pInScene->setExtraObject(pExtra);
	}
}

void CCSceneManager::addCachableScene(CCSceneExtension* pScene)
{
	CCSceneExTransition* pTransitionScene = dynamic_cast<CCSceneExTransition*>(pScene);
	CCSceneExtension* pInScene = pScene;

	if( pTransitionScene )
	{
		pInScene = pTransitionScene->getInScene();
	}

	map<string, CCSceneExtension*>::iterator mitr = m_mSceneCachePool.find(pInScene->getClassName());
	if( mitr == m_mSceneCachePool.end() && pInScene->isCachable() )
	{
		m_mSceneCachePool.insert(make_pair(pInScene->getClassName(), pInScene));
		pInScene->retain();
	}
}

const char* CCSceneManager::getSceneClassName(CCSceneExtension* pScene)
{
	CCSceneExTransition* pTransitionScene = dynamic_cast<CCSceneExTransition*>(pScene);
	CCSceneExtension* pInScene = pScene;

	if( pTransitionScene )
	{
		pInScene = pTransitionScene->getInScene();
	}

	return pInScene->getClassName();
}

int CCSceneManager::getTouchPriority()
{
	static int nTouchPriority = 0;
	return nTouchPriority--;
}

#if(COCOS2D_DEBUG >= 1)
void CCSceneManager::debugSceneSwitchInfo()
{
	string strStackText = "Running Scene : ";
	vector<CCSceneExtension*>::iterator itr = m_vRunningSceneStack.begin();
	vector<CCSceneExtension*>::iterator end = m_vRunningSceneStack.end();

	for(; itr != end; ++itr )
	{
		if( dynamic_cast<CCSceneExTransition*>(*itr) )
		{
			strStackText.append("Transition -> ");
		}
		else
		{
			const char* pClassName = (*itr)->getClassName();
			strStackText.append(pClassName).append(" -> ");
		}
	}
	strStackText.erase(strStackText.size() - 4);

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SetWindowTextA(CCEGLView::sharedOpenGLView()->getHWnd(), strStackText.c_str());
	CCLOG(strStackText.c_str());
#else
	//CCLOG(strStackText.c_str());
#endif
}
#endif

NS_CC_END