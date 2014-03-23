#ifndef __STORE_UI_H__
#define __STORE_UI_H__

#include "tui/TuiBase.h"
#include "tui/TuiManager.h"
#include "module/AnimManager.h"
#include "module/GameController.h"
#include "domain/goods/GoodsBase.h"
#include "domain/goods/Weapon.h"
#include "domain/goods/Medicine.h"
#include "domain/goods/Prop.h"
//¹ºÂòÉÌÆ·
#define BUG_GOODS(__goods__,__array__,__basePosId__)												\
	if(__array__->count() > 4) return;																\
	CCObject *obj = NULL;																			\
	CCARRAY_FOREACH(__array__,obj){																	\
	GoodsBase* item = (GoodsBase*)obj;																\
		if(item->getId() == id) return;															\
	}																								\
	__goods__->curScene = SCENE_STORE;																\
	__goods__->setData(id,m_type);																	\
	panel->addChild(__goods__);																		\
	__array__->addObject(__goods__);																\
	CCPoint basePos = getControl(PANEL_STORE_TOOL,__basePosId__)->getPosition();					\
	m_animManager->resetPlaceTool(__array__,basePos);												\
	setCoin(getCoin() - __goods__->getCost());														\

class Storeui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Storeui);
	Storeui();
	~Storeui();

	virtual void onLoadResources();
	virtual void onLoadScene();

	CCNode* getPanel(int tagPanel);
protected:
	void event_btn_menu(CCObject* s);
	void event_btn_launch(CCObject* s);

	void event_toggle(CCObject* pSender, bool bChecked);
	void event_btn_pay(CCObject* s);

	inline void setCoin(int v);
	inline int getCoin();
private:
	AnimManager* m_animManager;

	CCArray* m_arrWeapon;
	CCArray* m_arrMedicine;
	CCArray* m_arrProp;
	
	int m_type;
	int m_coin;
};

#endif