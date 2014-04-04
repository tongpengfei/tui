#include "StoreAnimTask.h"

bool StoreAnim::init(){
	return true;
}


void StoreAnim::renderList(TuiBase* pScene,SEL_ClickHandler clickHandler,const char* type,int length){

	CListView* listView = (CListView*)pScene->getControl(PANEL_STORE_GOODS,LIST_GOODS);
	listView->removeAllNodes();
	CImageView* imgBg = NULL;
	CButton* btnPay = NULL;
	CLayout* pLayout = NULL;
	CCString *str = NULL;

	for(int i=1;i<=length; i++){
		pLayout = CLayout::create();
		str = CCString::createWithFormat("res_iphone/store/img_listgoods%s%d.png",type,i);
		imgBg = TuiManager::sharedManager()->createImage(101,str->getCString(),0,0);
		CCSize size = imgBg->getContentSize();
		imgBg->setPosition(ccp(size.width/2,size.height/2));
		pLayout->setContentSize(size);
		btnPay = TuiManager::sharedManager()->createBtn(102,"res_iphone/store/btn_pay_normal.png",
			"res_iphone/store/btn_pay_select.png",
			"res_iphone/store/btn_pay_disable.png",0,0,70,36);

		btnPay->setTag(i);
		btnPay->setPosition(ccp(size.width/2+120,size.height/2));
		btnPay->setOnClickListener(pScene, clickHandler);
		pLayout->addChild(imgBg);
		pLayout->addChild(btnPay);

		listView->insertNodeAtLast(pLayout);
	}
	listView->reloadData();
}