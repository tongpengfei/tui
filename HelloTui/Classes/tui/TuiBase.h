#ifndef __BASE_H__
#define __BASE_H__

#include "tuiTagMap.h"
#include "cocos2d.h"
#include "cocos-ext.h"

#include "../../../CocosWidget/cocos-widget.h"
#include "../../../CocosBase/cocos-base.h"

using namespace cocos2d::extension;
using namespace cocos2d::cocoswidget;
USING_NS_CC;

class TuiBase : public CCSceneExtension {
public:
	TuiBase();
	virtual ~TuiBase();
	virtual CCNode *getControl(int tagPanel,int tagControl);
	virtual CCNode *getPanel(int tagPanel);

protected:
	CC_SYNTHESIZE(bool, m_isAutoRemoveUnusedSpriteFrame, AutoRemoveUnusedSpriteFrame);
private:
};

#endif

