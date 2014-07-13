﻿#include "MessageBox.h"
#include "../../tui/TuiManager.h"
#include "tagMap/tuiTag_main.h"

NS_MAIN_BEGIN

void MessageBox::onLoadScene()
{
	setAutoRemoveUnusedTexture(true);
	TuiManager::sharedManager()->parseScene(this, "panel_msgbox", PATH_MAIN);
	//注册事件
	CButton *pBtnClose = (CButton*)getControl(PANEL_MSGBOX,BTN_CLOSE);
	pBtnClose->setOnClickListener(this,ccw_click_selector(MessageBox::event_btn_close));
	
	CSlider *pSlider = (CSlider*)getControl(PANEL_MSGBOX,SLIDER_TEST);
	pSlider->setOnValueChangedListener(this,ccw_valuechanged_selector(MessageBox::event_slider_test));

	CProgressBar *pProg = (CProgressBar*)this->getControl(PANEL_MSGBOX,PROG_HP);
	pProg->setShowValueLabel(true);
}

void MessageBox::event_btn_close( CCObject *pSender )
{
	CCSceneManager::sharedManager()->popUIScene(this);
	//解除塑形
	CCSceneManager::sharedManager()->getRunningScene()->setModalable(false);
}

void MessageBox::event_slider_test(CCObject *pSender, int value)
{
	char buf[128] = {0};
	sprintf(buf,"%d",value);
	CLabelAtlas *pLab = (CLabelAtlas*)this->getControl(PANEL_MSGBOX,LABATLAS_NUM);
	pLab->setString(buf);

	CProgressBar *pProg = (CProgressBar*)this->getControl(PANEL_MSGBOX,PROG_HP);
	pProg->setValue(value);

}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
CCNode *MessageBox::getPanel( int tagPanel )
{
	CCNode *pPanel = nullptr;
	switch (tagPanel)
	{
	case PANEL_MSGBOX:
		pPanel = this->getChildByTag(PANEL_MSGBOX);
		break;
	}
	return pPanel;
}


NS_MAIN_END