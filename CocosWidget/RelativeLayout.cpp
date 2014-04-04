#include "RelativeLayout.h"

NS_CC_WIDGET_BEGIN

RelativeLayout::RelativeLayout()
{
}

RelativeLayout::~RelativeLayout(){

}

RelativeLayout *RelativeLayout::create(){
	RelativeLayout* pRet = new RelativeLayout();
	if( pRet && pRet->init() )
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

RelativeLayout *RelativeLayout::create(const CCSize& tContentSize){
	RelativeLayout* pRet = new RelativeLayout();
	if( pRet && pRet->init() )
	{
		pRet->setContentSize(tContentSize);
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void RelativeLayout::setContentSize(const CCSize& tContentSize){

	CCSize lastSize = this->getContentSize();//未改变之前的size
	if(lastSize.width == tContentSize.width && lastSize.height == tContentSize.height) return;

	CWidgetWindow::setContentSize(tContentSize);

	if( m_pChildren && m_pChildren->count() > 0 ){

		float scaleX = tContentSize.width / lastSize.width;
		float scaleY = tContentSize.height / lastSize.height;

		CCObject* pObject = NULL;
		CCARRAY_FOREACH_REVERSE( m_pChildren, pObject )
		{
			CCNode* pNode = dynamic_cast<CCNode*>(pObject);
			float x = pNode->getPositionX() * scaleX;
			float y = pNode->getPositionY() * scaleY;

			CCLOG("child x=%f pNode->getPositionX() = %f",x,pNode->getPositionX());
			pNode->setPosition(CCPoint(x,y));
		}
	}
}

NS_CC_WIDGET_END