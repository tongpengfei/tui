#include "TuiBase.h"

TuiBase::TuiBase()
{
}

CCNode* TuiBase::getControl(int tagPanel,int tagControl){
	CCNode* control = getPanel(tagPanel)->getChildByTag(tagControl);
	return control;
}
CCNode* TuiBase::getPanel(int tagPanel){
	return NULL;
}