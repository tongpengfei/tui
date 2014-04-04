#include "module/DataProxy.h"

DataProxy* DataProxy::m_instance = NULL;
DataProxy* DataProxy::sharedManager(){
	if(m_instance == NULL){
		m_instance = new DataProxy();
		if(m_instance && m_instance->init()){
			m_instance->retain();
		}else{
			CC_SAFE_DELETE(m_instance);
			m_instance = NULL;
		}
	}
	return m_instance;
}

bool DataProxy::init(){

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