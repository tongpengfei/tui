#ifndef __ARMATURE_BTN__
#define __ARMATURE_BTN__
#include "cocos2d.h"
#include "../extensions/cocos-ext.h"
#include "Widget.h"

using namespace cocos2d::extension;
NS_CC_WIDGET_BEGIN

class ArmatureBtn : public CCArmature, public CWidget, public CClickableProtocol
{
public:

	ArmatureBtn();
	static ArmatureBtn *create(const char *name);

	void setSpeed(int v);
	int getSpeed();
public:
	
	virtual CWidgetTouchModel onTouchBegan(CCTouch *pTouch);
	virtual void onTouchEnded(CCTouch *pTouch, float fDuration);
	
protected:
private:
	int m_speed;
};

NS_CC_WIDGET_END

#endif