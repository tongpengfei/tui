#include <tui.h>

#include <tuiconsts.h>
#include <tuiutil.h>
#include <tuimanager.h>
#include <tmenuitemimage.h>
#include <string>
using std::string;

Tui::Tui(TuiManager* uimanager, const char* name )
{
	tAssertc( name, return );
	menu_group = NULL;
	ui_manager = uimanager;
	strncpy( tui_name, name, sizeof(tui_name) );
}

Tui::~Tui()
{
	tLogDebug( ">>> %s", tui_name );
}

Tui* Tui::create( TuiManager* uimanager, const char* name )
{
	Tui* pRet = new Tui(uimanager, name);
	if (pRet && pRet->init()){   
		pRet->autorelease();
		return pRet;
	}else{   
		CC_SAFE_DELETE(pRet);
		return NULL;
	}   
}

bool Tui::init(){
	bool ret = CCLayer::init();
	if( !ret ) return false;

    // enable standard touch
    this->setTouchEnabled(true);
	// should have call TuiManager::showTui to set Tui visible
	setVisible( false );
	return true;
}

void Tui::onEnter()
{
	CCLayer::onEnter();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
/*
    // add "HelloWorld" splash screen"
	//res/img/pipe_lrb.png" x="-87.65" y="-153.65
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//    CCSprite* pSprite = CCSprite::create("res/cogs/pipe_lrt.png");
	CCSprite* pSprite = CCSprite::create("res/iphone/game_background.png");
    // position the sprite on the center of the screen
//	float c_x = -87.65f;
	float c_x = 0;
	float c_y = 0;
	float c_ox = 160;
	float c_oy = 240;
	float ox = 320/2.0 - c_ox;
	float oy = 480/2.0 - c_oy;
	float x = TuiUtil::convertTuiX( c_x - ox );
	float y = TuiUtil::convertTuiY( -(c_y - oy) );
	//float x = TuiUtil::convertx( 0 );
	//float y = TuiUtil::converty( 30 );
//	float y = visibleSize.height - (visibleSize.height/2+ origin.y + c_y + c_oy);
    pSprite->setPosition( ccp( x, y ) );

    //pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
*/
}

void Tui::onExit()
{
	CCLayer::onExit();
}


void Tui::registerListener()
{
	TEventController* tec = TEventController::I();
	size_t nsize = vec_event.size();
	for( size_t i=0; i<nsize; ++i ){
		tec->registerListener( vec_event[i], ui_manager, tevent_cb(TuiManager::onEvent) );
		tLogDebug( "<<<--- %s", vec_event[i].c_str() );
	}
}

void Tui::unregisterListener()
{
	TEventController* tec = TEventController::I();
	size_t nsize = vec_event.size();
	for( size_t i=0; i<nsize; ++i ){
		tec->unregisterListener( vec_event[i], ui_manager, tevent_cb(TuiManager::onEvent) );
		tLogDebug( "--->>> %s", vec_event[i].c_str() );
	}
}

CCNode* Tui::getControl( const char* key )
{
	tAssertc( key, return NULL );
	TuiControlDictionary::iterator it = dict_control.find( string(key) );
	if( it != dict_control.end() ){
		return it->second;
	}
	return NULL;
}

void Tui::onButtonClick( CCObject* o )
{
	TMenuItemImage* pmenu = (TMenuItemImage*)o;
	const char* e = pmenu->eventClick();
//	tLogDebug( "send event click, 0x%x %s", o, e );
	TEventController* tec = TEventController::I();
	TEvent event;
	event.event_id = e;
	tec->dispatchEvent( (void*)o, &event );
}
