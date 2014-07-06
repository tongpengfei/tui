#ifndef __BAG_UI__
#define __BAG_UI__

#include "../../tui/TuiBase.h"
#include "BagCfg.h"

NS_BAG_BEGIN

class Bagui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Bagui);

	void onLoadScene();
	CCNode* getPanel(int tagPanel);
protected:
	CCObject* event_adapt_gvBag(CCObject* pConvertCell, unsigned int uIdx);
	CCObject* event_adapt_tblBag(CCObject* pConvertCell, unsigned int uIdx);
	CCObject* event_adapt_pageBag(CCObject* pConvertCell, unsigned int uIdx);
	void event_btn_back(CCObject* pSender);

	void event_btn_gv(CCObject* pSender);
private:

};

NS_BAG_END

#endif