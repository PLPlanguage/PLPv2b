/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

/*
** Libraries to use in LUA and PLP programs
** Technology Group in Computer Graphics
*/
#ifndef lualib_h
#define lualib_h

void iolib_open   (void);
void strlib_open  (void);
void mathlib_open (void);


/* auxiliar functions (private) */
void lua_arg_error(char *funcname);
char *lua_check_string (int numArg, char *funcname);
float lua_check_number (int numArg, char *funcname);
char *lua_opt_string (int numArg, char *def, char *funcname);
#define lua_opt_int(n,d)	((int)lua_opt_number(n,d))

#endif 
