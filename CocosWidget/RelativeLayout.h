#ifndef __RELATIVELAYOUT_H__
#define __RELATIVELAYOUT_H__
#include "cocos2d.h"
#include "WidgetWindow.h"

NS_CC_WIDGET_BEGIN

class RelativeLayout : public CWidgetWindow
{
public:
	RelativeLayout();
	virtual ~RelativeLayout();
	
	static RelativeLayout* create();
	static RelativeLayout* create(const CCSize& tContentSize);
	virtual void setContentSize(const CCSize& tContentSize);

protected:
private:
};

NS_CC_WIDGET_END

#endif