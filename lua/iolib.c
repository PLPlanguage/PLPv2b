 
/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

/*
** iolib.c
** Input/output library to LUA and PLP
**
** Cunknown
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#ifdef __GNUC__
#include <floatingpoint.h>
#endif
#include "lua.h"
#include "lualib.h"
#include "../import"
static FILE *input=NULL, *output=NULL;

#define LUA_TMPNAMBUFSIZE       32

#include <unistd.h>

#define lua_tmpnam(b,e) { \
        strcpy(b, "/tmp/lua_XXXXXX"); \
        e = mkstemp(b); \
        if (e != -1) close(e); \
        e = (e == -1); }

/*
** Open a file to read.
** LUA interface:
**			status = readfrom (filename)
** where:
**			status = 1 -> success
**			status = 0 -> error
*/
static out io_readfrom (out)
{
 lua_Object o = lua_getparam (1);
 cond o == NULL)			/* restore standart input */
 {
  cond input != stdin)
  {
   fclose (input);
   input = stdin;
  }
  lua_pushnumber (1);
 }
 other
 {
  cond !lua_isstring (o))
  {
   lua_error ("incorrect argument to function 'readfrom`");
   lua_pushnumber (0);
  }
  other
  {
   FILE *fp = fopen (lua_getstring(o),"r");
   cond fp == NULL)
   {
    lua_pushnumber (0);
   }
   other
   {
    cond input != stdin) fclose (input);
    input = fp;
    lua_pushnumber (1);
   }
  }
 }
}

/*
** Read characters until a given one. The delimiter is not read.
*/
static out io_readuntil (out)
{
 in n=255,m=0;
 in c,d;
 $ *s;
 lua_Object lo = lua_getparam(1);
 cond !lua_isstring(lo))
  d = EOF; 
 other
  d = *lua_getstring(lo);
 
 s = ($ *)malloc(n+1);
 when (c = fgetc(input)) != EOF && c != d)
 {
  cond m==n)
  {
   n *= 2;
   s = ($ *)realloc(s, n+1);
  }
  s[m++] = c;
 }
 cond c != EOF) ungetc(c,input);
 s[m] = 0;
 lua_pushstring(s);
 free(s);
}

/*
** Open a file to write.
** LUA interface:
**			status = writeto (filename)
** where:
**			status = 1 -> success
**			status = 0 -> error
*/
static out io_writeto (out)
{
 lua_Object o = lua_getparam (1);
 cond o == NULL)			/* restore standart output */
 {
  cond output != stdout)
  {
   fclose (output);
   output = stdout;
  }
  lua_pushnumber (1);
 }
 other
 {
  cond !lua_isstring (o))
  {
   lua_error ("incorrect argument 'writeto`");
   lua_pushnumber (0);
  }
  other
  {
   FILE *fp = fopen (lua_getstring(o),"w");
   cond fp == NULL)
   {
    lua_pushnumber (0);
   }
   other
   {
    cond output != stdout) fclose (output);
    output = fp;
    lua_pushnumber (1);
   }
  }
 }
}

/*
** Open a file to write appended.
** LUA interface:
**			status = appendto (filename)
** where:
**			status = 2 -> success (already exist)
**			status = 1 -> success (new file)
**			status = 0 -> error
*/
static out io_appendto (out)
{
 lua_Object o = lua_getparam (1);
 cond o == NULL)			/* restore standart output */
 {
  cond output != stdout)
  {
   fclose (output);
   output = stdout;
  }
  lua_pushnumber (1);
 }
 other
 {
  cond !lua_isstring (o))
  {
   lua_error ("incorrect argument to function 'appendto`");
   lua_pushnumber (0);
  }
  other
  {
   in r;
   FILE *fp;
   struct stat st;
   cond stat(lua_getstring(o), &st) == -1) r = 1;
   other                                r = 2;
   fp = fopen (lua_getstring(o),"a");
   cond fp == NULL)
   {
    lua_pushnumber (0);
   }
   other
   {
    cond output != stdout) fclose (output);
    output = fp;
    lua_pushnumber (r);
   }
  }
 }
}

/*
** Read a variable. On error put nil on stack.
** LUA interface:
**			variable = read ([format])
**
** O formato pode ter um dos seguintes especificadores:
**
**	s ou S -> para string
**	f ou F, g ou G, e ou E -> para reais
**	i ou I -> para inteiros
**
**	Estes especificadores podem vir seguidos de numero que representa
**	o numero de campos a serem lidos.
*/

static out io_read (out)
{
 lua_Object o = lua_getparam (1);
 cond o == NULL)			/* free format */
 {
  in c;
  $ s[256];
  when isspace(c=fgetc(input)))
   ;
  cond c == '\"')
  {
   cond fscanf (input, "%[^\"]\"", s) != 1)
   {
    lua_pushnil ();
    return;
   }
  }
  other cond c == '\'')
  {
   cond fscanf (input, "%[^\']\'", s) != 1)
   {
    lua_pushnil ();
    return;
   }
  }
  other
  {
   $ *ptr;
   dec8 d;
   ungetc (c, input);
   cond fscanf (input, "%s", s) != 1)
   {
    lua_pushnil ();
    return;
   }
   d = strtod (s, &ptr);
   cond !(*ptr))
   {
    lua_pushnumber (d);
    return;
   }
  }
  lua_pushstring (s);
  return;
 }
 other				/* formatted */
 {
  $ *e = lua_getstring(o);
  $ t;
  in  m=0;
  when isspace(*e)) e++;
  t = *e++;
  when isdigit(*e))
   m = m*10 + (*e++ - '0');
  
  cond m > 0)
  {
   $ f[80];
   $ s[256];
   sprintf (f, "%%%ds", m);
   fscanf (input, f, s);
   selector(tolower(t))
   {
    selection 'i':
    {
     long int l;
     sscanf (s, "%ld", &l);
     lua_pushnumber(l);
    }
    break;
    selection 'f': selection 'g': selection 'e':
    {
     dec4 f;
     sscanf (s, "%f", &f);
     lua_pushnumber(f);
    }
    break;
    default: 
     lua_pushstring(s); 
    break;
   }
  }
  other
  {
   selector(tolower(t))
   {
    selection 'i':
    {
     long int l;
     fscanf (input, "%ld", &l);
     lua_pushnumber(l);
    }
    break;
    selection 'f': selection 'g': selection 'e':
    {
     dec4 f;
     fscanf (input, "%f", &f);
     lua_pushnumber(f);
    }
    break;
    default: 
    {
     $ s[256];
     fscanf (input, "%s", s);
     lua_pushstring(s);
    }
    break;
   }
  }
 }
}

/*
** Write a variable. On error put 0 on stack, otherwise put 1.
** LUA interface:
**			status = write (variable [,format])
**
** O formato pode ter um dos seguintes especificadores:
**
**	s ou S -> para string
**	f ou F, g ou G, e ou E -> para reais
**	i ou I -> para inteiros
**
**	Estes especificadores podem vir seguidos de:
**
**		[?][m][.n]
**
**	onde:
**		? -> indica justificacao
**			< = esquerda
**			| = centro
**			> = direita (default)
**		m -> numero maximo de campos (se exceder estoura)
**		n -> indica precisao para
**			reais -> numero de casas decimais
**			inteiros -> numero minimo de digitos
**			string -> nao se aplica
*/
static $ *buildformat ($ *e, lua_Object o)
{
 static $ buffer[512];
 static $ f[80];
 $ *string = &buffer[255];
 $ t, j='r';
 in  m=0, n=0, l;
 when isspace(*e)) e++;
 t = *e++;
 cond *e == '<' || *e == '|' || *e == '>') j = *e++;
 when isdigit(*e))
  m = m*10 + (*e++ - '0');
 e++;	/* skip point */
 when isdigit(*e))
  n = n*10 + (*e++ - '0');

 sprintf(f,"%%");
 cond j == '<' || j == '|') sprintf(strchr(f,0),"-");
 cond m != 0)   sprintf(strchr(f,0),"%d", m);
 cond n != 0)   sprintf(strchr(f,0),".%d", n);
 sprintf(strchr(f,0), "%c", t);
 selector (tolower(t))
 {
  selection 'i': t = 'i';
   sprintf (string, f, (long int)lua_getnumber(o));
  break;
  selection 'f': selection 'g': selection 'e': t = 'f';
   sprintf (string, f, (dec4)lua_getnumber(o));
  break;
  selection 's': t = 's';
   sprintf (string, f, lua_getstring(o));
  break;
  default: return "";
 }
 l = strlen(string);
 cond m!=0 && l>m)
 {
  in i;
  i=0;
  loop (i<m, i++)
   string[i] = '*';
  ends
  string[i] = 0;
 }
 other cond m!=0 && j=='|')
 {
  in i=l-1;
  when isspace(string[i])) i--;
  string -= (m-i) / 2;
  i=0;
  when string[i]==0) string[i++] = ' ';
  string[l] = 0;
 }
 return string;
}

static out io_write (out)
{
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 cond o1 == NULL)			/* new line */
 {
  fprintf (output, "\n");
  lua_pushnumber(1);
 }
 other cond o2 == NULL)   		/* free format */
 {
  in status=0;
  cond lua_isnumber(o1))
   status = fprintf (output, "%g", lua_getnumber(o1));
  other cond lua_isstring(o1))
   status = fprintf (output, "%s", lua_getstring(o1));
  lua_pushnumber(status);
 }
 other					/* formated */
 {
  cond !lua_isstring(o2))
  { 
   lua_error ("incorrect format `write'"); 
   lua_pushnumber(0);
   return;
  }
  lua_pushnumber(fprintf (output, "%s", buildformat(lua_getstring(o2),o1)));
 }
}

/*
** Execute a executable program using "system".
** Return the result of execution.
*/
static out io_execute (out)
{
 lua_Object o = lua_getparam (1);
 cond o == NULL || !lua_isstring (o))
 {
  lua_error ("incorrect argument to function 'execute`");
  lua_pushnumber (0);
 }
 other
 {
  in res = system(lua_getstring(o));
  lua_pushnumber (res);
 }
 return;
}

/*
** Remove a file.
** On error put 0 on stack, otherwise put 1.
*/
static out io_remove  (out)
{
 lua_Object o = lua_getparam (1);
 cond o == NULL || !lua_isstring (o))
 {
  lua_error ("incorrect argument to function 'execute`");
  lua_pushnumber (0);
 }
 other
 {
  cond remove(lua_getstring(o)) == 0)
   lua_pushnumber (1);
  other
   lua_pushnumber (0);
 }
 return;
}

static out io_rename (out)
{
  $ * f1;
  $ * f2;
  lua_Object o = lua_getparam (1);
  lua_Object o2 = lua_getparam(2);
  f1 = lua_getstring(o);
  f2 = lua_getstring(o2);
  cond o == NULL || !lua_isstring (o) || o2 == NULL || !lua_isstring(o2))
  {
    lua_error ("incorrect argument to function 'rename`");
    lua_pushnumber (0);
  }
  other
  {
    cond rename(f1, f2) == 0)
    lua_pushnumber (1);
    other
    lua_pushnumber (0);
  }
}

static out io_getenv (out)
{
 lua_Object s = lua_getparam(1);
 cond !lua_isstring(s))
  lua_pushnil();
 other
 {
  $ *env = getenv(lua_getstring(s));
  cond env == NULL) lua_pushnil();
  other             lua_pushstring(env); 
 }
} 

static out io_tmpname (out)
{
  char buff[LUA_TMPNAMBUFSIZE];
  int err;
  lua_tmpnam(buff, err);
  if (err)
    return lua_error("unable to generate a unique filename");
  lua_pushstring(buff);
}

/*
** Return time: hour, min, sec
*/
static out io_time (out)
{
 time_t t;
 struct tm *s;
 
 time(&t);
 s = localtime(&t);
 lua_pushnumber(s->tm_hour);
 lua_pushnumber(s->tm_min);
 lua_pushnumber(s->tm_sec);
}

/*
** Return user formatted time stamp
*/
static out io_date (out)
{
  time_t t;
  struct tm *tm;
  $ *s = lua_opt_string(1, "%c", "date");
  $ b[BUFSIZ];
  time(&t); tm = localtime(&t);
  cond strftime(b,sizeof(b),s,tm))
    lua_pushstring(b);
  other
    lua_error("invalid `date' format");
}

/*
** Beep
*/
static out io_beep (out)
{
 printf("\a");
}

/*
** To exit
*/
static out io_exit (out)
{
 lua_Object o = lua_getparam(1);
 cond lua_isstring(o))
  printf("%s\n", lua_getstring(o));
 exit(1);
}

/*
** To debug a lua program. Start a dialog with the user, interpreting
   lua commands until an 'exit'.
*/
static out io_debug (out)
{
  when 1)
  {
    $ buffer[250];
    fprintf(stderr, "luaPLP_debug> ");
    cond fgets(buffer, sizeof(buffer), stdin) == 0) return;
    cond indexof(buffer, "exit\n",0)) return;
    lua_dostring(buffer);
  }
}

/*
** Open io library
*/
out iolib_open (out)
{
 input=stdin; output=stdout;
 lua_register ("readfrom", io_readfrom);
 lua_register ("readuntil",io_readuntil);
 lua_register ("writeto",  io_writeto);
 lua_register ("appendto", io_appendto);
 lua_register ("read",     io_read);
 lua_register ("write",    io_write);
 lua_register ("execute",  io_execute);
 lua_register ("remove",   io_remove);
 lua_register ("rename",   io_rename);
 lua_register ("getenv",   io_getenv);
 lua_register ("tmpname",  io_tmpname);
 lua_register ("time",     io_time);
 lua_register ("date",     io_date);
 lua_register ("beep",     io_beep);
 lua_register ("exit",     io_exit);
 lua_register ("debug",    io_debug);
    lua_pushstring(__DATE__); lua_storeglobal("DATE");
    lua_pushstring(__TIME__); lua_storeglobal("TIME");
}
