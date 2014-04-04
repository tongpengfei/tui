#ifndef __GOODS_H__
#define __GOODS_H__

#include "cocos2d.h"
#include "domain/config.h"
#include "../../CocosWidget/cocos-widget.h"
#include "../../CocosBase/cocos-base.h"
using namespace cocos2d::cocoswidget;
USING_NS_CC;

#define GET_GOODSTRTYPE(__type__,__str__)	\
switch(__type__){							\
case TYPE_WEAPON:							\
	__str__ = "weapon";						\
	break;									\
case TYPE_MEDICINE:							\
	__str__ = "medicine";					\
	break;									\
case TYPE_PROP:								\
	__str__ = "prop";						\
	break;									\
}											\

class GoodsBase : public CLayout
{
public:
	virtual bool init();
	CREATE_FUNC(GoodsBase);

	GoodsBase();

	virtual CWidgetTouchModel onTouchBegan(CCTouch* pTouch);//发送消息 中转给场景

	void setData(int id,int type);
	void setCost(int cost);
	void setType(int type);
	virtual void setId(int id);
	int getCost();
	int getType();
	int getId();
	
	int curScene;//记录当前所在的场景
protected:
	int m_cost;
	int m_id;
	int m_type;
	CImageView* m_icon;
private:
	void render();//渲染
};
#endif