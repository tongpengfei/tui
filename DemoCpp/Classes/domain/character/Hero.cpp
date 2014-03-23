#include "Hero.h"
#include "Monstor.h"

bool Hero::init(){
	if(!CharacterBase::init()) return false;
	m_maxHpValue = 3000;

	return true;
}

void Hero::setPos(float offsetX, float offsetY){

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_pArmature->setPosition(m_pArmature->getPosition()+ CCPoint(offsetX,offsetY));//移动
	//移动hpSlider和hpLabel
	CharacterBase::setPos(m_pArmature->getPositionX(),m_pArmature->getPositionY());
	//-----------------------限制英雄可行范围-------------------------------
	if(m_pArmature->getPositionX() > visibleSize.width/2){//右
		m_pArmature->setPositionX(visibleSize.width/2);
	}else if(m_pArmature->getPositionX() < -visibleSize.width/2){//左
		m_pArmature->setPositionX(-visibleSize.width/2);
	}

	if(m_pArmature->getPositionY() > visibleSize.height/2){//上
		m_pArmature->setPositionY(visibleSize.height/2);
	}else if(m_pArmature->getPositionY() < -visibleSize.height/2){//下
		m_pArmature->setPositionY(-visibleSize.height/2);
	}
	setDir(offsetX,offsetY);//设置方向
	sortZorder();//设置深度
}

void Hero::setDir(float x, float y){
	float angel = atan2(y,x) * 180 / 3.1415;
	if(angel<0) angel+= 360;

	if(angel> 350 || angel<= 10){
		m_pArmature->setScaleX(-1);
		m_pArmature->getAnimation()->play("s",0,20,1);
		m_angelDir = 0;
	}else if(angel> 10 && angel<= 35){
		m_pArmature->setScaleX(-1);
		m_pArmature->getAnimation()->play("uss",0,20,1);
		m_angelDir = 22.5;
	}else if(angel> 35 && angel<= 55){
		m_pArmature->setScaleX(-1);
		m_pArmature->getAnimation()->play("us",0,20,1);
		m_angelDir = 45;
	}else if(angel> 55 && angel<= 80){
		m_pArmature->setScaleX(-1);
		m_pArmature->getAnimation()->play("uus",0,20,1);
		m_angelDir = 67.5;
	}else if(angel> 80 && angel<= 100){
		m_pArmature->setScaleX(-1);
		m_pArmature->getAnimation()->play("u",0,20,1);
		m_angelDir = 90;
	}else if(angel> 100 && angel<= 125){
		m_pArmature->setScaleX(1);
		m_pArmature->getAnimation()->play("uus",0,20,1);
		m_angelDir = 112.5;
	}else if(angel> 125 && angel<= 145){
		m_pArmature->setScaleX(1);
		m_pArmature->getAnimation()->play("us",0,20,1);
		m_angelDir = 135;
	}else if(angel> 145 && angel<= 170){
		m_pArmature->setScaleX(1);
		m_pArmature->getAnimation()->play("uss",0,20,1);	
		m_angelDir = 157.5;
	}else if(angel> 170 && angel<= 190){
		m_pArmature->setScaleX(1);
		m_pArmature->getAnimation()->play("s",0,20,1);
		m_angelDir = 180;
	}else if(angel> 190 && angel<= 215){
		m_pArmature->setScaleX(1);
		m_pArmature->getAnimation()->play("dss",0,20,1);
		m_angelDir = 202.5;
	}else if(angel> 215 && angel<= 235){
		m_pArmature->setScaleX(1);
		m_pArmature->getAnimation()->play("ds",0,20,1);
		m_angelDir = 225;
	}else if(angel> 235 && angel<= 260){
		m_pArmature->setScaleX(1);
		m_pArmature->getAnimation()->play("dds",0,20,1);
		m_angelDir = 247.5;
	}else if(angel> 260 && angel<= 280){
		m_pArmature->setScaleX(1);
		m_pArmature->getAnimation()->play("d",0,20,1);
		m_angelDir = 270;
	}else if(angel> 280 && angel<= 305){
		m_pArmature->setScaleX(-1);
		m_pArmature->getAnimation()->play("dds",0,20,1);
		m_angelDir = 292.5;
	}else if(angel> 305 && angel<= 325){
		m_pArmature->setScaleX(-1);
		m_pArmature->getAnimation()->play("ds",0,20,1);
		m_angelDir = 315;
	}else if(angel> 325 && angel<= 350){
		m_pArmature->setScaleX(-1);
		m_pArmature->getAnimation()->play("dss",0,20,1);
		m_angelDir = 337.5;
	}

	if(m_angelDir != m_angelDirLast){//确保每次动画都从第一帧开始
		CCArmatureAnimation *anim = m_pArmature->getBone("gun")->getChildArmature()->getAnimation();
		if(anim->getIsPlaying()) anim->gotoAndPause(1);
		m_angelDirLast = m_angelDir;
	}
	
	//腿部动画
	CCArmatureAnimation* pAnimLeg = m_pArmature->getBone("leg")->getChildArmature()->getAnimation();
	if(!pAnimLeg->getIsPlaying()){
		m_pArmature->getBone("leg")->getChildArmature()->getAnimation()->play("run",0,15);
	}
}

bool Hero::isCollision(CCObject *checkObj){
	CharacterBase* pEnemy = (CharacterBase*) checkObj;
	bool b = false;
	if(m_weaponId == 3){//圆圈攻击范围
		float baseX = this->getArmatrue()->getPositionX();
		float baseY = this->getArmatrue()->getPositionY();
		CCPoint attackP = pEnemy->getArmatrue()->getPosition();
		float dis = ccpDistance(ccp(baseX,baseY+50),attackP);
		b = dis <= this->m_powerLength;
	}else{//直线攻击范围
		vector<CCPoint> vet = getFirePoints();
		for(vector<CCPoint>::iterator it=vet.begin(); it!=vet.end(); ++it){
			if(pEnemy->getArmatrue()->boundingBox().containsPoint(*it)){
				b = true;
				break;
			}
		}
	}
	return b;
}

bool Hero::fire(){
	CCArmatureAnimation* pAnim = m_pArmature->getBone("gun")->getChildArmature()->getAnimation();
	bool ret = pAnim->getIsPlaying();
	if(!ret){
		CCString *str = CCString::createWithFormat("fire%d",this->m_weaponId);
		m_pArmature->getBone("gun")->getChildArmature()->getAnimation()->play(str->getCString(),0,20);
	}
	return ret;
}

void Hero::hurt(int v){
	setHp(getHp()-v);//扣血
	if(getHp()<=0 && isLive()){
		setLive(false);
		CCMsgManager::sharedManager()->PostMessage(MSG_HERO_DEAD);//广播英雄死亡的消息
	}
	CharacterBase::hurt(v);
}

void Hero::resume(int id,int resumeLength){
	setHp(getHp() + resumeLength);
}

void Hero::useProp(int id){

}

vector<CCPoint> Hero::getFirePoints(){
	float x = m_pArmature->getPositionX();
	float y = m_pArmature->getPositionY();
	float startX = x + this->m_powerLength;
	float startY = y;

	CCPoint tagetP = ccpRotateByAngle(ccp(startX,startY),ccp(x,y), CC_DEGREES_TO_RADIANS(m_angelDir));

	int offset = 50;//重心偏移量
	vector< CCPoint > vec;
	vec.push_back(ccp(tagetP.x,tagetP.y+ offset));//终点
	//vec.push_back(ccp(x,y+ offen));//起点
	vec.push_back(ccp((tagetP.x+x)*0.5,(tagetP.y+y)*0.5+ offset));//中点

	return vec;
}

void Hero::setWeapon(int id,int powerLength,int attackValue){
	if(!isLive()) return;
	this->m_weaponId = id;
	this->m_powerLength = powerLength;
	this->m_attackValue = attackValue;
	string strs[] = {"dds","ds","dss","s","uss","us","uus","u","d"};
	char weaponStr[6];
	sprintf(weaponStr,"fire%d",id);
	for(int i=0; i<9; i++){
		m_pArmature->getAnimation()->play(strs[i].c_str());
		m_pArmature->getBone("gun")->getChildArmature()->getAnimation()->play(weaponStr); 
		m_pArmature->getBone("gun")->getChildArmature()->getAnimation()->gotoAndPause(0);
	}
}

Hero::~Hero(){
	m_pHPSlider->release();
}