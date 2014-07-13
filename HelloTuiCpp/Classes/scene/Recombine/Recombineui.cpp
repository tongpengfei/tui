#include "Recombineui.h"
#include "tagMap/tuiTag_recombineui.h"
#include "../../tui/TuiManager.h"

void Recomebineui::onLoadScene()
{
	TuiManager::sharedManager()->parseScene(this, "panel_recombine", PATH_RECOMBINEUI);

	CGridPageView *pGpvBag = (CGridPageView*)this->getControl(PANEL_RECOMBINE, GPV_BAG);
	pGpvBag->setDataSourceAdapter(this,ccw_datasource_adapter_selector(Recomebineui::adapt_gpv_bag));
	pGpvBag->reloadData();

	CButton *pBtnBack = (CButton*)this->getControl(PANEL_RECOMBINE, BTN_BACK);
	pBtnBack->setOnClickListener(this, ccw_click_selector(Recomebineui::event_btn_back));
}

CCObject* Recomebineui::adapt_gpv_bag(CCObject* pConvertCell, unsigned int uIdx)
{
	CGridPageViewCell* pCell = (CGridPageViewCell*)pConvertCell;
	CButton *btn = nullptr;
	if (!pCell)
	{
		pCell = new CGridPageViewCell();
		pCell->autorelease();

		TuiManager::sharedManager()->parseCell(pCell, "cell_grid", PATH_RECOMBINEUI);
		btn = (CButton*)pCell->getChildByTag(BTN_GRID);
		btn->setOnClickListener(this, ccw_click_selector(Recomebineui::event_btn_click));
	}
	else{
		btn = (CButton*)pCell->getChildByTag(BTN_GRID);
	}
	btn->setUserTag(uIdx);
	return pCell;
}

void Recomebineui::event_btn_click(CCObject* pSender)
{
	CButton *btn = (CButton*)pSender;
	int id = btn->getUserTag();

	CCLOG("id = %d", id);
}

void Recomebineui::event_btn_back(CCObject* pSender)
{
	CCSceneManager::sharedManager()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Main::Mainui")));
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/

CCNode * Recomebineui::getPanel(int tagPanel)
{
	CCNode *pPanel = nullptr;
	switch (tagPanel)
	{
	case PANEL_RECOMBINE:
		pPanel = this->getChildByTag(PANEL_RECOMBINE);
		break;
	}
	return pPanel;
}
