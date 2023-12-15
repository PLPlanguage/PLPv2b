/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License and MIT License
 Time: 21/08/01 00:00 GMT
*/

 #ifndef CMATH_H
    #define CMATH_H

#include "Type"
#include "Define"
#ifndef __cplusplus
#include <math.h>
#else
#include <cmath>
#endif
    
    #define PI          acos(0.0)*2
    #define Euler	exp(1)
    #define Enum	exp(1)

    #define deg(a) ((a)*180.0/PI)
    #define rad(a)    ((a)*PI/180.0)
    #define radius(a)   (a*a)*PI
#ifndef __cplusplus
    #define eulers(theta) (creal(cos(theta)) + cimag(sin(theta)))
#endif
#ifdef __cplusplus
    #define eulers(theta) (real(cos(theta)) + imag(sin(theta)))
#endif
#ifndef __cplusplus
    #define min(X, Y) (((X) < (Y)) ? (X) : (Y))
    #define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#endif
  #ifdef __cplusplus
	extern "C"{
  #endif

dec8 fermat 	    (in n);
dec4 Cos	    (in C);
dec4 Tan	    (in T);
dec4 Sin	    (in S);
dec4 ACos           (in AC);
dec4 ATan           (in AT);
dec4 ASin           (in AS);
dec4 Exp            (dec4 E);
dec4 Frexp          (dec4 X);
dec4 derivative     (dec4 x, dec4 n);
dec8 integral       (dec8 x, dec8 n);
dec4 pi		    (dec4 i,dec4 n,dec4 x);
dec4 sigma	    (dec4 i,dec4 n,dec4 x);
in   matrix	    (in row,in column,in *mat);
in   ack	    (in m, in n);
in   mod	    (in d1,in d2);
in   gcd	    (in a,in b);
in   lcm	    (in a,in b);
in   fib	    (in n);
#define fibonacci(n) fib(n - 1)
in   factorial      (in c);
in   collatz        (in n);
ULIN catalan        (UIN n);

  
  #ifdef __cplusplus
	}
  #endif

  #endif
