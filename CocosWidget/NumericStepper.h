#ifndef __NUMERICSTEPPER_H__
#define __NUMERICSTEPPER_H__
#include "cocos2d.h"
#include "Layout.h"
#include "Button.h"
#include "Label.h"
#include "ImageView.h"

NS_CC_WIDGET_BEGIN

class NumericStepper : public CLayout, public CValueChangeableProtocol
{
public:
	NumericStepper();
	virtual bool init();
	virtual bool init(const char *lnormal,const char *lselet,const char *ldisable,
						const char *rnormal,const char *rselet,const char *rdisable,const char* bg);

	static NumericStepper *create();
	static NumericStepper *create(const char *lnormal,const char *lselet,const char *ldisable,
									const char *rnormal,const char *rselet,const char *rdisable,const char* bg);

	virtual void setlNormalSpriteFrameName(const char* pSpriteName);
	virtual void setlSelectedSpriteFrameName(const char* pSpriteName);
	virtual void setlDisabledSpriteFrameName(const char* pSpriteName);
	
	virtual void setrNormalSpriteFrameName(const char* pSpriteName);
	virtual void setrSelectedSpriteFrameName(const char* pSpriteName);
	virtual void setrDisabledSpriteFrameName(const char* pSpriteName);

	virtual void setStepBgSpriteFrameName(const char* pSpriteName);

	virtual CWidgetTouchModel onTouchBegan(CCTouch* pTouch);
	void onTouchEnded(CCTouch* pTouch, float fDuration);
	void onTouchMoved(CCTouch* pTouch, float fDuration);
	void onTouchCancelled(CCTouch* pTouch, float fDuration);

	void setValue(int v);
	int getValue();
	void setStep(int v);
	int getStep();
private:
	void resetSelf();//���������ڲ��ռ������ͳߴ�
protected:
	CButton* m_btnLeft;
	CButton* m_btnRight;
	CLabel* m_labNum;
	CImageView* m_bg;

	void event_btn_left(CCObject* s);
	void event_btn_right(CCObject* s);
private:
	int m_value;
	int m_step;
};

NS_CC_WIDGET_END

#endif