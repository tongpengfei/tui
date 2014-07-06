#ifndef __TUI_BASE_H__
#define __TUI_BASE_H__

#include "cocos2d.h"

#include "../CocosWidget/cocos-widget.h"
#include "../extensions/cocos-ext.h"

#if USING_LUA == 0
#include "../CocosBase/cocos-base.h"
#endif

using namespace cocos2d::cocoswidget;
USING_NS_CC;

class TuiBase
#if USING_LUA
	: public CCScene 
#else
	: public CCSceneExtension
#endif
{
public:
	static TuiBase* create();
	virtual bool init();
	TuiBase();
	virtual ~TuiBase();
	virtual CCNode *getControl(int tagPanel,int tagControl);
	virtual CCNode *getPanel(int tagPanel);

	CC_SYNTHESIZE(bool, m_isAutoRemoveUnusedSpriteFrame, AutoRemoveUnusedSpriteFrame);
protected:

private:
};

#endif

