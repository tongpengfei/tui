/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCSceneExTransition.h"
#include "CCSceneManager.h"

NS_CC_BEGIN

const unsigned int kSceneFade = 0xFADEFADE;

CCSceneExTransition::CCSceneExTransition()
{
}
CCSceneExTransition::~CCSceneExTransition()
{
    m_pInScene->release();
    m_pOutScene->release();
}

CCSceneExTransition * CCSceneExTransition::create(float t, CCSceneExtension *scene)
{
    CCSceneExTransition * pScene = new CCSceneExTransition();
    if(pScene && pScene->initWithDuration(t,scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

bool CCSceneExTransition::initWithDuration(float t, CCSceneExtension *scene)
{
    CCAssert( scene != NULL, "Argument scene must be non-nil");

    if (CCSceneExtension::init())
    {
        m_fDuration = t;

        // retain
        m_pInScene = scene;
        m_pInScene->retain();
		m_pOutScene = CCSceneManager::sharedManager()->getRunningScene();
        if (m_pOutScene == NULL)
        {
            m_pOutScene = new CCSceneExtension();
            m_pOutScene->init();
        }
        m_pOutScene->retain();

        CCAssert( m_pInScene != m_pOutScene, "Incoming scene must be different from the outgoing scene" );
        
        sceneOrder();

        return true;
    }
    else
    {
        return false;
    }
}

void CCSceneExTransition::sceneOrder()
{
    m_bIsInSceneOnTop = true;
}

void CCSceneExTransition::draw()
{
    CCSceneExtension::draw();

    if( m_bIsInSceneOnTop ) {
        m_pOutScene->visit();
        m_pInScene->visit();
    } else {
        m_pInScene->visit();
        m_pOutScene->visit();
    }
}

void CCSceneExTransition::finish()
{
    // clean up     
     m_pInScene->setVisible(true);
     m_pInScene->setPosition(ccp(0,0));
     m_pInScene->setScale(1.0f);
     m_pInScene->setRotation(0.0f);
     m_pInScene->getCamera()->restore();
 
     m_pOutScene->setVisible(false);
     m_pOutScene->setPosition(ccp(0,0));
     m_pOutScene->setScale(1.0f);
     m_pOutScene->setRotation(0.0f);
     m_pOutScene->getCamera()->restore();

    //[self schedule:@selector(setNewScene:) interval:0];
    this->schedule(schedule_selector(CCSceneExTransition::setNewScene), 0);

}

void CCSceneExTransition::setNewScene(float dt)
{    
    CC_UNUSED_PARAM(dt);

    this->unschedule(schedule_selector(CCSceneExTransition::setNewScene));
    
    // Before replacing, save the "send cleanup to scene"
	CCSceneManager* manager = CCSceneManager::sharedManager();
    m_bIsSendCleanupToScene = manager->isSendCleanupToScene();
    
    manager->replaceScene(m_pInScene);
    
    // issue #267
    m_pOutScene->setVisible(true);
}

void CCSceneExTransition::hideOutShowIn()
{
    m_pInScene->setVisible(true);
    m_pOutScene->setVisible(false);
}


// custom onEnter
void CCSceneExTransition::onEnter()
{
    CCSceneExtension::onEnter();
    
    // disable events while transitions
    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(false);
    
    // outScene should not receive the onEnter callback
    // only the onExitTransitionDidStart
    m_pOutScene->onExitTransitionDidStart();
    
    m_pInScene->onEnter();
}

// custom onExit
void CCSceneExTransition::onExit()
{
    CCSceneExtension::onExit();
    
    // enable events while transitions
    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
    
    m_pOutScene->onExit();

    // m_pInScene should not receive the onEnter callback
    // only the onEnterTransitionDidFinish
    m_pInScene->onEnterTransitionDidFinish();
}

// custom cleanup
void CCSceneExTransition::cleanup()
{
    CCSceneExtension::cleanup();

    if( m_bIsSendCleanupToScene )
        m_pOutScene->cleanup();
}

CCSceneExtension* CCSceneExTransition::getInScene()
{
	return m_pInScene;
}

//
// Oriented Transition
//

CCSceneExTransitionOriented::CCSceneExTransitionOriented()
{
}

CCSceneExTransitionOriented::~CCSceneExTransitionOriented()
{
}

CCSceneExTransitionOriented * CCSceneExTransitionOriented::create(float t, CCSceneExtension *scene, tOrientation orientation)
{
    CCSceneExTransitionOriented * pScene = new CCSceneExTransitionOriented();
    pScene->initWithDuration(t,scene,orientation);
    pScene->autorelease();
    return pScene;
}

bool CCSceneExTransitionOriented::initWithDuration(float t, CCSceneExtension *scene, tOrientation orientation)
{
    if ( CCSceneExTransition::initWithDuration(t, scene) )
    {
        m_eOrientation = orientation;
    }
    return true;
}

//
// RotoZoom
//
CCSceneExTransitionRotoZoom::CCSceneExTransitionRotoZoom()
{
}

CCSceneExTransitionRotoZoom* CCSceneExTransitionRotoZoom::create(float t, CCSceneExtension* scene)                   
{                                                               
    CCSceneExTransitionRotoZoom* pScene = new CCSceneExTransitionRotoZoom();                                
    if(pScene && pScene->initWithDuration(t, scene))            
    {                                                           
        pScene->autorelease();                                  
        return pScene;                                          
    }                                                           
    CC_SAFE_DELETE(pScene);                                     
    return NULL;                                                
}

CCSceneExTransitionRotoZoom::~CCSceneExTransitionRotoZoom()
{
}

void CCSceneExTransitionRotoZoom:: onEnter()
{
    CCSceneExTransition::onEnter();

    m_pInScene->setScale(0.001f);
    m_pOutScene->setScale(1.0f);

    m_pInScene->setAnchorPoint(ccp(0.5f, 0.5f));
    m_pOutScene->setAnchorPoint(ccp(0.5f, 0.5f));

    CCActionInterval *rotozoom = (CCActionInterval*)(CCSequence::create
    (
        CCSpawn::create
        (
            CCScaleBy::create(m_fDuration/2, 0.001f),
            CCRotateBy::create(m_fDuration/2, 360 * 2),
            NULL
        ),
        CCDelayTime::create(m_fDuration/2),
        NULL
    ));

    m_pOutScene->runAction(rotozoom);
    m_pInScene->runAction
    (
        CCSequence::create
        (
            rotozoom->reverse(),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
            NULL
        )
    );
}

//
// JumpZoom
//
CCSceneExTransitionJumpZoom::CCSceneExTransitionJumpZoom()
{
}
CCSceneExTransitionJumpZoom::~CCSceneExTransitionJumpZoom()
{
}

CCSceneExTransitionJumpZoom* CCSceneExTransitionJumpZoom::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionJumpZoom* pScene = new CCSceneExTransitionJumpZoom();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionJumpZoom::onEnter()
{
    CCSceneExTransition::onEnter();
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    m_pInScene->setScale(0.5f);
    m_pInScene->setPosition(ccp(s.width, 0));
    m_pInScene->setAnchorPoint(ccp(0.5f, 0.5f));
    m_pOutScene->setAnchorPoint(ccp(0.5f, 0.5f));

    CCActionInterval *jump = CCJumpBy::create(m_fDuration/4, ccp(-s.width,0), s.width/4, 2);
    CCActionInterval *scaleIn = CCScaleTo::create(m_fDuration/4, 1.0f);
    CCActionInterval *scaleOut = CCScaleTo::create(m_fDuration/4, 0.5f);

    CCActionInterval *jumpZoomOut = (CCActionInterval*)(CCSequence::create(scaleOut, jump, NULL));
    CCActionInterval *jumpZoomIn = (CCActionInterval*)(CCSequence::create(jump, scaleIn, NULL));

    CCActionInterval *delay = CCDelayTime::create(m_fDuration/2);

    m_pOutScene->runAction(jumpZoomOut);
    m_pInScene->runAction
    (
        CCSequence::create
        (
            delay,
            jumpZoomIn,
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
            NULL
        )
    );
}

//
// MoveInL
//
CCSceneExTransitionMoveInL::CCSceneExTransitionMoveInL()
{
}

CCSceneExTransitionMoveInL::~CCSceneExTransitionMoveInL()
{
}

CCSceneExTransitionMoveInL* CCSceneExTransitionMoveInL::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionMoveInL* pScene = new CCSceneExTransitionMoveInL();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionMoveInL::onEnter()
{
    CCSceneExTransition::onEnter();
    this->initScenes();

    CCActionInterval *a = this->action();

    m_pInScene->runAction
    (
        CCSequence::create
        (
            this->easeActionWithAction(a),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
            NULL
        )
    );
}
 
CCActionInterval* CCSceneExTransitionMoveInL::action()
{
    return CCMoveTo::create(m_fDuration, ccp(0,0));
}

CCActionInterval* CCSceneExTransitionMoveInL::easeActionWithAction(CCActionInterval* action)
{
    return CCEaseOut::create(action, 2.0f);
//    return [EaseElasticOut actionWithAction:action period:0.4f];
}

void CCSceneExTransitionMoveInL::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition(ccp(-s.width,0));
}

//
// MoveInR
//
CCSceneExTransitionMoveInR::CCSceneExTransitionMoveInR()
{
}
CCSceneExTransitionMoveInR::~CCSceneExTransitionMoveInR()
{
}

CCSceneExTransitionMoveInR* CCSceneExTransitionMoveInR::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionMoveInR* pScene = new CCSceneExTransitionMoveInR();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionMoveInR::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(s.width,0) );
}

//
// MoveInT
//
CCSceneExTransitionMoveInT::CCSceneExTransitionMoveInT()
{
}
CCSceneExTransitionMoveInT::~CCSceneExTransitionMoveInT()
{
}

CCSceneExTransitionMoveInT* CCSceneExTransitionMoveInT::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionMoveInT* pScene = new CCSceneExTransitionMoveInT();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionMoveInT::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(0,s.height) );
}

//
// MoveInB
//
CCSceneExTransitionMoveInB::CCSceneExTransitionMoveInB()
{
}
CCSceneExTransitionMoveInB::~CCSceneExTransitionMoveInB()
{
}

CCSceneExTransitionMoveInB* CCSceneExTransitionMoveInB::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionMoveInB* pScene = new CCSceneExTransitionMoveInB();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionMoveInB::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(0,-s.height) );
}


//
// SlideInL
//

// The adjust factor is needed to prevent issue #442
// One solution is to use DONT_RENDER_IN_SUBPIXELS images, but NO
// The other issue is that in some transitions (and I don't know why)
// the order should be reversed (In in top of Out or vice-versa).
#ifndef ADJUST_FACTOR
#define ADJUST_FACTOR 0.5f
#endif
CCSceneExTransitionSlideInL::CCSceneExTransitionSlideInL()
{
}

CCSceneExTransitionSlideInL::~CCSceneExTransitionSlideInL()
{
}

void CCSceneExTransitionSlideInL::onEnter()
{
    CCSceneExTransition::onEnter();
    this->initScenes();

    CCActionInterval *in = this->action();
    CCActionInterval *out = this->action();

    CCActionInterval* inAction = easeActionWithAction(in);
    CCActionInterval* outAction = (CCActionInterval*)CCSequence::create
    (
        easeActionWithAction(out),
        CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)), 
        NULL
    );
    m_pInScene->runAction(inAction);
    m_pOutScene->runAction(outAction);
}

void CCSceneExTransitionSlideInL::sceneOrder()
{
    m_bIsInSceneOnTop = false;
}

void CCSceneExTransitionSlideInL:: initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(-(s.width-ADJUST_FACTOR),0) );
}

CCActionInterval* CCSceneExTransitionSlideInL::action()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    return CCMoveBy::create(m_fDuration, ccp(s.width-ADJUST_FACTOR,0));
}

CCActionInterval* CCSceneExTransitionSlideInL::easeActionWithAction(CCActionInterval* action)
{
    return CCEaseOut::create(action, 2.0f);
}

CCSceneExTransitionSlideInL* CCSceneExTransitionSlideInL::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionSlideInL* pScene = new CCSceneExTransitionSlideInL();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

//
// SlideInR
//
CCSceneExTransitionSlideInR::CCSceneExTransitionSlideInR()
{
}
CCSceneExTransitionSlideInR::~CCSceneExTransitionSlideInR()
{
}

CCSceneExTransitionSlideInR* CCSceneExTransitionSlideInR::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionSlideInR* pScene = new CCSceneExTransitionSlideInR();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionSlideInR::sceneOrder()
{
    m_bIsInSceneOnTop = true;
}

void CCSceneExTransitionSlideInR::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(s.width-ADJUST_FACTOR,0) );
}


CCActionInterval* CCSceneExTransitionSlideInR:: action()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    return CCMoveBy::create(m_fDuration, ccp(-(s.width-ADJUST_FACTOR),0));
}


//
// SlideInT
//
CCSceneExTransitionSlideInT::CCSceneExTransitionSlideInT()
{
}
CCSceneExTransitionSlideInT::~CCSceneExTransitionSlideInT()
{
}

CCSceneExTransitionSlideInT* CCSceneExTransitionSlideInT::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionSlideInT* pScene = new CCSceneExTransitionSlideInT();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionSlideInT::sceneOrder()
{
    m_bIsInSceneOnTop = false;
}

void CCSceneExTransitionSlideInT::initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(0,s.height-ADJUST_FACTOR) );
}


CCActionInterval* CCSceneExTransitionSlideInT::action()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    return CCMoveBy::create(m_fDuration, ccp(0,-(s.height-ADJUST_FACTOR)));
}

//
// SlideInB
//
CCSceneExTransitionSlideInB::CCSceneExTransitionSlideInB()
{
}
CCSceneExTransitionSlideInB::~CCSceneExTransitionSlideInB()
{
}

CCSceneExTransitionSlideInB* CCSceneExTransitionSlideInB::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionSlideInB* pScene = new CCSceneExTransitionSlideInB();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionSlideInB::sceneOrder()
{
    m_bIsInSceneOnTop = true;
}

void CCSceneExTransitionSlideInB:: initScenes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pInScene->setPosition( ccp(0,-(s.height-ADJUST_FACTOR)) );
}


CCActionInterval* CCSceneExTransitionSlideInB:: action()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    return CCMoveBy::create(m_fDuration, ccp(0,s.height-ADJUST_FACTOR));
}

//
// ShrinkGrow Transition
//
CCSceneExTransitionShrinkGrow::CCSceneExTransitionShrinkGrow()
{
}
CCSceneExTransitionShrinkGrow::~CCSceneExTransitionShrinkGrow()
{
}

CCSceneExTransitionShrinkGrow* CCSceneExTransitionShrinkGrow::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionShrinkGrow* pScene = new CCSceneExTransitionShrinkGrow();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionShrinkGrow::onEnter()
{
    CCSceneExTransition::onEnter();

    m_pInScene->setScale(0.001f);
    m_pOutScene->setScale(1.0f);

    m_pInScene->setAnchorPoint(ccp(2/3.0f,0.5f));
    m_pOutScene->setAnchorPoint(ccp(1/3.0f,0.5f));    

    CCActionInterval* scaleOut = CCScaleTo::create(m_fDuration, 0.01f);
    CCActionInterval* scaleIn = CCScaleTo::create(m_fDuration, 1.0f);

    m_pInScene->runAction(this->easeActionWithAction(scaleIn));
    m_pOutScene->runAction
    (
        CCSequence::create
        (
            this->easeActionWithAction(scaleOut),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)), 
            NULL
        )
    );
}
CCActionInterval* CCSceneExTransitionShrinkGrow:: easeActionWithAction(CCActionInterval* action)
{
    return CCEaseOut::create(action, 2.0f);
//    return [EaseElasticOut actionWithAction:action period:0.3f];
}

//
// FlipX Transition
//
CCSceneExTransitionFlipX::CCSceneExTransitionFlipX()
{
}
CCSceneExTransitionFlipX::~CCSceneExTransitionFlipX()
{
}

void CCSceneExTransitionFlipX::onEnter()
{
    CCSceneExTransitionOriented::onEnter();

    CCActionInterval *inA, *outA;
    m_pInScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( m_eOrientation == kCCTransitionOrientationRightOver )
    {
        inDeltaZ = 90;
        inAngleZ = 270;
        outDeltaZ = 90;
        outAngleZ = 0;
    }
    else
    {
        inDeltaZ = -90;
        inAngleZ = 90;
        outDeltaZ = -90;
        outAngleZ = 0;
    }

    inA = (CCActionInterval*)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCShow::create(),
            CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 0, 0),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)), 
            NULL
        );

    outA = (CCActionInterval *)CCSequence::create
        (
            CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 0, 0),
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL 
        );

    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCSceneExTransitionFlipX* CCSceneExTransitionFlipX::create(float t, CCSceneExtension* s, tOrientation o)
{
    CCSceneExTransitionFlipX* pScene = new CCSceneExTransitionFlipX();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCSceneExTransitionFlipX* CCSceneExTransitionFlipX::create(float t, CCSceneExtension* s)
{
    return CCSceneExTransitionFlipX::create(t, s, kCCTransitionOrientationRightOver);
}

//
// FlipY Transition
//
CCSceneExTransitionFlipY::CCSceneExTransitionFlipY()
{
}
CCSceneExTransitionFlipY::~CCSceneExTransitionFlipY()
{
}

void CCSceneExTransitionFlipY::onEnter()
{
    CCSceneExTransitionOriented::onEnter();

    CCActionInterval *inA, *outA;
    m_pInScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( m_eOrientation == kCCTransitionOrientationUpOver ) 
    {
        inDeltaZ = 90;
        inAngleZ = 270;
        outDeltaZ = 90;
        outAngleZ = 0;
    } 
    else 
    {
        inDeltaZ = -90;
        inAngleZ = 90;
        outDeltaZ = -90;
        outAngleZ = 0;
    }

    inA = (CCActionInterval*)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCShow::create(),
            CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)), 
            NULL
        );
    outA = (CCActionInterval*)CCSequence::create
        (
            CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL
        );

    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);

}

CCSceneExTransitionFlipY* CCSceneExTransitionFlipY::create(float t, CCSceneExtension* s, tOrientation o)
{
    CCSceneExTransitionFlipY* pScene = new CCSceneExTransitionFlipY();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCSceneExTransitionFlipY* CCSceneExTransitionFlipY::create(float t, CCSceneExtension* s)
{
    return CCSceneExTransitionFlipY::create(t, s, kCCTransitionOrientationUpOver);
}

//
// FlipAngular Transition
//
CCSceneExTransitionFlipAngular::CCSceneExTransitionFlipAngular()
{
}

CCSceneExTransitionFlipAngular::~CCSceneExTransitionFlipAngular()
{
}

void CCSceneExTransitionFlipAngular::onEnter()
{
    CCSceneExTransitionOriented::onEnter();

    CCActionInterval *inA, *outA;
    m_pInScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( m_eOrientation == kCCTransitionOrientationRightOver ) 
    {
        inDeltaZ = 90;
        inAngleZ = 270;
        outDeltaZ = 90;
        outAngleZ = 0;
    } 
    else 
    {
        inDeltaZ = -90;
        inAngleZ = 90;
        outDeltaZ = -90;
        outAngleZ = 0;
    }

    inA = (CCActionInterval *)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCShow::create(),
            CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, -45, 0),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)), 
            NULL
        );
    outA = (CCActionInterval *)CCSequence::create
        (
            CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 45, 0),
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL
        );

    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCSceneExTransitionFlipAngular* CCSceneExTransitionFlipAngular::create(float t, CCSceneExtension* s, tOrientation o)
{
    CCSceneExTransitionFlipAngular* pScene = new CCSceneExTransitionFlipAngular();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCSceneExTransitionFlipAngular* CCSceneExTransitionFlipAngular::create(float t, CCSceneExtension* s)
{
    return CCSceneExTransitionFlipAngular::create(t, s, kCCTransitionOrientationRightOver);
}

//
// ZoomFlipX Transition
//
CCSceneExTransitionZoomFlipX::CCSceneExTransitionZoomFlipX()
{
}
CCSceneExTransitionZoomFlipX::~CCSceneExTransitionZoomFlipX()
{
}

void CCSceneExTransitionZoomFlipX::onEnter()
{
    CCSceneExTransitionOriented::onEnter();

    CCActionInterval *inA, *outA;
    m_pInScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( m_eOrientation == kCCTransitionOrientationRightOver ) {
        inDeltaZ = 90;
        inAngleZ = 270;
        outDeltaZ = 90;
        outAngleZ = 0;
    } 
    else 
    {
        inDeltaZ = -90;
        inAngleZ = 90;
        outDeltaZ = -90;
        outAngleZ = 0;
    }
    inA = (CCActionInterval *)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 0, 0),
                CCScaleTo::create(m_fDuration/2, 1),
                CCShow::create(),
                NULL
            ),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
            NULL
        );
    outA = (CCActionInterval *)CCSequence::create
        (
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 0, 0),
                CCScaleTo::create(m_fDuration/2, 0.5f),
                NULL
            ),
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL
        );

    m_pInScene->setScale(0.5f);
    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCSceneExTransitionZoomFlipX* CCSceneExTransitionZoomFlipX::create(float t, CCSceneExtension* s, tOrientation o)
{
    CCSceneExTransitionZoomFlipX* pScene = new CCSceneExTransitionZoomFlipX();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCSceneExTransitionZoomFlipX* CCSceneExTransitionZoomFlipX::create(float t, CCSceneExtension* s)
{
    return CCSceneExTransitionZoomFlipX::create(t, s, kCCTransitionOrientationRightOver);
}

//
// ZoomFlipY Transition
//
CCSceneExTransitionZoomFlipY::CCSceneExTransitionZoomFlipY()
{
}

CCSceneExTransitionZoomFlipY::~CCSceneExTransitionZoomFlipY()
{
}

void CCSceneExTransitionZoomFlipY::onEnter()
{
    CCSceneExTransitionOriented::onEnter();

    CCActionInterval *inA, *outA;
    m_pInScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( m_eOrientation== kCCTransitionOrientationUpOver ) {
        inDeltaZ = 90;
        inAngleZ = 270;
        outDeltaZ = 90;
        outAngleZ = 0;
    } else {
        inDeltaZ = -90;
        inAngleZ = 90;
        outDeltaZ = -90;
        outAngleZ = 0;
    }

    inA = (CCActionInterval *)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
                CCScaleTo::create(m_fDuration/2, 1),
                CCShow::create(),
                NULL
            ),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
            NULL
        );

    outA = (CCActionInterval *)CCSequence::create
        (
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
                CCScaleTo::create(m_fDuration/2, 0.5f),
                NULL
            ),                            
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),
            NULL
        );

    m_pInScene->setScale(0.5f);
    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCSceneExTransitionZoomFlipY* CCSceneExTransitionZoomFlipY::create(float t, CCSceneExtension* s, tOrientation o)
{
    CCSceneExTransitionZoomFlipY* pScene = new CCSceneExTransitionZoomFlipY();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCSceneExTransitionZoomFlipY* CCSceneExTransitionZoomFlipY::create(float t, CCSceneExtension* s)
{
    return CCSceneExTransitionZoomFlipY::create(t, s, kCCTransitionOrientationUpOver);
}

//
// ZoomFlipAngular Transition
//
CCSceneExTransitionZoomFlipAngular::CCSceneExTransitionZoomFlipAngular()
{
}
CCSceneExTransitionZoomFlipAngular::~CCSceneExTransitionZoomFlipAngular()
{
}


void CCSceneExTransitionZoomFlipAngular::onEnter()
{
    CCSceneExTransitionOriented::onEnter();

    CCActionInterval *inA, *outA;
    m_pInScene->setVisible(false);

    float inDeltaZ, inAngleZ;
    float outDeltaZ, outAngleZ;

    if( m_eOrientation == kCCTransitionOrientationRightOver ) {
        inDeltaZ = 90;
        inAngleZ = 270;
        outDeltaZ = 90;
        outAngleZ = 0;
    } 
    else 
    {
        inDeltaZ = -90;
        inAngleZ = 90;
        outDeltaZ = -90;
        outAngleZ = 0;
    }

    inA = (CCActionInterval *)CCSequence::create
        (
            CCDelayTime::create(m_fDuration/2),
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0, inAngleZ, inDeltaZ, -45, 0),
                CCScaleTo::create(m_fDuration/2, 1),
                CCShow::create(),
                NULL
            ),
            CCShow::create(),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
            NULL
        );
    outA = (CCActionInterval *)CCSequence::create
        (
            CCSpawn::create
            (
                CCOrbitCamera::create(m_fDuration/2, 1, 0 , outAngleZ, outDeltaZ, 45, 0),
                CCScaleTo::create(m_fDuration/2, 0.5f),
                NULL
            ),                            
            CCHide::create(),
            CCDelayTime::create(m_fDuration/2),                            
            NULL
        );

    m_pInScene->setScale(0.5f);
    m_pInScene->runAction(inA);
    m_pOutScene->runAction(outA);
}

CCSceneExTransitionZoomFlipAngular* CCSceneExTransitionZoomFlipAngular::create(float t, CCSceneExtension* s, tOrientation o)
{
    CCSceneExTransitionZoomFlipAngular* pScene = new CCSceneExTransitionZoomFlipAngular();
    pScene->initWithDuration(t, s, o);
    pScene->autorelease();

    return pScene;
}

CCSceneExTransitionZoomFlipAngular* CCSceneExTransitionZoomFlipAngular::create(float t, CCSceneExtension* s)
{
    return CCSceneExTransitionZoomFlipAngular::create(t, s, kCCTransitionOrientationRightOver);
}

//
// Fade Transition
//
CCSceneExTransitionFade::CCSceneExTransitionFade()
{
}
CCSceneExTransitionFade::~CCSceneExTransitionFade()
{
}

CCSceneExTransitionFade * CCSceneExTransitionFade::create(float duration, CCSceneExtension *scene, const ccColor3B& color)
{
    CCSceneExTransitionFade * pTransition = new CCSceneExTransitionFade();
    pTransition->initWithDuration(duration, scene, color);
    pTransition->autorelease();
    return pTransition;
}

CCSceneExTransitionFade* CCSceneExTransitionFade::create(float duration,CCSceneExtension* scene)
{
    return CCSceneExTransitionFade::create(duration, scene, ccBLACK);
}

bool CCSceneExTransitionFade::initWithDuration(float duration, CCSceneExtension *scene, const ccColor3B& color)
{
    if (CCSceneExTransition::initWithDuration(duration, scene))
    {
        m_tColor.r = color.r;
        m_tColor.g = color.g;
        m_tColor.b = color.b;
        m_tColor.a = 0;
    }
    return true;
}

bool CCSceneExTransitionFade::initWithDuration(float t, CCSceneExtension *scene)
{
    this->initWithDuration(t, scene, ccBLACK);
    return true;
}

void CCSceneExTransitionFade :: onEnter()
{
    CCSceneExTransition::onEnter();

    CCLayerColor* l = CCLayerColor::create(m_tColor);
    m_pInScene->setVisible(false);

    addChild(l, 2, kSceneFade);
    CCNode* f = getChildByTag(kSceneFade);

    CCActionInterval* a = (CCActionInterval *)CCSequence::create
        (
            CCFadeIn::create(m_fDuration/2),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::hideOutShowIn)),//CCCallFunc::create:self selector:@selector(hideOutShowIn)],
            CCFadeOut::create(m_fDuration/2),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)), //:self selector:@selector(finish)],
            NULL
        );
    f->runAction(a);
}

void CCSceneExTransitionFade::onExit()
{
    CCSceneExTransition::onExit();
    this->removeChildByTag(kSceneFade, false);
}

//
// Cross Fade Transition
//
CCSceneExTransitionCrossFade::CCSceneExTransitionCrossFade()
{
}
CCSceneExTransitionCrossFade::~CCSceneExTransitionCrossFade()
{
}

CCSceneExTransitionCrossFade* CCSceneExTransitionCrossFade::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionCrossFade* pScene = new CCSceneExTransitionCrossFade();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionCrossFade:: draw()
{
    // override draw since both scenes (textures) are rendered in 1 scene
}

void CCSceneExTransitionCrossFade::onEnter()
{
    CCSceneExTransition::onEnter();

    // create a transparent color layer
    // in which we are going to add our rendertextures
    ccColor4B  color = {0,0,0,0};
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor* layer = CCLayerColor::create(color);

    // create the first render texture for inScene
    CCRenderTexture* inTexture = CCRenderTexture::create((int)size.width, (int)size.height);

    if (NULL == inTexture)
    {
        return;
    }

    inTexture->getSprite()->setAnchorPoint( ccp(0.5f,0.5f) );
    inTexture->setPosition( ccp(size.width/2, size.height/2) );
    inTexture->setAnchorPoint( ccp(0.5f,0.5f) );

    // render inScene to its texturebuffer
    inTexture->begin();
    m_pInScene->visit();
    inTexture->end();

    // create the second render texture for outScene
    CCRenderTexture* outTexture = CCRenderTexture::create((int)size.width, (int)size.height);
    outTexture->getSprite()->setAnchorPoint( ccp(0.5f,0.5f) );
    outTexture->setPosition( ccp(size.width/2, size.height/2) );
    outTexture->setAnchorPoint( ccp(0.5f,0.5f) );

    // render outScene to its texturebuffer
    outTexture->begin();
    m_pOutScene->visit();
    outTexture->end();

    // create blend functions

    ccBlendFunc blend1 = {GL_ONE, GL_ONE}; // inScene will lay on background and will not be used with alpha
    ccBlendFunc blend2 = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}; // we are going to blend outScene via alpha 

    // set blendfunctions
    inTexture->getSprite()->setBlendFunc(blend1);
    outTexture->getSprite()->setBlendFunc(blend2);    

    // add render textures to the layer
    layer->addChild(inTexture);
    layer->addChild(outTexture);

    // initial opacity:
    inTexture->getSprite()->setOpacity(255);
    outTexture->getSprite()->setOpacity(255);

    // create the blend action
    CCAction* layerAction = CCSequence::create
    (
        CCFadeTo::create(m_fDuration, 0),
        CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::hideOutShowIn)),
        CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
        NULL
    );


    // run the blend action
    outTexture->getSprite()->runAction( layerAction );

    // add the layer (which contains our two rendertextures) to the scene
    addChild(layer, 2, kSceneFade);
}

// clean up on exit
void CCSceneExTransitionCrossFade::onExit()
{
    // remove our layer and release all containing objects 
    this->removeChildByTag(kSceneFade, false);
    CCSceneExTransition::onExit();
}

//
// TurnOffTilesTransition
//
CCSceneExTransitionTurnOffTiles::CCSceneExTransitionTurnOffTiles()
{
}

CCSceneExTransitionTurnOffTiles::~CCSceneExTransitionTurnOffTiles()
{
}

CCSceneExTransitionTurnOffTiles* CCSceneExTransitionTurnOffTiles::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionTurnOffTiles* pScene = new CCSceneExTransitionTurnOffTiles();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

// override addScenes, and change the order
void CCSceneExTransitionTurnOffTiles::sceneOrder()
{
    m_bIsInSceneOnTop = false;
}

void CCSceneExTransitionTurnOffTiles::onEnter()
{
    CCSceneExTransition::onEnter();
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    float aspect = s.width / s.height;
    int x = (int)(12 * aspect);
    int y = 12;

    CCTurnOffTiles* toff = CCTurnOffTiles::create(m_fDuration, CCSizeMake(x,y));
    CCActionInterval* action = easeActionWithAction(toff);
    m_pOutScene->runAction
    (
        CCSequence::create
        (
            action,
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)), 
            CCStopGrid::create(),
            NULL
        )
    );
}


CCActionInterval* CCSceneExTransitionTurnOffTiles:: easeActionWithAction(CCActionInterval* action)
{
    return action;
}

//
// SplitCols Transition
//
CCSceneExTransitionSplitCols::CCSceneExTransitionSplitCols()
{
}
CCSceneExTransitionSplitCols::~CCSceneExTransitionSplitCols()
{
}

CCSceneExTransitionSplitCols* CCSceneExTransitionSplitCols::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionSplitCols* pScene = new CCSceneExTransitionSplitCols();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionSplitCols::onEnter()
{
    CCSceneExTransition::onEnter();
    m_pInScene->setVisible(false);

    CCActionInterval* split = action();
    CCActionInterval* seq = (CCActionInterval*)CCSequence::create
    (
        split,
        CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::hideOutShowIn)),
        split->reverse(),
        NULL
    );

    this->runAction
    ( 
        CCSequence::create
        (
            easeActionWithAction(seq),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
            CCStopGrid::create(),
            NULL
        )
    );
}

CCActionInterval* CCSceneExTransitionSplitCols:: action()
{
    return CCSplitCols::create(m_fDuration/2.0f, 3);
}


CCActionInterval* CCSceneExTransitionSplitCols::easeActionWithAction(CCActionInterval * action)
{
    return CCEaseInOut::create(action, 3.0f);
}


//
// SplitRows Transition
//
CCSceneExTransitionSplitRows::CCSceneExTransitionSplitRows()
{
}

CCSceneExTransitionSplitRows::~CCSceneExTransitionSplitRows()
{
}

CCActionInterval* CCSceneExTransitionSplitRows::action()
{
    return CCSplitRows::create(m_fDuration/2.0f, 3);
}

CCSceneExTransitionSplitRows* CCSceneExTransitionSplitRows::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionSplitRows* pScene = new CCSceneExTransitionSplitRows();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

//
// FadeTR Transition
//
CCSceneExTransitionFadeTR::CCSceneExTransitionFadeTR()
{
}
CCSceneExTransitionFadeTR::~CCSceneExTransitionFadeTR()
{
}

CCSceneExTransitionFadeTR* CCSceneExTransitionFadeTR::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionFadeTR* pScene = new CCSceneExTransitionFadeTR();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionFadeTR::sceneOrder()
{
    m_bIsInSceneOnTop = false;
}

void CCSceneExTransitionFadeTR::onEnter()
{
    CCSceneExTransition::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    float aspect = s.width / s.height;
    int x = (int)(12 * aspect);
    int y = 12;

    CCActionInterval* action  = actionWithSize(CCSizeMake(x,y));

    m_pOutScene->runAction
    (
        CCSequence::create
        (
            easeActionWithAction(action),
            CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)), 
            CCStopGrid::create(),
            NULL
        )
    );
}


CCActionInterval*  CCSceneExTransitionFadeTR::actionWithSize(const CCSize& size)
{
    return CCFadeOutTRTiles::create(m_fDuration, size);
}

CCActionInterval* CCSceneExTransitionFadeTR:: easeActionWithAction(CCActionInterval* action)
{
    return action;
}


//
// FadeBL Transition
//

CCSceneExTransitionFadeBL::CCSceneExTransitionFadeBL()
{
}
CCSceneExTransitionFadeBL::~CCSceneExTransitionFadeBL()
{
}

CCSceneExTransitionFadeBL* CCSceneExTransitionFadeBL::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionFadeBL* pScene = new CCSceneExTransitionFadeBL();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCActionInterval*  CCSceneExTransitionFadeBL::actionWithSize(const CCSize& size)
{
    return CCFadeOutBLTiles::create(m_fDuration, size);
}

//
// FadeUp Transition
//
CCSceneExTransitionFadeUp::CCSceneExTransitionFadeUp()
{
}

CCSceneExTransitionFadeUp::~CCSceneExTransitionFadeUp()
{
}

CCSceneExTransitionFadeUp* CCSceneExTransitionFadeUp::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionFadeUp* pScene = new CCSceneExTransitionFadeUp();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCActionInterval* CCSceneExTransitionFadeUp::actionWithSize(const CCSize& size)
{
    return CCFadeOutUpTiles::create(m_fDuration, size);
}

//
// FadeDown Transition
//
CCSceneExTransitionFadeDown::CCSceneExTransitionFadeDown()
{
}
CCSceneExTransitionFadeDown::~CCSceneExTransitionFadeDown()
{
}

CCSceneExTransitionFadeDown* CCSceneExTransitionFadeDown::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionFadeDown* pScene = new CCSceneExTransitionFadeDown();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCActionInterval* CCSceneExTransitionFadeDown::actionWithSize(const CCSize& size)
{
    return CCFadeOutDownTiles::create(m_fDuration, size);
}


CCSceneExTransitionPageTurn::CCSceneExTransitionPageTurn()
{
}

CCSceneExTransitionPageTurn::~CCSceneExTransitionPageTurn()
{
}

/** creates a base transition with duration and incoming scene */
CCSceneExTransitionPageTurn * CCSceneExTransitionPageTurn::create(float t, CCSceneExtension *scene, bool backwards)
{
    CCSceneExTransitionPageTurn * pTransition = new CCSceneExTransitionPageTurn();
    pTransition->initWithDuration(t,scene,backwards);
    pTransition->autorelease();
    return pTransition;
}

/** initializes a transition with duration and incoming scene */
bool CCSceneExTransitionPageTurn::initWithDuration(float t, CCSceneExtension *scene, bool backwards)
{
    // XXX: needed before [super init]
    m_bBack = backwards;

    if (CCSceneExTransition::initWithDuration(t, scene))
    {
        // do something
    }
    return true;
}

void CCSceneExTransitionPageTurn::sceneOrder()
{
    m_bIsInSceneOnTop = m_bBack;
}

void CCSceneExTransitionPageTurn::onEnter()
{
    CCSceneExTransition::onEnter();
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    int x,y;
    if (s.width > s.height)
    {
        x=16;
        y=12;
    }
    else
    {
        x=12;
        y=16;
    }

    CCActionInterval *action  = this->actionWithSize(CCSizeMake(x,y));

    if (! m_bBack )
    {
        m_pOutScene->runAction
        (
            CCSequence::create
            (
                action,
                CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
                CCStopGrid::create(),
                NULL
            )
        );
    }
    else
    {
        // to prevent initial flicker
        m_pInScene->setVisible(false);
        m_pInScene->runAction
        (
            CCSequence::create
            (
                CCShow::create(),
                action,
                CCCallFunc::create(this, callfunc_selector(CCSceneExTransition::finish)),
                CCStopGrid::create(),
                NULL
            )
        );
    }
}

CCActionInterval* CCSceneExTransitionPageTurn:: actionWithSize(const CCSize& vector)
{
    if (m_bBack)
    {
        // Get hold of the PageTurn3DAction
        return CCReverseTime::create
        (
            CCPageTurn3D::create(m_fDuration, vector)
        );
    }
    else
    {
        // Get hold of the PageTurn3DAction
        return CCPageTurn3D::create(m_fDuration, vector);
    }
}

enum {
    kCCSceneRadial = 0xc001,
};

CCSceneExTransitionProgress::CCSceneExTransitionProgress()
: m_fTo(0.0f)
, m_fFrom(0.0f)
, m_pSceneToBeModified(NULL)
{

}

CCSceneExTransitionProgress* CCSceneExTransitionProgress::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionProgress* pScene = new CCSceneExTransitionProgress();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

// CCTransitionProgress
void CCSceneExTransitionProgress::onEnter()
{
    CCSceneExTransition::onEnter();

    setupTransition();
    
    // create a transparent color layer
    // in which we are going to add our rendertextures
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // create the second render texture for outScene
    CCRenderTexture *texture = CCRenderTexture::create((int)size.width, (int)size.height);
    texture->getSprite()->setAnchorPoint(ccp(0.5f,0.5f));
    texture->setPosition(ccp(size.width/2, size.height/2));
    texture->setAnchorPoint(ccp(0.5f,0.5f));

    // render outScene to its texturebuffer
    texture->clear(0, 0, 0, 1);
    texture->begin();
    m_pSceneToBeModified->visit();
    texture->end();


    //    Since we've passed the outScene to the texture we don't need it.
    if (m_pSceneToBeModified == m_pOutScene)
    {
        hideOutShowIn();
    }
    //    We need the texture in RenderTexture.
    CCProgressTimer *pNode = progressTimerNodeWithRenderTexture(texture);

    // create the blend action
    CCActionInterval* layerAction = (CCActionInterval*)CCSequence::create(
        CCProgressFromTo::create(m_fDuration, m_fFrom, m_fTo),
        CCCallFunc::create(this, callfunc_selector(CCSceneExTransitionProgress::finish)), 
        NULL);
    // run the blend action
    pNode->runAction(layerAction);

    // add the layer (which contains our two rendertextures) to the scene
    addChild(pNode, 2, kCCSceneRadial);
}

// clean up on exit
void CCSceneExTransitionProgress::onExit()
{
    // remove our layer and release all containing objects
    removeChildByTag(kCCSceneRadial, true);
    CCSceneExTransition::onExit();
}

void CCSceneExTransitionProgress::sceneOrder()
{
    m_bIsInSceneOnTop = false;
}

void CCSceneExTransitionProgress::setupTransition()
{
    m_pSceneToBeModified = m_pOutScene;
    m_fFrom = 100;
    m_fTo = 0;
}

CCProgressTimer* CCSceneExTransitionProgress::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{
    CCAssert(false, "override me - abstract class");
    return NULL;
}


// CCTransitionProgressRadialCCW

CCProgressTimer* CCSceneExTransitionProgressRadialCCW::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCProgressTimer* pNode = CCProgressTimer::create(texture->getSprite());

    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType(kCCProgressTimerTypeRadial);

    //    Return the radial type that we want to use
    pNode->setReverseDirection(false);
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}

CCSceneExTransitionProgressRadialCCW* CCSceneExTransitionProgressRadialCCW::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionProgressRadialCCW* pScene = new CCSceneExTransitionProgressRadialCCW();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

// CCTransitionProgressRadialCW
CCSceneExTransitionProgressRadialCW* CCSceneExTransitionProgressRadialCW::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionProgressRadialCW* pScene = new CCSceneExTransitionProgressRadialCW();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCProgressTimer* CCSceneExTransitionProgressRadialCW::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCProgressTimer* pNode = CCProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType( kCCProgressTimerTypeRadial );
    
    //    Return the radial type that we want to use
    pNode->setReverseDirection(true);
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}

// CCTransitionProgressHorizontal
CCSceneExTransitionProgressHorizontal* CCSceneExTransitionProgressHorizontal::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionProgressHorizontal* pScene = new CCSceneExTransitionProgressHorizontal();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCProgressTimer* CCSceneExTransitionProgressHorizontal::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{    
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCProgressTimer* pNode = CCProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType( kCCProgressTimerTypeBar);
    
    pNode->setMidpoint(ccp(1, 0));
    pNode->setBarChangeRate(ccp(1,0));
    
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));

    return pNode;
}

// CCTransitionProgressVertical
CCSceneExTransitionProgressVertical* CCSceneExTransitionProgressVertical::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionProgressVertical* pScene = new CCSceneExTransitionProgressVertical();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCProgressTimer* CCSceneExTransitionProgressVertical::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCProgressTimer* pNode = CCProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType(kCCProgressTimerTypeBar);
    
    pNode->setMidpoint(ccp(0, 0));
    pNode->setBarChangeRate(ccp(0,1));
    
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}


// CCTransitionProgressInOut
CCSceneExTransitionProgressInOut* CCSceneExTransitionProgressInOut::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionProgressInOut* pScene = new CCSceneExTransitionProgressInOut();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void CCSceneExTransitionProgressInOut::sceneOrder()
{
    m_bIsInSceneOnTop = false;
}

void CCSceneExTransitionProgressInOut::setupTransition()
{
    m_pSceneToBeModified = m_pInScene;
    m_fFrom = 0;
    m_fTo = 100;    
}

CCProgressTimer* CCSceneExTransitionProgressInOut::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCProgressTimer* pNode = CCProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType( kCCProgressTimerTypeBar);
    
    pNode->setMidpoint(ccp(0.5f, 0.5f));
    pNode->setBarChangeRate(ccp(1, 1));
    
    pNode->setPercentage(0);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}


// CCTransitionProgressOutIn
CCSceneExTransitionProgressOutIn* CCSceneExTransitionProgressOutIn::create(float t, CCSceneExtension* scene)
{
    CCSceneExTransitionProgressOutIn* pScene = new CCSceneExTransitionProgressOutIn();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

CCProgressTimer* CCSceneExTransitionProgressOutIn::progressTimerNodeWithRenderTexture(CCRenderTexture* texture)
{    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCProgressTimer* pNode = CCProgressTimer::create(texture->getSprite());
    
    // but it is flipped upside down so we flip the sprite
    pNode->getSprite()->setFlipY(true);
    pNode->setType( kCCProgressTimerTypeBar );
    
    pNode->setMidpoint(ccp(0.5f, 0.5f));
    pNode->setBarChangeRate(ccp(1, 1));
    
    pNode->setPercentage(100);
    pNode->setPosition(ccp(size.width/2, size.height/2));
    pNode->setAnchorPoint(ccp(0.5f,0.5f));
    
    return pNode;
}

NS_CC_END
