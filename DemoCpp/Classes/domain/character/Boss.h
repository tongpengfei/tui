#ifndef __BOSS_H__
#define __BOSS_H__

#include "domain/character/CharacterBase.h"

class Boss : public CharacterBase
{
public:
	CREATE_FUNC(Boss);
	virtual bool init();

	~Boss();

	void hurt(float v);
	void setPos(float x, float y);
	bool isCollision(CCObject* obj);
	void attack();
	void intoHospital();
protected:
private:
};

#endif