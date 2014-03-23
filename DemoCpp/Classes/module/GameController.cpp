#include "module/GameController.h"

GameController* GameController::m_instance = NULL;
GameController* GameController::sharedController(){
	if(m_instance == NULL){
		m_instance = new GameController();
		if(m_instance && m_instance->init()){
			m_instance->retain();
		}else{
			CC_SAFE_DELETE(m_instance);
			m_instance = NULL;
		}
	}
	return m_instance;
}

bool GameController::init(){

	m_arrWeapon = CCArray::create();
	m_arrWeapon->retain();
	m_arrMedicine = CCArray::create();
	m_arrMedicine->retain();
	m_arrProp = CCArray::create();
	m_arrProp->retain();

	m_level = 1;
	m_isWin = false;
	m_coin = HERO_INIT_COIN;

	return true;
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void GameController::setWin(bool v){
	this->m_isWin = v;
}

bool GameController::isWin(){
	return this->m_isWin;
}

void GameController::setLevel(int v){
	m_level = v;
}

int GameController::getLevel(){
	return this->m_level;
}

void GameController::setCoin(int v){
	m_coin = v;
}

int GameController::getCoin(){
	return m_coin;
}

void GameController::setArrWeapon(CCArray* pArrWeapon){
	this->m_arrWeapon = pArrWeapon;
}

CCArray* GameController::getArrWeapon(){
	return this->m_arrWeapon;
}

void GameController::setArrMedicine(CCArray* pArrMedicine){
	this->m_arrMedicine = pArrMedicine;
}

CCArray* GameController::getArrMedicine(){
	return this->m_arrMedicine;
} 

void GameController::setArrProp(CCArray* pArrProp){
	this->m_arrProp = pArrProp;
}

CCArray* GameController::getArrProp(){
	return this->m_arrProp;
}