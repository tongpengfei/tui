#include "LevelManager.h"


bool LevelManager::init(){

	return true;
}

void LevelManager::startGame(CCNode* panel,MonstorManager* pMonstorManager,Hero *pHero,CCArray* arrWeapon,int level){
	//初始化英雄装备
	initHero(pHero,arrWeapon);
	//创建怪物
	pMonstorManager->createMonstors(50,CCString::createWithFormat("armature_monster%d",level)->getCString(),
		CCString::createWithFormat("res_iphone/ingame/armature_monster%d.png",level)->getCString(),
		CCString::createWithFormat("res_iphone/ingame/armature_monster%d.plist",level)->getCString(),
		CCString::createWithFormat("res_iphone/ingame/armature_monster%d.xml",level)->getCString());
	pMonstorManager->initMonstor(panel,pHero);
	
	//清理入口动画
	panel->removeChildByTag(TMP_ENTRANCEANIM_TAG);
}

void LevelManager::placeBoss(CCNode* panel,MonstorManager* pMonstorManager,Hero *pHero,CCArray* arrWeapon,int level){
	//创建boss
	pMonstorManager->createBosss(2,CCString::createWithFormat("armature_boss%d",level)->getCString(),
		CCString::createWithFormat("res_iphone/ingame/armature_boss%d.png",level)->getCString(),
		CCString::createWithFormat("res_iphone/ingame/armature_boss%d.plist",level)->getCString(),
		CCString::createWithFormat("res_iphone/ingame/armature_boss%d.xml",level)->getCString());
	pMonstorManager->initBoss(panel,pHero);
	//创建跟班怪物
	pMonstorManager->createMonstors(15,CCString::createWithFormat("armature_monster%d",level)->getCString(),
		CCString::createWithFormat("res_iphone/ingame/armature_monster%d.png",level)->getCString(),
		CCString::createWithFormat("res_iphone/ingame/armature_monster%d.plist",level)->getCString(),
		CCString::createWithFormat("res_iphone/ingame/armature_monster%d.xml",level)->getCString());
	pMonstorManager->initMonstor(panel,pHero);
}

void LevelManager::endGame(MonstorManager* pMonstorManager){
	pMonstorManager->clear();
	CCSceneManager::sharedManager()->runUIScene(LoadScene("Resuleui"));
}

void LevelManager::initHero(Hero* pHero,CCArray* arrWeapon){
	pHero->setHp(pHero->getMaxHp());
	pHero->setLive(true);
	if(arrWeapon->count()>0){
		Weapon* goodItem = (Weapon*)arrWeapon->objectAtIndex(0);
		pHero->setWeapon(goodItem->getId(),goodItem->getPowerLength(),goodItem->getAttackValue());
	}else{
		pHero->setWeapon(0,WEAPON_BASE_POWERLENGTH,WEAPON_BASE_ATTACTVALUE);
	}
}