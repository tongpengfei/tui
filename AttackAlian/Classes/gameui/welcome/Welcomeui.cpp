#include "Welcomeui.h"

void Welcomeui::onLoadScene(){
	
	setAutoRemoveUnusedTexture(true);
	TuiManager::sharedManager()->parseScene(this,"panel_welcome");

	//×¢²á°´Å¥ÊÂ¼þ
	CButton* pBtnStart = (CButton*) this->getControl(PANEL_WELCOME,BTN_START);
	pBtnStart->setOnClickListener(this, ccw_click_selector(Welcomeui::event_btn_start));
	CButton* pBtnOption = (CButton*) this->getControl(PANEL_WELCOME,BTN_OPTION);
	pBtnOption->setOnClickListener(this,ccw_click_selector(Welcomeui::event_btn_option));
	CButton* pBtnExit = (CButton*) this->getControl(PANEL_WELCOME,BTN_EXIT);
	pBtnExit->setOnClickListener(this,ccw_click_selector(Welcomeui::event_btn_exit));

	NetWorkMgr::sharedManager()->send();
}

void Welcomeui::event_btn_start(CCObject* s){
	CCSceneManager::sharedManager()->replaceScene(CCSceneExTransitionFade::create(0.5f,LoadScene("Levelui")));
}

void Welcomeui::event_btn_option(CCObject* s){
	CCSceneManager::sharedManager()->replaceScene(CCSceneExTransitionFade::create(0.5f,LoadScene("Optionui")));
}

void Welcomeui::event_btn_exit(CCObject* s){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

Welcomeui::~Welcomeui(){
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
CCNode* Welcomeui::getPanel(int tag){
	CCNode* panel = NULL;
	switch(tag){
	case PANEL_WELCOME:
		panel = this->getChildByTag(PANEL_WELCOME);
		break;
	case PANEL_INGAME_UI:
		panel = this->getChildByTag(PANEL_WELCOME)->getChildByTag(PANEL_INGAME_UI);
		break;
	}
	return panel;
}