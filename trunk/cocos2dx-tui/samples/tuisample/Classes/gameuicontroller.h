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
	void on_event_panel_start_click_btn_start( void*o, TEvent* e );
	void on_event_panel_start_click_btn_sound( void*o, TEvent* e );
	void on_event_panel_game_click_btn_back( void*o, TEvent* e );
	void on_event_panel_game_click_btn_help( void*o, TEvent* e );

private:
	static GameUIController* s_instance;
};

#endif//GAMEUICONTROLLER_H
