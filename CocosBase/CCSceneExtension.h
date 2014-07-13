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
#ifndef __CCBASE_SCENEEXTENSION_H__
#define __CCBASE_SCENEEXTENSION_H__

#include "cocos2d.h"
#include "CCBaseMacros.h"
#include "CCMsgDelegate.h"
#include "CCBundle.h"
#include <string>

NS_CC_BEGIN

/**
 * class  : CCSceneExtension
 * author : Jason lee
 * email  : jason.lee.c@foxmail.com
 * descpt : the base scene of game
 */
class CCSceneExtension 
#if USING_COCOSWIDGET //using CWidgetWindow base scene
: public cocos2d::cocoswidget::CWidgetWindow
#else
: public CCNode
#endif
, public CCMsgDelegate
{
public:
	CCSceneExtension();
	virtual ~CCSceneExtension();

	// the first call, load resources if needed, it will call just once
	virtual void onLoadResources(){};

	// the seconed call, load completed, it will call just once
	virtual void onLoadResourcesCompleted(){};

	// the third call, load this scene, it will call just once
	virtual void onLoadScene(){};

	// when this scene is showing
	virtual void onEnterScene(){};

	// when this scene is hiding
	virtual void onExitScene(){};

	// add image in sync, it will block the main loop for a while
	void addImage(const char* pFile);

	// add image in async, it will not block the main loop
	void addImageAsync(const char* pFile);

	// is auto remove on scene destory
	bool isAutoRemoveUnusedTexture() const;

	// is auto remove unused texture on scene destory
	void setAutoRemoveUnusedTexture(bool bAuto);

	// is a cachable scene ?
	bool isCachable() const;

	// set true it will be a cachable scene
	void setCachable(bool bCachable);

	// get extra data
	CCObject* getExtraObject() const;

	// set the extra data
	void setExtraObject(CCObject* pExtraObject);

	// get class name, work on every time
	const char* getClassName();

	// is this scene is already loaded ?
	bool isLoaded() const;

#if! USING_COCOSWIDGET
	// get touch priority
	int getTouchPriority() const;
#endif
public:
	// override
	virtual void onEnter();
	// override
	virtual void onExit();
	
private:
	friend class CCSceneManager;

	// is need load in async after onLoadResources ?
	bool isLoadingResourcesAsync();

	// load resources sync 
	void loadResourcesSync();

	// load resources async
	void loadResourcesAsync();

	// load resources async call back func
	void loadingResourcesCallBack(CCObject* pTextureObj);

	// set the class name for scene
	void setClassName(const char* pClassName);

	// make sure is already loaded
	void setLoaded(bool bLoaded);

	// is auto remove unuse texture
	bool m_bAutoRemoveUnusedTexture;

	// the temp of image file on sync type
	std::vector<std::string> m_vLoadImageFilesSync;

	// the temp of image file on async type
	std::vector<std::string> m_vLoadImageFilesAsync;

	// class name of scene
	std::string m_strClassName;

	// extra of scene
	CCObject* m_pExtraObject;

	// is this scene already loaded ?
	bool m_bLoaded;
	
	// is this scene on cachable
	bool m_bCachable;

#if! USING_COCOSWIDGET
	// the touch priority, by scene manager
	int m_nTouchPriority;
#endif
	// load count in async
	int m_nLoadResourcesAsyncCount;
	// load index num
	int m_nLoadResourcesAsyncIdx;
};

NS_CC_END

#endif //__CCBASE_SCENEEXTENSION_H__