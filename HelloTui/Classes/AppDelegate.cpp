#include "AppDelegate.h"
#include "MyFirstTui.h"
#include "MySecondTui.h"
#include "MyThirdui.h"
#include "tui/TuiManager.h"
#include "MyFourthTui.h"

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

	//×¢²á³¡¾°
	REGISTER_SCENE_FUNC(MyFirstTui);
	REGISTER_SCENE_FUNC(MySecondTui);
	REGISTER_SCENE_FUNC(MyThirdui);
	REGISTER_SCENE_FUNC(MyFourthTui);
    // run
	CCSceneManager::sharedManager()->runWithScene(LoadScene("MyThirdui"));

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
