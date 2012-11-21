#include "AppDelegate.h"
#include "HelloWorldScene.h"
//#include <tuimanager.h>
#include <gameuicontroller.h>
#include <tuilocalization.h>

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();

    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
//	TuiLocalization::I()->setLocalization( "zh-Hans" );
	GameUIController* uic = GameUIController::I();
	uic->loadTuiXML( "tui.xml" );
	bool retina = uic->isRetina();

    TargetPlatform target = getTargetPlatform();
    
    if (target == kTargetIpad){
        // ipad
        
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        
        // don't enable retina because we don't have ipad hd resource
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960, 640, kResolutionNoBorder);
    }else if (target == kTargetIphone){
        // iphone
        // try to enable retina on device
        if ( retina && true == CCDirector::sharedDirector()->enableRetinaDisplay(true) ){
            // iphone hd
            CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        }else{
            CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
        }
    }else{
        // android, windows, blackberry, linux or mac
        // use 960*640 resources as design resolution size
//        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960, 640, kResolutionNoBorder);
//        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(320, 480, kResolutionNoBorder);
		int w = uic->schemeWidth();
		int h = uic->schemeHeight();
		if( retina ){
			CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
		}else{
			CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
		}
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(w, h, kResolutionNoBorder);
    }

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	pDirector->enableRetinaDisplay( retina );

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

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
