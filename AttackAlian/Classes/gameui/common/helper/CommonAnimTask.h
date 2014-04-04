#ifndef __COMMON_ANIM__
#define __COMMON_ANIM__

#include "domain/character/CharacterBase.h"
#include "domain/character/Boss.h"
#include "domain/goods/GoodsBase.h"
#include "tui/TuiManager.h"
#include "tui/TuiBase.h"

class CommonAnimTask : public CCObject
{
public:
	CREATE_FUNC(CommonAnimTask);
	virtual bool init();

	//添加装备进工具栏
	void addChildInTool(CCArray* arrWeapon,CCArray* arrMedicine,CCArray* arrProp,CCNode* panel,CCPoint baseP1,CCPoint baseP2,CCPoint baseP3);
	//在工具栏放置道具
	void resetPlaceTool(CCArray* arr,CCPoint p);
	//展示loading
	void showLoading(TuiBase* tuiBase,int tagPanel);

protected:
private:
};

#endif