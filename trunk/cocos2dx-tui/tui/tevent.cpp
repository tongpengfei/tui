#include <tevent.h>
#include <macro.h>
using std::pair;

TEventController* TEventController::s_instance = NULL;
TEventController* TEventController::I()
{
	if( NULL == s_instance ){
		s_instance = new TEventController();
	}
	return s_instance;
}

void TEventController::registerListener( string eventid, TEventListener* pTarget, TEVENT_CALLBACK cb )
{
	tAssertcm( cb, return, "eventid %s", eventid.c_str() );
	TEventCBVector* pcbvec = NULL;
	TEventListenerMap::iterator it = event_listener_map.find( eventid ); 
	if( it != event_listener_map.end() ){
		pcbvec = it->second;
	}else{
		pcbvec = new TEventCBVector();
		event_listener_map.insert( pair<string, TEventCBVector*>(eventid, pcbvec) );
	}
	TListener* plistener = new TListener();
	plistener->pTarget = pTarget;
	plistener->cb = cb;
	pcbvec->push_back( plistener );
}

void TEventController::unregisterListener( string eventid, TEventListener* pTarget, TEVENT_CALLBACK cb )
{
	tAssertcm( cb, return , "eventid %s", eventid.c_str() );

	TEventListenerMap::iterator it = event_listener_map.find( eventid ); 
	tAssertcm( it != event_listener_map.end(), return, "can not find event %s", eventid.c_str() );
	TEventCBVector& cbvec = *(it->second);
	int n = cbvec.size();
	for( int i=0; i<n; ++i ){
		TListener* plistener = cbvec[i];
		if( plistener->cb == cb && plistener->pTarget == pTarget ){
			cbvec.erase( cbvec.begin() + i );
			delete plistener;
			plistener = NULL;
			break;
		}
	}
}


/*
	I think there has some problem when user remove or add IListener to TEventController
	
	you must copy the dispatch listener vector, and soon dispatch it
*/
void TEventController::dispatchEvent( void* o, TEvent* e )
{
	tAssertc( e, return );
	TEventListenerMap::iterator it = event_listener_map.find( e->event_id ); 
	if( it != event_listener_map.end() ){
		TEventCBVector& vec = *(it->second);
		int n = vec.size();
		/*TListener* plistener = NULL;
		TEventListener* pTarget = NULL;
		TEVENT_CALLBACK cb = NULL;
		for( int i=0; i<n; ++i ){
			plistener = vec[i];
			pTarget = plistener->pTarget;
			cb = plistener->cb;
			(pTarget->*cb)( o, e );
		}*/
		
		TEventCBVector vec_copy(n);  // this vec_copy can be an member variable of TEventController for optmize
		std::copy(vec.begin(), vec.end(), vec_copy.begin());
		
		TListener* plistener = NULL;
		TEventListener* pTarget = NULL;
		TEVENT_CALLBACK cb = NULL;
		for( int i=0; i<n; ++i ){
			plistener = vec_copy[i];
			pTarget = plistener->pTarget;
			cb = plistener->cb;
			(pTarget->*cb)( o, e );
		}
		
	}
}

void TEventController::debug()
{
	TEventListenerMap::iterator it = event_listener_map.begin();
	while( it != event_listener_map.end() ){
		const char* eventid = it->first.c_str();
		TEventCBVector* cbvec = it->second;
		tLogDebug( "eventid %s, listener %p", eventid, cbvec );
		it++;
	}
}
