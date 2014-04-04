#ifndef __NETWORKMGR__
#define __NETWORKMGR__

#include<Winsock2.h>
#include "cocos2d.h"
USING_NS_CC;

class NetWorkMgr : public CCObject
{
public:
	CREATE_FUNC(NetWorkMgr);
	virtual bool init();

	static NetWorkMgr* sharedManager();
	void send();
protected:
private:
	static NetWorkMgr *m_instance;
	
};

#endif