#include "Storeui.h"

Storeui::Storeui(){
	m_arrWeapon = GameController::sharedController()->getArrWeapon();
	m_arrWeapon->retain();
	m_arrMedicine = GameController::sharedController()->getArrMedicine();
	m_arrMedicine->retain();
	m_arrProp = GameController::sharedController()->getArrProp();
	m_arrProp->retain();

	m_animManager = AnimManager::create();
	m_animManager->retain();
}

void Storeui::onLoadResources(){
	addImageAsync("res_iphone/store/img_bgstore.png");
}

void Storeui::onLoadScene(){

	setAutoRemoveUnusedTexture(true);
	TuiManager::sharedManager()->parseScene(this,"panel_store");

	CButton *pBtnMenu = (CButton *)this->getControl(PANEL_STORE,BTN_MENU);
	pBtnMenu->setOnClickListener(this, ccw_click_selector(Storeui::event_btn_menu));
	CButton *pBtnLaunch =  (CButton *)this->getControl(PANEL_STORE,BTN_LAUNCH);
	pBtnLaunch->setOnClickListener(this, ccw_click_selector(Storeui::event_btn_launch));
	
	CToggleView* pToggleWeapon = (CToggleView*)this->getControl(PANEL_STORE,TGV_WEAPON);
	pToggleWeapon->setOnCheckListener(this,ccw_check_selector(Storeui::event_toggle));
	CToggleView* pToggleMedicine = (CToggleView*)this->getControl(PANEL_STORE,TGV_MEDICINE);
	pToggleMedicine->setOnCheckListener(this,ccw_check_selector(Storeui::event_toggle));
	CToggleView* pToggleProp = (CToggleView*)this->getControl(PANEL_STORE,TGV_PROP);
	pToggleProp->setOnCheckListener(this,ccw_check_selector(Storeui::event_toggle));
	pToggleWeapon->setChecked(true); 

	setCoin(GameController::sharedController()->getCoin());
	m_animManager->addChildInTool(m_arrWeapon,m_arrMedicine,m_arrProp,
		getPanel(PANEL_STORE_TOOL),
		getControl(PANEL_STORE_TOOL,IMG_STORE_P_TOOL1)->getPosition(),
		getControl(PANEL_STORE_TOOL,IMG_STORE_P_TOOL5)->getPosition(),
		getControl(PANEL_STORE_TOOL,IMG_STORE_P_TOOL9)->getPosition());
}

void Storeui::event_btn_menu(CCObject* s){
	CCSceneManager::sharedManager()->replaceScene(CCSceneExTransitionFade::create(0.5f,LoadScene("Welcomeui")));
}

void Storeui::event_btn_launch(CCObject* s){
	m_animManager->showLoading(this,PANEL_STORE);
	CCSceneManager::sharedManager()->replaceScene(CCSceneExTransitionFade::create(0.5f,LoadScene("Ingameui")));
}

void Storeui::event_btn_pay(CCObject* s){
	CCNode *panel = getPanel(PANEL_STORE_TOOL);
	int id = ((CButton*)s)->getTag();
	switch(m_type){
	case TYPE_WEAPON:
		{
			Weapon* pWeapon = Weapon::create();
			BUG_GOODS(pWeapon,m_arrWeapon,IMG_STORE_P_TOOL1);
		}
		break;
	case TYPE_MEDICINE:
		{
			Medicine *pMedicine = Medicine::create();
			BUG_GOODS(pMedicine,m_arrMedicine,IMG_STORE_P_TOOL5);
		}
		break;
	case TYPE_PROP:
		{
			Prop *pProp = Prop::create();
			BUG_GOODS(pProp,m_arrProp,IMG_STORE_P_TOOL9);
		}
		break;
	}
}

void Storeui::event_toggle(CCObject* pSender, bool bChecked){
	CToggleView* pToggle = (CToggleView*) pSender;
	if(bChecked){
		switch (pToggle->getTag())
		{
		case TGV_WEAPON:
			{
				m_type = TYPE_WEAPON;
				m_animManager->renderList(this,ccw_click_selector(Storeui::event_btn_pay),"weapon",12);
			}
			break;
		case TGV_MEDICINE:
			{
				m_type = TYPE_MEDICINE;
				m_animManager->renderList(this,ccw_click_selector(Storeui::event_btn_pay),"medicine",3);
			}
			break;
		case TGV_PROP:
			{
				m_type = TYPE_PROP;
				m_animManager->renderList(this,ccw_click_selector(Storeui::event_btn_pay),"prop",2);
			}
			break;
		}
	}
}

Storeui::~Storeui(){
	
	m_animManager->release();
	
	m_arrWeapon->release();
	m_arrMedicine->release();
	m_arrProp->release();
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void Storeui::setCoin(int v){
	m_coin = v;
	GameController::sharedController()->setCoin(v);
	CLabel *pLab =(CLabel*)this->getControl(PANEL_STORE_GOODS,TEXT_COIN);
	pLab->setString(CCString::createWithFormat("%d",v)->getCString());
}

int Storeui::getCoin(){
	return this->m_coin;
}

CCNode* Storeui::getPanel(int tagPanel){
	CCNode *panel = NULL;
	switch(tagPanel){
	case PANEL_STORE:
		panel = this->getChildByTag(PANEL_STORE);
		break;
	case PANEL_STORE_GOODS:
		panel = this->getChildByTag(PANEL_STORE)->getChildByTag(PANEL_STORE_GOODS);
		break;
	case PANEL_STORE_TOOL:
		panel = this->getChildByTag(PANEL_STORE)->getChildByTag(PANEL_STORE_TOOL);
		break;
	}
	return panel;
}