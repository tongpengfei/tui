#include "ShowPhoneui.h"
#include "tagMap/tuiTag_showPhone.h"
#include "../../tui/TuiManager.h"

NS_SHOWPHONE_BEGIN

void ShowPhoneui::onLoadScene()
{
	TuiManager::sharedManager()->parseScene(this, "panel_showphone", PATH_SHOWPHONE);

	CircleMenu *menu = (CircleMenu*)this->getControl(PANEL_SHOWPHONE, CIRCLEMENU_SHOWPHONE);
	menu->setOnClickListener(this, ccw_click_selector(ShowPhoneui::event_menu_phone));
}

void ShowPhoneui::event_menu_phone(CCObject* pSender)
{
	CCNode* node = (CCNode*)pSender;
	CCLOG("tag %d", node->getTag());

	CCSceneManager::sharedManager()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Main::Mainui")));
}

CCNode * ShowPhoneui::getPanel(int tagPanel)
{
	CCNode *pPanel = nullptr;
	switch (tagPanel)
	{
	case PANEL_SHOWPHONE:
		pPanel = this->getChildByTag(PANEL_SHOWPHONE);
		break;
	}
	return pPanel;
}


NS_SHOWPHONE_END