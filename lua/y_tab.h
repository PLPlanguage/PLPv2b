/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

#include "../import"
define union  
{
 in   vInt;
 lnum  vLong;
 dec4 vFloat;
 Word  vWord;
 Byte *pByte;
} YYSTYPE;
extern YYSTYPE yylval;
# define NIL 257
# define IF 258
# define THEN 259
# define ELSE 260
# define ELSEIF 261
# define WHILE 262
# define DO 263
# define REPEAT 264
# define UNTIL 265
# define END 266
# define RETURN 267
# define LOCAL 268
# define NUMBER 269
# define FUNCTION 270
# define NAME 271
# define STRING 272
# define DEBUG 273
# define NOT 274
# define AND 275
# define OR 276
# define NE 277
# define LE 278
# define GE 279
# define CONC 280
# define UNARY 281 
