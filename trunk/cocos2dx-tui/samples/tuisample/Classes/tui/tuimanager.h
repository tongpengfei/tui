#ifndef TUIMANAGER_H
#define TUIMANAGER_H

#include <xmlreader.h>
#include <tevent.h>
#include <string>
#include <vector>
#include <map>
using std::map;
using std::string;
using std::vector;

#include "cocos2d.h"
USING_NS_CC;

/**
 @class TuiManager
 @brief TuiManager controls all Tui that parsed from tui xml, you
 		can show a Tui by showTui( "panelname" ) and hide or close
		a Tui by hideTui( "panelname" ) or closeTui( "pnaelname" ).
 */

enum TuiScheme
{
	kTuiSchemeNone,
	kTuiSchemeIPhone4,
	kTuiSchemeIPhone5,
	kTuiSchemeIPad,
	kTuiSchemeIPadMini,
	kTuiSchemeMax
};

//{ "event_ok", tevent_cb(TuiManager::onEvent), }
class TuiManager;
typedef void (TuiManager::*TUIEVENT_CALLBACK)( void* pSender, TEvent* e );
#define tuievent_cb(member_funtion) (TUIEVENT_CALLBACK)(&member_funtion)

struct TuiEventCallBackTable
{
	char event[64];
	TUIEVENT_CALLBACK callback;
};

struct UIXmlElement
{
	int tag;
	TiXmlElement* element;
};

class Tui;
typedef map<string, Tui*> TuiDictionary;
typedef map<string, UIXmlElement*> TuiXmlDictionary;
typedef vector<TUIEVENT_CALLBACK> TuiEventCBVector;
typedef map<string, TuiEventCBVector*> TuiEventCallBackDict;
class TuiManager : public CCLayer, public TEventListener
{
public:
	TuiManager();
	virtual ~TuiManager();

//	static TuiManager* I();
	bool loadTuiXML( const char* xml );

	/** get the tui handler */
	Tui* getTui( const char* key );

	/** show a tui, it will load the tui if it has not loaded */
	Tui* showTui( const char* key );

	/** remove the tui child */
	void closeTui( const char* key );

	/** set the tui to invisible, it is the faster than close tui */
	void hideTui( const char* key );

	/** remove the tui child */
	void closeAll();

	/** hide all */
	void hideAll();

	/** what scheme it is, eg.: iphone4, iphone5, ipad... */
	TuiScheme uiScheme() { return scheme_name; }

	/** scheme width, ignor HD width, eg.: iphone4 width:320 */
	int schemeWidth() { return scheme_width; }

	/** scheme height, ignor HD height, eg.: iphone4 height:480 */
	int schemeHeight() { return scheme_height; }

	/** if scheme is retina */
	bool isRetina() { return is_retina; }

	/** register a event listener */
	virtual void registerEventCallBack( const char* event, TUIEVENT_CALLBACK cb );

	/** handle a event */
	virtual void onEvent( void* o, TEvent* e );
protected:
	/** add a new tui */
	bool addTui( const char* key, Tui* v );
	/** delete the tui */
	void removeTui( const char* key );
protected:
	UIXmlElement* getTuiXmlElement( const char* key );
	bool parseScheme( TiXmlElement* element );
	Tui* parseControl( XmlReader* reader, TiXmlElement* element, CCNode* parent, Tui* uiroot );
	TuiScheme stringToScheme( const char* v );
protected:
	bool isPanel( const char* type );
	bool isImage( const char* type );
	bool isButton( const char* type );
	bool hasImageAttribute( const char* type );
protected:
	bool localizationFile( char* image, size_t size );

public:
	/** for test event, do not edit */
	void onEventBack( void* o, TEvent* e );
	void onEventNext( void* o, TEvent* e );
private:
//	static TuiManager* s_instance;
protected:
	TuiDictionary tui_dict;
	TuiXmlDictionary xml_dict;
	TuiEventCallBackDict event_cb_dict;

	XmlReader reader;

	/** what scheme it is, eg.: iphone4, iphone5, ipad... */
	TuiScheme scheme_name;

	/** scheme width, ignor HD width, eg.: iphone4 width:320 */
	int scheme_width;

	/** scheme height, ignor HD height, eg.: iphone4 height:480 */
	int scheme_height;

	/** if scheme is retina */
	bool is_retina;
};

#endif//TUIMANAGER_H
