#include "Storeui.h"
#include "../../tui/TuiManager.h"
#include "tagMap/tuiTag_store.h"

NS_STORE_BEGIN

void Storeui::onLoadScene()
{
	setAutoRemoveUnusedTexture(true);
	TuiManager::sharedManager()->parseScene(this,"panel_store",PATH_STORE);

	CListView *pListGoods = (CListView*)this->getControl(PANEL_STORE, LIST_GOODS);
	CCArray* arr = pListGoods->getContainer()->getChildren();
	CCObject *pObj = NULL;
	CCARRAY_FOREACH(arr, pObj){
		CCNode *pNode = (CCNode*)pObj;
		CButton *pBtnPay = dynamic_cast<CButton*>(pNode->getChildByTag(BTN_PAY));
		pBtnPay->setOnClickListener(this, ccw_click_selector(Storeui::event_btn_pay));
	}

	ArmatureBtn *pBtn = (ArmatureBtn*)this->getControl(PANEL_STORE,ARMBTN_TEST2);
	pBtn->setOnClickListener(this,ccw_click_selector(Storeui::event_btn_test));

}

void Storeui::event_btn_test( CCObject* pSender )
{
	CCSceneManager::sharedManager()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Main::Mainui")));
}

void Storeui::event_btn_pay(CCObject* pSender)
{
	CCNode *pBtn = (CCNode*)pSender;
	CCLOG("pay index :%d", pBtn->getParent()->getTag());
}



/************************************************************************/
//	GET/SET/IS
/************************************************************************/
CCNode * Storeui::getPanel( int tagPanel )
{
	CCNode *pPanel = nullptr;
	switch (tagPanel)
	{
	case PANEL_STORE:
		pPanel = this->getChildByTag(PANEL_STORE);
		break;
	}
	return pPanel;
}



NS_STORE_END
