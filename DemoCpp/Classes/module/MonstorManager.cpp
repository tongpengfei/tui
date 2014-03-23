#include "module/MonstorManager.h"

bool MonstorManager::init(){
	m_poolMonstor = CCArray::create();
	m_poolMonstor->retain();
	m_poolBoss = CCArray::create();
	m_poolBoss->retain();

	m_isPlaceBoss = false;
	m_hadSendMonstorDead = false;
	m_hadSendBossDead = false;
	return true;
}

void MonstorManager::pushMonstor(Monstor* pMonstor){
	m_poolMonstor->addObject(pMonstor);
}

Monstor* MonstorManager::popMonstor(){
	Monstor* monstor = (Monstor*)m_poolMonstor->lastObject();
	return monstor;
}

void MonstorManager::createMonstors(int size,const char* name,const char* png,const char* plist,const char* xml){
	
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(png,plist,xml);
	for(int i=0;i<size; i++){
		Monstor* pMonstor = Monstor::create();
		pMonstor->setArmature(CCArmature::create(name));
		m_poolMonstor->addObject(pMonstor);
	}
}

void MonstorManager::createBosss(int size,const char* name,const char* png,const char* plist,const char* xml){

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(png,plist,xml);
	for(int i=0;i<size; i++){
		Boss* pBoss = Boss::create();
		pBoss->setArmature(CCArmature::create(name));
		m_poolBoss->addObject(pBoss);
	}
}

void MonstorManager::initMonstor(CCNode* container,Hero *pHero){
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_poolMonstor,obj){
		Monstor* monstor = (Monstor*)obj;
		if(!monstor->getArmatrue()->getParent()){
			monstor->createHpSlider(container);
			monstor->setPos(CCRANDOM_MINUS1_1()*800,CCRANDOM_MINUS1_1()*800);
			monstor->setAttackObj(pHero);
			container->addChild(monstor->getArmatrue());
		}
	}
}

void MonstorManager::initBoss(CCNode* container,Hero* pHero){
	m_isPlaceBoss = true;//标记Boss已出场
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_poolBoss,obj){
		Boss* pBoss = (Boss*)obj;
		pBoss->createHpSlider(container);
		pBoss->setPos(CCRANDOM_MINUS1_1()*800,CCRANDOM_MINUS1_1()*480);
		pBoss->setAttackObj(pHero);
		container->addChild(pBoss->getArmatrue());
	}
}

void MonstorManager::checkHurtHero(CharacterBase *characterBase){
	Hero *pHero = (Hero*)characterBase;
	if(!pHero->isLive()) return;
	float tagX = pHero->getArmatrue()->getPositionX();
	float tagY = pHero->getArmatrue()->getPositionY();

	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_poolMonstor,obj){
		Monstor* monstor = (Monstor*)obj;
		if(monstor->isLive()){
			monstor->chase(tagX,tagY);
			if(monstor->isCollision(characterBase)){
				monstor->attack();//攻击
			}else{
				monstor->attackStop();//停止攻击
			}
		}
	}
	if(!m_isPlaceBoss) return;
	obj = NULL;
	CCARRAY_FOREACH(m_poolBoss,obj){
		Boss* pBoss = (Boss*)obj;
		if(pBoss->isLive()){
			pBoss->chase(tagX,tagY);
			if(pBoss->isCollision(characterBase)){
				pBoss->attack();//开始攻击
			}
		}
	}
}

void MonstorManager::checkHurtEnemy(CharacterBase *characterBase){
	Hero *pHero = (Hero*)characterBase;
	if(!pHero->isLive()) return;
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_poolMonstor,obj){
		Monstor* monstor = (Monstor*)obj;
		if(pHero->isCollision(monstor)){
			monstor->hurt(pHero->getAttackValue());//扣血
		}
	}
	if(!m_isPlaceBoss) return;
	obj = NULL;
	CCARRAY_FOREACH(m_poolBoss,obj){
		Boss* pBoss = (Boss*)obj;
		if(pHero->isCollision(pBoss)){
			pBoss->hurt(pHero->getAttackValue());//扣血
		}
	}
}

void MonstorManager::checkMonstorNum(){
	int countLive = 0;
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_poolMonstor,obj){
		Monstor* item = (Monstor*) obj;
		if(item->isLive()) countLive++;
	}
	if(countLive == 0){//没有生还的怪物
		if(!m_hadSendMonstorDead){
			m_hadSendMonstorDead = true;//避免重复发送消息
			CCMsgManager::sharedManager()->PostMessage(MSG_PLACEBOSS);//出boss
		}
	}
}

void MonstorManager::checkBossNum(){
	int countLive = 0;
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_poolBoss,obj){
		Boss* item = (Boss*) obj;
		if(item->isLive()) countLive++;
	}
	if(countLive == 0){//没有生还的Boss
		if(!m_hadSendBossDead){
			m_hadSendBossDead = true;//避免重复发送消息
			CCMsgManager::sharedManager()->PostMessage(MSG_ENDGAME);//游戏结束
		}
	}
}

void MonstorManager::checkIntoNum(){
	CCObject* obj = NULL;
	int count = 0;
	CCARRAY_FOREACH(m_poolMonstor,obj){
		Monstor* pMonstor = (Monstor*) obj;
		if(pMonstor->getArmatrue()->isVisible() && pMonstor->isLive()){//正在走进医院的怪物
			count++;
		}
	}
	obj = NULL;
	CCARRAY_FOREACH(m_poolBoss,obj){
		Boss* pBoss = (Boss*) obj;
		if(pBoss->getArmatrue()->isVisible() && pBoss->isLive()){
			count++;
		}
	}
	if(count == 0){//全部进入医院了
		CCMsgManager::sharedManager()->PostMessage(MSG_ENDGAME);
	}
}

void MonstorManager::walkToEntrance(CCNode* entrance){
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_poolMonstor,obj){
		Monstor* monstor = (Monstor*)obj;
		if(monstor->isLive()){
			bool isInto = monstor->chase(entrance->getPositionX(),entrance->getPositionY());
			if(isInto){
				if(monstor->getArmatrue()->isVisible())
				monstor->intoHospital();
			}
		}
	}

	if(m_isPlaceBoss){
		obj = NULL;
		CCARRAY_FOREACH(m_poolBoss,obj){
			Boss* pBoss = (Boss*) obj;
			if(pBoss->isLive()){
				bool isInto = pBoss->chase(entrance->getPositionX(),entrance->getPositionY());
				if(isInto){
					if(pBoss->getArmatrue()->isVisible())
						pBoss->intoHospital();
				}
			}
		}
	}
}

void MonstorManager::clear(){
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_poolMonstor,obj){
		Monstor* monstor = (Monstor*)obj;
		monstor->attackStop();
		monstor->getArmatrue()->removeFromParent();
	}
	m_poolMonstor->removeAllObjects();
	if(m_isPlaceBoss){
		CCObject* obj2 = NULL;
		CCARRAY_FOREACH(m_poolBoss,obj2){
			Boss* pBoss = (Boss*)obj2;
			pBoss->getArmatrue()->removeFromParent();
		}
	}
	m_poolBoss->removeAllObjects();
	m_isPlaceBoss = false;
	m_hadSendMonstorDead = false;
	m_hadSendBossDead = false;
}

MonstorManager::~MonstorManager(){
	m_poolMonstor->release();
	m_poolBoss->release();
}

/*************************************************************************/
// GET/SET/IS                                                         
/************************************************************************/
CCArray* MonstorManager::getMonstorPool(){
	return this->m_poolMonstor;
}

CCArray* MonstorManager::getBossPool(){
	return this->m_poolBoss;
}

bool MonstorManager::isPlaceBoss(){
	return m_isPlaceBoss;
}