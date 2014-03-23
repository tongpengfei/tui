#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "domain/goods/GoodsBase.h"
class Weapon : public GoodsBase
{
public:
	CREATE_FUNC(Weapon);
	virtual bool init();

	int getPowerLength();
	int getAttackValue();
	void setId(int id);
protected:
	int m_powerLength;
	int m_attackValue;
private:
};

#endif