/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

/*
** inout.h
** I/O in lua Programming Language
** Cunknown
*/

#include "../import"
#ifndef inout_h
#define inout_h

extern int lua_linenumber;
extern int lua_debug;
extern int lua_debugline;

char *lua_openfile    (char *fn);
void lua_closefile    (void);
int  lua_openstring   (char *s);
void lua_closestring  (void);
int  lua_pushfunction (int file, int function);
void lua_popfunction  (void);
void lua_reportbug    (char *s);

#endif
