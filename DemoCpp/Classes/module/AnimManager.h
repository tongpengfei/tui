#ifndef __ANIM_MANAGER_H__
#define __ANIM_MANAGER_H__

#include "domain/character/CharacterBase.h"

#include "tui/TuiBase.h"
#include "tui/tuiTagMap.h"

class AnimManager : public CCObject
{
public:
	CREATE_FUNC(AnimManager);
	virtual bool init();

	~AnimManager();

	void showLoading(TuiBase* tuiBase,int tagPanel);
	void showEntrance(CCNode* panel,CCNode* pos);
	void addChildInTool(CCArray* arrWeapon,CCArray* arrMedicine,CCArray* arrProp,CCNode* panel,
						CCPoint baseP1,CCPoint baseP2,CCPoint baseP3);
	void resetPlaceTool(CCArray* arr,CCPoint p);

	void moveOffsetToBg(CCNode *bg,float offsetX,float offsetY);//±³¾°Æ«ÒÆ
	void moveOffsetToMonstorPool(CCArray *pool);//¹ÖÎïÆ«ÒÆ
	void moveOffsetToEntrance(CCNode *entrance);//Èë¿ÚÆ«ÒÆ
	

	void toggleTool(CCNode *panel);

	void renderList(TuiBase* pScene,SEL_ClickHandler clickHandler,const char* type,int length);
protected:
	CCPoint m_offsetPos;
private:
	bool m_bToggleTool;
	
};

#endif