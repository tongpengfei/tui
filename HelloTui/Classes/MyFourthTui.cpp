#include "MyFourthTui.h"
#include "tui/TuiManager.h"

using namespace Expand;

void MyFourthTui::onLoadScene()
{
	TuiManager::sharedManager()->parseScene(this,"panel_fourth");
	//×¢²áÊÂ¼þ
	ArmatureBtn *pBtnTest = (ArmatureBtn*)getControl(PANEL_FOURTH,ARMBTN_TEST2);
	pBtnTest->setOnClickListener(this,ccw_click_selector(MyFourthTui::event_armBtn_test));

	NumericStepper *pNumStep = (NumericStepper*)getControl(PANEL_FOURTH,NUMSTEP_TEST);
	pNumStep->setOnValueChangedListener(this,ccw_valuechanged_selector(MyFourthTui::event_numStep_test));
}

void MyFourthTui::event_armBtn_test( CCObject *pSender )
{
	CCLOG("%s","clicked");
}

void MyFourthTui::event_numStep_test( CCObject *pSender,int value )
{
	CCLOG("%d",value);
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
CCNode * MyFourthTui::getPanel( int tagPanel )
{
	CCNode *pPanel = NULL;
	switch (tagPanel)
	{
	case PANEL_FOURTH:
		pPanel = this->getChildByTag(PANEL_FOURTH);
		break;
	}
	return pPanel;
}


