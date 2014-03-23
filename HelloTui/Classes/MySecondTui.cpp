#include "MySecondTui.h"
#include "tui/TuiManager.h"


void MySecondTui::onLoadScene(){

	TuiManager::sharedManager()->parseScene(this,"panel_welcome2");

	//×¢²áÊÖ±úÊÂ¼þ
	CControlView* pControlView = (CControlView*) this->getControl(PANEL_WELCOME2,CTLV_LEFT);
	pControlView->setOnControlListener(this, ccw_control_selector(MySecondTui::event_on_move));

	m_animCoin = getControl(PANEL_WELCOME2,ANIM_COIN);
}

void MySecondTui::event_on_move(CCObject* pSender, float fx, float fy){
	m_animCoin->setPosition(m_animCoin->getPosition() + ccp(fx,fy));
}

CCNode* MySecondTui::getPanel(int tagPanel){
	CCNode* pPanel = NULL;
	switch (tagPanel)
	{
	case PANEL_WELCOME2:
		pPanel = this->getChildByTag(PANEL_WELCOME2);
	default:
		break;
	}
	return pPanel;
}