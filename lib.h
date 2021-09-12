/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License and MIT License
 Time: 21/08/01 00:00 GMT
*/

  #ifndef LIB_H
    #define LIB_H

#include "Type"
#include "Define"
#include <time.h>

  #ifdef __cplusplus
    extern "C"{
  #endif

in  randomize       (in lower,in upper,in count);
in  binary_hex      (lin b);
in  hex_binary      ($ h[1000]);
in  binary_dec      (in num);
in  dec_binary      (in n);
in  reverse         (fix $ *s);
out sort            (in val[100],in chk);
  #ifndef __CYGWIN__
out itoa	          (in value, $* str, in base);
  #endif
out beep	          (out);
out times           (out);

  #ifdef  __cplusplus
    }
  #endif  

  #endif
