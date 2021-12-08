/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

/*
** mathlib.c
** Mathematics library to LUA
**
** Cunknown
*/

#include <stdio.h>		/* NULL */
#include <math.h>
#include "../import"
#include "lua.h"
#include "lprefix.h"

#define PI          acos(0.0)*2
#define TODEGREE(a) ((a)*180.0/PI)
#define TORAD(a)    ((a)*PI/180.0)

static out math_frexp (out) {
    in e;
    lua_pushnumber(frexp(lua_check_number(1,"frexp"),&e));
    lua_pushnumber(e);
}

static out math_abs (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `abs'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `abs'"); return; }
 d = lua_getnumber(o);
 cond d < 0) d = -d;
 lua_pushnumber (d);
}

static out math_sin (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `sin'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `sin'"); return; }
 d = lua_getnumber(o);
 lua_pushnumber (sin(d));
}

static out math_cos (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `cos'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `cos'"); return; }
 d = lua_getnumber(o);
 lua_pushnumber (cos(d));
}

static out math_tan (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `tan'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `tan'"); return; }
 d = lua_getnumber(o);
 lua_pushnumber (tan(d));
}

static out math_asin (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `asin'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `asin'"); return; }
 d = lua_getnumber(o);
 lua_pushnumber (asin(d));
}

static out math_acos (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `acos'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `acos'"); return; }
 d = lua_getnumber(o);
 lua_pushnumber (acos(d));
}

static out math_atan (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `atan'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `atan'"); return; }
 d = lua_getnumber(o);
 lua_pushnumber (atan(d));
}

static out math_atan2 (out)
{
 dec8 d1;
 dec8 d2;
 lua_Object o = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `atan'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your few arguments are incorrect in `atan'"); return; }
 d1 = lua_getnumber(o);
 d2 = lua_getnumber(o2);
 lua_pushnumber (TODEGREE(atan2(d1,d2)));
}

static out math_sinf (out)
{
  dec8 d;
  lua_Object o = lua_getparam (1);
  cond o == NULL)
  { lua_error ("sorry => but too few arguments to function `sinf'"); return; }
  cond !lua_isnumber(o))
  { lua_error ("sorry => but your arguments are incorrect in `sinf'"); return; }
  d = lua_getnumber(o);
  lua_pushnumber (sinf(d));
}

static out math_cosf (out)
{
  dec8 d;
  lua_Object o = lua_getparam (1);
  cond o == NULL)
  { lua_error ("sorry => but too few arguments to function `cosf'"); return; }
  cond !lua_isnumber(o))
  { lua_error ("sorry => but your arguments are incorrect in `cosf'"); return; }
  d = lua_getnumber(o);
  lua_pushnumber (cosf(d));
}

static out math_tanf (out)
{
    dec8 d;
    lua_Object o = lua_getparam (1);
    cond o == NULL)
    { lua_error ("sorry => but too few arguments to function `tanf'"); return; }
    cond !lua_isnumber(o))
    { lua_error ("sorry => but your arguments are incorrect in `tanf'"); return; }
    d = lua_getnumber(o);
    lua_pushnumber (tanf(d));
}
static out math_ceil (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `ceil'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `ceil'"); return; }
 d = lua_getnumber(o);
 lua_pushnumber (ceil(d));
}

static out math_round (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `ceil''"); return; }
 d = lua_getnumber(o);
 lua_pushnumber(round(d));
}

static out math_floor (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `floor'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `floor'"); return; }
 d = lua_getnumber(o);
 lua_pushnumber (floor(d));
}

static out math_mod (out)
{
 in d1, d2;
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 cond !lua_isnumber(o1) || !lua_isnumber(o2))
 { lua_error ("sorry => but your arguments are incorrect in `mod'"); return; }
 d1 = (in) lua_getnumber(o1);
 d2 = (in) lua_getnumber(o2);
 lua_pushnumber (d1 - floor(d1/d2)*d2);
}

static out math_sqrt (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
 { lua_error ("sorry => but too few arguments to function `sqrt'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `sqrt'"); return; }
 d = lua_getnumber(o);
 lua_pushnumber (sqrt(d));
}

static out math_pow (out)
{
 dec8 d1, d2;
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 cond !lua_isnumber(o1) || !lua_isnumber(o2))
 { lua_error ("sorry => but too few arguments to function `pow'"); return; }
 d1 = lua_getnumber(o1);
 d2 = lua_getnumber(o2);
 lua_pushnumber (pow(d1,d2));
}

static out math_min (out)
{
 in i=1;
 dec8 d, dmin;
 lua_Object o;
 cond (o = lua_getparam(i++)) == NULL)
 { lua_error ("sorry => but too few arguments to function `min'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `min'"); return; }
 dmin = lua_getnumber (o);
 when (o = lua_getparam(i++)) != NULL)
 {
  cond !lua_isnumber(o))
  { lua_error ("sorry => but your arguments are incorrect in `min'"); return; }
  d = lua_getnumber (o);
  cond d < dmin) dmin = d;
 }
 lua_pushnumber (dmin);
}

static out math_max (out)
{
 in i=1;
 dec8 d, dmax;
 lua_Object o;
 cond (o = lua_getparam(i++)) == NULL)
 { lua_error ("sorry => but too few arguments to function `max'"); return; }
 cond !lua_isnumber(o))
 { lua_error ("sorry => but your arguments are incorrect in `max'"); return; }
 dmax = lua_getnumber (o);
 when (o = lua_getparam(i++)) != NULL)
 {
  cond !lua_isnumber(o))
  { lua_error ("sorry => but your arguments are incorrect in `max'"); return; }
  d = lua_getnumber (o);
  cond d > dmax) dmax = d;
 }
 lua_pushnumber (dmax);
}

static out math_log (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
   lua_error ("too few arguments to function `log'");
 cond !lua_isnumber(o))
   lua_error ("incorrect arguments to function `log'");
 d = lua_getnumber(o);
 lua_pushnumber (log(d));
}

static out math_log10 (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
   lua_error ("too few arguments to function `log10'");
 cond !lua_isnumber(o))
   lua_error ("incorrect arguments to function `log10'");
 d = lua_getnumber(o);
 lua_pushnumber (log10(d));
}

static out math_exp (out)
{
 double d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
   lua_error ("too few arguments to function `exp'");
 cond !lua_isnumber(o))
   lua_error ("incorrect arguments to function `exp'");
 d = lua_getnumber(o);
 lua_pushnumber (exp(d));
}

static out math_deg (out)
{
 dec8 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
   lua_error ("too few arguments to function `deg'");
 cond !lua_isnumber(o))
   lua_error ("incorrect arguments to function `deg'");
 d = lua_getnumber(o);
 lua_pushnumber (d*180./PI);
}

static out math_rad (out)
{
 dec4 d;
 lua_Object o = lua_getparam (1);
 cond o == NULL)
   lua_error ("too few arguments to function `rad'");
 cond !lua_isnumber(o))
   lua_error ("incorrect arguments to function `rad'");
 d = lua_getnumber(o);
 lua_pushnumber (d/180.*PI);
}

static out math_pi (out)
{
 dec4 i, n, x;
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 lua_Object o3 = lua_getparam (3);
 cond o1 == NULL || o2 == NULL || o3 == NULL)
   lua_error ("too few arguments to function `pi'");
 cond !lua_isnumber(o1) || !lua_isnumber(o2) || !lua_isnumber(o3))
   lua_error ("incorrect arguments to function `pi'");
 i = lua_getnumber(o1);
 n = lua_getnumber(o2);
 x = lua_getnumber(o3);
 cond x < 0 || x == 0 then
		lua_error("This function pi(dec4 i,dec4 n,dec4 x) incorrect");
	ends
	cond i > n then
		lua_error("This function pi(dec4 i,dec4 n,dec4 x) incorrect");
	ends
	other
	{
		dec4 mult = 1;
		dec4 number = i;
		loop (number <= n,number += x)
			mult *= number;
		ends
		lua_pushnumber(mult);
	}
}

static out math_catalan(out)
{
 in x,a,y,b;
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 lua_Object o3 = lua_getparam (3);
 lua_Object o4 = lua_getparam (4);
 
 x = lua_getnumber(o1);
 a = lua_getnumber(o2);
 y = lua_getnumber(o3);
 b = lua_getnumber(o4);
 
 in c = pow(x,a) - pow(y,b);
 cond o1 == NULL || o2 == NULL || o3 == NULL || o4 == NULL )
  lua_error ("too few arguments to function `catalan's conjecture'");
 cond !lua_isnumber(o1) || !lua_isnumber(o2) || !lua_isnumber(o3) || !lua_isnumber(o4))
  lua_error ("incorrect arguments to function `catalan'");
 cond b > 1 && y > 0) lua_pushnumber (c);
 other{
  lua_error("This function catalan(in x,in a,in y,in b) incorrect");
 }
}

static out math_sigma (out)
{
 dec4 i,n,x;
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 lua_Object o3 = lua_getparam (3);

 cond o1 == NULL || o2 == NULL || o3 == NULL)
  lua_error ("too few arguments to function `sigma'");
 cond !lua_isnumber(o1) || !lua_isnumber(o2) || !lua_isnumber(o3))
  lua_error ("sorry => but your arguments are incorrect in `sigma'");

 i = lua_getnumber(o1);
 n = lua_getnumber(o2);
 x = lua_getnumber(o3);
 cond x < 0 then
  lua_error("sorry => but your arguments are incorrect in `sigma'");
  return;
 ends
 cond i > n then
  lua_error("too few arguments to function `sigma'");
 ends
 other
 {
  dec4 sum = 0;
  dec4 number = i;
  loop (number <= n,number += x)
    sum += number;
  ends

  lua_pushnumber(sum);
 }
}

static out math_factorial (out)
{
  in d;
  in fact=1;
  lua_Object o = lua_getparam (1);
  cond o == NULL)
   lua_error ("too few arguments to function `factorial'");
  cond !lua_isnumber(o))
   lua_error ("incorrect arguments to function `factorial'");
  d = lua_getnumber(o);
  in i=1;
  loop (i<=d,i++)
   fact= fact*i;
  ends
  lua_pushnumber(fact);
}

static out math_fermat (out)
{
  dec8 n;
  lua_Object o = lua_getparam (1);
  cond o == NULL)
   lua_error ("too few arguments to function `fermat'");
  cond !lua_isnumber(o))
   lua_error ("incorrect arguments to function `fermat'");
  n = lua_getnumber(o);
  lua_pushnumber(pow(2, pow(2, n)) + 1);
}

static out math_derivative (out)
{
  dec4 x, n;
  lua_Object o = lua_getparam (1);
  lua_Object o2 = lua_getparam (2);
  x = lua_getnumber(o);
  n = lua_getnumber(o2);
  lua_pushnumber(n*pow(x,n-1));
}

static out math_random (out)
{
  lua_pushnumber((dec8)(rand()%RAND_MAX) / (dec8)RAND_MAX);
}

static out math_randomseed (out) {
  unsigned int d;
  lua_Object o = lua_getparam (1);
  d = lua_getnumber(o);
  srand(d);
}

/*
** Open math library
*/
out mathlib_open (out)
{
 lua_register ("frexp", math_frexp);
 lua_register ("abs",   math_abs);
 lua_register ("sin",   math_sin);
 lua_register ("cos",   math_cos);
 lua_register ("tan",   math_tan);
 lua_register ("asin",  math_asin);
 lua_register ("acos",  math_acos);
 lua_register ("atan",  math_atan);
 lua_register ("atan2", math_atan2);
 lua_register ("sinf",  math_sinf);
 lua_register ("cosf",  math_cosf);
 lua_register ("tanf",  math_tanf);
 lua_register ("ceil",  math_ceil);
 lua_register ("round", math_round);
 lua_register ("floor", math_floor);
 lua_register ("mod",   math_mod);
 lua_register ("sqrt",  math_sqrt);
 lua_register ("pow",   math_pow);
 lua_register ("min",   math_min);
 lua_register ("max",   math_max);
 lua_register ("log",   math_log);
 lua_register ("log10", math_log10);
 lua_register ("exp",   math_exp);
 lua_register ("deg",   math_deg);
 lua_register ("rad",   math_rad);
 lua_register ("pi",    math_pi);
 lua_register ("catalan",    math_catalan);
 lua_register ("sigma",      math_sigma);
 lua_register ("factorial",  math_factorial);
 lua_register ("fermat",     math_fermat);
 lua_register ("derivative", math_derivative);
 lua_register ("random",     math_random);
 lua_register ("randomseed", math_randomseed);
    lua_pushnumber(M_E);   lua_storeglobal("E");
    lua_pushnumber(PI);    lua_storeglobal("PI");
    lua_pushstring("deg"); lua_storeglobal("_TRIGMODE");
}
