#ifndef TEVENT_H
#define TEVENT_H

#include <map>
#include <vector>
#include <string>
using std::map;
using std::vector;
using std::string;

/**
 @struct TEvent
 @brief Tui event base struct
 */
struct TEvent
{
	string event_id;
};

/**
 @class TEventListener
 @brief TEvent listener
 */
class TEventListener
{
public:
	/**
	 @brief default event handler
	 @param void* pSender: event sender
	 @param TEvent* e: event
	 */
	virtual void onEvent( void* pSender, TEvent* e ){(void)pSender; (void)e;}
};

//! tui event handler callback
typedef void (TEventListener::*TEVENT_CALLBACK)( void* pSender, TEvent* e );
#define tevent_cb(member_funtion) (TEVENT_CALLBACK)(&member_funtion)

/**
 @class TEventController
 @brief tui event controller, event dispatcher
 */
class TEventController
{
	struct TListener{
		TEventListener* pTarget;
		TEVENT_CALLBACK cb;
	};

	typedef vector<TListener*> TEventCBVector;
	typedef map<string, TEventCBVector*> TEventListenerMap;
public:
	static TEventController* I();

	/**
	 @brief register event listener, the handler must register in controller, 
	 		it will triger if the event id was happen
	 @param string eventid: which event you care
	 @param TEventListener* pTarget: the target who will call the callback
	 @param TEVENT_CALLBACK callback: event handler
	 */
	void registerListener( string eventid, TEventListener* pTarget, TEVENT_CALLBACK callback );

	/**
	 @brief remove event handler
	 @param string eventid: which event you care
	 @param TEventListener* pTarget: the target who will call the callback
	 @param TEVENT_CALLBACK callback: event handler
	 */
	void unregisterListener( string eventid, TEventListener* pTarget, TEVENT_CALLBACK callback );

	/**
	 @brief dispatch a event, all listener will triger who listening this event id
	 @param void* pSender: the event sender
	 @param TEvent* e: event
	 */
	void dispatchEvent( void* pSender, TEvent* e ); 

	/** pring registed listener */
	void debug();
private:
	static TEventController* s_instance;
protected:
	/** event listener table */
	TEventListenerMap event_listener_map;
};

#endif//TEVENT_H
