#include "NumericStepper.h"

NS_CC_WIDGET_BEGIN

NumericStepper::NumericStepper()
:m_value(15)
,m_step(1)
{
}

NumericStepper *NumericStepper::create(const char *lnormal,const char *lselet,const char *ldisable, 
										const char *rnormal,const char *rselet,const char *rdisable,const char* bg){
	
	NumericStepper *numericStepper = new NumericStepper();
	if (numericStepper && numericStepper->init(lnormal,lselet,ldisable,rnormal,rselet,rdisable,bg))
	{
		numericStepper->autorelease();
		return numericStepper;
	}
	CC_SAFE_DELETE(numericStepper);
	return NULL;
}

bool NumericStepper::init(const char *lnormal,const char *lselet,const char *ldisable, 
						  const char *rnormal,const char *rselet,const char *rdisable,const char* bg){

	m_btnLeft = CButton::create(lnormal,lselet,ldisable);
	m_btnRight = CButton::create(rnormal,rselet,rdisable);
	m_bg = CImageView::create(bg);
	m_labNum = CLabel::create("15","",16,m_bg->getContentSize(),kCCTextAlignmentCenter);

	m_btnLeft->setPosition(m_btnLeft->getContentSize().width/2,m_btnLeft->getContentSize().height/2);
	m_btnLeft->setOnClickListener(this,ccw_click_selector(NumericStepper::event_btn_left));
	m_bg->setPosition(ccp(m_btnLeft->getPositionX()+m_btnLeft->getContentSize().width/2+m_bg->getContentSize().width/2,
						m_btnLeft->getPositionY()));
	m_btnRight->setPosition((m_bg->getPositionX()+m_bg->getContentSize().width/2+m_btnRight->getContentSize().width/2),
						m_btnLeft->getPositionY());
	m_btnRight->setOnClickListener(this,ccw_click_selector(NumericStepper::event_btn_right));
	m_labNum->setPosition(m_bg->getPosition());

	this->addChild(m_btnLeft);
	this->addChild(m_btnRight);
	this->addChild(m_bg);
	this->addChild(m_labNum);

	setThisObject(this);
	setCascadeOpacityEnabled(true);

	this->setContentSize(CCSize(m_btnLeft->getContentSize().width+m_bg->getContentSize().width+m_btnRight->getContentSize().width,
								m_bg->getContentSize().height));
	return true;
}

CWidgetTouchModel NumericStepper::onTouchBegan(CCTouch* pTouch){

	CCPoint touchPointInView = this->convertToNodeSpace(pTouch->getLocation());
	if(m_btnLeft->boundingBox().containsPoint(touchPointInView)){
		m_btnLeft->onTouchBegan(pTouch);
	}else if(m_btnRight->boundingBox().containsPoint(touchPointInView)){
		m_btnRight->onTouchBegan(pTouch);
	}
	return eWidgetTouchTransient;
}

void NumericStepper::onTouchEnded(CCTouch* pTouch, float fDuration){

	CCPoint touchPointInView = this->convertToNodeSpace(pTouch->getLocation());
	if(m_btnLeft->boundingBox().containsPoint(touchPointInView)){
		m_btnLeft->onTouchEnded(pTouch,fDuration);
	}else if(m_btnRight->boundingBox().containsPoint(touchPointInView)){
		m_btnRight->onTouchEnded(pTouch,fDuration);
	}
}

void NumericStepper::onTouchMoved(CCTouch* pTouch, float fDuration){

	CCPoint touchPointInView = this->convertToNodeSpace(pTouch->getLocation());
	m_btnLeft->onTouchMoved(pTouch,fDuration);
	m_btnRight->onTouchMoved(pTouch,fDuration);
}

void NumericStepper::onTouchCancelled(CCTouch* pTouch, float fDuration){

	CCPoint touchPointInView = this->convertToNodeSpace(pTouch->getLocation());
	m_btnLeft->onTouchCancelled(pTouch,fDuration);
	m_btnRight->onTouchCancelled(pTouch,fDuration);
}

void NumericStepper::event_btn_left(CCObject* s){
	setValue(m_value - m_step);
}

void NumericStepper::event_btn_right(CCObject* s){
	setValue(m_value + m_step);
}
/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void NumericStepper::setValue(int v){
	if(v == m_value) return;
	m_value = v;
	m_labNum->setString(CCString::createWithFormat("%d",m_value)->getCString());
	executeValueChangedHandler(this,m_value);
}

int NumericStepper::getValue(){
	return m_value;
}

void NumericStepper::setStep(int v){
	if(v == m_step) return;
	m_step = v;
}

int NumericStepper::getStep(){
	return m_step;
}

NS_CC_WIDGET_END