#include "Boss.h"
#include "Hero.h"

bool Boss::init(){
	if(!CharacterBase::init()) return false;
	m_vx = 0;
	m_vy = 0;
	m_speed = 3;
	m_maxHpValue = 1000;
	m_life = 1000;
	m_isLive = true;
	m_attackValue = 100;
	m_pAttackObj = NULL;
	return true;
}

void Boss::setPos(float x, float y){
	m_pArmature->setPosition(ccp(x,y));
	//移动hp
	CharacterBase::setPos(m_pArmature->getPositionX(),m_pArmature->getPositionY());

	CCArmatureAnimation* anim = m_pArmature->getAnimation();
	if(!anim->getIsPlaying() && m_isLive){
		anim->play("live",0,70);
	}

	sortZorder();
}

bool Boss::isCollision(CCObject* obj){
	Hero* pHero = (Hero*) obj;
	float dis = ccpDistance(this->getArmatrue()->getPosition(),
		pHero->getArmatrue()->getPosition());
	return (dis < HERO_CHASE_DIS);
}

void Boss::hurt(float v){
	setHp(getHp()-v);//扣血
	if(getHp() <= 0 && m_isLive){
		m_isLive = false;
		getArmatrue()->getAnimation()->play("die",0,20);
		getHPSlider()->removeFromParent();
		CCMsgManager::sharedManager()->PostMessage(MSG_BOSS_DEAD);//Boss死了 广播游戏结束
	}
	CharacterBase::hurt(v);
}

void Boss::attack(){
	bool ret = m_pArmature->getAnimation()->getIsPlaying();
	if(!ret){
		m_pArmature->getAnimation()->play("attack",0,50);
		Hero* pHero = (Hero*)m_pAttackObj;
		pHero->hurt(m_attackValue);
	}
}

void Boss::intoHospital(){
	this->getArmatrue()->setVisible(false);
	this->getHPSlider()->removeFromParent();
	CCMsgManager::sharedManager()->PostMessage(MSG_INTOENTRANCE);
}

Boss::~Boss(){
	m_pHPSlider->release();
}