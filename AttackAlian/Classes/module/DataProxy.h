#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "domain/config.h"
#include "domain/character/Hero.h"
#include "cocos2d.h"
USING_NS_CC;

class DataProxy : public CCObject
{
public:
	static DataProxy* sharedManager();
	bool virtual init();

	CC_SYNTHESIZE(int,m_coin, Coin);//当前金币数
	CC_SYNTHESIZE(int,m_level,Level);//当前关卡
	CC_SYNTHESIZE(bool,m_isWin,Win);//是否胜利

	CC_SYNTHESIZE(Hero*,m_hero,Hero);//当前玩家
	CC_SYNTHESIZE(CCArray*,m_arrWeapon,ArrWeapon);//当前武器
	CC_SYNTHESIZE(CCArray*,m_arrMedicine,ArrMedicine);//当前药水
	CC_SYNTHESIZE(CCArray*,m_arrProp,ArrProp);//当前道具

protected:
private:
	static DataProxy* m_instance;
};

#endif