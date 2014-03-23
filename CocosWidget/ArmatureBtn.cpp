#include "ArmatureBtn.h"

NS_CC_WIDGET_BEGIN

ArmatureBtn::ArmatureBtn()
:m_speed(150)
{
	setThisObject(this);
	setCascadeOpacityEnabled(true);
}

ArmatureBtn *ArmatureBtn::create(const char *name)
{
	ArmatureBtn *pArmatureBtn = new ArmatureBtn();
	if (pArmatureBtn && pArmatureBtn->init(name))
	{
		pArmatureBtn->autorelease();
		pArmatureBtn->getAnimation()->play("normal",0,150,1);
		return pArmatureBtn;
	}
	CC_SAFE_DELETE(pArmatureBtn);
	return NULL;
}

CWidgetTouchModel ArmatureBtn::onTouchBegan(CCTouch *pTouch)
{
	this->getAnimation()->play("select");
	return eWidgetTouchTransient;
}

void ArmatureBtn::onTouchEnded(CCTouch *pTouch, float fDuration)
{
	CCPoint touchPointInView = m_pParent->convertToNodeSpace(pTouch->getLocation());
	if( boundingBox().containsPoint(touchPointInView) )
	{
		executeClickHandler(this);
	}
	this->getAnimation()->play("normal",0,m_speed,1);
}
/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void ArmatureBtn::setSpeed(int v){
	if(m_speed == v) return;
	m_speed = v;
}

int ArmatureBtn::getSpeed(){
	return m_speed;
}

NS_CC_WIDGET_END