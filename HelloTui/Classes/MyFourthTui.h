#ifndef __MYFOURTH_UI_H__
#define __MYFOURTH_UI_H__

#include "tui/TuiBase.h"

class MyFourthTui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(MyFourthTui);

	void onLoadScene();

	CCNode *getPanel(int tagPanel);
protected:
	void event_armBtn_test(CCObject *pSender);
	void event_numStep_test(CCObject *pSender,int value);
private:
};

#endif