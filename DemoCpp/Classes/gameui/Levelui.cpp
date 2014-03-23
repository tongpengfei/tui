#include "gameui/Levelui.h"

void Levelui::onLoadResources(){
	addImageAsync("res_iphone/level/img_bglevel3.png");
	addImageAsync("res_iphone/level/img_bglevel1.png");
	addImageAsync("res_iphone/level/img_bglevel2.png");
}

void Levelui::onLoadScene(){

	setAutoRemoveUnusedTexture(true);
	TuiManager::sharedManager()->parseScene(this,"panel_level");
	//注册事件
	CButton* pBtnBack = (CButton*)this->getControl(PANEL_LEVEL,BTN_LEVEL_BACK);
	pBtnBack->setOnClickListener(this,ccw_click_selector(Levelui::event_btn_back));
	
	//渲染page
	m_pPageView = (CPageView*)this->getControl(PANEL_LEVEL,PAGE_LEVEL);
	m_pPageView->setCountOfCell(4);
	m_pPageView->setDataSourceAdapter(this,ccw_datasource_adapter_selector(Levelui::adapter_page_level));
	m_pPageView->setOnPageChangedListener(this,ccw_pagechanged_selector(Levelui::event_page_level));
	m_pPageView->reloadData();
}

void Levelui::event_btn_back(CCObject* s){
	CCSceneManager::sharedManager()->replaceScene(CCSceneExTransitionFade::create(0.5f,LoadScene("Welcomeui")));
}

void Levelui::event_page_level(CCObject* s, unsigned int nPageIdx){

}

void Levelui::event_btn_ok(CCObject* s){
	CButton* btn = (CButton*)s;
	GameController::sharedController()->setLevel(btn->getParent()->getTag());//取当前cell的tag作为level
	CCSceneManager::sharedManager()->replaceScene(CCSceneExTransitionFade::create(0.5f,LoadScene("Storeui")));
}

CCObject* Levelui::adapter_page_level(CCObject* pConvertCell, unsigned int nPageIdx){
	CPageViewCell *pCell = (CPageViewCell *)pConvertCell;
	CButton *pBtnOk = NULL;
	char bufBg[48] = {0};
	sprintf(bufBg,"res_iphone/level/img_bglevel%d.png",nPageIdx+1);
	if(!pCell){
		pCell = new CPageViewCell();
		pCell->autorelease();
		pCell->setBackgroundImage(bufBg);
		pBtnOk = TuiManager::sharedManager()->createBtn(1,
			"res_iphone/level/btn_ok_normal.png",
			"res_iphone/level/btn_ok_select.png",
			"res_iphone/level/btn_ok_disable.png",500,-68,196,68);
		pCell->addChild(pBtnOk);
		pBtnOk->setOnClickListener(this,ccw_click_selector(Levelui::event_btn_ok));
	}else{
		pCell->setBackgroundImage(bufBg);
	}
	pCell->setTag(nPageIdx+1);//记录当前关卡
	return pCell;
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/

CCNode* Levelui::getPanel(int tagPanel){
	CCNode* panel = NULL;
	switch(tagPanel){
	case PANEL_LEVEL:
		panel = this->getChildByTag(PANEL_LEVEL);
		break;
	}
	return panel;
}