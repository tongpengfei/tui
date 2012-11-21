#include "HelloWorldScene.h"
#include <tui.h>
#include <tuimanager.h>
#include <gameuicontroller.h>

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	GameUIController* uic = GameUIController::I();
	uic->showTui( "panel_fuck" );
//	uic->showTui( "panel_level" );
//	uic->showTui( "panel_result" );
//	uic->closeTui( "panel_result" );
//	uic->hideTui( "panel_result" );
//	uic->showTui( "panel_result" );

    // add layer as a child to scene
    scene->addChild(uic);

    // return the scene
    return scene;
}
