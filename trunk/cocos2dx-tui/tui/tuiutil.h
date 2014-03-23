#ifndef TUIUTIL_H
#define TUIUTIL_H

#include "cocos2d.h"
USING_NS_CC;

class TuiUtil
{
public:
	static float convertx( float x );
	static float converty( float y );

	static float convertTuiX( float x );
	static float convertTuiY( float y );
};

#endif//TUIUTIL_H
