  #ifndef LUASYNTAX_H
    #define LUASYNTAX_H

#include "Define"
#include "Type"
#include "lua/lua.h"
#include "lua/lualib.h" 

    #define errorfunction   lua_errorfunction
    #define dofile          lua_dofile
    #define dostring        lua_dostring
    #define call            lua_call

    #define getparam        lua_getparam
    #define getnumber       lua_getnumber
    #define getstring       lua_getstring
    #define copystring      lua_copystring
    #define getcfunction    lua_getcfunction
    #define getuserdata     lua_getuserdata
    #define getfield        lua_getfield
    #define getindexed      lua_getindexed
    #define lua_getglobal   lua_getglobal

    #define pop             lua_pop

    #define pushnil         lua_pushnil
    #define pushnumber      lua_pushnumber
    #define pushstring      lua_pushstring
    #define pushcfunction   lua_pushcfunction
    #define pushuserdata    lua_pushuserdata
    #define pushobject      lua_pushobject

    #define storeglobal     lua_storeglobal
    #define storeindexed    lua_sotreindexed
    #define isnil           lua_isnil
             #undef  isnumber
    #define isnumber        lua_isnumber
    #define isstring         lua_isstring
    #define istable         lua_istable
    #define iscfunction     lua_iscfunction
    #define isuserdata      lua_isuserdata

// -----------------lua syntax---------------------

  #ifdef __cplusplus
	extern "C"{
  #endif

out printl($ * str);
out writel($ * str);
out debugl(out);
in  executel($ * s);

  #ifdef __cplusplus
	}
  #endif
  
  #endif
