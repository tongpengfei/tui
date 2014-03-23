#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

#include "domain/character/CharacterBase.h"
#include "domain/goods/GoodsBase.h"
#include "domain/goods/Weapon.h"
#include "module/MonstorManager.h"
#include "domain/character/Hero.h"

class LevelManager : public CCObject
{
public:
	CREATE_FUNC(LevelManager);
	virtual bool init();

	void startGame(CCNode* panel,MonstorManager* pMonstorManager,Hero *pHero,CCArray* arrWeapon,int level);
	void placeBoss(CCNode* panel,MonstorManager* pMonstorManager,Hero *pHero,CCArray* arrWeapon,int level);
	void endGame(MonstorManager* pMonstorManager);

	void initHero(Hero *pHero,CCArray* arrWeapon);
protected:
private:
};

#endif