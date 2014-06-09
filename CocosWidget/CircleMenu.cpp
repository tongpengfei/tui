#include "CircleMenu.h"
#include <algorithm>

NS_CC_WIDGET_BEGIN

CircleMenu::CircleMenu()
:m_isMouseDown(false)
, m_mouseMove(0.25f)
, m_vx(0)
, m_maxVx(25)
, m_easing(0.95f)
, m_itemScaleA(20)
, m_itemScaleB(50)
, m_noFocusOpacity(0.6f)
{
	setThisObject(this);
	setCascadeOpacityEnabled(true);
	setAnchorPoint(CCWIDGET_BASIC_DEFAULT_ANCHOR_POINT);
}

CircleMenu* CircleMenu::create(vector<CCNode*> vet, CCSize contentSize)
{
	CircleMenu *pRet = new CircleMenu();
	if (pRet && pRet->init(vet, contentSize)){
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CircleMenu* CircleMenu::create(CCSize contentSize)
{
	CircleMenu *pRet = new CircleMenu();
	if (pRet && pRet->init(contentSize)){
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CircleMenu::init(vector<CCNode*> vet, CCSize contentSize)
{
	this->setContentSize(contentSize);
	int length = vet.size();
	for (int i = 0; i < length; i++)
	{
		CCNode *node = vet.at(i);
		float angel = (i + 1) * (360 / length);
		node->setUserData(new float(angel));
		this->addChild(node);
	}

	unscheduleUpdate();
	scheduleUpdate();
	return true;
}	

bool CircleMenu::init(CCSize contentSize)
{
	this->setContentSize(contentSize);
	return true;
}

void CircleMenu::reloadData()
{
	CCArray* arr = this->getChildren();
	int length = arr->count();
	for (int i = 0; i < length; i++)
	{
		CCNode *node = dynamic_cast<CCNode*>(arr->objectAtIndex(i));
		float angel = (i + 1) * (360 / length);
		node->setUserData(new float(angel));
	}

	unscheduleUpdate();
	scheduleUpdate();
}

void CircleMenu::update(float dt)
{
	if (m_isMouseDown){
		m_vx = (m_nowPoint.x - m_prePoint.x) * m_mouseMove;
		if (m_vx > m_maxVx){
			m_vx = m_maxVx;
		}
		if (m_vx < -m_maxVx){
			m_vx = -m_maxVx;
		}
		m_prePoint = m_nowPoint;
	}
	else{
		m_vx *= m_easing;
		if (abs(m_vx) < 0.5) m_vx = 0;
	}

	CCArray* arr = this->getChildren();
	int length = arr->count();
	for (int i = 0; i < length; i++)
	{
		CCNode* node = dynamic_cast<CCNode*>(arr->objectAtIndex(i));
		float *angel = static_cast<float*>(node->getUserData());
		(*angel) += m_vx;
		
		float angelValue = (*angel);
		if (angelValue > 360){
			angelValue -= 360;
		}
		else if (angelValue < -360){
			angelValue += 360;
		}

		CCSize size = this->getContentSize();
		node->setScale(0.3f + ((m_itemScaleA + m_itemScaleB * sin(CC_DEGREES_TO_RADIANS(angelValue)) / length) * 0.05f));
		node->setPositionX(size.width / 2 - cos(CC_DEGREES_TO_RADIANS(angelValue)) * size.width / 2);
		node->setPositionY(size.height / 2);
	}

	vector<CCNode*> vet;
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(arr, pObj){
		CCNode* node = dynamic_cast<CCNode*>(pObj);
		vet.push_back(node);
	}

	sort(vet.begin(), vet.end(), CircleMenu::sortOnDepth);
	
	for (int i = length-1; i >=0; i--)
	{
		CCNode *pChild = vet.at(i);
		float opacity = i == length - 1 ? 1 : m_noFocusOpacity;
		//pChild->setOpacity((GLubyte)255 * opacity);
		pChild->setZOrder(i);
	}
}

bool CircleMenu::sortOnDepth(CCNode* itemA, CCNode* itemB)
{
	return (itemA->getScaleX() < itemB->getScaleX());
}

CWidgetTouchModel CircleMenu::onTouchBegan(CCTouch *touch)
{
	m_isMouseDown = true;
	m_prePoint = touch->getLocation();
	m_nowPoint = touch->getLocation();

	return eWidgetTouchTransient;
}

void CircleMenu::onTouchEnded(CCTouch *touch, float fDuration)
{
	m_isMouseDown = false;
	
	CCArray* arr = this->getChildren();
	int length = arr->count();
	CCNode *pChild = nullptr;
	for (int j = 0; j < length; j++){
		pChild = ((CCNode*)arr->objectAtIndex(j));
		if (pChild->getZOrder() == length - 1){
			break;
		}
	}
	if (pChild->boundingBox().containsPoint(convertToNodeSpace(touch->getLocation()))){
		executeClickHandler(pChild);
	}
}

void CircleMenu::onTouchMoved(CCTouch *touch, float fDuration)
{
	m_nowPoint = touch->getLocation();
}

NS_CC_WIDGET_END