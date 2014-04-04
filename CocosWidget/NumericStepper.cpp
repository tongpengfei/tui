#include "NumericStepper.h"

NS_CC_WIDGET_BEGIN

NumericStepper::NumericStepper()
:m_value(15)
,m_step(1)
{
	setThisObject(this);
	setCascadeOpacityEnabled(true);
	setAnchorPoint(CCWIDGET_BASIC_DEFAULT_ANCHOR_POINT);
}

NumericStepper *NumericStepper::create(const char *lnormal,const char *lselet,const char *ldisable, 
									   const char *rnormal,const char *rselet,const char *rdisable,const char* bg)
{
	 NumericStepper *numericStepper = new NumericStepper();
	if (numericStepper && numericStepper->init(lnormal,lselet,ldisable,rnormal,rselet,rdisable,bg))
	{
		numericStepper->autorelease();
		return numericStepper;
	}
	CC_SAFE_DELETE(numericStepper);
	return NULL;
}

NumericStepper* NumericStepper::create()
{
	NumericStepper* pRet = new NumericStepper();
	if( pRet && pRet->init() )
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool NumericStepper::init(){
	
	m_btnLeft = CButton::create();
	m_btnRight = CButton::create();
	m_bg = CImageView::create();
	m_labNum = CLabel::create("15","",m_bg->getContentSize().height-2,m_bg->getContentSize(),kCCTextAlignmentCenter);

	m_btnLeft->setOnClickListener(this,ccw_click_selector(NumericStepper::event_btn_left));
	m_btnRight->setOnClickListener(this,ccw_click_selector(NumericStepper::event_btn_right));

	this->addChild(m_btnLeft);
	this->addChild(m_btnRight);
	this->addChild(m_bg);
	this->addChild(m_labNum);
	return true;
}

bool NumericStepper::init(const char *lnormal,const char *lselet,const char *ldisable, 
						  const char *rnormal,const char *rselet,const char *rdisable,const char* bg){

	m_btnLeft = CButton::create(lnormal,lselet,ldisable);
	m_btnRight = CButton::create(rnormal,rselet,rdisable);
	m_bg = CImageView::create(bg);
	m_labNum = CLabel::create("15","",m_bg->getContentSize().height-2,m_bg->getContentSize(),kCCTextAlignmentCenter);

	
	m_btnLeft->setOnClickListener(this,ccw_click_selector(NumericStepper::event_btn_left));
	m_btnRight->setOnClickListener(this,ccw_click_selector(NumericStepper::event_btn_right));

	this->addChild(m_btnLeft);
	this->addChild(m_btnRight);
	this->addChild(m_bg);
	this->addChild(m_labNum);
	resetSelf();
	return true;
}


void NumericStepper::setlNormalSpriteFrameName( const char* pSpriteName ){
	m_btnLeft->setNormalSpriteFrameName(pSpriteName);
	resetSelf();
}

void NumericStepper::setlSelectedSpriteFrameName( const char* pSpriteName ){
	m_btnLeft->setSelectedSpriteFrameName(pSpriteName);
	resetSelf();
}

void NumericStepper::setlDisabledSpriteFrameName(const char* pSpriteName){
	m_btnLeft->setDisabledSpriteFrameName(pSpriteName);
	resetSelf();
}

void NumericStepper::setrNormalSpriteFrameName(const char* pSpriteName){
	m_btnRight->setNormalSpriteFrameName(pSpriteName);
	resetSelf();
}

void NumericStepper::setrSelectedSpriteFrameName(const char* pSpriteName){
	m_btnRight->setSelectedSpriteFrameName(pSpriteName);
	resetSelf();
}

void NumericStepper::setrDisabledSpriteFrameName(const char* pSpriteName){
	m_btnRight->setDisabledSpriteFrameName(pSpriteName);
	resetSelf();
}

void NumericStepper::setStepBgSpriteFrameName(const char* pSpriteName){
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pSpriteName);
	m_bg->setDisplayFrame(pFrame);
	m_labNum->setFontSize(m_bg->getContentSize().height-2);//字体大小根据stepBg的高度而变化
	resetSelf();
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

void NumericStepper::resetSelf(){
	CLayout::setContentSize(CCSize(m_btnLeft->getContentSize().width+m_bg->getContentSize().width+m_btnRight->getContentSize().width,
		m_bg->getContentSize().height));

	m_btnLeft->setPosition(m_btnLeft->getContentSize().width/2,m_btnLeft->getContentSize().height/2);
	m_bg->setPosition(ccp(m_btnLeft->getPositionX()+m_btnLeft->getContentSize().width/2+m_bg->getContentSize().width/2,
		m_btnLeft->getPositionY()));
	m_labNum->setPosition(m_bg->getPosition());
	m_btnRight->setPosition((m_bg->getPositionX()+m_bg->getContentSize().width/2+m_btnRight->getContentSize().width/2),m_btnLeft->getPositionY());
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