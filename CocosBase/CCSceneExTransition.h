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

#ifndef __CCSCENEEXTRANSITION_H__
#define __CCSCENEEXTRANSITION_H__

#include "cocos2d.h"
#include "CCSceneExtension.h"
#include "CCBaseMacros.h"
#include "ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup transition
 * @{
 */

//static creation function macro
//c/c++ don't support object creation of using class name
//so, all classes need creation method.

class CCActionInterval;
class CCNode;

/** @brief CCTransitionEaseScene can ease the actions of the scene protocol.
@since v0.8.2
*/
class  CCSceneExTransitionEase// : public CCObject
{
public:
    /** returns the Ease action that will be performed on a linear action.
    @since v0.8.2
    */
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action) = 0;
};

/** @brief Base class for CCTransition scenes
*/
class  CCSceneExTransition : public CCSceneExtension
{

protected:
	CCSceneExtension    * m_pInScene;
    CCSceneExtension    * m_pOutScene;
    float    m_fDuration;
    bool    m_bIsInSceneOnTop;
    bool    m_bIsSendCleanupToScene;

public:
    /**
     *  @js ctor
     */
    CCSceneExTransition();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransition();
    virtual void draw();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onExit();
    virtual void cleanup();

	virtual CCSceneExtension* getInScene();

    /** creates a base transition with duration and incoming scene */
    static CCSceneExTransition * create(float t, CCSceneExtension *scene);

    /** initializes a transition with duration and incoming scene */
    virtual bool initWithDuration(float t,CCSceneExtension* scene);

    /** called after the transition finishes */
    void finish(void);

    /** used by some transitions to hide the outer scene */
    void hideOutShowIn(void);

protected:
    virtual void sceneOrder();
private:
    void setNewScene(float dt);

};

/** @brief A CCTransition that supports orientation like.
* Possible orientation: LeftOver, RightOver, UpOver, DownOver
*/
class  CCSceneExTransitionOriented : public CCSceneExTransition
{
protected:
    tOrientation m_eOrientation;

public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionOriented();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionOriented();

    /** creates a base transition with duration and incoming scene */
    static CCSceneExTransitionOriented * create(float t,CCSceneExtension* scene, tOrientation orientation);

    /** initializes a transition with duration and incoming scene */
    virtual bool initWithDuration(float t,CCSceneExtension* scene,tOrientation orientation);
};

/** @brief CCTransitionRotoZoom:
Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming 
*/
class  CCSceneExTransitionRotoZoom : public CCSceneExTransition
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionRotoZoom();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionRotoZoom();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCSceneExTransitionRotoZoom* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionJumpZoom:
Zoom out and jump the outgoing scene, and then jump and zoom in the incoming 
*/
class  CCSceneExTransitionJumpZoom : public CCSceneExTransition
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionJumpZoom();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionJumpZoom();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCSceneExTransitionJumpZoom* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionMoveInL:
Move in from to the left the incoming scene.
*/
class  CCSceneExTransitionMoveInL : public CCSceneExTransition, public CCSceneExTransitionEase
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionMoveInL();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionMoveInL();
    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed */
    virtual CCActionInterval* action(void);

    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCSceneExTransitionMoveInL* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionMoveInR:
Move in from to the right the incoming scene.
*/
class  CCSceneExTransitionMoveInR : public CCSceneExTransitionMoveInL
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionMoveInR();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionMoveInR();
    virtual void initScenes();

    static CCSceneExTransitionMoveInR* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionMoveInT:
Move in from to the top the incoming scene.
*/
class  CCSceneExTransitionMoveInT : public CCSceneExTransitionMoveInL 
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionMoveInT();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionMoveInT();
    virtual void initScenes();

    static CCSceneExTransitionMoveInT* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionMoveInB:
Move in from to the bottom the incoming scene.
*/
class  CCSceneExTransitionMoveInB : public CCSceneExTransitionMoveInL
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionMoveInB();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionMoveInB();
    virtual void initScenes();

    static CCSceneExTransitionMoveInB* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionSlideInL:
Slide in the incoming scene from the left border.
*/
class  CCSceneExTransitionSlideInL : public CCSceneExTransition, public CCSceneExTransitionEase
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionSlideInL();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionSlideInL();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    static CCSceneExTransitionSlideInL* create(float t, CCSceneExtension* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionSlideInR:
Slide in the incoming scene from the right border.
*/
class  CCSceneExTransitionSlideInR : public CCSceneExTransitionSlideInL 
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionSlideInR();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionSlideInR();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    static CCSceneExTransitionSlideInR* create(float t, CCSceneExtension* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionSlideInB:
Slide in the incoming scene from the bottom border.
*/
class  CCSceneExTransitionSlideInB : public CCSceneExTransitionSlideInL
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionSlideInB();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionSlideInB();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    static CCSceneExTransitionSlideInB* create(float t, CCSceneExtension* scene);
protected: 
    virtual void sceneOrder();
};

/** @brief CCTransitionSlideInT:
Slide in the incoming scene from the top border.
*/
class  CCSceneExTransitionSlideInT : public CCSceneExTransitionSlideInL
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionSlideInT();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionSlideInT();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    static CCSceneExTransitionSlideInT* create(float t, CCSceneExtension* scene);
protected:
    virtual void sceneOrder();
};

/**
@brief Shrink the outgoing scene while grow the incoming scene
*/
class  CCSceneExTransitionShrinkGrow : public CCSceneExTransition , public CCSceneExTransitionEase
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionShrinkGrow();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionShrinkGrow();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    static CCSceneExTransitionShrinkGrow* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionFlipX:
Flips the screen horizontally.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class  CCSceneExTransitionFlipX : public CCSceneExTransitionOriented
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionFlipX();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionFlipX();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCSceneExTransitionFlipX* create(float t, CCSceneExtension* s, tOrientation o);
    static CCSceneExTransitionFlipX* create(float t, CCSceneExtension* s);
};

/** @brief CCTransitionFlipY:
Flips the screen vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class  CCSceneExTransitionFlipY : public CCSceneExTransitionOriented
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionFlipY();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionFlipY();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCSceneExTransitionFlipY* create(float t, CCSceneExtension* s, tOrientation o);
    static CCSceneExTransitionFlipY* create(float t, CCSceneExtension* s);
};

/** @brief CCTransitionFlipAngular:
Flips the screen half horizontally and half vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class  CCSceneExTransitionFlipAngular : public CCSceneExTransitionOriented
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionFlipAngular();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionFlipAngular();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    
    static CCSceneExTransitionFlipAngular* create(float t, CCSceneExtension* s, tOrientation o);
    static CCSceneExTransitionFlipAngular* create(float t, CCSceneExtension* s);
};

/** @brief CCTransitionZoomFlipX:
Flips the screen horizontally doing a zoom out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class  CCSceneExTransitionZoomFlipX : public CCSceneExTransitionOriented
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionZoomFlipX();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionZoomFlipX();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCSceneExTransitionZoomFlipX* create(float t, CCSceneExtension* s, tOrientation o);
    static CCSceneExTransitionZoomFlipX* create(float t, CCSceneExtension* s);
};

/** @brief CCTransitionZoomFlipY:
Flips the screen vertically doing a little zooming out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class  CCSceneExTransitionZoomFlipY : public CCSceneExTransitionOriented
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionZoomFlipY();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionZoomFlipY();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCSceneExTransitionZoomFlipY* create(float t, CCSceneExtension* s, tOrientation o);
    static CCSceneExTransitionZoomFlipY* create(float t, CCSceneExtension* s);
};

/** @brief CCTransitionZoomFlipAngular:
Flips the screen half horizontally and half vertically doing a little zooming out/in.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class  CCSceneExTransitionZoomFlipAngular : public CCSceneExTransitionOriented
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionZoomFlipAngular();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionZoomFlipAngular();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCSceneExTransitionZoomFlipAngular* create(float t, CCSceneExtension* s, tOrientation o);
    static CCSceneExTransitionZoomFlipAngular* create(float t, CCSceneExtension* s);
};

/** @brief CCTransitionFade:
Fade out the outgoing scene and then fade in the incoming scene.'''
*/
class  CCSceneExTransitionFade : public CCSceneExTransition
{
protected:
    ccColor4B    m_tColor;

public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionFade();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionFade();
    
    /** creates the transition with a duration and with an RGB color
    * Example: FadeTransition::create(2, scene, ccc3(255,0,0); // red color
    */
    static CCSceneExTransitionFade* create(float duration,CCSceneExtension* scene, const ccColor3B& color);
    static CCSceneExTransitionFade* create(float duration,CCSceneExtension* scene);

    /** initializes the transition with a duration and with an RGB color */
    virtual bool initWithDuration(float t, CCSceneExtension*scene ,const ccColor3B& color);

    virtual bool initWithDuration(float t,CCSceneExtension* scene);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onExit();
};

class CCRenderTexture;
/**
@brief CCTransitionCrossFade:
Cross fades two scenes using the CCRenderTexture object.
*/
class  CCSceneExTransitionCrossFade : public CCSceneExTransition
{
public :
    /**
     *  @js ctor
     */
    CCSceneExTransitionCrossFade();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionCrossFade();

    virtual void draw();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onExit();

public:
    static CCSceneExTransitionCrossFade* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionTurnOffTiles:
Turn off the tiles of the outgoing scene in random order
*/
class  CCSceneExTransitionTurnOffTiles : public CCSceneExTransition ,public CCSceneExTransitionEase
{
public :
    /**
     *  @js ctor
     */
    CCSceneExTransitionTurnOffTiles();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionTurnOffTiles();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:
    static CCSceneExTransitionTurnOffTiles* create(float t, CCSceneExtension* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionSplitCols:
The odd columns goes upwards while the even columns goes downwards.
*/
class  CCSceneExTransitionSplitCols : public CCSceneExTransition , public CCSceneExTransitionEase
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionSplitCols();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionSplitCols();

    virtual CCActionInterval* action(void);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:

    static CCSceneExTransitionSplitCols* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionSplitRows:
The odd rows goes to the left while the even rows goes to the right.
*/
class  CCSceneExTransitionSplitRows : public CCSceneExTransitionSplitCols
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionSplitRows();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionSplitRows();

    virtual CCActionInterval* action(void);

public:

    static CCSceneExTransitionSplitRows* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionFadeTR:
Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
*/
class  CCSceneExTransitionFadeTR : public CCSceneExTransition , public CCSceneExTransitionEase
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionFadeTR();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionFadeTR();
    virtual CCActionInterval* actionWithSize(const CCSize& size);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

public:

    static CCSceneExTransitionFadeTR* create(float t, CCSceneExtension* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionFadeBL:
Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
*/
class  CCSceneExTransitionFadeBL : public CCSceneExTransitionFadeTR
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionFadeBL();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionFadeBL();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static CCSceneExTransitionFadeBL* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionFadeUp:
* Fade the tiles of the outgoing scene from the bottom to the top.
*/
class  CCSceneExTransitionFadeUp : public CCSceneExTransitionFadeTR
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionFadeUp();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionFadeUp();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static CCSceneExTransitionFadeUp* create(float t, CCSceneExtension* scene);
};

/** @brief CCTransitionFadeDown:
* Fade the tiles of the outgoing scene from the top to the bottom.
*/
class  CCSceneExTransitionFadeDown : public CCSceneExTransitionFadeTR
{
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionFadeDown();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionFadeDown();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static CCSceneExTransitionFadeDown* create(float t, CCSceneExtension* scene);
};

/**
@brief A transition which peels back the bottom right hand corner of a scene
to transition to the scene beneath it simulating a page turn.

This uses a 3DAction so it's strongly recommended that depth buffering
is turned on in CCDirector using:

 CCDirector::sharedDirector()->setDepthBufferFormat(kDepthBuffer16);

 @since v0.8.2
*/
class CCSceneExTransitionPageTurn : public CCSceneExTransition
{
protected:
    bool    m_bBack;
    
public:
    /**
     *  @js ctor
     */
    CCSceneExTransitionPageTurn();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCSceneExTransitionPageTurn();

    /**
    * Creates a base transition with duration and incoming scene.
    * If back is true then the effect is reversed to appear as if the incoming 
    * scene is being turned from left over the outgoing scene.
    */
	static CCSceneExTransitionPageTurn* create(float t,CCSceneExtension* scene,bool backwards);

    /**
    * Creates a base transition with duration and incoming scene.
    * If back is true then the effect is reversed to appear as if the incoming 
    * scene is being turned from left over the outgoing scene.
    */
	virtual bool initWithDuration(float t,CCSceneExtension* scene,bool backwards);

    CCActionInterval* actionWithSize(const CCSize& vector);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

protected:
    virtual void sceneOrder();
};



class CCSceneExTransitionProgress : public CCSceneExTransition
{
public:
	static CCSceneExTransitionProgress* create(float t, CCSceneExtension* scene);
    /**
     *  @js ctor
     */
    CCSceneExTransitionProgress();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onExit();
protected:
    virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);
    virtual void setupTransition();
    virtual void sceneOrder();
    float m_fTo;
    float m_fFrom;
    CCSceneExtension* m_pSceneToBeModified;
};


/** CCTransitionRadialCCW transition.
 A counter clock-wise radial transition to the next scene
 */
class CCSceneExTransitionProgressRadialCCW : public CCSceneExTransitionProgress
{
public:
	static CCSceneExTransitionProgressRadialCCW* create(float t, CCSceneExtension* scene);
protected:
    virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);
  
};


/** CCTransitionRadialCW transition.
 A counter clock-wise radial transition to the next scene
*/
class CCSceneExTransitionProgressRadialCW : public CCSceneExTransitionProgress
{
public:
	static CCSceneExTransitionProgressRadialCW* create(float t, CCSceneExtension* scene);
protected:
    virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);

};

/** CCTransitionProgressHorizontal transition.
 A  clock-wise radial transition to the next scene
 */
class CCSceneExTransitionProgressHorizontal : public CCSceneExTransitionProgress
{
public:

    static CCSceneExTransitionProgressHorizontal* create(float t, CCSceneExtension* scene);
protected:
    virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);

};

class CCSceneExTransitionProgressVertical : public CCSceneExTransitionProgress
{
public:

    static CCSceneExTransitionProgressVertical* create(float t, CCSceneExtension* scene);
protected:
    virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);

};

class CCSceneExTransitionProgressInOut : public CCSceneExTransitionProgress
{
public:

    static CCSceneExTransitionProgressInOut* create(float t, CCSceneExtension* scene);
protected:
    virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);
    virtual void sceneOrder();
    virtual void setupTransition();
};

class CCSceneExTransitionProgressOutIn : public CCSceneExTransitionProgress
{
public:

    static CCSceneExTransitionProgressOutIn* create(float t, CCSceneExtension* scene);
protected:
    virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);

};

// end of transition group
/// @}

NS_CC_END

#endif // __CCSCENEEXTRANSITION_H__

