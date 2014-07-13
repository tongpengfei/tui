#include "Welcomeui.h"
#include "../../tui/TuiManager.h"
#include "tagMap/tuiTag_welcome.h"

NS_WELCOME_BEGIN

void Welcomeui::onLoadScene()
{
	setAutoRemoveUnusedTexture(true);
	TuiManager::sharedManager()->parseScene(this,"panel_welcome",PATH_WELCOME);

	this->runAction(
		CCSequence::create(
		CCDelayTime::create(1.5f), 
		CCCallFunc::create(this,callfunc_selector(Welcomeui::event_go_main)),
		NULL));
}


void Welcomeui::event_go_main(){
	CCSceneManager::sharedManager()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Main::Mainui")));
}
/************************************************************************/
//	GET/SET/IS
/************************************************************************/
CCNode * Welcomeui::getPanel(int tagPanel)
{
	CCNode *pPanel = nullptr;
	switch (tagPanel)
	{
	case PANEL_WELCOME:
		pPanel = this->getChildByTag(PANEL_WELCOME);
		break;
	}
	return pPanel;
}

NS_WELCOME_END