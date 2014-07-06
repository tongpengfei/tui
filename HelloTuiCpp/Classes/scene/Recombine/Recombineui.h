#ifndef __RECOMBINE_UI_H__
#define __RECOMBINE_UI_H__

#include "../../tui/TuiBase.h"

class Recomebineui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Recomebineui);

	virtual void onLoadScene();

	CCNode *getPanel(int tagPanel);
protected:
	CCObject* adapt_gpv_bag(CCObject* pConvertCell, unsigned int uIdx);

	void event_btn_click(CCObject* pSender);
	void event_btn_back(CCObject* pSender);
private:
	

};


#endif 
