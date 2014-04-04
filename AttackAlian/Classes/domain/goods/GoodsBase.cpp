#include "GoodsBase.h"
GoodsBase::GoodsBase()
:m_icon(NULL)
{
}

bool GoodsBase::init(){
	if(!CLayout::init()) return false;

	setContentSize(CCSize(60,60));
	return true;
}

void GoodsBase::render(){
	if(m_icon != NULL) m_icon->removeFromParent();
	std::string imgTypeStr;
	GET_GOODSTRTYPE(m_type,imgTypeStr);
	CCString *str = CCString::createWithFormat("res_iphone/store/img_%s%d.png",imgTypeStr.c_str(),m_id);
	m_icon = CImageView::create(str->getCString());
	CCSize parentSize = getContentSize();
	m_icon->setPosition(ccp(parentSize.width/2,parentSize.height/2));
	this->addChild(m_icon);
}

CWidgetTouchModel GoodsBase::onTouchBegan(CCTouch* pTouch){
	CCMsgManager::sharedManager()->PostMessage(curScene,this);
	return CLayout::onTouchBegan(pTouch);
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void GoodsBase::setData(int id,int type){
	m_type = type;
	switch(type){
	case TYPE_WEAPON:
		m_cost = id * COST_BASE_WEAPON;
		break;
	case TYPE_MEDICINE:
		m_cost = id * COST_BASE_MEDICINE;
		break;
	case TYPE_PROP:
		m_cost = id * COST_BASE_PROP;
		break;
	}
	setId(id);//¡Ù∏¯≈……˙¿‡∏≤∏«
}

void GoodsBase::setId(int id){
	m_id = id;
	render();
}

void GoodsBase::setType(int type){
	m_type = type;
	render();
}

void GoodsBase::setCost(int cost){
	m_cost = cost;
}

int GoodsBase::getCost(){
	return m_cost;
}

int GoodsBase::getType(){
	return m_type;
}

int GoodsBase::getId(){
	return m_id;
}