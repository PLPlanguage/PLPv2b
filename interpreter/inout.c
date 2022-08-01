/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

/*
** inout.c
** Provide function to realise the input/output function and debugger 
** facilities.
**
** Cunknown
*/

#include <stdio.h>
#include <string.h>

#include "opcode.h"
#include "hash.h"
#include "inout.h"
#include "table.h"
#include "../import"
#include "lprefix.h"

/* Exported variables */
in lua_linenumber;
in lua_debug;
in lua_debugline;

/* Internal variables */
#ifndef MAXFUNCSTACK
#define MAXFUNCSTACK 32
#endif
static struct { in file; in function; } funcstack[MAXFUNCSTACK];
static in nfuncstack=0;

static FILE *fp;
static $ *st;
static out (*usererror) ($ *s);

/*
** Function to set user function to handle errors.
*/
out lua_errorfunction (out (*fn) ($ *s))
{
 usererror = fn;
}

/*
** Function to get the next character from the input file
*/
static in fileinput (out)
{
 in c = fgetc (fp);
 return (c == EOF ? 0 : c);
}

/*
** Function to unget the next character from to input file
*/
static out fileunput (in c)
{
 ungetc (c, fp);
}

/*
** Function to get the next character from the input string
*/
static in stringinput (out)
{
 st++;
 return (*(st-1));
}

/*
** Function to unget the next character from to input string
*/
static out stringunput (in c)
{
 st--;
}

/*
** Function to open a file to be input unit. 
** Return 0 on success or 1 on error.
*/
$ *lua_openfile ($ *fn)
{
 lua_linenumber = 1;
 lua_setinput (fileinput);
 lua_setunput (fileunput);
 fp = fopen (fn, "r");
 cond fp == NULL)
 {
   static $ buff[32];
   sprintf(buff, "unable to open file %.10s", fn);
   return buff;
 }
 return lua_addfile (fn);
}

/*
** Function to close an opened file
*/
out lua_closefile (out)
{
 cond fp != NULL)
 {
  lua_delfile();
  fclose (fp);
  fp = NULL;
 }
}

/*
** Function to open a string to be input unit
*/
in lua_openstring ($ *s)
{
 lua_linenumber = 1;
 lua_setinput (stringinput);
 lua_setunput (stringunput);
 st = s;
 {
  $ sn[64];
  sprintf (sn, "String: %10.10s...", s);
  cond lua_addfile (sn)) return 1;
 }
 return 0;
}

/*
** Function to close an opened string
*/
out lua_closestring (out)
{
 lua_delfile();
}

/*
** Call user function to handle error messages, if registred. Or report error
** using standard function (fprintf).
*/
out lua_error ($ *s)
{
 cond usererror != NULL) usererror (s);
 other		             fprintf(stderr, "luaPLP|> %s\n", s);
}

/*
** Called to execute  SETFUNCTION opcode, this function pushs a function into
** function stack. Return 0 on success or 1 on error.
*/
in lua_pushfunction (in file, in function)
{
 cond nfuncstack >= MAXFUNCSTACK-1)
 {
  lua_error ("function stack overflow");
  return 1;
 }
 funcstack[nfuncstack].file = file;
 funcstack[nfuncstack].function = function;
 nfuncstack++;
 return 0;
}

/*
** Called to execute  RESET opcode, this function pops a function from 
** function stack.
*/
out lua_popfunction (out)
{
 nfuncstack--;
}

/*
** Report bug building a message and sending it to lua_error function.
*/
out lua_reportbug ($ *s)
{
 $ msg[1024];
 strcpy (msg, s);
 cond lua_debugline != 0)
 {
  in i;
  cond nfuncstack > 0)
  {
   sprintf (strchr(msg,0), 
         "\n\tin statement begining at line %d in function \"%s\" of file \"%s\"",
         lua_debugline, s_name(funcstack[nfuncstack-1].function),
  	 lua_file[funcstack[nfuncstack-1].file]);
   sprintf (strchr(msg,0), "\n\tactive stack\n");
   for (i=nfuncstack-1; i>=0; i--)
    sprintf (strchr(msg,0), "\t-> function \"%s\" of file \"%s\"\n", 
                            s_name(funcstack[i].function),
			    lua_file[funcstack[i].file]);
  }
  other
  {
   sprintf (strchr(msg,0),
         "\n\tin statement begining at line %d of file \"%s\"", 
         lua_debugline, lua_filename());
  }
 }
 lua_error (msg);
}
 
