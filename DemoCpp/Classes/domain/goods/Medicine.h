#ifndef __MEDICINE_H__
#define __MEDICINE_H__

#include "domain/goods/GoodsBase.h"

class Medicine : public GoodsBase
{
public:
	CREATE_FUNC(Medicine);
	virtual bool init();
	
	int getResumeLength();
	void setId(int id);
protected:
	int m_resumeLength;
private:
};
#endif