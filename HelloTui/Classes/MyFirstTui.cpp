#include "MyFirstTui.h"
#include "tui/TuiManager.h"

void MyFirstTui::onLoadScene(){

	TuiManager::sharedManager()->parseScene(this,"panel_welcome");
	//×¢²áÊÂ¼þ
	CButton* pBtnOk = (CButton*)getControl(PANEL_WELCOME,BTN_OK);
	pBtnOk->setOnClickListener(this,ccw_click_selector(MyFirstTui::event_btn_ok));


}

void MyFirstTui::event_btn_ok(CCObject* pSender){
	CCSceneManager::sharedManager()->replaceScene(LoadScene("MySecondTui"));
}

CCNode* MyFirstTui::getPanel(int tagPanel){
	CCNode* pPanel = NULL;
	switch (tagPanel)
	{
	case PANEL_WELCOME:
		pPanel = this->getChildByTag(PANEL_WELCOME);
		break;
	default:
		break;
	}
	return pPanel;
}