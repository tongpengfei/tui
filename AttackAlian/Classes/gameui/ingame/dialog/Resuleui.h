#ifndef __RESULEUI_H__
#define __RESULEUI_H__

#include "tui/TuiBase.h"
#include "tui/TuiManager.h"
#include "module/DataProxy.h"
#include "domain/config.h"

class Resuleui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Resuleui);
	virtual void onLoadScene();
	virtual void onLoadResources();

	~Resuleui();

	CCNode* getPanel(int tagPanel);
protected:
	void event_btn_equip(CCObject* s);
	void event_btn_again(CCObject* s);
	void event_btn_next(CCObject* s);

	//ResulePackage* reponsePkg;//»ØÓ¦°ü
private:
};

#endif