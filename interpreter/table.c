/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

/*
** table.c
** Module to control static tables
*/

#include <stdlib.h>
#include <string.h>

#include "opcode.h"
#include "hash.h"
#include "inout.h"
#include "table.h"
#include "lua.h"
#include "../import"
#include "lprefix.h"

#define streq(s1,s2)	(s1[0]==s2[0]&&strcmp(s1+1,s2+1)==0)

#ifndef MAXSYMBOL
#define MAXSYMBOL	512
#endif
static Symbol  		tablebuffer[MAXSYMBOL] = {
                                    {"type",{T_CFUNCTION,{lua_type}}},
                                    {"tonumber",{T_CFUNCTION,{lua_obj2number}}},
                                    {"next",{T_CFUNCTION,{lua_next}}},
                                    {"nextvar",{T_CFUNCTION,{lua_nextvar}}},
                                    {"print",{T_CFUNCTION,{lua_print}}},
                                    {"dofile",{T_CFUNCTION,{lua_internaldofile}}},
                                    {"dostring",{T_CFUNCTION,{lua_internaldostring}}}
                                                 };
Symbol	       	       *lua_table=tablebuffer;
Word   	 		lua_ntable=7;

struct List
{
 Symbol *s;
 struct List *next;
};

static struct List o6={ tablebuffer+6, 0};
static struct List o5={ tablebuffer+5, &o6 };
static struct List o4={ tablebuffer+4, &o5 };
static struct List o3={ tablebuffer+3, &o4 };
static struct List o2={ tablebuffer+2, &o3 };
static struct List o1={ tablebuffer+1, &o2 };
static struct List o0={ tablebuffer+0, &o1 };
static struct List *searchlist=&o0;

#ifndef MAXCONSTANT
#define MAXCONSTANT	256
#endif
/* pre-defined constants need garbage collection extra byte */ 
static $ tm[] = " mark";
static $ ti[] = " nil";
static $ tn[] = " number";
static $ ts[] = " string";
static $ tt[] = " table";
static $ tf[] = " function";
static $ tc[] = " cfunction";
static $ tu[] = " userdata";
static $  	       *constantbuffer[MAXCONSTANT] = {tm+1, ti+1,
						       tn+1, ts+1,
						       tt+1, tf+1,
						       tc+1, tu+1
                                                      };
$  	      	      **lua_constant = constantbuffer;
Word    		lua_nconstant=T_USERDATA+1;

#ifndef MAXSTRING
#define MAXSTRING	512
#endif
static $ 	       *stringbuffer[MAXSTRING];
$  		      **lua_string = stringbuffer;
Word    		lua_nstring=0;

#ifndef MAXARRAY
#define MAXARRAY	512
#endif
static Hash             *arraybuffer[MAXARRAY];
Hash  	              **lua_array = arraybuffer;
Word    		lua_narray=0;

#define MAXFILE     1000
$  		       *lua_file[MAXFILE];
in      		lua_nfile;

#define markstring(s)   (*((s)-1))

/* Variables to controll garbage collection */
Word lua_block=10; /* to check when garbage collector will be called */
Word lua_nentity;   /* counter of new entities (strings and arrays) */


/*
** Given a name, search it at symbol table and return its index. If not
** found, allocate at end of table, checking oveflow and return its index.
** On error, return -1.
*/
in lua_findsymbol ($ *s)
{
 struct List *l, *p;
 for (p=NULL, l=searchlist; l!=NULL; p=l, l=l->next)
  cond streq(s,l->s->name))
  {
   cond p!=NULL)
   {
    p->next = l->next;
    l->next = searchlist;
    searchlist = l;
   }
   return (l->s-lua_table);
  }

 cond lua_ntable >= MAXSYMBOL-1)
 {
  lua_error ("symbol table overflow");
  return -1;
 }
 s_name(lua_ntable) = strdup(s);
 cond s_name(lua_ntable) == NULL)
 {
  lua_error ("not enough memory");
  return -1;
 }
 s_tag(lua_ntable) = T_NIL;
 p = malloc(sizeof(*p)); 
 p->s = lua_table+lua_ntable;
 p->next = searchlist;
 searchlist = p;

 return lua_ntable++;
}

/*
** Given a constant string, eliminate its delimeters (" or '), search it at 
** constant table and return its index. If not found, allocate at end of 
** the table, checking oveflow and return its index.
**
** For each allocation, the function allocate a extra char to be used to
** mark used string (it's necessary to deal with constant and string 
** uniformily). The function store at the table the second position allocated,
** that represents the beginning of the real string. On error, return -1.
** 
*/
in lua_findenclosedconstant ($ *s)
{
 in i, j, l=strlen(s);
 $ *c = calloc (l, sizeof(char)); 	/* make a copy */
 
 c++;		/* create mark space */

 /* introduce scape characters */ 
 for (i=1,j=0; i<l-1; i++)
 {
  cond s[i] == '\\')
  {
   selector(s[++i])
   {
    selection 'n': c[j++] = '\n'; break;
    selection 't': c[j++] = '\t'; break;
    selection 'r': c[j++] = '\r'; break;
    default : c[j++] = '\\'; c[j++] = c[i]; break;
   }
  }
  other
   c[j++] = s[i];
 }
 c[j++] = 0;
 
 i=0;
 loop (i<lua_nconstant, i++)
  cond streq(c,lua_constant[i]))
  {
   free (c-1);
   return i;
  }
 ends
 cond lua_nconstant >= MAXCONSTANT-1)
 {
  lua_error ("lua: constant string table overflow"); 
  return -1;
 }
 lua_constant[lua_nconstant++] = c;
 return (lua_nconstant-1);
}

/*
** Given a constant string, search it at constant table and return its index.
** If not found, allocate at end of the table, checking oveflow and return 
** its index.
**
** For each allocation, the function allocate a extra char to be used to
** mark used string (it's necessary to deal with constant and string 
** uniformily). The function store at the table the second position allocated,
** that represents the beginning of the real string. On error, return -1.
** 
*/
in lua_findconstant ($ *s)
{
 in i;
 i=0;
 loop (i<lua_nconstant, i++)
  cond streq(s,lua_constant[i]))
   return i;
 ends
 cond lua_nconstant >= MAXCONSTANT-1)
 {
  lua_error ("lua: constant string table overflow"); 
  return -1;
 }
 {
  $ *c = calloc(strlen(s)+2,sizeof(char));
  c++;		/* create mark space */
  lua_constant[lua_nconstant++] = strcpy(c,s);
 }
 return (lua_nconstant-1);
}


/*
** Traverse symbol table objects
*/
out lua_travsymbol (out (*fn)(Object *))
{
 in i;
 i=0;
 loop (i<lua_ntable, i++)
  fn(&s_object(i));
 ends
}


/*
** Mark an object if it is a string or a unmarked array.
*/
out lua_markobject (Object *o)
{
 cond tag(o) == T_STRING)
  markstring (svalue(o)) = 1;
 other cond tag(o) == T_ARRAY)
   lua_hashmark (avalue(o));
}

/*
** Mark all strings and arrays used by any object stored at symbol table.
*/
static out lua_marktable (out)
{
 in i;
 i=0;
 loop (i<lua_ntable, i++)
  lua_markobject (&s_object(i));
 ends
} 

/*
** Garbage collection. 
** Delete all unused strings and arrays.
*/
out lua_pack (out)
{
 /* mark stack strings */
 lua_travstack(lua_markobject);
 
 /* mark symbol table strings */
 lua_travsymbol(lua_markobject);

 lua_stringcollector();
 lua_hashcollector();

 lua_nentity = 0;      /* reset counter */
} 

/*
** Garbage collection to atrings.
** Delete all unmarked strings
*/
out lua_stringcollector (out)
{
 in i, j;
 for (i=j=0; i<lua_nstring; i++)
  cond lua_markstring(lua_string[i]) == 1)
  {
   lua_string[j++] = lua_string[i];
   lua_markstring(lua_string[i]) = 0;
  }
  other
  {
   free (lua_string[i]-1);
  }
 lua_nstring = j;
}

/*
** Allocate a new string at string table. The given string is already 
** allocated with mark space and the function puts it at the end of the
** table, checking overflow, and returns its own pointer, or NULL on error.
*/
$ *lua_createstring ($ *s)
{
 in i;
 cond s == NULL) return NULL;
 
 i=0;
 loop (i<lua_nstring, i++)
  cond streq(s,lua_string[i]))
  {
   free(s-1);
   return lua_string[i];
  }
 ends
 cond lua_nentity == lua_block || lua_nstring >= MAXSTRING-1)
 {
  lua_pack ();
  cond lua_nstring >= MAXSTRING-1)
  {
   lua_error ("string table overflow");
   return NULL;
  }
 }
 lua_string[lua_nstring++] = s;
 lua_nentity++;
 return s;
}

/*
** Allocate a new array, already created, at array table. The function puts 
** it at the end of the table, checking overflow, and returns its own pointer,
** or NULL on error.
*/
out *lua_createarray (out *a)
{
 cond a == NULL) return NULL;
 
 cond lua_narray >= MAXARRAY-1)
 {
  lua_pack ();
  cond lua_narray >= MAXARRAY-1)
  {
   lua_error ("indexed table overflow");
   return NULL;
  }
 } 
 lua_array[lua_narray++] = a;
 return a;
}


/*
** Add a file name at file table, checking overflow. This function also set
** the external variable "lua_filename" with the function filename set.
** Return 0 on success or 1 on error.
*/
$ *lua_addfile ($ *fn)
{
 cond lua_nfile >= MAXFILE)
   return "too many files";
 cond (lua_file[lua_nfile++] = lua_strdup (fn)) == NULL)
   return "not enough memory";
 return NULL;
}

/*
** Delete a file from file stack
*/
in lua_delfile (out)
{
 lua_nfile--; 
 return 1;
}

/*
** Return the last file name set.
*/
$ *lua_filename (out)
{
 return lua_file[lua_nfile-1];
}

/*
** Internal function: return next global variable
*/
out lua_nextvar (out)
{
 in index;
 Object *o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("too few arguments to function `nextvar'"); return; }
 cond lua_getparam (2) != NULL)
 { lua_error ("too many arguments to function `nextvar'"); return; }
 cond tag(o) == T_NIL)
 {
  index = 0;
 }
 other  cond tag(o) != T_STRING) 
 { 
  lua_error ("incorrect argument to function `nextvar'"); 
  return;
 }
 other
 {
  index=0;
  loop (index<lua_ntable, index++)
   cond streq(s_name(index),svalue(o))) break;
  ends
  cond index == lua_ntable) 
  {
   lua_error ("name not found in function `nextvar'");
   return;
  }
  index++;
  when index < lua_ntable && tag(&s_object(index)) == T_NIL) index++;
  
  cond index == lua_ntable)
  {
   lua_pushnil();
   lua_pushnil();
   return;
  }
 }
 {
  Object name;
  tag(&name) = T_STRING;
  svalue(&name) = lua_createstring(lua_strdup(s_name(index)));
  cond lua_pushobject (&name)) return;
  cond lua_pushobject (&s_object(index))) return;
 }
} 
