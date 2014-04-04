#ifndef __UI_LEVEL_H__
#define __UI_LEVEL_H__

#include "tui/TuiBase.h"
#include "tui/TuiManager.h"
#include "module/DataProxy.h"

class Levelui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Levelui);
	virtual void onLoadResources();
	virtual void onLoadScene();

	CCNode* getPanel(int tagPanel);
protected:
	void event_btn_back(CCObject* s);
	void event_page_level(CCObject* pPage, unsigned int nPageIndx);
	void event_btn_ok(CCObject* s);
	CCObject* adapter_page_level(CCObject* pConvertCell, unsigned int nPageIdx);
private:
	CPageView* m_pPageView;
	int nCurLevel;
};

#endif