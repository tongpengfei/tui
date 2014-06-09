#include "ResoureMgr.h"

#include "scene/Main/Mainui.h"
#include "scene/Main/dialog/MessageBox.h"


bool ResoureMgr::init(){
	return true;
}

void ResoureMgr::registScene(){

	REGISTER_SCENE_FUNC(Main::Mainui);						//主界面
	REGISTER_SCENE_FUNC(Main::MessageBox);					//消息框

}