/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License and MIT License
 Time: 21/08/01 00:00 GMT
*/

 #ifndef CMATH_H
    #define CMATH_H

#include "Type"
#include "Define"
#include <math.h>
    
    #define PI          acos(0.0)*2
    #define Euler	2.718281828459045
    #define Enum	2.718281828459045

    #define deg(a) ((a)*180.0/PI)
    #define rad(a)    ((a)*PI/180.0)
    #define radius(a)   (a*a)*PI
    
    #define min(X, Y) (((X) < (Y)) ? (X) : (Y))
    #define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
     
  #ifdef __cplusplus
	extern "C"{
  #endif

dec8  fermat 	    (in n);
dec4 Cos	    (in C);
dec4 Tan	    (in T);
dec4 Sin	    (in S);
dec4 ACos           (in AC);
dec4 ATan           (in AT);
dec4 ASin           (in AS);
dec4 Exp            (dec4 E);
dec4 Frexp          (dec4 X);
dec4 pi		    (dec4 i,dec4 n,dec4 x);
dec4 sigma	    (dec4 i,dec4 n,dec4 x);
in   matrix	    (in row,in column,in *mat);
in   mod	    (in d1,in d2);
in   gcd	    (in a,in b);
in   lcm	    (in a,in b);
in   factorial      (in c);
in   collatz        (in n);
in   catalan        (in x,in a,in y,in b);

  
  #ifdef __cplusplus
	}
  #endif

  #endif
