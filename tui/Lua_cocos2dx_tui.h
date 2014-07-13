#ifndef __TUI_LUA_H__
#define __TUI_LUA_H__

#include "../../CocosWidget/WidgetMacros.h"

#if USING_LUA
#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

TOLUA_API int tolua_Lua_cocos2dx_tui_open(lua_State* tolua_S);
#endif

#endif //__TUI_LUA_H__
