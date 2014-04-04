#ifndef __DOMAINBASE_H__
#define __DOMAINBASE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "domain/config.h"
#include "../../CocosBase/cocos-base.h"
#include "../../CocosWidget/cocos-widget.h"

using namespace std;
using namespace cocos2d::cocoswidget;
using namespace cocos2d::extension;
USING_NS_CC;

class CharacterBase : public CCObject
{
public:
	CREATE_FUNC(CharacterBase);

	virtual bool init();
	virtual void setPos(float x, float y);//移动
	
	virtual void createHpSlider(CCNode *container);
	virtual void sortZorder();
	virtual void hurt(int v);

	virtual void cb_anim_hplabel(CCNode *pNode);

	virtual bool chase(float tagX,float tagY);//追逐
	virtual bool isCollision(CCObject* obj);
	virtual bool isLive();

	virtual void setHp(int v);
	virtual int getHp();
	virtual int getMaxHp();
	virtual void setLive(bool b);
	virtual void setArmature(CCArmature* pArmature);//通过骨骼 创建容器
	virtual void setAttackObj(CCObject* obj);//设置攻击对象
 	virtual CCObject* getAttackObj();//获取攻击对象
	virtual CCArmature* getArmatrue();
	virtual CSlider* getHPSlider();
	virtual int getAttackValue();
	virtual void setAttackValue(int v);
protected:
	CCArmature* m_pArmature;
	CSlider* m_pHPSlider;
	CCObject* m_pAttackObj;

	int m_attackValue;//伤害值
	bool m_isLive;//是否还活着 
	int m_life;//生命值
	int m_maxHpValue;//生命最大值

	bool m_isAttack;//是否正在攻击

	int m_vx;
	int m_vy;
	int m_speed;
private:
};
#endif