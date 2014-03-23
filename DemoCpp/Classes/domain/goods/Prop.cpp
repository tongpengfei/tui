#include "domain/goods/Prop.h"

bool Prop::init(){
	if(!GoodsBase::init()) return false;
	
	return true;
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void Prop::setId(int id){

	GoodsBase::setId(id);
}