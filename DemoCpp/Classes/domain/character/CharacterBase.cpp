#include "domain/character/CharacterBase.h"
#include "tui/TuiManager.h"

bool CharacterBase::init(){
	m_pHPSlider = NULL;
	m_pArmature = NULL;
	return true;
}

void CharacterBase::setPos(float x, float y){
	if(m_pHPSlider!= NULL){
		m_pHPSlider->setPosition(ccp(x,y+getArmatrue()->getContentSize().height));
	}
}

void CharacterBase::createHpSlider(CCNode *container){
	m_pHPSlider = TuiManager::sharedManager()->createSlider(0,"res_iphone/ingame/slider_hp_bg.png",
		"res_iphone/ingame/slider_hp_progress.png","res_iphone/ingame/slider_hp_thumb.png",0,0);
	container->addChild(m_pHPSlider);
	m_pHPSlider->setMaxValue(m_maxHpValue);
	m_pHPSlider->setMinValue(0);
	m_pHPSlider->setValue(getHp());
	m_pHPSlider->setZOrder(INT_MAX -20);
	m_pHPSlider->retain();
}

void CharacterBase::hurt(int v){
	if(!isLive()) return;
	CLabelAtlas* pLabel = TuiManager::sharedManager()->createLabelAtlas(0,"res_iphone/ingame/labAtlas_num.png",0,0,312,34);
	pLabel->setString(CCString::createWithFormat("%d",v)->getCString());
	pLabel->setZOrder(INT_MAX-20);

	CCScaleBy *actScale = CCScaleBy::create(0.2f,0.5f,0.5f);
	CCCallFuncN* actCallBack = CCCallFuncN::create(this,callfuncN_selector(CharacterBase::cb_anim_hplabel));
	CCSequence *seq = CCSequence::create(actScale,actCallBack,NULL);
	pLabel->runAction(seq);
	
	getArmatrue()->getParent()->addChild(pLabel);
	pLabel->setPosition(ccp(m_pHPSlider->getPositionX(),m_pHPSlider->getPositionY()+20));
}

bool CharacterBase::chase(float tagX,float tagY){
	int x = m_pArmature->getPositionX();
	int y = m_pArmature->getPositionY();
	float dis = sqrt(pow(x-tagX,2)+pow(y-tagY,2));
	int scaleX = x > tagX ? -1 : 1;
	m_pArmature->setScaleX(scaleX);
	if(dis < HERO_CHASE_DIS) return true;

	float dx = tagX - x ;
	float dy = tagY - y ;
	float angle = atan2(dy,dx);
	m_vx = cos(angle) * m_speed;
	m_vy = sin(angle) * m_speed;
	setPos(x+m_vx,y+m_vy);
	return false;
}

void CharacterBase::sortZorder(){
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	int z = -m_pArmature->getPositionY()+size.height / 2;
	m_pArmature->setZOrder(z);
}

void CharacterBase::cb_anim_hplabel(CCNode *pNode){
	pNode->removeFromParent();
}

/************************************************************************/
//GET /SET /IS
/************************************************************************/

bool CharacterBase::isCollision(CCObject* checkObj){
	return false;
}

bool CharacterBase::isLive(){
	return m_isLive;
}

void CharacterBase::setArmature(CCArmature* pArmature){
	this->m_pArmature = pArmature;
}

CCArmature* CharacterBase::getArmatrue(){
	return this->m_pArmature;
}

void CharacterBase::setAttackObj(CCObject* obj){
	this->m_pAttackObj = obj;
}

CCObject* CharacterBase::getAttackObj(){
	return this->m_pAttackObj;
}

int CharacterBase::getAttackValue(){
	return this->m_attackValue;
}

void CharacterBase::setAttackValue(int v){
	this->m_attackValue = v;
}

CSlider* CharacterBase::getHPSlider(){
	return this->m_pHPSlider;
}

void CharacterBase::setHp(int v){
	if(m_pHPSlider != NULL){
		m_pHPSlider->setValue(v);
	}
	m_life = min(max(0,v),m_maxHpValue);
}

int CharacterBase::getHp(){
	return m_life;
}

int CharacterBase::getMaxHp(){
	return m_maxHpValue;
}

void CharacterBase::setLive(bool b){
	if(m_pHPSlider != NULL){
		m_pHPSlider->setVisible(b);
	}
	if(m_pArmature != NULL){
		const char *actionLabel = b ? "d" : "dead";
		m_pArmature->getAnimation()->play(actionLabel,0,30);
	}
	m_isLive = b;
}