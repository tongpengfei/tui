#include "HelloWorldScene.h"
#include <tui.h>
#include <tuimanager.h>
#include <gameuicontroller.h>
#include <gameuievent.h>

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	GameUIController* uic = GameUIController::I();
	uic->showTui( s_t_panel_start );

    // add layer as a child to scene
    scene->addChild(uic);

    // return the scene
    return scene;
}
