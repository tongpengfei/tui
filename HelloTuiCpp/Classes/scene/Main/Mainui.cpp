﻿#include "Mainui.h"
#include "../../tui/TuiManager.h"
#include "tagMap/tuiTag_main.h"

NS_MAIN_BEGIN

void Mainui::onLoadScene()
{
	setAutoRemoveUnusedTexture(true);
	TuiManager::sharedManager()->parseScene(this,"panel_main",PATH_MAIN);

	//注册事件
	CControlView *ctlv = (CControlView*)this->getControl(PANEL_MAIN,CTLV_LEFT);
	ctlv->setOnControlListener(this,ccw_control_selector(Mainui::event_ctlv_left));

	CButton *pBtnOk = (CButton*)this->getControl(PANEL_MAIN, BTN_OK);
	pBtnOk->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_ok));

	CButton *pBtnGo = (CButton*)this->getControl(PANEL_MAIN, BTN_GO);
	pBtnGo->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_go));

	CButton *pBtnPhone = (CButton*)this->getControl(PANEL_MAIN, BTN_SHOWPHONE);
	pBtnPhone->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_showphone));

	CButton *pBtnBag = (CButton*)this->getControl(PANEL_MAIN, BTN_BAG);
	pBtnBag->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_bag));

	CButton *pBtnRecombine = (CButton*)this->getControl(PANEL_MAIN, BTN_RECOMBINE);
	pBtnRecombine->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_recombine));

	CToggleView *pTgvA = (CToggleView*)this->getControl(PANEL_MAIN, TGV_A);
	pTgvA->setOnCheckListener(this, ccw_check_selector(Mainui::event_tgvA_check));

	CToggleView *pTgvB = (CToggleView*)this->getControl(PANEL_MAIN, TGV_B);
	pTgvB->setOnCheckListener(this, ccw_check_selector(Mainui::event_tgvB_check));

	//播放骨骼动画(默认不播放)
	CCArmature *armature = (CCArmature*)this->getControl(PANEL_MAIN,ARMATURE_BOSS1);
	armature->getAnimation()->play("live",-1,-1,1);
}

void Mainui::event_ctlv_left( CCObject* pSender, float fx, float fy )
{
	CCSprite *pIcon = (CCSprite*)this->getControl(PANEL_MAIN,ANIM_COIN);
	pIcon->setPosition(pIcon->getPosition() + CCPoint(fx,fy));
}

void Mainui::event_btn_ok(CCObject* pSender)
{
	//开启塑形
	//((CWidgetWindow*)this->getPanel(PANEL_MAIN))->setModalable(true);
	CCSceneManager::sharedManager()->runUIScene(LoadScene("Main::MsgBox"));
}
void Mainui::event_btn_showphone(CCObject* pSender)
{
	CCSceneManager::sharedManager()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("ShowPhone::ShowPhoneui")));
}

void Mainui::event_btn_go(CCObject* pSender)
{
	CCSceneManager::sharedManager()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Store::Storeui")));

}

void Mainui::event_btn_bag(CCObject* pSender)
{
	CCSceneManager::sharedManager()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Bag::Bagui")));
}

void Mainui::event_btn_recombine(CCObject* pSender)
{
	CCSceneManager::sharedManager()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Recomebineui")));
}


void Mainui::event_tgvA_check(CCObject *pSender, bool bChecked)
{
	
}

void Mainui::event_tgvB_check(CCObject *pSender, bool bChecked)
{
	
}


/************************************************************************/
//	GET/SET/IS
/************************************************************************/
CCNode* Mainui::getPanel( int tagPanel )
{
	CCNode *pPanel = nullptr;
	switch (tagPanel)
	{
	case PANEL_MAIN:
		pPanel = this->getChildByTag(PANEL_MAIN);
		break;
	}
	return pPanel;
}


NS_MAIN_END 