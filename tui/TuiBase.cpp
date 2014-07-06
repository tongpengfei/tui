#include "TuiBase.h"

TuiBase::TuiBase()
:m_isAutoRemoveUnusedSpriteFrame(false)
{
}

TuiBase* TuiBase::create()
{
	TuiBase *pRet = new TuiBase();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool TuiBase::init()
{
	return true;
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

