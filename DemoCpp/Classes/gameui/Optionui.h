#ifndef __UI_OPTION_H__
#define __UI_OPTION_H__

#include "tui/TuiBase.h"
#include "tui/TuiManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class Optionui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Optionui);
	virtual void onLoadScene();

	CCNode* getPanel(int tagPanel);
protected:
	void event_btn_menu(CCObject* s);
	void event_slider_bgmusic(CCObject* pSender, int nValue);
	void event_slider_music(CCObject* pSender, int nValue);
	void event_ckb_bgmusic(CCObject* s);
	void event_ckb_music(CCObject* s);
private:
};
#endif