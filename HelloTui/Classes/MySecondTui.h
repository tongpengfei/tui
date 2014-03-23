#ifndef __MYSECONDTUI_H__
#define __MYSECONDTUI_H__

#include "tui/TuiBase.h"

class MySecondTui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(MySecondTui);
	void onLoadScene();

	CCNode *getPanel(int tagPanel);
protected:
	void event_on_move(CCObject* pSender, float fx, float fy);
private:
	CCNode *m_animCoin;
};
#endif