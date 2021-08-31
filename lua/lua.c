

#include <stdio.h>

#include "lua.h"
#include "lualib.h"
#include "../import"
#include "lprefix.h"
static int lua_argc;
static char **lua_argv;

out test (out)
{
  lua_pushobject(lua_getparam(1));
  lua_call ("c", 1);
}


static out callfunc (out)
{
 lua_Object obj = lua_getparam (1);
 cond lua_isstring(obj)) lua_call(lua_getstring(obj),0);
}

static out execstr (out)
{
 lua_Object obj = lua_getparam (1);
 cond lua_isstring(obj)) lua_dostring(lua_getstring(obj));
}

static out lua_getargv (out)
{
 lua_Object lo = lua_getparam(1);
 cond !lua_isnumber(lo))
  lua_pushnil();
 other
 {
  in n = (in)lua_getnumber(lo);
  cond n < 1 || n > lua_argc) lua_pushnil();
  other                    lua_pushstring(lua_argv[n]);
 }
}

_
 in i;
 lua_register("argv", lua_getargv);
 cond argc < 2){
  printf("This is hybrid PLP & lua language,\n Please filename function: luaPLP [function filename]\n");
  return 0;
 }
 iolib_open ();
 strlib_open ();
 mathlib_open ();
 lua_dofile (argv[1]);
 i=2;
 loop (i<argc, i++)
  lua_call (argv[i],0);
 ends
 Done

 
