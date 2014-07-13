/*
** Lua binding: Lua_cocos2dx_tui
** Generated automatically by tolua++-1.0.92 on 07/13/14 10:16:31.
*/

/****************************************************************************
Copyright (c) 2014 Lijunlin - Jason lee

Created by Lijunlin - Jason lee on 2014

jason.lee.c@foxmail.com
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
#include "WidgetMacros.h"

#if USING_LUA
extern "C" {
#include "tolua_fix.h"
}

#include "lua_cocos2dx_widget.h"
#include "cocos-widget.h"
#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"

using namespace cocos2d;
using namespace cocos2d::cocoswidget;

/* Exported function */
TOLUA_API int  tolua_Lua_cocos2dx_tui_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_TuiBase (lua_State* tolua_S)
{
 TuiBase* self = (TuiBase*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCAnimation");
 tolua_usertype(tolua_S,"AnimationUtil");
 tolua_usertype(tolua_S,"CPageView");
 tolua_usertype(tolua_S,"CCParticleSystemQuad");
 tolua_usertype(tolua_S,"CSlider");
 tolua_usertype(tolua_S,"CGridPageView");
 tolua_usertype(tolua_S,"CToggleView");
 tolua_usertype(tolua_S,"CLabel");
 tolua_usertype(tolua_S,"MovieView");
 tolua_usertype(tolua_S,"TuiBase");
 tolua_usertype(tolua_S,"CCScene");
 tolua_usertype(tolua_S,"TuiManager");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CWidgetWindow");
 tolua_usertype(tolua_S,"CControlView");
 tolua_usertype(tolua_S,"CCheckBox");
 tolua_usertype(tolua_S,"NumericStepper");
 tolua_usertype(tolua_S,"CGridView");
 tolua_usertype(tolua_S,"CTableView");
 tolua_usertype(tolua_S,"CScrollView");
 tolua_usertype(tolua_S,"ArmatureBtn");
 tolua_usertype(tolua_S,"CCEditBox");
 tolua_usertype(tolua_S,"CCArmature");
 tolua_usertype(tolua_S,"CImageView");
 tolua_usertype(tolua_S,"CProgressBar");
 tolua_usertype(tolua_S,"CLayout");
 tolua_usertype(tolua_S,"CButton");
 tolua_usertype(tolua_S,"CImageViewScale9");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CLabelAtlas");
 tolua_usertype(tolua_S,"CListView");
}

/* method: sharedManager of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_sharedManager00
static int tolua_Lua_cocos2dx_tui_TuiManager_sharedManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TuiManager* tolua_ret = (TuiManager*)  TuiManager::sharedManager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TuiManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_init00
static int tolua_Lua_cocos2dx_tui_TuiManager_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: parseScene of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_parseScene00
static int tolua_Lua_cocos2dx_tui_TuiManager_parseScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"TuiBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  TuiBase* pScene = ((TuiBase*)  tolua_tousertype(tolua_S,2,0));
  const char* sceneName = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* xmlPath = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'parseScene'", NULL);
#endif
  {
   self->parseScene(pScene,sceneName,xmlPath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'parseScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: parseCell of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_parseCell00
static int tolua_Lua_cocos2dx_tui_TuiManager_parseCell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CLayout",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  CLayout* pCell = ((CLayout*)  tolua_tousertype(tolua_S,2,0));
  const char* cellName = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* xmlPath = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'parseCell'", NULL);
#endif
  {
   self->parseCell(pCell,cellName,xmlPath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'parseCell'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUseSpriteFrame of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_setUseSpriteFrame00
static int tolua_Lua_cocos2dx_tui_TuiManager_setUseSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUseSpriteFrame'", NULL);
#endif
  {
   self->setUseSpriteFrame(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUseSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createPanel of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createPanel00
static int tolua_Lua_cocos2dx_tui_TuiManager_createPanel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  int w = ((int)  tolua_tonumber(tolua_S,5,0));
  int h = ((int)  tolua_tonumber(tolua_S,6,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createPanel'", NULL);
#endif
  {
   CWidgetWindow* tolua_ret = (CWidgetWindow*)  self->createPanel(tag,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CWidgetWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createPanel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createLayout of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createLayout00
static int tolua_Lua_cocos2dx_tui_TuiManager_createLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  float w = ((float)  tolua_tonumber(tolua_S,5,0));
  float h = ((float)  tolua_tonumber(tolua_S,6,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createLayout'", NULL);
#endif
  {
   CLayout* tolua_ret = (CLayout*)  self->createLayout(tag,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CLayout");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createScrollView of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createScrollView00
static int tolua_Lua_cocos2dx_tui_TuiManager_createScrollView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  int direction = ((int)  tolua_tonumber(tolua_S,3,0));
  float x = ((float)  tolua_tonumber(tolua_S,4,0));
  float y = ((float)  tolua_tonumber(tolua_S,5,0));
  float w = ((float)  tolua_tonumber(tolua_S,6,0));
  float h = ((float)  tolua_tonumber(tolua_S,7,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createScrollView'", NULL);
#endif
  {
   CScrollView* tolua_ret = (CScrollView*)  self->createScrollView(tag,direction,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CScrollView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createScrollView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createListView of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createListView00
static int tolua_Lua_cocos2dx_tui_TuiManager_createListView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* img = ((const char*)  tolua_tostring(tolua_S,3,0));
  float x = ((float)  tolua_tonumber(tolua_S,4,0));
  float y = ((float)  tolua_tonumber(tolua_S,5,0));
  float w = ((float)  tolua_tonumber(tolua_S,6,0));
  float h = ((float)  tolua_tonumber(tolua_S,7,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createListView'", NULL);
#endif
  {
   CListView* tolua_ret = (CListView*)  self->createListView(tag,img,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CListView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createListView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createImage of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createImage00
static int tolua_Lua_cocos2dx_tui_TuiManager_createImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
  float scaleX = ((float)  tolua_tonumber(tolua_S,4,0));
  float scaleY = ((float)  tolua_tonumber(tolua_S,5,0));
  float x = ((float)  tolua_tonumber(tolua_S,6,0));
  float y = ((float)  tolua_tonumber(tolua_S,7,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createImage'", NULL);
#endif
  {
   CImageView* tolua_ret = (CImageView*)  self->createImage(tag,file,scaleX,scaleY,x,y,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CImageView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createImage9 of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createImage900
static int tolua_Lua_cocos2dx_tui_TuiManager_createImage900(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,13,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
  float x = ((float)  tolua_tonumber(tolua_S,4,0));
  float y = ((float)  tolua_tonumber(tolua_S,5,0));
  float w = ((float)  tolua_tonumber(tolua_S,6,0));
  float h = ((float)  tolua_tonumber(tolua_S,7,0));
  float up = ((float)  tolua_tonumber(tolua_S,8,0));
  float down = ((float)  tolua_tonumber(tolua_S,9,0));
  float left = ((float)  tolua_tonumber(tolua_S,10,0));
  float right = ((float)  tolua_tonumber(tolua_S,11,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,12,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createImage9'", NULL);
#endif
  {
   CImageViewScale9* tolua_ret = (CImageViewScale9*)  self->createImage9(tag,file,x,y,w,h,up,down,left,right,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CImageViewScale9");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createImage9'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createBtn of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createBtn00
static int tolua_Lua_cocos2dx_tui_TuiManager_createBtn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* normal = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* select = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* disable = ((const char*)  tolua_tostring(tolua_S,5,0));
  float x = ((float)  tolua_tonumber(tolua_S,6,0));
  float y = ((float)  tolua_tonumber(tolua_S,7,0));
  float w = ((float)  tolua_tonumber(tolua_S,8,0));
  float h = ((float)  tolua_tonumber(tolua_S,9,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,10,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createBtn'", NULL);
#endif
  {
   CButton* tolua_ret = (CButton*)  self->createBtn(tag,normal,select,disable,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createBtn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createToggleView of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createToggleView00
static int tolua_Lua_cocos2dx_tui_TuiManager_createToggleView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  int exclusion = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* normal = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* select = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* disable = ((const char*)  tolua_tostring(tolua_S,6,0));
  float x = ((float)  tolua_tonumber(tolua_S,7,0));
  float y = ((float)  tolua_tonumber(tolua_S,8,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createToggleView'", NULL);
#endif
  {
   CToggleView* tolua_ret = (CToggleView*)  self->createToggleView(tag,exclusion,normal,select,disable,x,y,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CToggleView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createToggleView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSlider of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createSlider00
static int tolua_Lua_cocos2dx_tui_TuiManager_createSlider00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* bg = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* progress = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* thumb = ((const char*)  tolua_tostring(tolua_S,5,0));
  int dir = ((int)  tolua_tonumber(tolua_S,6,0));
  float x = ((float)  tolua_tonumber(tolua_S,7,0));
  float y = ((float)  tolua_tonumber(tolua_S,8,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createSlider'", NULL);
#endif
  {
   CSlider* tolua_ret = (CSlider*)  self->createSlider(tag,bg,progress,thumb,dir,x,y,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CSlider");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSlider'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createProgress of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createProgress00
static int tolua_Lua_cocos2dx_tui_TuiManager_createProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* bg = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* progress = ((const char*)  tolua_tostring(tolua_S,4,0));
  int dir = ((int)  tolua_tonumber(tolua_S,5,0));
  float x = ((float)  tolua_tonumber(tolua_S,6,0));
  float y = ((float)  tolua_tonumber(tolua_S,7,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createProgress'", NULL);
#endif
  {
   CProgressBar* tolua_ret = (CProgressBar*)  self->createProgress(tag,bg,progress,dir,x,y,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CProgressBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createLabel of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createLabel00
static int tolua_Lua_cocos2dx_tui_TuiManager_createLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,14,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,15,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,16,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,17,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,18,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,19,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,20,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,21,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* font = ((const char*)  tolua_tostring(tolua_S,4,0));
  int alignment = ((int)  tolua_tonumber(tolua_S,5,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,6,0));
  int r = ((int)  tolua_tonumber(tolua_S,7,0));
  int g = ((int)  tolua_tonumber(tolua_S,8,0));
  int b = ((int)  tolua_tonumber(tolua_S,9,0));
  float x = ((float)  tolua_tonumber(tolua_S,10,0));
  float y = ((float)  tolua_tonumber(tolua_S,11,0));
  float w = ((float)  tolua_tonumber(tolua_S,12,0));
  float h = ((float)  tolua_tonumber(tolua_S,13,0));
  int r2 = ((int)  tolua_tonumber(tolua_S,14,0));
  int g2 = ((int)  tolua_tonumber(tolua_S,15,0));
  int b2 = ((int)  tolua_tonumber(tolua_S,16,0));
  float strokeSize = ((float)  tolua_tonumber(tolua_S,17,0));
  int shadowDistance = ((int)  tolua_tonumber(tolua_S,18,0));
  float shadowBlur = ((float)  tolua_tonumber(tolua_S,19,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,20,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createLabel'", NULL);
#endif
  {
   CLabel* tolua_ret = (CLabel*)  self->createLabel(tag,text,font,alignment,fontSize,r,g,b,x,y,w,h,r2,g2,b2,strokeSize,shadowDistance,shadowBlur,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CLabel");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createLabelAtlas of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createLabelAtlas00
static int tolua_Lua_cocos2dx_tui_TuiManager_createLabelAtlas00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
  float x = ((float)  tolua_tonumber(tolua_S,4,0));
  float y = ((float)  tolua_tonumber(tolua_S,5,0));
  float w = ((float)  tolua_tonumber(tolua_S,6,0));
  float h = ((float)  tolua_tonumber(tolua_S,7,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createLabelAtlas'", NULL);
#endif
  {
   CLabelAtlas* tolua_ret = (CLabelAtlas*)  self->createLabelAtlas(tag,file,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CLabelAtlas");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createLabelAtlas'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createArmature of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createArmature00
static int tolua_Lua_cocos2dx_tui_TuiManager_createArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* png = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* plist = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* xml = ((const char*)  tolua_tostring(tolua_S,6,0));
  float x = ((float)  tolua_tonumber(tolua_S,7,0));
  float y = ((float)  tolua_tonumber(tolua_S,8,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createArmature'", NULL);
#endif
  {
   CCArmature* tolua_ret = (CCArmature*)  self->createArmature(tag,name,png,plist,xml,x,y,rotation);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArmature");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createAnim of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createAnim00
static int tolua_Lua_cocos2dx_tui_TuiManager_createAnim00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* png = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* plist = ((const char*)  tolua_tostring(tolua_S,5,0));
  float x = ((float)  tolua_tonumber(tolua_S,6,0));
  float y = ((float)  tolua_tonumber(tolua_S,7,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createAnim'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->createAnim(tag,name,png,plist,x,y,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createAnim'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createControl of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createControl00
static int tolua_Lua_cocos2dx_tui_TuiManager_createControl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* baseboard = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* joystick = ((const char*)  tolua_tostring(tolua_S,4,0));
  float x = ((float)  tolua_tonumber(tolua_S,5,0));
  float y = ((float)  tolua_tonumber(tolua_S,6,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createControl'", NULL);
#endif
  {
   CControlView* tolua_ret = (CControlView*)  self->createControl(tag,baseboard,joystick,x,y,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CControlView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createControl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createCheckBox of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createCheckBox00
static int tolua_Lua_cocos2dx_tui_TuiManager_createCheckBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isstring(tolua_S,7,0,&tolua_err) ||
     !tolua_isstring(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* normal1 = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* normal2 = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* select1 = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* select2 = ((const char*)  tolua_tostring(tolua_S,6,0));
  const char* disable1 = ((const char*)  tolua_tostring(tolua_S,7,0));
  const char* disable2 = ((const char*)  tolua_tostring(tolua_S,8,0));
  float x = ((float)  tolua_tonumber(tolua_S,9,0));
  float y = ((float)  tolua_tonumber(tolua_S,10,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,11,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createCheckBox'", NULL);
#endif
  {
   CCheckBox* tolua_ret = (CCheckBox*)  self->createCheckBox(tag,normal1,normal2,select1,select2,disable1,disable2,x,y,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCheckBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createCheckBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createArmatureBtn of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createArmatureBtn00
static int tolua_Lua_cocos2dx_tui_TuiManager_createArmatureBtn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* png = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* plist = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* xml = ((const char*)  tolua_tostring(tolua_S,6,0));
  float x = ((float)  tolua_tonumber(tolua_S,7,0));
  float y = ((float)  tolua_tonumber(tolua_S,8,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createArmatureBtn'", NULL);
#endif
  {
   ArmatureBtn* tolua_ret = (ArmatureBtn*)  self->createArmatureBtn(tag,name,png,plist,xml,x,y,rotation);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ArmatureBtn");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createArmatureBtn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createNumStep of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createNumStep00
static int tolua_Lua_cocos2dx_tui_TuiManager_createNumStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isstring(tolua_S,7,0,&tolua_err) ||
     !tolua_isstring(tolua_S,8,0,&tolua_err) ||
     !tolua_isstring(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,13,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* lnormal = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* lselect = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* ldisable = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* rnormal = ((const char*)  tolua_tostring(tolua_S,6,0));
  const char* rselect = ((const char*)  tolua_tostring(tolua_S,7,0));
  const char* rdisable = ((const char*)  tolua_tostring(tolua_S,8,0));
  const char* stepBg = ((const char*)  tolua_tostring(tolua_S,9,0));
  float x = ((float)  tolua_tonumber(tolua_S,10,0));
  float y = ((float)  tolua_tonumber(tolua_S,11,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,12,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createNumStep'", NULL);
#endif
  {
   NumericStepper* tolua_ret = (NumericStepper*)  self->createNumStep(tag,lnormal,lselect,ldisable,rnormal,rselect,rdisable,stepBg,x,y,rotation);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"NumericStepper");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createNumStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createParticle of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createParticle00
static int tolua_Lua_cocos2dx_tui_TuiManager_createParticle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* plist = ((const char*)  tolua_tostring(tolua_S,3,0));
  float x = ((float)  tolua_tonumber(tolua_S,4,0));
  float y = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createParticle'", NULL);
#endif
  {
   CCParticleSystemQuad* tolua_ret = (CCParticleSystemQuad*)  self->createParticle(tag,plist,x,y);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCParticleSystemQuad");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createParticle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createTableView of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createTableView00
static int tolua_Lua_cocos2dx_tui_TuiManager_createTableView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,13,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* img = ((const char*)  tolua_tostring(tolua_S,3,0));
  int dir = ((int)  tolua_tonumber(tolua_S,4,0));
  int num = ((int)  tolua_tonumber(tolua_S,5,0));
  int cellWidth = ((int)  tolua_tonumber(tolua_S,6,0));
  int cellHeight = ((int)  tolua_tonumber(tolua_S,7,0));
  float x = ((float)  tolua_tonumber(tolua_S,8,0));
  float y = ((float)  tolua_tonumber(tolua_S,9,0));
  float w = ((float)  tolua_tonumber(tolua_S,10,0));
  float h = ((float)  tolua_tonumber(tolua_S,11,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,12,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createTableView'", NULL);
#endif
  {
   CTableView* tolua_ret = (CTableView*)  self->createTableView(tag,img,dir,num,cellWidth,cellHeight,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CTableView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createTableView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createPageView of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createPageView00
static int tolua_Lua_cocos2dx_tui_TuiManager_createPageView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* img = ((const char*)  tolua_tostring(tolua_S,3,0));
  int dir = ((int)  tolua_tonumber(tolua_S,4,0));
  int num = ((int)  tolua_tonumber(tolua_S,5,0));
  float x = ((float)  tolua_tonumber(tolua_S,6,0));
  float y = ((float)  tolua_tonumber(tolua_S,7,0));
  float w = ((float)  tolua_tonumber(tolua_S,8,0));
  float h = ((float)  tolua_tonumber(tolua_S,9,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,10,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createPageView'", NULL);
#endif
  {
   CPageView* tolua_ret = (CPageView*)  self->createPageView(tag,img,dir,num,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CPageView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createPageView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createGridView of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createGridView00
static int tolua_Lua_cocos2dx_tui_TuiManager_createGridView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,13,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* img = ((const char*)  tolua_tostring(tolua_S,3,0));
  int column = ((int)  tolua_tonumber(tolua_S,4,0));
  int num = ((int)  tolua_tonumber(tolua_S,5,0));
  int cellWidth = ((int)  tolua_tonumber(tolua_S,6,0));
  int cellHeight = ((int)  tolua_tonumber(tolua_S,7,0));
  float x = ((float)  tolua_tonumber(tolua_S,8,0));
  float y = ((float)  tolua_tonumber(tolua_S,9,0));
  float w = ((float)  tolua_tonumber(tolua_S,10,0));
  float h = ((float)  tolua_tonumber(tolua_S,11,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,12,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createGridView'", NULL);
#endif
  {
   CGridView* tolua_ret = (CGridView*)  self->createGridView(tag,img,column,num,cellWidth,cellHeight,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CGridView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createGridView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createGridPageView of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createGridPageView00
static int tolua_Lua_cocos2dx_tui_TuiManager_createGridPageView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,14,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,15,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* img = ((const char*)  tolua_tostring(tolua_S,3,0));
  int dir = ((int)  tolua_tonumber(tolua_S,4,0));
  int column = ((int)  tolua_tonumber(tolua_S,5,0));
  int row = ((int)  tolua_tonumber(tolua_S,6,0));
  int num = ((int)  tolua_tonumber(tolua_S,7,0));
  int cellWidth = ((int)  tolua_tonumber(tolua_S,8,0));
  int cellHeight = ((int)  tolua_tonumber(tolua_S,9,0));
  float x = ((float)  tolua_tonumber(tolua_S,10,0));
  float y = ((float)  tolua_tonumber(tolua_S,11,0));
  float w = ((float)  tolua_tonumber(tolua_S,12,0));
  float h = ((float)  tolua_tonumber(tolua_S,13,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,14,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createGridPageView'", NULL);
#endif
  {
   CGridPageView* tolua_ret = (CGridPageView*)  self->createGridPageView(tag,img,dir,column,row,num,cellWidth,cellHeight,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CGridPageView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createGridPageView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createEditBox of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createEditBox00
static int tolua_Lua_cocos2dx_tui_TuiManager_createEditBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
  int inputMode = ((int)  tolua_tonumber(tolua_S,4,0));
  int inputFlag = ((int)  tolua_tonumber(tolua_S,5,0));
  float x = ((float)  tolua_tonumber(tolua_S,6,0));
  float y = ((float)  tolua_tonumber(tolua_S,7,0));
  float w = ((float)  tolua_tonumber(tolua_S,8,0));
  float h = ((float)  tolua_tonumber(tolua_S,9,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,10,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createEditBox'", NULL);
#endif
  {
   CCEditBox* tolua_ret = (CCEditBox*)  self->createEditBox(tag,file,inputMode,inputFlag,x,y,w,h,rotation);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCEditBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createEditBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createMovieView of class  TuiManager */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiManager_createMovieView00
static int tolua_Lua_cocos2dx_tui_TuiManager_createMovieView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiManager* self = (TuiManager*)  tolua_tousertype(tolua_S,1,0);
  float tag = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* json = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* plist = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* png = ((const char*)  tolua_tostring(tolua_S,5,0));
  float x = ((float)  tolua_tonumber(tolua_S,6,0));
  float y = ((float)  tolua_tonumber(tolua_S,7,0));
  float rotation = ((float)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createMovieView'", NULL);
#endif
  {
   MovieView* tolua_ret = (MovieView*)  self->createMovieView(tag,json,plist,png,x,y,rotation);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MovieView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createMovieView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  TuiBase */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiBase_create00
static int tolua_Lua_cocos2dx_tui_TuiBase_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TuiBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TuiBase* tolua_ret = (TuiBase*)  TuiBase::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TuiBase");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  TuiBase */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiBase_init00
static int tolua_Lua_cocos2dx_tui_TuiBase_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiBase* self = (TuiBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TuiBase */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiBase_new00
static int tolua_Lua_cocos2dx_tui_TuiBase_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TuiBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TuiBase* tolua_ret = (TuiBase*)  Mtolua_new((TuiBase)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TuiBase");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  TuiBase */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiBase_new00_local
static int tolua_Lua_cocos2dx_tui_TuiBase_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TuiBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TuiBase* tolua_ret = (TuiBase*)  Mtolua_new((TuiBase)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TuiBase");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  TuiBase */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiBase_delete00
static int tolua_Lua_cocos2dx_tui_TuiBase_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiBase* self = (TuiBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getControl of class  TuiBase */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiBase_getControl00
static int tolua_Lua_cocos2dx_tui_TuiBase_getControl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiBase* self = (TuiBase*)  tolua_tousertype(tolua_S,1,0);
  int tagPanel = ((int)  tolua_tonumber(tolua_S,2,0));
  int tagControl = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getControl'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getControl(tagPanel,tagControl);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getControl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPanel of class  TuiBase */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiBase_getPanel00
static int tolua_Lua_cocos2dx_tui_TuiBase_getPanel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiBase* self = (TuiBase*)  tolua_tousertype(tolua_S,1,0);
  int tagPanel = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPanel'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getPanel(tagPanel);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPanel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoRemoveUnusedSpriteFrame of class  TuiBase */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiBase_setAutoRemoveUnusedSpriteFrame00
static int tolua_Lua_cocos2dx_tui_TuiBase_setAutoRemoveUnusedSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiBase",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiBase* self = (TuiBase*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoRemoveUnusedSpriteFrame'", NULL);
#endif
  {
   self->setAutoRemoveUnusedSpriteFrame(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoRemoveUnusedSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAutoRemoveUnusedSpriteFrame of class  TuiBase */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_TuiBase_getAutoRemoveUnusedSpriteFrame00
static int tolua_Lua_cocos2dx_tui_TuiBase_getAutoRemoveUnusedSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TuiBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TuiBase* self = (TuiBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAutoRemoveUnusedSpriteFrame'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getAutoRemoveUnusedSpriteFrame();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAutoRemoveUnusedSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createAnimWithName of class  AnimationUtil */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_AnimationUtil_createAnimWithName00
static int tolua_Lua_cocos2dx_tui_AnimationUtil_createAnimWithName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationUtil",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  float delay = ((float)  tolua_tonumber(tolua_S,3,0));
  unsigned int iLoops = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
  {
   CCAnimation* tolua_ret = (CCAnimation*)  AnimationUtil::createAnimWithName(name,delay,iLoops);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createAnimWithName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createAnimWithNameAndNum of class  AnimationUtil */
#ifndef TOLUA_DISABLE_tolua_Lua_cocos2dx_tui_AnimationUtil_createAnimWithNameAndNum00
static int tolua_Lua_cocos2dx_tui_AnimationUtil_createAnimWithNameAndNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationUtil",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int iNum = ((int)  tolua_tonumber(tolua_S,3,0));
  float delay = ((float)  tolua_tonumber(tolua_S,4,0));
  unsigned int iLoops = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
  {
   CCAnimation* tolua_ret = (CCAnimation*)  AnimationUtil::createAnimWithNameAndNum(name,iNum,delay,iLoops);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createAnimWithNameAndNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Lua_cocos2dx_tui_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"TuiManager","TuiManager","CCObject",NULL);
  tolua_beginmodule(tolua_S,"TuiManager");
   tolua_function(tolua_S,"sharedManager",tolua_Lua_cocos2dx_tui_TuiManager_sharedManager00);
   tolua_function(tolua_S,"init",tolua_Lua_cocos2dx_tui_TuiManager_init00);
   tolua_function(tolua_S,"parseScene",tolua_Lua_cocos2dx_tui_TuiManager_parseScene00);
   tolua_function(tolua_S,"parseCell",tolua_Lua_cocos2dx_tui_TuiManager_parseCell00);
   tolua_function(tolua_S,"setUseSpriteFrame",tolua_Lua_cocos2dx_tui_TuiManager_setUseSpriteFrame00);
   tolua_function(tolua_S,"createPanel",tolua_Lua_cocos2dx_tui_TuiManager_createPanel00);
   tolua_function(tolua_S,"createLayout",tolua_Lua_cocos2dx_tui_TuiManager_createLayout00);
   tolua_function(tolua_S,"createScrollView",tolua_Lua_cocos2dx_tui_TuiManager_createScrollView00);
   tolua_function(tolua_S,"createListView",tolua_Lua_cocos2dx_tui_TuiManager_createListView00);
   tolua_function(tolua_S,"createImage",tolua_Lua_cocos2dx_tui_TuiManager_createImage00);
   tolua_function(tolua_S,"createImage9",tolua_Lua_cocos2dx_tui_TuiManager_createImage900);
   tolua_function(tolua_S,"createBtn",tolua_Lua_cocos2dx_tui_TuiManager_createBtn00);
   tolua_function(tolua_S,"createToggleView",tolua_Lua_cocos2dx_tui_TuiManager_createToggleView00);
   tolua_function(tolua_S,"createSlider",tolua_Lua_cocos2dx_tui_TuiManager_createSlider00);
   tolua_function(tolua_S,"createProgress",tolua_Lua_cocos2dx_tui_TuiManager_createProgress00);
   tolua_function(tolua_S,"createLabel",tolua_Lua_cocos2dx_tui_TuiManager_createLabel00);
   tolua_function(tolua_S,"createLabelAtlas",tolua_Lua_cocos2dx_tui_TuiManager_createLabelAtlas00);
   tolua_function(tolua_S,"createArmature",tolua_Lua_cocos2dx_tui_TuiManager_createArmature00);
   tolua_function(tolua_S,"createAnim",tolua_Lua_cocos2dx_tui_TuiManager_createAnim00);
   tolua_function(tolua_S,"createControl",tolua_Lua_cocos2dx_tui_TuiManager_createControl00);
   tolua_function(tolua_S,"createCheckBox",tolua_Lua_cocos2dx_tui_TuiManager_createCheckBox00);
   tolua_function(tolua_S,"createArmatureBtn",tolua_Lua_cocos2dx_tui_TuiManager_createArmatureBtn00);
   tolua_function(tolua_S,"createNumStep",tolua_Lua_cocos2dx_tui_TuiManager_createNumStep00);
   tolua_function(tolua_S,"createParticle",tolua_Lua_cocos2dx_tui_TuiManager_createParticle00);
   tolua_function(tolua_S,"createTableView",tolua_Lua_cocos2dx_tui_TuiManager_createTableView00);
   tolua_function(tolua_S,"createPageView",tolua_Lua_cocos2dx_tui_TuiManager_createPageView00);
   tolua_function(tolua_S,"createGridView",tolua_Lua_cocos2dx_tui_TuiManager_createGridView00);
   tolua_function(tolua_S,"createGridPageView",tolua_Lua_cocos2dx_tui_TuiManager_createGridPageView00);
   tolua_function(tolua_S,"createEditBox",tolua_Lua_cocos2dx_tui_TuiManager_createEditBox00);
   tolua_function(tolua_S,"createMovieView",tolua_Lua_cocos2dx_tui_TuiManager_createMovieView00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TuiBase","TuiBase","CCScene",tolua_collect_TuiBase);
  #else
  tolua_cclass(tolua_S,"TuiBase","TuiBase","CCScene",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TuiBase");
   tolua_function(tolua_S,"create",tolua_Lua_cocos2dx_tui_TuiBase_create00);
   tolua_function(tolua_S,"init",tolua_Lua_cocos2dx_tui_TuiBase_init00);
   tolua_function(tolua_S,"new",tolua_Lua_cocos2dx_tui_TuiBase_new00);
   tolua_function(tolua_S,"new_local",tolua_Lua_cocos2dx_tui_TuiBase_new00_local);
   tolua_function(tolua_S,".call",tolua_Lua_cocos2dx_tui_TuiBase_new00_local);
   tolua_function(tolua_S,"delete",tolua_Lua_cocos2dx_tui_TuiBase_delete00);
   tolua_function(tolua_S,"getControl",tolua_Lua_cocos2dx_tui_TuiBase_getControl00);
   tolua_function(tolua_S,"getPanel",tolua_Lua_cocos2dx_tui_TuiBase_getPanel00);
   tolua_function(tolua_S,"setAutoRemoveUnusedSpriteFrame",tolua_Lua_cocos2dx_tui_TuiBase_setAutoRemoveUnusedSpriteFrame00);
   tolua_function(tolua_S,"getAutoRemoveUnusedSpriteFrame",tolua_Lua_cocos2dx_tui_TuiBase_getAutoRemoveUnusedSpriteFrame00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"AnimationUtil","AnimationUtil","",NULL);
  tolua_beginmodule(tolua_S,"AnimationUtil");
   tolua_function(tolua_S,"createAnimWithName",tolua_Lua_cocos2dx_tui_AnimationUtil_createAnimWithName00);
   tolua_function(tolua_S,"createAnimWithNameAndNum",tolua_Lua_cocos2dx_tui_AnimationUtil_createAnimWithNameAndNum00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Lua_cocos2dx_tui (lua_State* tolua_S) {
 return tolua_Lua_cocos2dx_tui_open(tolua_S);
};
#endif

#endif //USING_LUA