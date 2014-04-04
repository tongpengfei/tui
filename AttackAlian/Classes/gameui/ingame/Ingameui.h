#ifndef __UI_INGAME_H__
#define __UI_INGAME_H__

#include "tui/TuiBase.h"
#include "tui/TuiManager.h"
#include "domain/goods/GoodsBase.h"
#include "domain/goods/Weapon.h"
#include "domain/goods/Medicine.h"
#include "domain/goods/Prop.h"
#include "domain/character/Hero.h"
#include "domain/character/Monstor.h"
#include "gameui/ingame/helper/MonstorMgr.h"
#include "gameui/ingame/helper/LevelHelper.h"
#include "gameui/ingame/helper/IngameAnimTask.h"
#include "gameui/welcome/Welcomeui.h"
#include "gameui/common/helper/CommonAnimTask.h"
#include "module/DataProxy.h"

class Ingameui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(Ingameui);
	Ingameui();
	~Ingameui();
	virtual void onLoadResources();
	virtual void onLoadScene();
	virtual void update(float delta);

	CCNode* getPanel(int tagPanel);
	Hero* getHero();
protected:
	void event_btn_fire(CCObject* s);
	void event_btn_tool(CCObject* s);
	void event_on_move(CCObject* pSender, float fx, float fy);
	
	void excuteEndGame(float dt);

	void onMessage(unsigned int uMsg, CCObject* pMsgObj, void* wParam, void* lParam);
private:
	Hero *m_pHero;
	MonstorMgr* m_monstorManager;
	IngameAnimTask* m_ingameAnim;
	CommonAnimTask* m_commAnim;//通用动画逻辑

	LevelMgr* m_levelManager;
	CCNode *m_BgMap;
	float m_speed;
	int m_curLevel;//当前游戏关卡

	CCArray* m_arrWeapon;//工具栏 武器
	CCArray* m_arrMedicine;//药水
	CCArray* m_arrProp;//道具
};
#endif