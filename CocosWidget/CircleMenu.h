#ifndef __CIRECLE_MENU__	
#define __CIRECLE_MENU__

#include "Layout.h"

using namespace std;

NS_CC_WIDGET_BEGIN

class CircleMenu : public CLayout, public CClickableProtocol
{
public:
	CircleMenu();
	static CircleMenu* create(vector<CCNode*> vet, CCSize contentSize);
	virtual bool init(vector<CCNode*> vet, CCSize contentSize);

	static CircleMenu* create(CCSize contentSize);
	virtual bool init(CCSize contentSize);
	void reloadData();

	virtual CWidgetTouchModel onTouchBegan(CCTouch* pTouch);
	virtual void onTouchMoved(CCTouch* pTouch, float fDuration);
	virtual void onTouchEnded(CCTouch* pTouch, float fDuration);

	void update(float dt);

	CC_SYNTHESIZE(float, m_noFocusOpacity, NoFocusOpacity);
	CC_SYNTHESIZE(float, m_itemScaleA, ItemScaleA);
	CC_SYNTHESIZE(float, m_itemScaleB, ItemScaleB);

protected:
	static bool sortOnDepth(CCNode* itemA, CCNode* itemB);

private:
	bool m_isMouseDown;
	float m_vx;
	float m_maxVx;
	float m_mouseMove;
	float m_easing;
	CCPoint m_prePoint;
	CCPoint m_nowPoint;
};

NS_CC_WIDGET_END

#endif