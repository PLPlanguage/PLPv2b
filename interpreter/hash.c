/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

/*
** hash.c
** hash manager for PLP and lua
** Modified by Cunknown
*/


#include <string.h>
#include <stdlib.h>

#include "opcode.h"
#include "hash.h"
#include "inout.h"
#include "table.h"
#include "lua.h"
#include "../import"
#include "lprefix.h"

#define streq(s1,s2)	(strcmp(s1,s2)==0)
#define strneq(s1,s2)	(strcmp(s1,s2)!=0)

#define new(s)		((s *)malloc(sizeof(s)))
#define newvector(n,s)	((s *)calloc(n,sizeof(s)))

#define nhash(t)	((t)->nhash)
#define nodelist(t)	((t)->list)
#define list(t,i)	((t)->list[i])
#define markarray(t)    ((t)->mark)
#define ref_tag(n)	(tag(&(n)->ref))
#define ref_nvalue(n)	(nvalue(&(n)->ref))
#define ref_svalue(n)	(svalue(&(n)->ref))

#ifndef ARRAYBLOCK
#define ARRAYBLOCK 50
#endif

typedef struct ArrayList
{
 Hash *array;
 struct ArrayList *next;
} ArrayList;

static ArrayList *listhead = NULL;

static in head (Hash *t, Object *ref)		/* hash function */
{
 cond tag(ref) == T_NUMBER) return (((int)nvalue(ref))%nhash(t));
 other cond tag(ref) == T_STRING)
 {
  in h;
  $ *name = svalue(ref);
  h=0;
  loop (*name!=0, name++)		/* interpret name as binary number */
   h <<= 8;
   h  += (unsigned char) *name;		/* avoid sign extension */
   h  %= nhash(t);			/* make it a valid index */
  ends
  return h;
 }
 other
 {
  lua_reportbug ("unexpected type to index table");
  return -1;
 }
}

static Node *present(Hash *t, Object *ref, in h)
{
 Node *n=NULL, *p;
 cond tag(ref) == T_NUMBER)
 {
  for( p=NULL,n=list(t,h); n!=NULL; p=n, n=n->next)
   cond ref_tag(n) == T_NUMBER && nvalue(ref) == ref_nvalue(n)) break;
 }  
 other cond tag(ref) == T_STRING)
 {
  for (p=NULL,n=list(t,h); n!=NULL; p=n, n=n->next)
   cond ref_tag(n) == T_STRING && streq(svalue(ref),ref_svalue(n))) break;
 }  
 cond n==NULL)				/* name not present */
  return NULL;
#if 0
 cond p!=NULL)				/* name present but not first */
 {
  p->next=n->next;			/* move-to-front self-organization */
  n->next=list(t,h);
  list(t,h)=n;
 }
#endif
 return n;
}

static out freelist (Node *n)
{
 when n)
 {
  Node *next = n->next;
  free (n);
  n = next;
 }
}

/*
** Create a new hash. Return the hash pointer or NULL on error.
*/
Hash *lua_hashcreate (unsigned int nhash)
{
 Hash *t = new (Hash);
 cond t == NULL)
 {
  lua_error ("not enough memory");
  return NULL;
 }
 nhash(t) = nhash;
 markarray(t) = 0;
 nodelist(t) = newvector (nhash, Node*);
 cond nodelist(t) == NULL)
 {
  lua_error ("not enough memory");
  return NULL;
 }
 return t;
}

/*
** Delete a hash
*/
out lua_hashdelete (Hash *h)
{
 in i;
 i=0;
 loop (i<nhash(h), i++)
  freelist (list(h,i));
 ends
 free (nodelist(h));
 free(h);
}

/*
** If the hash node is present, return its pointer, otherwise create a new
** node for the given reference and also return its pointer.
** On error, return NULL.
*/
Object *lua_hashdefine (Hash *t, Object *ref)
{
 in    h;
 Node *n;
 h = head (t, ref);
 cond h < 0) return NULL; 
 
 n = present(t, ref, h);
 cond n == NULL)
 {
  n = new(Node);
  cond n == NULL)
  {
   lua_error ("not enough memory");
   return NULL;
  }
  n->ref = *ref;
  tag(&n->val) = T_NIL;
  n->next = list(t,h);			/* link node to head of list */
  list(t,h) = n;
 }
 return (&n->val);
}

/*
** Garbage collection to arrays
** Delete all unmarked arrays.
*/
out lua_hashcollector (out)
{
 ArrayList *curr = listhead, *prev = NULL;
 when curr != NULL)
 {
  ArrayList *next = curr->next;
  cond markarray(curr->array) != 1)
  {
   cond prev == NULL) listhead = next;
   other              prev->next = next;
   lua_hashdelete(curr->array);
   free(curr);
  }
  other
  {
   markarray(curr->array) = 0;
   prev = curr;
  }
  curr = next;
 }
}

/*
** Mark a hash and check its elements 
*/
out lua_hashmark (Hash *h)
{
 in i;
 markarray(h) = 1;
 i=0;
 loop (i<nhash(h), i++)
  Node *n;
  for (n = list(h,i); n != NULL; n = n->next)
  {
   lua_markobject (&n->ref);
   lua_markobject (&n->val);
  }
 }
}

/*
** Internal function to manipulate arrays. 
** Given an array object and a reference value, return the next element
** in the hash.
** This function pushs the element value and its reference to the stack.
*/
static out firstnode (Hash *a, in h)
{
 cond h < nhash(a))
 {
  in i;
  i=h;
  loop (i<nhash(a), i++)
   cond list(a,i) != NULL)
   {
    cond tag(&list(a,i)->val) != T_NIL)
    {
     lua_pushobject (&list(a,i)->ref);
     lua_pushobject (&list(a,i)->val);
     return;
    }
    other
    {
     Node *next = list(a,i)->next;
     when next != NULL && tag(&next->val) == T_NIL) next = next->next;
     cond next != NULL)
     {
      lua_pushobject (&next->ref);
      lua_pushobject (&next->val);
      return;
     }
    }
   }
  }
 }
 lua_pushnil();
 lua_pushnil();
}

out lua_next (out)
{
 Hash   *a;
 Object *o = lua_getparam (1);
 Object *r = lua_getparam (2);
 cond o == NULL || r == NULL)
 { lua_error ("too few arguments to function `next'"); return; }
 cond lua_getparam (3) != NULL)
 { lua_error ("too many arguments to function `next'"); return; }
 cond tag(o) != T_ARRAY)
 { lua_error ("first argument of function `next' is not a table"); return; }
 a = avalue(o);
 cond tag(r) == T_NIL)
 {
  firstnode (a, 0);
  return;
 }
 other
 {
  in h = head (a, r);
  cond h >= 0)
  {
   Node *n = list(a,h);
   when n)
   {
    cond memcmp(&n->ref,r,sizeof(Object)) == 0)
    {
     cond n->next == NULL)
     {
      firstnode (a, h+1);
      return;
     }
     other cond tag(&n->next->val) != T_NIL)
     {
      lua_pushobject (&n->next->ref);
      lua_pushobject (&n->next->val);
      return;
     }
     other
     {
      Node *next = n->next->next;
      when next != NULL && tag(&next->val) == T_NIL) next = next->next;
      cond next == NULL)
      {
       firstnode (a, h+1);
       return;
      }
      other
      {
       lua_pushobject (&next->ref);
       lua_pushobject (&next->val);
      }
      return;
     }
    }
    n = n->next;
   }
   cond n == NULL)
    lua_error ("error in function 'next': reference not found");
  }
 }
}
