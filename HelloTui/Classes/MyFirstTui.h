#ifndef __MYFIRSTTUI_H__
#define __MYFIRSTTUI_H__

#include "tui/TuiBase.h"

class MyFirstTui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(MyFirstTui);
	void onLoadScene();

	CCNode* getPanel(int tagPanel);
protected:
	void event_btn_ok(CCObject* pSender);

private:
};
#endif