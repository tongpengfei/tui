﻿#include "ResoureMgr.h"

#include "scene/Main/Mainui.h"
#include "scene/Main/dialog/MsgBox.h"
#include "scene/Store/Storeui.h"
#include "scene/ShowPhone/ShowPhoneui.h"
#include "scene/Bag/Bagui.h"
#include "scene/Recombine/Recombineui.h"
#include "scene/Welcome/Welcomeui.h"

bool ResoureMgr::init(){
	return true;
}

void ResoureMgr::registScene(){

	REGISTER_SCENE_FUNC(Welcome::Welcomeui);

	REGISTER_SCENE_FUNC(Main::Mainui);						//主界面
	REGISTER_SCENE_FUNC(Main::MsgBox);						//消息框

	REGISTER_SCENE_FUNC(Store::Storeui);					//商店

	REGISTER_SCENE_FUNC(ShowPhone::ShowPhoneui);			//展示场景

	REGISTER_SCENE_FUNC(Bag::Bagui);						//背包

	REGISTER_SCENE_FUNC(Recomebineui);						//复合控件

}