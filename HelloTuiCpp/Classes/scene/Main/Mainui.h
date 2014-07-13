#ifndef __MAIN_UI_H__
#define __MAIN_UI_H__

#include "../../tui/TuiBase.h"
#include "MainCfg.h"

NS_MAIN_BEGIN

class Mainui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Mainui);

	void onLoadScene();

	CCNode* getPanel(int tagPanel);
protected:
	void event_btn_showphone(CCObject* pSender);
	void event_ctlv_left(CCObject* pSender, float fx, float fy);
	void event_btn_ok(CCObject* pSender);
	void event_btn_go(CCObject* pSender);
	void event_btn_bag(CCObject* pSender);
	void event_btn_recombine(CCObject* pSender);

	void event_tgvA_check(CCObject *pSender, bool bChecked);
	void event_tgvB_check(CCObject *pSender, bool bChecked);
private:
};


NS_MAIN_END
#endif