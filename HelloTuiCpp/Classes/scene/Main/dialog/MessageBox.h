﻿#ifndef __MESSAGEBOX_H__
#define __MESSAGEBOX_H__

#include "../../tui/TuiBase.h"
#include "../MainCfg.h"

NS_MAIN_BEGIN

class MessageBox : public TuiBase
{
public:
	CREATE_SCENE_FUNC(MessageBox);

	void onLoadScene();

	CCNode *getPanel(int tagPanel);
protected:
	void event_btn_close(CCObject *pSender);
	void event_slider_test(CCObject *pSender, int value);
private:
};


NS_MAIN_END
#endif 