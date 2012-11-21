#include <tuiutil.h>

float TuiUtil::convertx( float x )
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float v = visibleSize.width/2.0 + origin.x + x;
	return v;
}

float TuiUtil::converty( float y )
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float v = visibleSize.height/2+ origin.y + y;
	return v;
}

float TuiUtil::convertTuiX( float x )
{
//	return convertx( x );
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float v = visibleSize.width/2.0 + origin.x + x;
	return v;
}

float TuiUtil::convertTuiY( float y )
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//float v = visibleSize.height - (visibleSize.height/2+ origin.y + y);
	float v = visibleSize.height/2+ origin.y + y;
	return v;
}
