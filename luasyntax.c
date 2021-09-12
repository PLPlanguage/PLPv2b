/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License and MIT License
 Time: 21/08/01 00:00 GMT
*/

//Importing Lua language libraries
#include <luasyntax.h>

out luaimport ()
{
    mathlib_open();
    iolib_open();
    strlib_open();
}

out test (out)
{
  pushobject(getparam(1));
  call ("c", 1);
}

out printl ($ *str)
{
    luaimport();
     $ strs[256];
    strcpy(strs,"print(");
    strcat(strs,str);
    strcat(strs,")");
    dostring(strs);
}

out writel ($ *str)
{
    luaimport();
     $ strs[256];
     strcpy(strs,"write(");
     strcat(strs,str);
     strcat(strs,")");
     dostring(strs);
     return;
}

out debugl (out)
{
    luaimport();
   when 1 then
     $ buffer[256];
    fprintf(stderr, "luaPLP_debug|>");
   cond fgets(buffer, sizeof(buffer),stdin) == 0) return;
   cond indexof(buffer, "exit\n",0)) return;
    dostring(buffer);
    ends
}

in executel ($ * s)
{
   cond s == NULL then
    lua_error ("incorrect argument to function 'execute`");
    return 0;
 ends
   other{
    in res = system(s);
    return res;
 }
}

