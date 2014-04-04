#include "CommonAnimTask.h"

bool CommonAnimTask::init(){
	return true;
}

void CommonAnimTask::addChildInTool(CCArray* arrWeapon,CCArray* arrMedicine,CCArray* arrProp,CCNode* panel,
								CCPoint baseP1,CCPoint baseP2,CCPoint baseP3)
{
	CCObject* obj1 = NULL;
	CCARRAY_FOREACH(arrWeapon,obj1){
		GoodsBase* itemWeapon = (GoodsBase*)obj1;
		itemWeapon->removeFromParent();
		itemWeapon->curScene = SCENE_INGAME;
		panel->addChild(itemWeapon);
	}
	resetPlaceTool(arrWeapon,baseP1);
	CCObject* obj2 = NULL;
	CCARRAY_FOREACH(arrMedicine,obj2){
		GoodsBase* itemMedicine = (GoodsBase*)obj2;
		itemMedicine->removeFromParent();
		itemMedicine->curScene = SCENE_INGAME;
		panel->addChild(itemMedicine);
	}
	resetPlaceTool(arrMedicine,baseP2);
	CCObject* obj3 = NULL;
	CCARRAY_FOREACH(arrProp,obj3){
		GoodsBase* itemProp = (GoodsBase*)obj3;
		itemProp->removeFromParent();
		itemProp->curScene = SCENE_INGAME;
		panel->addChild(itemProp);
	}
	resetPlaceTool(arrProp,baseP3);
}

void CommonAnimTask::resetPlaceTool(CCArray* arr,CCPoint p){
	int offset = 3;
	CCObject *obj = NULL;
	int cout = 0;
	CCARRAY_FOREACH(arr,obj){
		CLayout* item = (CLayout*)obj;
		item->setPosition(p+ccp(((item->getContentSize().width+offset)*cout),0));
		cout++;
	}
}

void CommonAnimTask::showLoading(TuiBase* tuiBase,int tagPanel){
	CCSprite* pSprite = TuiManager::sharedManager()->createAnim(130,"anim_loading",
		"res_iphone/common/anim_loading.png","res_iphone/common/anim_loading.plist",0,0);
	pSprite->setZOrder(INT_MAX);
	tuiBase->getPanel(tagPanel)->addChild(pSprite);
}