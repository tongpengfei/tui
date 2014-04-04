#include "NetWorkMgr.h"

NetWorkMgr* NetWorkMgr::m_instance = NULL;
NetWorkMgr* NetWorkMgr::sharedManager(){
	if(m_instance == NULL){
		m_instance = new NetWorkMgr();
		if(m_instance && m_instance->init()){
			m_instance->retain();
		}else{
			CC_SAFE_DELETE(m_instance);
			m_instance = NULL;
		}
	}
	return m_instance;
}

bool NetWorkMgr::init(){

	return true;
}

void NetWorkMgr::send(){
	
}