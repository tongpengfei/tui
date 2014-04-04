#ifndef __ANIM_INGAME_MANAGER_H__
#define __ANIM_INGAME_MANAGER_H__

#include "tui/TuiManager.h"
#include "domain/character/CharacterBase.h"
#include "domain/character/Boss.h"
#include "domain/goods/GoodsBase.h"
#include "tui/TuiBase.h"
#include "tui/tuiTagMap.h"

class IngameAnimTask : public CCObject
{
public:
	CREATE_FUNC(IngameAnimTask);
	virtual bool init();

	
	void showEntrance(CCNode* panel,CCNode* pos);
	

	void moveOffsetToBg(CCNode *bg,float offsetX,float offsetY);//±³¾°Æ«ÒÆ
	void moveOffsetToMonstorPool(CCArray *pool);//¹ÖÎïÆ«ÒÆ
	void moveOffsetToEntrance(CCNode *entrance);//Èë¿ÚÆ«ÒÆ
	
	void toggleTool(CCNode *panel);

protected:
	CCPoint m_offsetPos;
private:
	bool m_bToggleTool;
	
};

#endif