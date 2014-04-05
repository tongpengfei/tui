#include "TuiBase.h"

TuiBase::TuiBase()
:m_isAutoRemoveUnusedSpriteFrame(false)
{
}

TuiBase::~TuiBase(){
	if(m_isAutoRemoveUnusedSpriteFrame){
		removeAllChildrenWithCleanup(true);
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	}
}

/************************************************************************/
// GET/SET/IS
/************************************************************************/
CCNode* TuiBase::getControl(int tagPanel,int tagControl){
	CCNode* control = getPanel(tagPanel)->getChildByTag(tagControl);
	return control;
}
CCNode* TuiBase::getPanel(int tagPanel){
	return NULL;
}
