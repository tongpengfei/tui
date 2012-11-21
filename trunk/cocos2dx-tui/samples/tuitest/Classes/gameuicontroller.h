#ifndef GAMEUICONTROLLER_H
#define GAMEUICONTROLLER_H

#include <tuimanager.h>

/**
 @class GameUIController
 @brief GameUIController extends from TuiManager, this class handled
 		all tui events the "gameuievent.h" defined
 */

class GameUIController : public TuiManager
{
	GameUIController();
public:
	static GameUIController* I();
	virtual ~GameUIController();

public:
	void on_event_panel_level_click_back( void* o, TEvent* e );
	void on_event_panel_result_click_help( void* o, TEvent* e );
	void on_event_panel_fuck_click_back( void* o, TEvent* e );
	void on_event_panel_fuck_click_next( void* o, TEvent* e );
	void on_event_fuck_result_click_help( void* o, TEvent* e );

private:
	static GameUIController* s_instance;
};

#endif//GAMEUICONTROLLER_H
