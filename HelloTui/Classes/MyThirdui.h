#ifndef __MYTHIRD_UI__
#define __MYTHIRD_UI__

#include "tui/TuiBase.h"
#include "tui/TuiManager.h"

class MyThirdui : public TuiBase
{
public:
	CREATE_SCENE_FUNC(MyThirdui);
	virtual void onLoadScene();

protected:
private:
};

#endif