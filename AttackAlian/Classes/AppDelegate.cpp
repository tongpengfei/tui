#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "../../CocosBase/cocos-base.h"

#include "gameui/welcome/Welcomeui.h"
#include "gameui/ingame/Ingameui.h"
#include "gameui/ingame/dialog/Resuleui.h"
#include "gameui/option/Optionui.h"
#include "gameui/store/Storeui.h"
#include "gameui/level/Levelui.h"

#include "tui/TuiManager.h"

using namespace CocosDenshion;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
	
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	//ÅäÖÃ½çÃæ
	TuiManager::sharedManager()->loadXml("tui/480x800.xml");
	CCSize screenSize = TuiManager::sharedManager()->getScreen();
	
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(screenSize.width, screenSize.height, 
		kResolutionNoBorder); 

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	//register scene
	REGISTER_SCENE_FUNC(Ingameui);
	REGISTER_SCENE_FUNC(Optionui);
	REGISTER_SCENE_FUNC(Welcomeui);
	REGISTER_SCENE_FUNC(Storeui);
	REGISTER_SCENE_FUNC(Resuleui);
	REGISTER_SCENE_FUNC(Levelui);

    // run
	CCSceneManager::sharedManager()->runWithScene(LoadScene("Welcomeui"));

	//²¥·Å±³¾°ÒôÀÖ
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/musicBg.mp3",true);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
