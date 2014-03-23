#ifndef __HERO_H__
#define __HERO_H__

#include "domain/character/CharacterBase.h"

class Hero : public CharacterBase{
public:
	CREATE_FUNC(Hero);
	virtual bool init();

	~Hero();

	void setPos(float x, float y);//移动
	inline void setDir(float x, float y);//转向
	void setWeapon(int id,int powerLength,int attackValue);//切换武器
	void resume(int id,int resumeLength);//恢复血量
	void useProp(int id);//使用道具

	bool fire();
	bool isCollision(CCObject* checkObj);
	void hurt(int v);

protected:
	vector<CCPoint> getFirePoints();//获取火枪攻击点
private:
	double m_angelDir;
	double m_angelDirLast;//记录上一次的方位

	int m_weaponId;//武器下标
	int m_powerLength;//武器攻击长度
};	
#endif