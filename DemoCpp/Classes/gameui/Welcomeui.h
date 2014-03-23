#ifndef __UI_WELCOME_H__
#define __UI_WELCOME_H__

#include "tui/TuiBase.h"
#include "tui/TuiManager.h"
#include "module/AnimManager.h"

class Welcomeui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Welcomeui);
	~Welcomeui();

	virtual void onLoadScene();
	CCNode* getPanel(int tagPanel);

protected:
	void event_btn_start(CCObject* s);
	void event_btn_option(CCObject* s);
	void event_btn_exit(CCObject* s);
private:
	AnimManager* m_animManager;
};
#endif