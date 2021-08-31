/*
** table.c
** Module to control static tables
*/
#include "../import"
#ifndef table_h
#define table_h

extern Symbol *lua_table;
extern Word    lua_ntable;

extern char  **lua_constant;
extern Word    lua_nconstant;

extern char  **lua_string;
extern Word    lua_nstring;

extern Hash  **lua_array;
extern Word    lua_narray;

extern char   *lua_file[];
extern int     lua_nfile;

extern Word    lua_block;
extern Word    lua_nentity;

#define lua_markstring(s)	(*((s)-1))


int   lua_findsymbol           (char *s);
int   lua_findenclosedconstant (char *s);
int   lua_findconstant         (char *s);
void  lua_travsymbol           (void (*fn)(Object *));
void  lua_markobject           (Object *o);
void  lua_pack                 (void);
void  lua_stringcollector      (void);
char *lua_createstring         (char *s);
void *lua_createarray          (void *a);
char *lua_addfile              (char *fn);
int   lua_delfile 	           (void);
char *lua_filename             (void);
void  lua_nextvar              (void);

#endif 
