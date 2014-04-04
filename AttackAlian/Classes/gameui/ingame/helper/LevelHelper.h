#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

#include "domain/character/CharacterBase.h"
#include "domain/goods/GoodsBase.h"
#include "domain/goods/Weapon.h"
#include "gameui/ingame/helper/MonstorMgr.h"
#include "domain/character/Hero.h"

class LevelMgr : public CCObject
{
public:
	CREATE_FUNC(LevelMgr);
	virtual bool init();

	void startGame(CCNode* panel,MonstorMgr* pMonstorManager,Hero *pHero,CCArray* arrWeapon,int level);
	void placeBoss(CCNode* panel,MonstorMgr* pMonstorManager,Hero *pHero,CCArray* arrWeapon,int level);
	void endGame(MonstorMgr* pMonstorManager);

	void initHero(Hero *pHero,CCArray* arrWeapon);
protected:
private:
};

#endif