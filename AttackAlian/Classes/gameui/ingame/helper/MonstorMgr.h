#ifndef __MONSTOR_MANAGER_H__
#define __MONSTOR_MANAGER_H__

#include "cocos2d.h"
#include "domain/character/Monstor.h"
#include "domain/character/Hero.h"
#include "domain/character/Boss.h"
#include "domain/character/CharacterBase.h"
using namespace std;
USING_NS_CC;

class MonstorMgr : public CCObject
{
public:
	CREATE_FUNC(MonstorMgr);
	virtual bool init();
	~MonstorMgr();

	void pushMonstor(Monstor*);
	Monstor* popMonstor();

	void createMonstors(int size,const char* name,const char* png,const char* plist,const char* xml);
	void createBosss(int size,const char* name,const char* png,const char* plist,const char* xml);

	void initMonstor(CCNode* container,Hero* pHero);
	void initBoss(CCNode* container,Hero* pHero);

	void checkHurtHero(CharacterBase* pHero);
	void checkHurtEnemy(CharacterBase* pHero);
	void checkMonstorNum();//检查剩余怪物数
	void checkBossNum();//检查剩余Boss数
	void checkIntoNum();//检查进入的数量
	void walkToEntrance(CCNode* entrance);//跑去入口

	void clear();

	CCArray* getMonstorPool();
	CCArray* getBossPool();
	bool isShowBoss();

protected:
	CCArray* m_poolMonstor;
	CCArray* m_poolBoss;

private:
	bool m_isPlaceBoss;
	bool m_hadSendMonstorDead;
	bool m_hadSendBossDead;
};
#endif