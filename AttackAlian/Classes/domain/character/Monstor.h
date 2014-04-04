#ifndef __MONSTOR_H__
#define __MONSTOR_H__

#include "domain/character/CharacterBase.h"
#include "domain/character/Hero.h"

class Monstor : public CharacterBase{

public:
	CREATE_FUNC(Monstor);
	virtual bool init();

	~Monstor();

	void hurt(float v);
	void attack();
	void attackStop();
	void setPos(float x,float y);
	void intoHospital();//进入医院

	bool isCollision(CCObject* checkObj);
protected:
	void executeAttack(float dt);//攻击
private:
	
};

#endif