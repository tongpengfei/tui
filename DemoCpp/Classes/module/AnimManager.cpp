#include "module/AnimManager.h"
#include "tui/TuiManager.h"
#include "gameui/Storeui.h"
#include "domain/character/Boss.h"
#include "domain/goods/GoodsBase.h"

bool AnimManager::init(){
	m_bToggleTool = false;
	return true;
}
///////////////////////Ingame////////////////////////////////////////////
void AnimManager::addChildInTool(CCArray* arrWeapon,CCArray* arrMedicine,CCArray* arrProp,CCNode* panel,
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

void AnimManager::moveOffsetToBg(CCNode *bg,float offsetX,float offsetY){

	CCSize mapSize = bg->getContentSize();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_offsetPos = ccp(offsetX,offsetY);//用来给怪物的移动AI用的
	//-----------------------限制地图可行范围-------------------------------
	bg->setPosition(bg->getPosition()+ CCPoint(offsetX*(-1),offsetY*(-1)));

	if(bg->getPositionX() > mapSize.width/2 - visibleSize.width/2){//左边界
		bg->setPositionX(mapSize.width/2 - visibleSize.width/2);
		m_offsetPos.x = 0;
	}else if(bg->getPositionX() < -mapSize.width/2 + visibleSize.width/2){//右边界
		bg->setPositionX(-mapSize.width/2 + visibleSize.width/2);
		m_offsetPos.x = 0;
	}

	if(bg->getPositionY() < -mapSize.height/2 + visibleSize.height/2){//上边界
		bg->setPositionY(-mapSize.height/2 + visibleSize.height/2);
		m_offsetPos.y = 0;
	}else if(bg->getPositionY() > mapSize.height/2 - visibleSize.height/2){//下边界
		bg->setPositionY(mapSize.height/2 - visibleSize.height/2 );
		m_offsetPos.y = 0;
	}
}

void AnimManager::moveOffsetToMonstorPool(CCArray *pool){
	CCObject* obj = NULL;
	CCARRAY_FOREACH(pool,obj){
		CharacterBase* pMonstor = (CharacterBase*)obj;
		float tagX = pMonstor->getArmatrue()->getPositionX() - m_offsetPos.x;//根据地图的偏移来移动
		float tagY = pMonstor->getArmatrue()->getPositionY() - m_offsetPos.y;
		pMonstor->setPos(tagX,tagY);
	}
}

void AnimManager::moveOffsetToEntrance(CCNode *entrance){
	float tagX = entrance->getPositionX() - m_offsetPos.x;//根据地图的偏移来移动
	float tagY = entrance->getPositionY() - m_offsetPos.y;
	entrance->setPosition(ccp(tagX,tagY));
}

void AnimManager::toggleTool(CCNode *panel){
	m_bToggleTool = !m_bToggleTool;
	CCAction* action = NULL;
	action = m_bToggleTool ? CCMoveBy::create(0.3f,ccp(0,-70)) : CCMoveBy::create(0.3f,ccp(0,70));
	panel->runAction(action);
}
///////////////////////Store////////////////////////////////////////////
void AnimManager::renderList(TuiBase* pScene,SEL_ClickHandler clickHandler,const char* type,int length){

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

///////////////////////Common////////////////////////////////////////////
void AnimManager::resetPlaceTool(CCArray* arr,CCPoint p){
	int offset = 3;
	CCObject *obj = NULL;
	int cout = 0;
	CCARRAY_FOREACH(arr,obj){
		CLayout* item = (CLayout*)obj;
		item->setPosition(p+ccp(((item->getContentSize().width+offset)*cout),0));
		cout++;
	}
}

void AnimManager::showLoading(TuiBase* tuiBase,int tagPanel){
	CCSprite* pSprite = TuiManager::sharedManager()->createAnim(130,"anim_loading",
		"res_iphone/common/anim_loading.png","res_iphone/common/anim_loading.plist",0,0);
	pSprite->setZOrder(INT_MAX);
	tuiBase->getPanel(tagPanel)->addChild(pSprite);
}
//展示入口
void AnimManager::showEntrance(CCNode* panel,CCNode* pos){
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("res_iphone/ingame/anim_entrance.plist",
		"res_iphone/ingame/anim_entrance.png");
	CCAnimation* pAnim = AnimationUtil::createAnimWithName("anim_entrance",0.05f,1);
	pAnim->setRestoreOriginalFrame(false);
	CCSprite* pSprite = CCSprite::create();
	pSprite->setPosition(pos->getPosition());
	pSprite->runAction(CCAnimate::create(pAnim));
	pSprite->setTag(TMP_ENTRANCEANIM_TAG);
	panel->addChild(pSprite);
}

AnimManager::~AnimManager(){

}