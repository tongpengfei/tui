//
//  tmenuitemimage.h
//
//  Created by tpf on 12-8-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef TMENUITEMIMAGE_H
#define TMENUITEMIMAGE_H

#include "cocos2d.h"
USING_NS_CC;

/**
 @class TMenuItemImage
 @brief show a button with a image, the image include 4 button state:
 		normal, highlight, selected, disable
 */
class TMenuItemImage : public CCMenuItemImage
{
public:
    static CCMenuItemImage* create(const char *img, CCObject* target, SEL_MenuHandler selector);

	/** what event id will send if the button clicked */
	void setEventClick( const char* v );
	const char* eventClick() { return event_click; }
protected:
	char event_click[64];
};

#endif//TMENUITEMIMAGE_H
