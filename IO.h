/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

#include "Define"
#include "Type"

  #ifndef IO_H
    #define IO_H
in  plp_error ($ * s);
in  inout     ($ * a);
in  argvinout ($ * s);
in  defkey    ($ * i);
in  cc	      (out);
in  cpp       (out);
    #define Windows(_WIN32)
  #ifndef Windows
  #undef
    #define Windows(_WIN64)
  #endif
  
  #endif
