//
//  tmenuitemimage.cpp
//
//  Created by tpf on 12-8-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <macro.h>
#include <tmenuitemimage.h>

CCMenuItemImage* TMenuItemImage::create(const char *img, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItemImage *pRet = new TMenuItemImage();
    CCTexture2D* ptex = CCTextureCache::sharedTextureCache()->addImage( img );
    int tw = ptex->getContentSize().width / 4;
    int th = ptex->getContentSize().height;
    CCNode* normal = CCSprite::createWithTexture( ptex, CCRect(0, 0, tw, th ) );
	CCNode *selected = CCSprite::createWithTexture(ptex, CCRect( tw*2, 0, tw, th) );
	CCNode *disabled = CCSprite::createWithTexture( ptex, CCRect( tw*3, 0, tw, th) );
    pRet->initWithNormalSprite(normal, selected, disabled, target, selector);
    pRet->autorelease();
    return pRet;
}

void TMenuItemImage::setEventClick( const char* v )
{
	tAssertc( v, return );
	strncpy( event_click, v, sizeof( event_click ) );
}
