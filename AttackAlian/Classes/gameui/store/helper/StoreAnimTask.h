#ifndef __ANIM_STORE_MANAGER_H__
#define __ANIM_STORE_MANAGER_H__

#include "domain/character/CharacterBase.h"

#include "tui/TuiManager.h"
#include "domain/goods/GoodsBase.h"
#include "tui/TuiBase.h"
#include "tui/tuiTagMap.h"

class StoreAnim : public CCObject
{
public:
	CREATE_FUNC(StoreAnim);
	virtual bool init();

	void renderList(TuiBase* pScene,SEL_ClickHandler clickHandler,const char* type,int length);
private:
};

#endif