#include "MyThirdui.h"

void MyThirdui::onLoadScene(){

	TuiManager::sharedManager()->parseScene(this,"panel_third");
	

}


CCNode * MyThirdui::getPanel( int tagPanel )
{
	CCNode *panel = NULL;
	switch (tagPanel)
	{
	case PANEL_THIRD:
		panel = this->getChildByTag(PANEL_THIRD);
		break;
	}
	return panel;
}

