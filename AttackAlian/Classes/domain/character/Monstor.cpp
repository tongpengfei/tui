#include "Monstor.h"
#include "Hero.h"

bool Monstor::init(){
	if(!CharacterBase::init()) return false;
	m_vx = 0;
	m_vy = 0;
	m_speed = 3;
	m_maxHpValue = 200;
	m_life = 200;
	m_isLive = true;
	m_isAttack = false;
	m_attackValue = 10;
	m_pAttackObj = NULL;
	return true;
}

void Monstor::setPos(float x,float y){
	m_pArmature->setPosition(ccp(x,y));
	//移动hp
	CharacterBase::setPos(m_pArmature->getPositionX(),m_pArmature->getPositionY());

	CCArmatureAnimation* anim = m_pArmature->getAnimation();
	if(!anim->getIsPlaying() && m_isLive){
		anim->play("live",0,70);
	}
	
	sortZorder();
}

bool Monstor::isCollision(CCObject *checkObj){
	Hero* pHero = (Hero*) checkObj;
	float dis = ccpDistance(this->getArmatrue()->getPosition(),
							 pHero->getArmatrue()->getPosition());
	return (dis < HERO_CHASE_DIS);
}

void Monstor::hurt(float v){
	setHp(getHp()-v);//扣血
	if(getHp() <= 0 && m_isLive){
		m_isLive = false;
		attackStop();
		getArmatrue()->getAnimation()->play("die",0,20);
		getHPSlider()->removeFromParent();
		CCMsgManager::sharedManager()->PostMessage(MSG_MONSTOR_DEAD);//广播该怪物已经死了
	}
	CharacterBase::hurt(v);
}

void Monstor::attack(){
	if(!m_isAttack){
		m_isAttack = true;//只触发一次 然后每隔0.5秒发动一次攻击
		executeAttack(0);
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
			schedule_selector(Monstor::executeAttack),this,0.5f,false);
	}
}

void Monstor::attackStop(){
	m_isAttack = false;
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(
		schedule_selector(Monstor::executeAttack),this);
}

void Monstor::executeAttack(float dt){
	Hero* pHero = (Hero*)m_pAttackObj;
	pHero->hurt(m_attackValue);
}

void Monstor::intoHospital(){
	this->getArmatrue()->setVisible(false);
	this->getHPSlider()->removeFromParent();
	CCMsgManager::sharedManager()->PostMessage(MSG_INTOENTRANCE);
}

Monstor::~Monstor(){
	m_pHPSlider->release();
}