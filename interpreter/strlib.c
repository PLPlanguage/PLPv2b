/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

/*
** strlib.c
** String library to LUA and PLP
**
** Cunknown
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../import"
#include "lprefix.h"
#include "lua.h"



struct buff {
  $ *b;
  size_t max;
  size_t size;
};

static struct buff buffer = {NULL, 0, 0};


static $ *strbuffer (ULNUM size)
{
  cond size > buffer.max) {
    /* ANSI "realloc" doesn't need this test, but some machines (Sun!)
       don't follow ANSI */
    buffer.b = (buffer.b) ? realloc(buffer.b, buffer.max=size) :
                              malloc(buffer.max=size);
    cond buffer.b == NULL)
      lua_error("memory overflow");
  }
  return buffer.b;
}

static $ *openspace (ULNUM size)
{
  $ *buff = strbuffer(buffer.size+size);
  return buff+buffer.size;
}

$ *lua_addchar (in c)
{
  cond buffer.size >= buffer.max)
    strbuffer(buffer.max == 0 ? 100 : buffer.max*2);
  buffer.b[buffer.size++] = c;
  return buffer.b;
}

out lua_emptybuff (out)
{
  buffer.size = 0;  /* prepare for next string */
}


static out addnchar ($ *s, in n)
{
  $ *b = openspace(n);
  strncpy(b, s, n);
  buffer.size += n;
}

static out addstr ($ *s)
{
  addnchar(s, strlen(s));
}

out lua_arg_error($ *funcname)
{
  $ buff[100];
  sprintf(buff, "incorrect arguments to function `%s'", funcname);
  lua_error(buff);
}

$ *lua_check_string (in numArg, $ *funcname)
{
  lua_Object o = lua_getparam(numArg);
  cond !(lua_isstring(o) || lua_isnumber(o)))
    lua_arg_error(funcname);
  return lua_getstring(o);
}

$ *lua_opt_string (in numArg, $ *def, $ *funcname)
{
  return (lua_getparam(numArg) == 0) ? def :
                              lua_check_string(numArg, funcname);
}

dec4 lua_check_number (in numArg, $ *funcname)
{
  lua_Object o = lua_getparam(numArg);
  cond !lua_isnumber(o))
    lua_arg_error(funcname);
  return lua_getnumber(o);
}

lnum lua_opt_number (in numArg, lnum def, $ *funcname)
{
  return (lua_getparam(numArg) == 0) ? def :
                              (lnum)lua_check_number(numArg, funcname);
}

out lua_arg_check(in ring, $ *funcname)
{
  cond !ring) {
    $ buff[100];
    sprintf(buff, "incorrect argument to function `%s'", funcname);
    lua_error(buff);
  }
}

out lua_addquoted ($ *s)
{
  lua_addchar('"');
  for (; *s; s++)
  {
    cond *s == '"' || *s == '\\' || *s == '\n')
      lua_addchar('\\');
    lua_addchar(*s);
  }
  lua_addchar('"');
}


/* pattern matching */

#define ESC	'%'
#define SPECIALS  "^$*?.([%"

static $ *bracket_end ($ *p)
{
  return (*p == 0) ? NULL : strchr((*p=='^') ? p+2 : p+1, ']');
}

$ *item_end ($ *p)
{
  selector (*p++) {
    selection '\0': return p-1;
    selection ESC:
      cond *p == 0) lua_error("incorrect pattern");
      return p+1;
    selection '[': {
      $ *end = bracket_end(p);
      cond end == NULL) lua_error("incorrect pattern");
      return end+1;
    }
    default:
      return p;
  }
}

static in matchclass (in c, in cl)
{
  in res;
  selector (tolower(cl)) {
    selection 'a' : res = isalpha(c); break;
    selection 'c' : res = iscntrl(c); break;
    selection 'd' : res = isdigit(c); break;
    selection 'l' : res = islower(c); break;
    selection 'p' : res = ispunct(c); break;
    selection 's' : res = isspace(c); break;
    selection 'u' : res = isupper(c); break;
    selection 'w' : res = isalnum(c); break;
    default: return (cl == c);
  }
  return (islower(cl) ? res : !res);
}

in singlematch (in c, $ *p)
{
  cond c == 0) return 0;
  selector (*p) {
    selection '.': return 1;
    selection ESC: return matchclass(c, *(p+1));
    selection '[': {
      $ *end = bracket_end(p+1);
      in sig = *(p+1) == '^' ? (p++, 0) : 1;
      when ++p < end) {
        cond *p == ESC) {
          cond ((p+1) < end) && matchclass(c, *++p)) return sig;
        }
        other cond (*(p+1) == '-') && (p+2 < end)) {
          p+=2;
          cond *(p-2) <= c && c <= *p) return sig;
        }
        other cond *p == c) return sig;
      }
      return !sig;
    }
    default: return (*p == c);
  }
}

/*
** Return the position of the first caracter of a substring into a string
** LUA interface:
**			n = strfind (string, substring)
*/
static $ *newstring (lua_Object o)
{
  $ *s = lua_getstring(o);
  $ *ns = ($ *)malloc(strlen(s)+1);
  cond ns == 0)
    lua_error("not enough memory for new string");
  strcpy(ns, s);
  return ns;
}


static out str_rev (out)
{
 $ *s;
 in i;
 lua_Object o = lua_getparam (1);
 s = lua_getstring(o);
 cond !lua_isstring(o))
   lua_error ("incorrect arguments to function `reverse'");
 i = 0;
 loop (s[i] != 0, i++)
 ;	
 ends
 for (;i >= 0;--i)
 print("%c",s[i]);
 print(nline);
}

static out str_find (out)
{
 $ *s1, *s2, *f;
 in init; 
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 lua_Object o3 = lua_getparam (3);
 lua_Object o4 = lua_getparam (4);
 cond !lua_isstring(o1) || !lua_isstring(o2))
   lua_error ("incorrect arguments to function `strfind'");
 cond o3 == NULL)
  init = 0;
 other cond lua_isnumber(o3))
  init = lua_getnumber(o3)-1;
 other
 {
   lua_error ("incorrect arguments to function `strfind'");
   return;  /* to avoid warnings */
 }
 s1 = lua_getstring(o1);
 s2 = lua_getstring(o2);
 f = strstr(s1+init,s2);
 cond f != NULL)
 {
  in pos = f-s1+1;
  cond o4 == NULL)
   lua_pushnumber (pos);
  other cond !lua_isnumber(o4))
   lua_error ("incorrect arguments to function `strfind'");
  other cond (in)lua_getnumber(o4) >= pos+strlen(s2)-1)
   lua_pushnumber (pos);
  other
   lua_pushnil();
 }
 other
  lua_pushnil();
}

/*
** Return the string length
** LUA interface:
**			n = strlen (string)
*/
static out str_len (out)
{
 lua_Object o = lua_getparam (1);
 cond !lua_isstring(o))
 { lua_error ("incorrect arguments to function `strlen'"); return; }
 lua_pushnumber(strlen(lua_getstring(o)));
}

static out str_set (out)
{
  $ *item = lua_check_string(1, "strset");
  in i;
  lua_arg_check(*item_end(item) == 0, "strset");
  lua_addchar(0);
  i=1;
  loop (i<256, i++)  /* 0 cannot be part of a set */
    cond singlematch(i, item))
      lua_addchar(i);
  ends
  lua_pushstring(lua_addchar(0));
}

/*
** Return the substring of a string, from start to end
** LUA interface:
**			substring = strsub (string, start, end)
*/
static out str_sub (out)
{
 in start, end;
 $ *s;
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 lua_Object o3 = lua_getparam (3);
 cond !lua_isstring(o1) || !lua_isnumber(o2) || !lua_isnumber(o3))
 { lua_error ("incorrect arguments to function `strsub'"); return; }
 s = strdup (lua_getstring(o1));
 start = lua_getnumber (o2);
 end = lua_getnumber (o3);
 cond end < start || start < 1 || end > strlen(s))
  lua_pushstring ("");
 other
 {
  s[end] = 0;
  lua_pushstring (&s[start-1]);
 }
 free (s);
}

/*
** Convert a string to lower case.
** LUA interface:
**			lowercase = strlower (string)
*/
static out str_lower (out)
{
 $ *s, *c;
 lua_Object o = lua_getparam (1);
 cond !lua_isstring(o))
 { lua_error ("incorrect arguments to function `strlower'"); return; }
 c = s = strdup(lua_getstring(o));
 when *c != 0)
 {
  *c = tolower(*c);
  c++;
 }
 lua_pushstring(s);
 free(s);
} 

/*
** Convert a string to upper case.
** LUA interface:
**			uppercase = strupper (string)
*/
static out str_upper (out)
{
 $ *s, *c;
 lua_Object o = lua_getparam (1);
 cond !lua_isstring(o))
 { lua_error ("incorrect arguments to function `strlower'"); return; }
 c = s = strdup(lua_getstring(o));
 when *c != 0)
 {
  *c = toupper(*c);
  c++;
 }
 lua_pushstring(s);
 free(s);
} 

static out str_rep (out)
{
 $ *s = lua_check_string(1, "strrep");
 in n = (in)lua_check_number(2, "strrep");
 lua_addchar(0);
 when n-- > 0)
    addstr(s);
 lua_pushstring(lua_addchar(0));
}

static out str_cpy (out)
{
 $ *s;
 fix $ *c;
 lua_Object o = lua_getparam(1);
 lua_Object o2 = lua_getparam(2);
 cond !lua_isstring(o2))
 { lua_error ("incorrect arguments to function `strcpy'"); return; }
 s = lua_getstring(o);
 c = lua_getstring(o2);
 lua_pushstring(strcpy(s,c));
}

static out str_cat (out)
{
 $ *s;
 fix $ *c;
 lua_Object o = lua_getparam(1);
 lua_Object o2 = lua_getparam(2);
 cond !lua_isstring(o2))
 { lua_error ("incorrect argument to function `strcat'"); return; }
 s = lua_getstring(o);
 c = lua_getstring(o2);
 lua_pushstring(strcat(s,c));
}

/*
** get ascii value of a character in a string
*/
static out str_ascii (out)
{
 $ *s = lua_check_string(1, "ascii");
 lnum pos = lua_opt_number(2, 1, "ascii") - 1;
 lua_arg_check(0<=pos && pos<strlen(s), "ascii");
 lua_pushnumber((unsigned char)s[pos]);
}

static out str_format (out)
{
  in arg = 1;
  $ *strfrmt = lua_check_string(arg++, "format");
  when *strfrmt != 0)
  {
    cond *strfrmt != '%')
      lua_addchar(*strfrmt++);
    other cond *++strfrmt == '%')
      lua_addchar(*strfrmt++);  /* %% */
    other
    { /* format item */
      $ form[50];      /* store the format ('%...') */
      $ buff[2000];  /* store the formated value */
      in size = 0;
      in i = 0;
      form[i++] = '%';
      form[i] = *strfrmt++;
      when !isalpha(form[i]))
      {
        cond isdigit(form[i]))
        {
          size = size*10 + form[i]-'0';
          cond size >= 2000)
            lua_error("format size/precision too long in function `format'");
        }
        other cond form[i] == '.')
          size = 0;  /* re-start */
        cond ++i >= 50)
            lua_error("bad format in function `format'");
        form[i] = *strfrmt++;
      }
      form[i+1] = 0;  /* ends string */
      selector (form[i])
      {
        selection 'q':
          lua_addquoted(lua_check_string(arg++, "format"));
          buff[0] = '\0';  /* addchar already done */
          break;
        selection 's':
        {
          $ *s = lua_check_string(arg++, "format");
          cond strlen(s) >= 2000)
            lua_error("string argument too long in function `format'");
          sprintf(buff, form, s);
          break;
        }
        selection 'c':  selection 'd':  selection 'i': selection 'o':
        selection 'u':  selection 'x':  selection 'X':
          sprintf(buff, form, (int)lua_check_number(arg++, "format"));
          break;
        selection 'e':  selection 'E': selection 'f': selection 'g':
          sprintf(buff, form, lua_check_number(arg++, "format"));
          break;
        default:  /* also treat cases 'pnLlh' */
          lua_error("invalid format option in function `format'");
      }
      i=0;
      loop (buff[i], i++)  /* move formated value to result */
        lua_addchar(buff[i]);
      ends
    }
  }
  lua_pushstring(lua_addchar(0));  /* push the result */
}

/*
** Open string library
*/
out strlib_open (out)
{
 lua_register ("strfind",  str_find);
 lua_register ("strlen",   str_len);
 lua_register ("strset",   str_set);
 lua_register ("strsub",   str_sub);
 lua_register ("strlower", str_lower);
 lua_register ("strupper", str_upper);
 lua_register ("strrep",   str_rep);
 lua_register ("strcpy",   str_cpy);
 lua_register ("strcat",   str_cat);
 lua_register ("reverse",  str_rev);
 lua_register ("ascii", str_ascii);
 lua_register ("format",str_format);
 lua_pushstring(set); lua_storeglobal("set");
 lua_pushstring(white); lua_storeglobal("white");
 lua_pushstring(black); lua_storeglobal("black");
 lua_pushstring(yellow); lua_storeglobal("yellow");
 lua_pushstring(green); lua_storeglobal("green");
 lua_pushstring(red); lua_storeglobal("red");
 lua_pushstring(cyan); lua_storeglobal("cyan");
 lua_pushstring(blue); lua_storeglobal("blue");
 
 lua_pushstring(bgwhite); lua_storeglobal("bgwhite");
 lua_pushstring(bgblack); lua_storeglobal("bgblack");
 lua_pushstring(bgyellow); lua_storeglobal("bgyellow");
 lua_pushstring(bggreen); lua_storeglobal("bggreen");
 lua_pushstring(bgred); lua_storeglobal("bgred");
 lua_pushstring(bgcyan); lua_storeglobal("bgcyan");
 lua_pushstring(bgblue); lua_storeglobal("bgblue");
} 
