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
out itoa	          (in value, $* str, in base);
out beep	          (out);
out times           (out);

  #ifdef  __cplusplus
    }
  #endif  

  #endif
