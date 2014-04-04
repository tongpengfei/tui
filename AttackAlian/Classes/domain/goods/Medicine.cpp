#include "domain/goods/Medicine.h"

bool Medicine::init(){
	if(!GoodsBase::init()) return false;

	return true;
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void Medicine::setId(int id){
	m_resumeLength = MEDICINE_BASE_RESUMELENGTH + (id-1) * 20;

	GoodsBase::setId(id);
}

int Medicine::getResumeLength(){
	return m_resumeLength;
}