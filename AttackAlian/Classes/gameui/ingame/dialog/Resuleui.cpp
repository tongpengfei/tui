#include "gameui/ingame/dialog/Resuleui.h"

void Resuleui::onLoadResources(){
	addImageAsync("res_iphone/ingame/dialog/img_bgdialogresule.png");
}

void Resuleui::onLoadScene(){

	setAutoRemoveUnusedTexture(true);
	TuiManager::sharedManager()->parseScene(this,"panel_resule");
	//注册按钮事件
	CButton* pBtnEquip = (CButton*)this->getControl(PANEL_RESULE,BTN_EQUIP);
	pBtnEquip->setOnClickListener(this,ccw_click_selector(Resuleui::event_btn_equip));
	CButton* pBtnAgain = (CButton*)this->getControl(PANEL_RESULE,BTN_AGAIN);
	pBtnAgain->setOnClickListener(this,ccw_click_selector(Resuleui::event_btn_again));
	CButton* pBtnNext = (CButton*)this->getControl(PANEL_RESULE,BTN_NEXT);
	pBtnNext->setOnClickListener(this,ccw_click_selector(Resuleui::event_btn_next));

	bool isWin = DataProxy::sharedManager()->getWin();
	getControl(PANEL_RESULE,IMG_SUCCESS)->setVisible(isWin);
	getControl(PANEL_RESULE,IMG_LOST)->setVisible(!isWin);
}

void Resuleui::event_btn_again(CCObject* s){
	CCSceneManager::sharedManager()->popAllUIScene();
	CCMsgManager::sharedManager()->PostMessage(MSG_RESPON_RESULE);
}

void Resuleui::event_btn_equip(CCObject* s){
	CCSceneManager::sharedManager()->popAllUIScene();
	CCSceneManager::sharedManager()->replaceScene(CCSceneExTransitionFade::create(0.5f,LoadScene("Storeui")));
}

void Resuleui::event_btn_next(CCObject* s){
	DataProxy* pGC = DataProxy::sharedManager();
	pGC->setLevel(pGC->getLevel()+1);
	if(pGC->getLevel() == 5) pGC->setLevel(1);//目前只有4关
	CCSceneManager::sharedManager()->popAllUIScene();
	CCMsgManager::sharedManager()->PostMessage(MSG_RESPON_RESULE);
}

Resuleui::~Resuleui(){
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
CCNode* Resuleui::getPanel(int tagPanel){
	CCNode* panel = NULL;
	switch(tagPanel){
	case PANEL_RESULE:
		panel = this->getChildByTag(PANEL_RESULE);
		break;
	}
	return panel;
}
