/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

/*
** hash.h
** hash manager for lua
** Luiz Henrique de Figueiredo - 17 Aug 90
** Modified by Waldemar Celes Filho
** 26 Apr 93
*/
#include "../import"
#ifndef hash_h
#define hash_h

typedef struct node
{
 Object ref;
 Object val;
 struct node *next;
} Node;

typedef struct Hash
{
 char           mark;
 unsigned int   nhash;
 Node         **list;
} Hash;

#define markarray(t)		((t)->mark)

Hash 	*lua_hashcreate (unsigned int nhash);
void 	 lua_hashdelete (Hash *h);
Object 	*lua_hashdefine (Hash *t, Object *ref);
void 	 lua_hashmark   (Hash *h);
void     lua_hashcollector (void);
void     lua_next (void);

#endif
