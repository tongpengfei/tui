#include "domain/goods/Weapon.h"

bool Weapon::init(){
	if(!GoodsBase::init()) return false;

	return true;
}
/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void Weapon::setId(int id){
	m_powerLength = id == 3 ? 170 : WEAPON_BASE_POWERLENGTH + int(id/4) * 70;//3∫≈Œ‰∆˜ «Ãÿ ‚Œ‰∆˜
	m_attackValue = WEAPON_BASE_ATTACTVALUE + (id-1) * 20;

	GoodsBase::setId(id);
}

int Weapon::getPowerLength(){
	return m_powerLength;
}

int Weapon::getAttackValue(){
	return m_attackValue;
}
