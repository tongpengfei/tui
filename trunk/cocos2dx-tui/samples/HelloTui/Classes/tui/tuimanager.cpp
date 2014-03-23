#include <macro.h>
#include <tuimanager.h>
#include <tuiutil.h>
#include <tui.h>
#include <tuiconsts.h>
#include <tuilocalization.h>
#include <tmenuitemimage.h>
#include <fstream>
#include <support/zip_support/unzip.h>
#include "cocos2d.h"
USING_NS_CC;
using std::pair;
/*
TuiManager* TuiManager::s_instance = NULL;
TuiManager* TuiManager::I()
{
	if( !s_instance ){
		s_instance = new TuiManager();
		if (s_instance && s_instance->init()){   
			s_instance->autorelease();
		}else{   
			CC_SAFE_DELETE(s_instance);
			return NULL;
		}   
	}
	return s_instance;
}
*/
/*
static TuiEventCallBackTable tui_event_cb_table[] ={
	{ "click_back", tevent_cb(TuiManager::onEventBack) },
	{ "click_next", tevent_cb(TuiManager::onEventNext) },
};
*/
TuiManager::TuiManager()
{
	scheme_name = kTuiSchemeNone;
	scheme_width = 0;
	scheme_height = 0;
	is_retina = false;
}

TuiManager::~TuiManager()
{
}

bool TuiManager::addTui( const char* key, Tui* v )
{
	tAssertc( key, return false );
	tAssertc( v, return false );

	string s( key );

	TuiDictionary::iterator it = tui_dict.find( s );
	if( it != tui_dict.end() ){
		tLogError( "ui %s already exist, auto delete first and set to new", key );
		delete it->second;
		tui_dict.erase( it );
	}
	tui_dict.insert( pair<string, Tui*>( s, v ) );
	return true;
}

UIXmlElement* TuiManager::getTuiXmlElement( const char* key )
{
	tAssertc( key, return NULL );
	string s( key );
	TuiXmlDictionary::iterator it = xml_dict.find( s );
	tAssertcm( it != xml_dict.end(), return NULL, "ui: %s", key );
	return it->second;
}

Tui* TuiManager::getTui( const char* key )
{
	tAssertc( key, return NULL );

	string s( key );
	TuiDictionary::iterator it = tui_dict.find( s );
	if( it == tui_dict.end() ){
		UIXmlElement* puixml = NULL;
		tAssertcm( (puixml = getTuiXmlElement( key )), return NULL, "ui: %s", key );
		TiXmlElement* pElement = puixml->element;

		Tui* pui = NULL;
		tAssertc( pui = parseControl( &reader, pElement, NULL, NULL ), return NULL );
		pui->setTag( puixml->tag );
		addTui( key, pui );

		return pui;
	}
	return it->second;
}

Tui* TuiManager::showTui( const char* key )
{
	Tui* pui = getTui( key );
	tAssertcm( pui, return NULL, "cant find ui: %s", key );
	if( !pui->isVisible() ){
		pui->setVisible( true );
		pui->registerListener();
	}
	if( NULL == getChildByTag( pui->getTag() ) ){
		addChild( pui );
	}
	return pui;
}

void TuiManager::closeTui( const char* key )
{
	Tui* pui = getTui( key );
	tAssertcm( pui, return, "cant find ui: %s", key );
	if( getChildByTag( pui->getTag() ) ){
		pui->unregisterListener();
		removeChild( pui, false );
		pui->release();
		TuiDictionary::iterator it = tui_dict.find( string(key) );
		tui_dict.erase( it );
	}
}

void TuiManager::hideTui( const char* key )
{
	Tui* pui = getTui( key );
	tAssertcm( pui, return, "cant find ui: %s", key );
	if( getChildByTag( pui->getTag() ) ){
		if( pui->isVisible() ){
			pui->setVisible( false );
			pui->unregisterListener();
		}
	}
}

void TuiManager::closeAll()
{
	removeAllChildrenWithCleanup( false );
	TuiDictionary::iterator it = tui_dict.begin();
	for( ; it != tui_dict.end(); ){
		Tui* pui = it->second;
		if( pui->isVisible() ){
			pui->unregisterListener();
		}
		pui->release();
		tui_dict.erase( it++ );
	}
}

void TuiManager::hideAll()
{
	TuiDictionary::iterator it = tui_dict.begin();
	for( ; it != tui_dict.end(); ++it ){
		Tui* pui = it->second;
		if( pui->isVisible() ){
			pui->setVisible( false );
			pui->unregisterListener();
		}
	}
}

bool TuiManager::loadTuiXML( const char* xml )
{
//	const char* fullpath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(xml);
    tAssertc( reader.open( xml ), return false );

    TiXmlElement* root = NULL;
    tAssertc( NULL != (root = reader.getRoot()), return false );

	TiXmlElement* pElement = NULL;
	pElement = root->FirstChildElement( kTuiNodeScheme );
	if( pElement ){
		tAssertc( parseScheme( pElement ), return false );
	}

    pElement = root->FirstChildElement( kTuiNodeControl );
	int nindex = 0;
	for( ; pElement ; pElement = pElement->NextSiblingElement(kTuiNodeControl) ){
		char c_name[64]; memset( c_name, 0x00, sizeof(c_name) );
		tAssertc(reader.getString(pElement, "name", c_name, sizeof(c_name)), return false );

		string s( c_name );
		
		TuiXmlDictionary::iterator it = xml_dict.find( s );
		tAssertcm( it == xml_dict.end(), return false, "ui xml is already exist: %s", c_name );
		UIXmlElement* puixml = new UIXmlElement();
		puixml->tag = nindex++;
		puixml->element = pElement;
		xml_dict.insert( pair<string, UIXmlElement*>( s, puixml ) );
		reader.setCurNode( pElement );
	}
	return true;
}

bool TuiManager::parseScheme( TiXmlElement* element )
{
	char scheme[32]; memset( scheme, 0x00, sizeof(scheme) );
	int v = 0;
	tAssertc( reader.getString( element, "name", scheme, sizeof(scheme) ), return false );
	tAssertc( reader.getInt( element, "is_retina", v ), return false );
	is_retina = (bool)v;

	tAssertc( reader.getInt( element, "screen_width", scheme_width ), return false );
	tAssertc( reader.getInt( element, "screen_height", scheme_height), return false );

	stringToScheme( scheme );
	return true;
}

TuiScheme TuiManager::stringToScheme( const char* v )
{
	tAssertc( v, return kTuiSchemeNone );

	if( strcmp( sSchemeNameIPhone4, v ) == 0 ){ scheme_name = kTuiSchemeIPhone4; }
	else if( strcmp( sSchemeNameIPhone5, v ) == 0 ){ scheme_name = kTuiSchemeIPhone5; }
	else if( strcmp( sSchemeNameIPad, v ) == 0 ){ scheme_name = kTuiSchemeIPad; }
	else if( strcmp( sSchemeNameIPadMini, v ) == 0 ){ scheme_name = kTuiSchemeIPadMini; }
	else { tLogError( "unknown scheme: %s", v ) };
	return scheme_name;
}


Tui* TuiManager::parseControl( XmlReader* reader, TiXmlElement* element, CCNode* parent, Tui* uiroot )
{
	tAssertc( element, return NULL );
	//return true;
	//read control attribute
	char c_type[32]; memset( c_type, 0x00, sizeof(c_type) );
	char c_img[256]; memset( c_img, 0x00, sizeof(c_img) );
	char c_name[64]; memset( c_name, 0x00, sizeof(c_name) );
	float c_x = 0.0f;
	float c_y = 0.0f;
	float c_ox=0.0f;
	float c_oy=0.0f;
	float c_width=0.0f;
	float c_height=0.0f;

	tAssertc(reader->getString(element, "type", c_type, sizeof(c_type)), return NULL);
//	tAssertc(reader->getString(element, "name", c_name, sizeof(c_name)), return NULL);
//	tAssertc(reader->getString(element, "image", c_img, sizeof(c_img)), return NULL);
	tAssertc(reader->getFloat(element, "x", c_x), return NULL );
	tAssertc(reader->getFloat(element, "y", c_y), return NULL );
	tAssertc(reader->getFloat(element, "ox", c_ox), return NULL );
	tAssertc(reader->getFloat(element, "oy", c_oy), return NULL );
	tAssertc(reader->getFloat(element, "width", c_width), return NULL );
	tAssertc(reader->getFloat(element, "height", c_height), return NULL );

//	tLogDebug( "<c type=%s image=%s x=%.2f y=%.2f ox=%.2f oy=%.2f width=%.2f height=%.2f>", 
//			c_type, c_img, c_x, c_y, c_ox, c_oy, c_width, c_height );

	CCNode* current = parent;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float ox = c_width/2.0 - c_ox;
	float oy = c_height/2.0 - c_oy;
	float x = c_x + ox;
	float y = - (c_y + oy ); //cocos2dx:tui y = -y
	//int scheme_w = ui_manager->schemeWidth();
	//int scheme_h = ui_manager->schemeHeight();
	if( isPanel( c_type ) ){
		//panel has no image, set positon only
		tAssertc(reader->getString(element, "name", c_name, sizeof(c_name)), return NULL);

		current = Tui::create( this, c_name );

		if( NULL != parent ){
			current->setPosition( ccp( x, y ) );
			current->setVisible( true );
			parent->addChild( current );
		}else{
			current->retain();
			uiroot = (Tui*)current;
			x = TuiUtil::convertTuiX( x - scheme_width/2 );
			y = TuiUtil::convertTuiY( y + scheme_height/2 );
			current->setPosition( ccp( x, y ) );
			current->setVisible( false );
			tLogDebug( "load panel %s, x: %.f y: %.f", c_name, x, y );
		}
		current->setContentSize( CCSize( c_width, c_height ) );
	}else if( isImage( c_type ) ){
		tAssertc(reader->getString(element, "image", c_img, sizeof(c_img)), return NULL);
		localizationFile( c_img, sizeof(c_img) );
		tAssertcm( current = CCSprite::create( c_img ), return NULL, "image %s", c_img );
		parent->addChild( current );
		current->setPosition( ccp( x, y) );
	}else if( isButton( c_type ) ){
		tAssertc(reader->getString(element, "image", c_img, sizeof(c_img)), return NULL);
		localizationFile( c_img, sizeof(c_img) );
		char c_click[64]; memset( c_click, 0x00, sizeof(c_click) );
		tAssertc(reader->getString(element,"click_event",c_click,sizeof(c_click)),return NULL);
		tAssertcm(current=TMenuItemImage::create(c_img, this, menu_selector(Tui::onButtonClick)),
						return NULL, "image %s", c_img );
		Tui* pui = dynamic_cast<Tui*>(parent);
		if( pui && NULL == pui->menu_group ){
			pui->menu_group = CCMenu::create();
			pui->addChild( pui->menu_group );
			pui->menu_group->setPosition( CCPointZero );
		}

		if( pui ){
			char fullevent[64]; memset( fullevent, 0x00, sizeof(fullevent) );
			snprintf( fullevent, sizeof(fullevent), "%s_%s", pui->name(), c_click );

			TMenuItemImage* pmenu = (TMenuItemImage*)current;
			pmenu->setEventClick( fullevent );

			//record button event
			uiroot->vec_event.push_back( string( fullevent ) );

			//parent is tui
			current->setPosition( ccp( x, y ) );
			pui->menu_group->addChild( current );
		}
	}else{
		tLogError( "unknown tui control type: %s", c_type );
	}

	if( NULL != parent ){
		if( reader->getString( element, "name", c_name, sizeof(c_name) ) ){
			Tui* pui = dynamic_cast<Tui*>(parent);
			if( pui ){
				pui->dict_control.insert( pair<string,CCNode*>( string(c_name), current ) );
			}else{
				uiroot->dict_control.insert( pair<string,CCNode*>( string(c_name), current ) );
			}
		}
	}

	//find child
	TiXmlElement* sub_element = element->FirstChildElement( kTuiNodeControl );
	if( sub_element ){
		tAssertc( parseControl( reader, sub_element, current, uiroot ), return NULL );
		//find sibling
		TiXmlElement* next_element = sub_element->NextSiblingElement( kTuiNodeControl );
		for( ; next_element; next_element = next_element->NextSiblingElement( kTuiNodeControl ) ){
			tAssertc( parseControl( reader, next_element, current, uiroot ), return NULL );
		}
	}
	return uiroot;
}


bool TuiManager::hasImageAttribute( const char* type )
{
	if( strcmp( type, "image" ) == 0 ) return true;
	if( strcmp( type, "button" )== 0 ) return true;
	return false;
}

bool TuiManager::isPanel( const char* type )
{
	if( strcmp( kTuiControlPanel, type ) == 0 ) return true;
	return false;
}

bool TuiManager::isImage( const char* type )
{
	if( strcmp( kTuiControlImage, type ) == 0 ) return true;
	return false;
}

bool TuiManager::isButton( const char* type )
{
	if( strcmp( kTuiControlButton, type ) == 0 ) return true;
	return false;
}


bool TuiManager::localizationFile( char* image, size_t size )
{
	tAssertc( image, return false );
	tAssertc( size > 0, return false );
	const char* prefix = TuiLocalization::I()->prefix();
	char temp[256]; memset( temp, 0x00, sizeof(temp));
	snprintf( temp, sizeof(temp), "%s", image );
	char full[256]; memset( full, 0x00, sizeof(full));
	char filename[64]; memset( filename, 0x00, sizeof(filename) );
	char* file = strrchr( temp, '/' );
	if( file ){
		*file = '\0';
		strncpy( filename, ++file, sizeof(filename) );
		snprintf( full, sizeof(full), "%s/%s%s", temp, prefix, filename );
	}else{
		snprintf( full, sizeof(full), "%s%s", prefix, temp );
	}
	
	if( isFileExists( full ) ){
		memset( image, 0x00, size );
		snprintf( image, size, "%s", full );
		return true;
	}

	if( file ){
		snprintf( image, size, "%s/%s", temp, filename );
	}else{
		snprintf( image, size, "%s", temp );
	}
	return false;
}

void TuiManager::registerEventCallBack( const char* event, TUIEVENT_CALLBACK cb )
{
	tAssertc( event, return );
	tAssertc( cb, return );

	string e(event);
	TuiEventCallBackDict::iterator it = event_cb_dict.find( e );
	TuiEventCBVector* vec = NULL;
	if( it == event_cb_dict.end() ){
		vec = new TuiEventCBVector();
		event_cb_dict.insert( pair<string, TuiEventCBVector*>( e, vec ) );
	}else{
		vec = it->second;
	}

	size_t nsize = vec->size();
	for( size_t i=0; i<nsize; ++i ){
		tAssertcm( (*vec)[i] != cb, return, "repeate register ui event[%s]", event );
	}

	vec->push_back( cb );
}

void TuiManager::onEvent( void* o, TEvent* e )
{
	const char* event = e->event_id.c_str();
//	tLogDebug( "find callback 0x%x %s", o, event );
	//find callback and call function
	string se(event);
	TuiEventCallBackDict::iterator it = event_cb_dict.find( se );
	tAssertcm( it != event_cb_dict.end(), return, "cant find event cb %s", event );

	TuiEventCBVector* vec = it->second;
	size_t nsize = vec->size();
	TUIEVENT_CALLBACK cb = NULL;
	for( size_t i = 0; i<nsize; ++i ){
		cb = (*vec)[i];
		(this->*cb)( o, e );
	}
}

void TuiManager::onEventBack( void* o, TEvent* e )
{
	tLogDebug( "--> on event back" );
}

void TuiManager::onEventNext( void* o, TEvent* e )
{
	tLogDebug( "--> on event click" );
}

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#endif
bool TuiManager::isFileExists( const char* file )
{
	tAssertc( file, return false );
#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	string fullPath(file);
	if(file[0] != '/'){
		// read from apk
		fullPath.insert(0, CCFileUtils::sharedFileUtils()->getResourceDirectory() );
		fullPath.insert(0, "assets/");
		const char* apk = getApkPath();

		unzFile pFile = NULL;
		bool res = false;
		tAssertc( apk && fullPath.c_str(), return false );
		tAssertc( strlen(apk), return false );
		pFile = unzOpen(apk);
		int nRet = unzLocateFile(pFile, fullPath.c_str(), 1);
		tLogDebug( "zip: %s locatefile: %s %d", apk, fullPath.c_str(), nRet );

		res = UNZ_OK == nRet;
		if (pFile){
			unzClose(pFile);
		}
		return res;
	}else{
		// read rrom other path than user set it
		FILE *fp = fopen( file, "rb" );
		if (fp){
			fclose(fp);
			return true;
		}
	}
#else
	const char* path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(file);
	tAssertcm( path, return NULL, "%s", file );
	FILE* fp = fopen( path, "r" );
	if( fp ){
		fclose( fp ); fp = NULL;
		return true;
	}
#endif
	return false;
}
