#ifndef __WELCOME_UI__
#define __WELCOME_UI__

#include "../../tui/TuiBase.h"
#include "WelcomeCfg.h"

NS_WELCOME_BEGIN

class Welcomeui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Welcomeui);

	void onLoadScene();

	CCNode *getPanel(int tagPanel);
protected:
	void event_go_main();
private:
};


NS_WELCOME_END
#endif