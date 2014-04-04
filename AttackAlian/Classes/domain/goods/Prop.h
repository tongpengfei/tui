#ifndef __PROP_H__
#define __PROP_H__

#include "domain/goods/GoodsBase.h"

class Prop : public GoodsBase
{
public:
	CREATE_FUNC(Prop);
	virtual bool init();

	void setId(int id);
protected:
private:
};
#endif