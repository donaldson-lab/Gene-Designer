/* ---------------------------------------------------------------------------
pknotsRG 1.3
Copyright (C) 2004-2006 Jens Reeder, Robert Giegerich, Peter Steffen
--------------------------------------------------------------------------- */
/* compiled by the ADP compiler, version 0.8 (rev 690)    Tue Sep 12 13:30:50 MEST 2006 */
/* source file: pknotsRG-enf-nd.lhs                                                 */
/* command:                                                                         */
/* adpcompile -c pknotsRG-enf-nd.lhs -al energy enum -cs energy -alpp pp -O -lcf -ta bto -bt so -gc cc -iuc -W */
/* -------------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "options.h"
#include "adplib.h"

#include "rnalib.h"

static void *hlp;  /* help pointer */
static void *hlp2; /* help pointer */

static tsequence *seq;
static toptions  *opts;
static char *z;
static int   n;

/* data structures                                                                  */
/* -------------------------------------------------------------------------------- */

struct str1 {
   int tup1;
   int tup2;
   int tup3;
};

static struct str1 move_str1(struct str1 s){
  s.tup2 -= opts->window_step;
  s.tup3 -= opts->window_step;
  return s;
}

struct str2 {
   int tup1;
   int tup2;
};
struct str3 {
   struct str3 *next;
   struct str3 *last;
   struct str_Signature *item;
};
struct str4 {
   int alg_energy;
   struct str3 *alg_enum;
};
struct str5 {
   struct str5 *next;
   struct str5 *last;
   struct str4 item;
};
struct str6 {
   struct str1 alg_energy;
   struct str3 *alg_enum;
};
struct str7 {
   struct str7 *next;
   struct str7 *last;
   struct str6 item;
};
struct str8 {
   struct str2 alg_energy;
   struct str3 *alg_enum;
};
struct str9 {
   struct str9 *next;
   struct str9 *last;
   struct str8 item;
};

/* supporting functions for objective functions                                     */
/* -------------------------------------------------------------------------------- */

static int sort_TLInt(void *p, void *q)
{
   int result;

   result = (*((int *)p)) > (*((int *)q)) ? 1 : (-1);
   return(result);
}

static char nub_TLInt(void *p, void *q)
{
   char result;

   result = (*((int *)p)) == (*((int *)q));
   return(result);
}

static int sort_PointerOfStructOfstrSignature(void *p, void *q)
{
   int result;

   result = (*((struct str_Signature **)p)) > (*((struct str_Signature **)q)) ? 1 : (-1);
   return(result);
}

static char nub_PointerOfStructOfstrSignature(void *p, void *q)
{
   char result;

   result = (*((struct str_Signature **)p)) == (*((struct str_Signature **)q));
   return(result);
}

/* backtrace variables                                                              */
/* -------------------------------------------------------------------------------- */

static struct str3 **pp_next, **pp_initA, **removeAddr;
static struct str3 ***pp_init;
static int pp_initC;
static int copy_depth;
static char *pp_outp, *result_prettyprint;
static int traceback_diff;
static char rmAllowed;

/* signature                                                                        */
/* -------------------------------------------------------------------------------- */

#define SIGID__NTID 1
#define SIGID_Sadd 2
#define SIGID_Cadd 3
#define SIGID_Is 4
#define SIGID_Sr 5
#define SIGID_Hl 6
#define SIGID_Bl 7
#define SIGID_Br 8
#define SIGID_Il 9
#define SIGID_Ml 10
#define SIGID_Drem 11
#define SIGID_Cons 12
#define SIGID_Ul 13
#define SIGID_Pul 14
#define SIGID_Addss 15
#define SIGID_Ssadd 16
#define SIGID_Nil 17
#define SIGID_Combine 18
#define SIGID_Sum 19
#define SIGID_Sumend 20
#define SIGID_Pk 21
#define SIGID_Pkml 22
#define SIGID_Pk_Pr 23
#define SIGID_Emptymid 24
#define SIGID_Midbase 25
#define SIGID_Midregion 26
#define SIGID_Pss 27

struct str_Signature {
   int utype;
   void *entry;
   char fcalled;
};

static struct str3 *new_Signature(int u, void *entry)
{
   struct str_Signature *t;
   struct str3 *l;

   t=(struct str_Signature *) myalloc(adp_dynmem, sizeof(struct str_Signature ));
   t->utype = u;
   t->entry = entry;
   t->fcalled = 0;
   l=(struct str3 *) myalloc(adp_dynmem, sizeof(struct str3 ));
   l->item = t;
   l->next = NULL;
   l->last = l;
   return(l);
}

/* signature operators                                                              */
/* -------------------------------------------------------------------------------- */
/* operator _NTID                                                                   */
/* -------------------------------------------------------------------------------- */

struct str__NTID {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};

static struct str3 *new__NTID(struct str3 *(*f1)(int , int , int ), int i1, int j1)
{
   struct str__NTID *t;

   t=(struct str__NTID *) myalloc(adp_dynmem, sizeof(struct str__NTID ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   return(new_Signature(SIGID__NTID, t));
}

/* operator Sadd                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Sadd {
   int a1;
   int isStructure2;
   struct str3 *structure2;
   struct str3 *a2;
   struct str3 *pp_init_a2;
   struct str3 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
};

static struct str3 *new_Sadd_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2)
{
   struct str_Sadd *t;

   t=(struct str_Sadd *) myalloc(adp_dynmem, sizeof(struct str_Sadd ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   return(new_Signature(SIGID_Sadd, t));
}


/* operator Cadd                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Cadd {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int isStructure2;
   struct str3 *structure2;
   struct str3 *a2;
   struct str3 *pp_init_a2;
   struct str3 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
};

static struct str3 *new_Cadd_ff(struct str3 *(*f1)(int , int , int ), int i1, int j1, struct str3 *(*f2)(int , int , int ), int i2, int j2)
{
   struct str_Cadd *t;

   t=(struct str_Cadd *) myalloc(adp_dynmem, sizeof(struct str_Cadd ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   return(new_Signature(SIGID_Cadd, t));
}




/* operator Is                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Is {
   int a1;
   int isStructure2;
   struct str3 *structure2;
   struct str3 *a2;
   struct str3 *pp_init_a2;
   struct str3 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
};

static struct str3 *new_Is_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3)
{
   struct str_Is *t;

   t=(struct str_Is *) myalloc(adp_dynmem, sizeof(struct str_Is ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   return(new_Signature(SIGID_Is, t));
}


/* operator Sr                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Sr {
   int a1;
   int isStructure2;
   struct str3 *structure2;
   struct str3 *a2;
   struct str3 *pp_init_a2;
   struct str3 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
};

static struct str3 *new_Sr_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3)
{
   struct str_Sr *t;

   t=(struct str_Sr *) myalloc(adp_dynmem, sizeof(struct str_Sr ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   return(new_Signature(SIGID_Sr, t));
}


/* operator Hl                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Hl {
   int a1;
   int a2;
   int a3;
   int a4;
   int a5;
   int a6;
   int diff;
};

static struct str3 *new_Hl_(int a1, int a2, int a3, int a4, int a5, int a6)
{
   struct str_Hl *t;

   t=(struct str_Hl *) myalloc(adp_dynmem, sizeof(struct str_Hl ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   t->a5 = a5;
   t->a6 = a6;
   return(new_Signature(SIGID_Hl, t));
}

/* operator Bl                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Bl {
   int a1;
   int a2;
   int a3;
   int a4;
   int isStructure5;
   struct str3 *structure5;
   struct str3 *a5;
   struct str3 *pp_init_a5;
   struct str3 *(*f5)(int , int , int );
   int i5, j5;
   int diff5;
   int a6;
   int a7;
};


static struct str3 *new_Bl_s(int a1, int a2, int a3, int a4, struct str3 *structure5, int a6, int a7)
{
   struct str_Bl *t;

   t=(struct str_Bl *) myalloc(adp_dynmem, sizeof(struct str_Bl ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   t->isStructure5 = 1;
   t->structure5 = structure5;
   t->a6 = a6;
   t->a7 = a7;
   return(new_Signature(SIGID_Bl, t));
}

/* operator Br                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Br {
   int a1;
   int a2;
   int isStructure3;
   struct str3 *structure3;
   struct str3 *a3;
   struct str3 *pp_init_a3;
   struct str3 *(*f3)(int , int , int );
   int i3, j3;
   int diff3;
   int a4;
   int a5;
   int a6;
   int a7;
};


static struct str3 *new_Br_s(int a1, int a2, struct str3 *structure3, int a4, int a5, int a6, int a7)
{
   struct str_Br *t;

   t=(struct str_Br *) myalloc(adp_dynmem, sizeof(struct str_Br ));
   t->a1 = a1;
   t->a2 = a2;
   t->isStructure3 = 1;
   t->structure3 = structure3;
   t->a4 = a4;
   t->a5 = a5;
   t->a6 = a6;
   t->a7 = a7;
   return(new_Signature(SIGID_Br, t));
}

/* operator Il                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Il {
   int a1;
   int a2;
   int a3;
   int a4;
   int isStructure5;
   struct str3 *structure5;
   struct str3 *a5;
   struct str3 *pp_init_a5;
   struct str3 *(*f5)(int , int , int );
   int i5, j5;
   int diff5;
   int a6;
   int a7;
   int a8;
   int a9;
};

static struct str3 *new_Il_f(int a1, int a2, int a3, int a4, struct str3 *(*f5)(int , int , int ), int i5, int j5, int a6, int a7, int a8, int a9)
{
   struct str_Il *t;

   t=(struct str_Il *) myalloc(adp_dynmem, sizeof(struct str_Il ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   t->isStructure5 = 0;
   t->f5 = f5;
   t->i5 = i5;
   t->j5 = j5;
   t->a6 = a6;
   t->a7 = a7;
   t->a8 = a8;
   t->a9 = a9;
   return(new_Signature(SIGID_Il, t));
}


/* operator Ml                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Ml {
   int a1;
   int a2;
   int isStructure3;
   struct str3 *structure3;
   struct str3 *a3;
   struct str3 *pp_init_a3;
   struct str3 *(*f3)(int , int , int );
   int i3, j3;
   int diff3;
   int a4;
   int a5;
};


static struct str3 *new_Ml_s(int a1, int a2, struct str3 *structure3, int a4, int a5)
{
   struct str_Ml *t;

   t=(struct str_Ml *) myalloc(adp_dynmem, sizeof(struct str_Ml ));
   t->a1 = a1;
   t->a2 = a2;
   t->isStructure3 = 1;
   t->structure3 = structure3;
   t->a4 = a4;
   t->a5 = a5;
   return(new_Signature(SIGID_Ml, t));
}

/* operator Drem                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Drem {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str3 *new_Drem_s(struct str3 *structure1)
{
   struct str_Drem *t;

   t=(struct str_Drem *) myalloc(adp_dynmem, sizeof(struct str_Drem ));
   t->isStructure1 = 1;
   t->structure1 = structure1;
   return(new_Signature(SIGID_Drem, t));
}

/* operator Cons                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Cons {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int isStructure2;
   struct str3 *structure2;
   struct str3 *a2;
   struct str3 *pp_init_a2;
   struct str3 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
};

static struct str3 *new_Cons_ff(struct str3 *(*f1)(int , int , int ), int i1, int j1, struct str3 *(*f2)(int , int , int ), int i2, int j2)
{
   struct str_Cons *t;

   t=(struct str_Cons *) myalloc(adp_dynmem, sizeof(struct str_Cons ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   return(new_Signature(SIGID_Cons, t));
}




/* operator Ul                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Ul {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str3 *new_Ul_s(struct str3 *structure1)
{
   struct str_Ul *t;

   t=(struct str_Ul *) myalloc(adp_dynmem, sizeof(struct str_Ul ));
   t->isStructure1 = 1;
   t->structure1 = structure1;
   return(new_Signature(SIGID_Ul, t));
}

/* operator Pul                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Pul {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str3 *new_Pul_s(struct str3 *structure1)
{
   struct str_Pul *t;

   t=(struct str_Pul *) myalloc(adp_dynmem, sizeof(struct str_Pul ));
   t->isStructure1 = 1;
   t->structure1 = structure1;
   return(new_Signature(SIGID_Pul, t));
}

/* operator Addss                                                                   */
/* -------------------------------------------------------------------------------- */

struct str_Addss {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int a2;
   int a3;
};

static struct str3 *new_Addss_f(struct str3 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3)
{
   struct str_Addss *t;

   t=(struct str_Addss *) myalloc(adp_dynmem, sizeof(struct str_Addss ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->a2 = a2;
   t->a3 = a3;
   return(new_Signature(SIGID_Addss, t));
}


/* operator Ssadd                                                                   */
/* -------------------------------------------------------------------------------- */

struct str_Ssadd {
   int a1;
   int a2;
   int isStructure3;
   struct str3 *structure3;
   struct str3 *a3;
   struct str3 *pp_init_a3;
   struct str3 *(*f3)(int , int , int );
   int i3, j3;
   int diff3;
};


static struct str3 *new_Ssadd_s(int a1, int a2, struct str3 *structure3)
{
   struct str_Ssadd *t;

   t=(struct str_Ssadd *) myalloc(adp_dynmem, sizeof(struct str_Ssadd ));
   t->a1 = a1;
   t->a2 = a2;
   t->isStructure3 = 1;
   t->structure3 = structure3;
   return(new_Signature(SIGID_Ssadd, t));
}

/* operator Nil                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Nil {
   int a1;
   int diff;
};

static struct str3 *new_Nil_(int a1)
{
   struct str_Nil *t;

   t=(struct str_Nil *) myalloc(adp_dynmem, sizeof(struct str_Nil ));
   t->a1 = a1;
   return(new_Signature(SIGID_Nil, t));
}

/* operator Combine                                                                 */
/* -------------------------------------------------------------------------------- */

struct str_Combine {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int isStructure2;
   struct str3 *structure2;
   struct str3 *a2;
   struct str3 *pp_init_a2;
   struct str3 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
};

static struct str3 *new_Combine_ff(struct str3 *(*f1)(int , int , int ), int i1, int j1, struct str3 *(*f2)(int , int , int ), int i2, int j2)
{
   struct str_Combine *t;

   t=(struct str_Combine *) myalloc(adp_dynmem, sizeof(struct str_Combine ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   return(new_Signature(SIGID_Combine, t));
}




/* operator Sum                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Sum {
   int a1;
   int isStructure2;
   struct str3 *structure2;
   struct str3 *a2;
   struct str3 *pp_init_a2;
   struct str3 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
   int a4;
};

static struct str3 *new_Sum_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4)
{
   struct str_Sum *t;

   t=(struct str_Sum *) myalloc(adp_dynmem, sizeof(struct str_Sum ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   t->a4 = a4;
   return(new_Signature(SIGID_Sum, t));
}


/* operator Sumend                                                                  */
/* -------------------------------------------------------------------------------- */

struct str_Sumend {
   int a1;
   int a2;
   int a3;
   int a4;
   int diff;
};

static struct str3 *new_Sumend_(int a1, int a2, int a3, int a4)
{
   struct str_Sumend *t;

   t=(struct str_Sumend *) myalloc(adp_dynmem, sizeof(struct str_Sumend ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   return(new_Signature(SIGID_Sumend, t));
}

/* operator Pk                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Pk {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int a2;
   int a3;
};

static struct str3 *new_Pk_f(struct str3 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3)
{
   struct str_Pk *t;

   t=(struct str_Pk *) myalloc(adp_dynmem, sizeof(struct str_Pk ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->a2 = a2;
   t->a3 = a3;
   return(new_Signature(SIGID_Pk, t));
}


/* operator Pkml                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Pkml {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int a2;
   int a3;
};

static struct str3 *new_Pkml_f(struct str3 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3)
{
   struct str_Pkml *t;

   t=(struct str_Pkml *) myalloc(adp_dynmem, sizeof(struct str_Pkml ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->a2 = a2;
   t->a3 = a3;
   return(new_Signature(SIGID_Pkml, t));
}


/* operator Pk_Pr                                                                   */
/* -------------------------------------------------------------------------------- */

struct str_Pk_Pr {
   int a1;
   int a2;
   int a3;
   int isStructure4;
   struct str3 *structure4;
   struct str3 *a4;
   struct str3 *pp_init_a4;
   struct str3 *(*f4)(int , int , int );
   int i4, j4;
   int diff4;
   int a5;
   int a6;
   int isStructure7;
   struct str3 *structure7;
   struct str3 *a7;
   struct str3 *pp_init_a7;
   struct str3 *(*f7)(int , int , int );
   int i7, j7;
   int diff7;
   int a8;
   int a9;
   int isStructure10;
   struct str3 *structure10;
   struct str3 *a10;
   struct str3 *pp_init_a10;
   struct str3 *(*f10)(int , int , int );
   int i10, j10;
   int diff10;
   int a11;
   int a12;
};








static struct str3 *new_Pk_Pr_sss(int a1, int a2, int a3, struct str3 *structure4, int a5, int a6, struct str3 *structure7, int a8, int a9, struct str3 *structure10, int a11, int a12)
{
   struct str_Pk_Pr *t;

   t=(struct str_Pk_Pr *) myalloc(adp_dynmem, sizeof(struct str_Pk_Pr ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->isStructure4 = 1;
   t->structure4 = structure4;
   t->a5 = a5;
   t->a6 = a6;
   t->isStructure7 = 1;
   t->structure7 = structure7;
   t->a8 = a8;
   t->a9 = a9;
   t->isStructure10 = 1;
   t->structure10 = structure10;
   t->a11 = a11;
   t->a12 = a12;
   return(new_Signature(SIGID_Pk_Pr, t));
}

/* operator Emptymid                                                                */
/* -------------------------------------------------------------------------------- */

struct str_Emptymid {
   int a1;
   int a2;
   int a3;
   int diff;
};

static struct str3 *new_Emptymid_(int a1, int a2, int a3)
{
   struct str_Emptymid *t;

   t=(struct str_Emptymid *) myalloc(adp_dynmem, sizeof(struct str_Emptymid ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   return(new_Signature(SIGID_Emptymid, t));
}

/* operator Midbase                                                                 */
/* -------------------------------------------------------------------------------- */

struct str_Midbase {
   int a1;
   int a2;
   int a3;
   int diff;
};

static struct str3 *new_Midbase_(int a1, int a2, int a3)
{
   struct str_Midbase *t;

   t=(struct str_Midbase *) myalloc(adp_dynmem, sizeof(struct str_Midbase ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   return(new_Signature(SIGID_Midbase, t));
}

/* operator Midregion                                                               */
/* -------------------------------------------------------------------------------- */

struct str_Midregion {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str3 *new_Midregion_s(struct str3 *structure1)
{
   struct str_Midregion *t;

   t=(struct str_Midregion *) myalloc(adp_dynmem, sizeof(struct str_Midregion ));
   t->isStructure1 = 1;
   t->structure1 = structure1;
   return(new_Signature(SIGID_Midregion, t));
}

/* operator Pss                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Pss {
   int a1;
   int a2;
   int diff;
};

static struct str3 *new_Pss_(int a1, int a2)
{
   struct str_Pss *t;

   t=(struct str_Pss *) myalloc(adp_dynmem, sizeof(struct str_Pss ));
   t->a1 = a1;
   t->a2 = a2;
   return(new_Signature(SIGID_Pss, t));
}

/* signature pretty printer                                                         */
/* -------------------------------------------------------------------------------- */
static int pp_str_Signature(struct str3 *l)
{
   struct str_Signature *c;
   int score, score1, score2, score3, score4, score5;
   int score6, score7, score8, score9, score10, score11, score12;

   if (l != NULL) {
      c = l->item;
      if (c->utype == SIGID__NTID) {
         if (((struct str__NTID *)(c->entry))->a1 != NULL) {
            if (((struct str__NTID *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str__NTID *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str__NTID *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str__NTID *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str__NTID *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str__NTID *)(c->entry))->a1);
            score = score1;
         }
      } else 
      if (c->utype == SIGID_Sadd) {
         if (((struct str_Sadd *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Sadd *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Sadd *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Sadd *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Sadd *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Sadd *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Sadd *)(c->entry))->a2);
            score = score2;
         }
      } else 
      if (c->utype == SIGID_Cadd) {
         rmAllowed = 0;
         if ((((struct str_Cadd *)(c->entry))->a1 != NULL) && (((struct str_Cadd *)(c->entry))->a2 != NULL)) {
            if (((struct str_Cadd *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Cadd *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Cadd *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Cadd *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Cadd *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Cadd *)(c->entry))->a1);
            if (((struct str_Cadd *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Cadd *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Cadd *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Cadd *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Cadd *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Cadd *)(c->entry))->a2);
            score = score1 + score2;
         }
      } else 
      if (c->utype == SIGID_Is) {
         if (((struct str_Is *)(c->entry))->a2 != NULL) {
            if (((struct str_Is *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Is *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Is *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Is *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Is *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Is *)(c->entry))->a2);
            score = score2 + termaupenalty(((struct str_Is *)(c->entry))->a1 + 1, ((struct str_Is *)(c->entry))->a3);
         }
      } else 
      if (c->utype == SIGID_Sr) {
         if (((struct str_Sr *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, "(");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Sr *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Sr *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Sr *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Sr *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Sr *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Sr *)(c->entry))->a2);
            sprintf(pp_outp, ")");
            pp_outp = pp_outp + strlen(pp_outp);
            score = score2 + sr_energy(((struct str_Sr *)(c->entry))->a1, ((struct str_Sr *)(c->entry))->a3);
         }
      } else 
      if (c->utype == SIGID_Hl) {
         sprintf(pp_outp, "((");
         pp_outp = pp_outp + strlen(pp_outp);
         sprintf(pp_outp, "%s", dots(((struct str_Hl *)(c->entry))->a3, ((struct str_Hl *)(c->entry))->a4));
         pp_outp = pp_outp + strlen(pp_outp);
         sprintf(pp_outp, "))");
         pp_outp = pp_outp + strlen(pp_outp);
         score = hl_energy(((struct str_Hl *)(c->entry))->a2, ((struct str_Hl *)(c->entry))->a5) + sr_energy(((struct str_Hl *)(c->entry))->a1, ((struct str_Hl *)(c->entry))->a6);
      } else 
      if (c->utype == SIGID_Bl) {
         if (((struct str_Bl *)(c->entry))->a5 != NULL) {
            sprintf(pp_outp, "((");
            pp_outp = pp_outp + strlen(pp_outp);
            sprintf(pp_outp, "%s", dots(((struct str_Bl *)(c->entry))->a3, ((struct str_Bl *)(c->entry))->a4));
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Bl *)(c->entry))->a5->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Bl *)(c->entry))->a5);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Bl *)(c->entry))->a5);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Bl *)(c->entry))->a5);
                  pp_initA[pp_initC] = ((struct str_Bl *)(c->entry))->pp_init_a5;
               }
            }
            score5 = pp_str_Signature(((struct str_Bl *)(c->entry))->a5);
            sprintf(pp_outp, "))");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score5 + bl_energy(((struct str_Bl *)(c->entry))->a2, ((struct str_Bl *)(c->entry))->a3, ((struct str_Bl *)(c->entry))->a4, ((struct str_Bl *)(c->entry))->a6)) + sr_energy(((struct str_Bl *)(c->entry))->a1, ((struct str_Bl *)(c->entry))->a7);
         }
      } else 
      if (c->utype == SIGID_Br) {
         if (((struct str_Br *)(c->entry))->a3 != NULL) {
            sprintf(pp_outp, "((");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Br *)(c->entry))->a3->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Br *)(c->entry))->a3);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Br *)(c->entry))->a3);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Br *)(c->entry))->a3);
                  pp_initA[pp_initC] = ((struct str_Br *)(c->entry))->pp_init_a3;
               }
            }
            score3 = pp_str_Signature(((struct str_Br *)(c->entry))->a3);
            sprintf(pp_outp, "%s", dots(((struct str_Br *)(c->entry))->a4, ((struct str_Br *)(c->entry))->a5));
            pp_outp = pp_outp + strlen(pp_outp);
            sprintf(pp_outp, "))");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score3 + br_energy(((struct str_Br *)(c->entry))->a2, ((struct str_Br *)(c->entry))->a4, ((struct str_Br *)(c->entry))->a5, ((struct str_Br *)(c->entry))->a6)) + sr_energy(((struct str_Br *)(c->entry))->a1, ((struct str_Br *)(c->entry))->a7);
         }
      } else 
      if (c->utype == SIGID_Il) {
         if (((struct str_Il *)(c->entry))->a5 != NULL) {
            sprintf(pp_outp, "((");
            pp_outp = pp_outp + strlen(pp_outp);
            sprintf(pp_outp, "%s", dots(((struct str_Il *)(c->entry))->a3, ((struct str_Il *)(c->entry))->a4));
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Il *)(c->entry))->a5->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Il *)(c->entry))->a5);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Il *)(c->entry))->a5);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Il *)(c->entry))->a5);
                  pp_initA[pp_initC] = ((struct str_Il *)(c->entry))->pp_init_a5;
               }
            }
            score5 = pp_str_Signature(((struct str_Il *)(c->entry))->a5);
            sprintf(pp_outp, "%s", dots(((struct str_Il *)(c->entry))->a6, ((struct str_Il *)(c->entry))->a7));
            pp_outp = pp_outp + strlen(pp_outp);
            sprintf(pp_outp, "))");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score5 + sr_energy(((struct str_Il *)(c->entry))->a1, ((struct str_Il *)(c->entry))->a9)) + il_energy(((struct str_Il *)(c->entry))->a3, ((struct str_Il *)(c->entry))->a4, ((struct str_Il *)(c->entry))->a6, ((struct str_Il *)(c->entry))->a7);
         }
      } else 
      if (c->utype == SIGID_Ml) {
         if (((struct str_Ml *)(c->entry))->a3 != NULL) {
            sprintf(pp_outp, "((");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Ml *)(c->entry))->a3->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Ml *)(c->entry))->a3);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Ml *)(c->entry))->a3);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Ml *)(c->entry))->a3);
                  pp_initA[pp_initC] = ((struct str_Ml *)(c->entry))->pp_init_a3;
               }
            }
            score3 = pp_str_Signature(((struct str_Ml *)(c->entry))->a3);
            sprintf(pp_outp, "))");
            pp_outp = pp_outp + strlen(pp_outp);
            score = ((380 + score3) + sr_energy(((struct str_Ml *)(c->entry))->a1, ((struct str_Ml *)(c->entry))->a5)) + termaupenalty(((struct str_Ml *)(c->entry))->a2, ((struct str_Ml *)(c->entry))->a4);
         }
      } else 
      if (c->utype == SIGID_Drem) {
         if (((struct str_Drem *)(c->entry))->a1 != NULL) {
            if (((struct str_Drem *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Drem *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Drem *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Drem *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Drem *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Drem *)(c->entry))->a1);
            score = score1;
         }
      } else 
      if (c->utype == SIGID_Cons) {
         rmAllowed = 0;
         if ((((struct str_Cons *)(c->entry))->a1 != NULL) && (((struct str_Cons *)(c->entry))->a2 != NULL)) {
            if (((struct str_Cons *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Cons *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Cons *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Cons *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Cons *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Cons *)(c->entry))->a1);
            if (((struct str_Cons *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Cons *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Cons *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Cons *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Cons *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Cons *)(c->entry))->a2);
            score = score1 + score2;
         }
      } else 
      if (c->utype == SIGID_Ul) {
         if (((struct str_Ul *)(c->entry))->a1 != NULL) {
            if (((struct str_Ul *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Ul *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Ul *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Ul *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Ul *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Ul *)(c->entry))->a1);
            score = 40 + score1;
         }
      } else 
      if (c->utype == SIGID_Pul) {
         if (((struct str_Pul *)(c->entry))->a1 != NULL) {
            if (((struct str_Pul *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Pul *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Pul *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Pul *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Pul *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Pul *)(c->entry))->a1);
            score = score1;
         }
      } else 
      if (c->utype == SIGID_Addss) {
         if (((struct str_Addss *)(c->entry))->a1 != NULL) {
            if (((struct str_Addss *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Addss *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Addss *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Addss *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Addss *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Addss *)(c->entry))->a1);
            sprintf(pp_outp, "%s", dots(((struct str_Addss *)(c->entry))->a2, ((struct str_Addss *)(c->entry))->a3));
            pp_outp = pp_outp + strlen(pp_outp);
            score = score1 + ss_energy(((struct str_Addss *)(c->entry))->a2, ((struct str_Addss *)(c->entry))->a3);
         }
      } else 
      if (c->utype == SIGID_Ssadd) {
         if (((struct str_Ssadd *)(c->entry))->a3 != NULL) {
            sprintf(pp_outp, "%s", dots(((struct str_Ssadd *)(c->entry))->a1, ((struct str_Ssadd *)(c->entry))->a2));
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Ssadd *)(c->entry))->a3->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Ssadd *)(c->entry))->a3);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Ssadd *)(c->entry))->a3);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Ssadd *)(c->entry))->a3);
                  pp_initA[pp_initC] = ((struct str_Ssadd *)(c->entry))->pp_init_a3;
               }
            }
            score3 = pp_str_Signature(((struct str_Ssadd *)(c->entry))->a3);
            score = (40 + score3) + ss_energy(((struct str_Ssadd *)(c->entry))->a1, ((struct str_Ssadd *)(c->entry))->a2);
         }
      } else 
      if (c->utype == SIGID_Nil) {
         sprintf(pp_outp, "");
         pp_outp = pp_outp + strlen(pp_outp);
         score = 0;
      } else 
      if (c->utype == SIGID_Combine) {
         rmAllowed = 0;
         if ((((struct str_Combine *)(c->entry))->a1 != NULL) && (((struct str_Combine *)(c->entry))->a2 != NULL)) {
            if (((struct str_Combine *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Combine *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Combine *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Combine *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Combine *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Combine *)(c->entry))->a1);
            if (((struct str_Combine *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Combine *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Combine *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Combine *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Combine *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Combine *)(c->entry))->a2);
            score = score1 + score2;
         }
      } else 
      if (c->utype == SIGID_Sum) {
         if (((struct str_Sum *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, "");
            pp_outp = pp_outp + strlen(pp_outp);
            score = score2 + sr_energy(((struct str_Sum *)(c->entry))->a1, ((struct str_Sum *)(c->entry))->a4);
         }
      } else 
      if (c->utype == SIGID_Sumend) {
         sprintf(pp_outp, "");
         pp_outp = pp_outp + strlen(pp_outp);
         score = 0;
      } else 
      if (c->utype == SIGID_Pk) {
         if (((struct str_Pk *)(c->entry))->a1 != NULL) {
            if (((struct str_Pk *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Pk *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Pk *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Pk *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Pk *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Pk *)(c->entry))->a1);
            score = score1;
         }
      } else 
      if (c->utype == SIGID_Pkml) {
         if (((struct str_Pkml *)(c->entry))->a1 != NULL) {
            if (((struct str_Pkml *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Pkml *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Pkml *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Pkml *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Pkml *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Pkml *)(c->entry))->a1);
            score = score1 + 600;
         }
      } else 
      if (c->utype == SIGID_Pk_Pr) {
         rmAllowed = 0;
         if ((((struct str_Pk_Pr *)(c->entry))->a4 != NULL) && ((((struct str_Pk_Pr *)(c->entry))->a7 != NULL) && (((struct str_Pk_Pr *)(c->entry))->a10 != NULL))) {
            sprintf(pp_outp, "%s", open1(((struct str_Pk_Pr *)(c->entry))->a2, ((struct str_Pk_Pr *)(c->entry))->a3));
            pp_outp = pp_outp + strlen(pp_outp);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Pk_Pr *)(c->entry))->a4->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Pk_Pr *)(c->entry))->a4);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Pk_Pr *)(c->entry))->a4);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Pk_Pr *)(c->entry))->a4);
                  pp_initA[pp_initC] = ((struct str_Pk_Pr *)(c->entry))->pp_init_a4;
               }
            }
            score4 = pp_str_Signature(((struct str_Pk_Pr *)(c->entry))->a4);
            sprintf(pp_outp, "%s", open2(((struct str_Pk_Pr *)(c->entry))->a5, ((struct str_Pk_Pr *)(c->entry))->a6));
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Pk_Pr *)(c->entry))->a7->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Pk_Pr *)(c->entry))->a7);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Pk_Pr *)(c->entry))->a7);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Pk_Pr *)(c->entry))->a7);
                  pp_initA[pp_initC] = ((struct str_Pk_Pr *)(c->entry))->pp_init_a7;
               }
            }
            score7 = pp_str_Signature(((struct str_Pk_Pr *)(c->entry))->a7);
            sprintf(pp_outp, "%s", close1(((struct str_Pk_Pr *)(c->entry))->a8, ((struct str_Pk_Pr *)(c->entry))->a9));
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Pk_Pr *)(c->entry))->a10->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Pk_Pr *)(c->entry))->a10);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Pk_Pr *)(c->entry))->a10);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Pk_Pr *)(c->entry))->a10);
                  pp_initA[pp_initC] = ((struct str_Pk_Pr *)(c->entry))->pp_init_a10;
               }
            }
            score10 = pp_str_Signature(((struct str_Pk_Pr *)(c->entry))->a10);
            sprintf(pp_outp, "..");
            pp_outp = pp_outp + strlen(pp_outp);
            sprintf(pp_outp, "%s", close2(((struct str_Pk_Pr *)(c->entry))->a11, ((struct str_Pk_Pr *)(c->entry))->a12));
            pp_outp = pp_outp + strlen(pp_outp);
            score = (((((pkinit + ((struct str_Pk_Pr *)(c->entry))->a1) + (3 * npp)) + score4) + score7) + score10) + dangles(((struct str_Pk_Pr *)(c->entry))->a2, ((struct str_Pk_Pr *)(c->entry))->a3, ((struct str_Pk_Pr *)(c->entry))->a5, ((struct str_Pk_Pr *)(c->entry))->a6, ((struct str_Pk_Pr *)(c->entry))->a8, ((struct str_Pk_Pr *)(c->entry))->a9, ((struct str_Pk_Pr *)(c->entry))->a11, ((struct str_Pk_Pr *)(c->entry))->a12);
         }
      } else 
      if (c->utype == SIGID_Emptymid) {
         sprintf(pp_outp, "");
         pp_outp = pp_outp + strlen(pp_outp);
         score = wkn * stack_dg_ac(((struct str_Emptymid *)(c->entry))->a2, ((struct str_Emptymid *)(c->entry))->a1 + 1, ((struct str_Emptymid *)(c->entry))->a3, ((struct str_Emptymid *)(c->entry))->a3 + 1);
      } else 
      if (c->utype == SIGID_Midbase) {
         sprintf(pp_outp, ".");
         pp_outp = pp_outp + strlen(pp_outp);
         score = (wkn * stack_dg_ac(((struct str_Midbase *)(c->entry))->a2, ((struct str_Midbase *)(c->entry))->a1 + 1, ((struct str_Midbase *)(c->entry))->a3 - 1, ((struct str_Midbase *)(c->entry))->a3 + 1)) + npp;
      } else 
      if (c->utype == SIGID_Midregion) {
         if (((struct str_Midregion *)(c->entry))->a1 != NULL) {
            if (((struct str_Midregion *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Midregion *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Midregion *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Midregion *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Midregion *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Midregion *)(c->entry))->a1);
            score = score1;
         }
      } else 
      if (c->utype == SIGID_Pss) {
         sprintf(pp_outp, "%s", dots(((struct str_Pss *)(c->entry))->a1, ((struct str_Pss *)(c->entry))->a2));
         pp_outp = pp_outp + strlen(pp_outp);
         score = sspenalty(((struct str_Pss *)(c->entry))->a2 - ((struct str_Pss *)(c->entry))->a1);
      };
   }
   return(score);
}

/* copy structures                                                                  */
/* -------------------------------------------------------------------------------- */
static struct str3 *copy_str_Signature(struct str3 *l)
{
   struct str3 *itr, *nstr, *last, *first, *setnext;
   void *entr;
   int id;

   copy_depth = copy_depth + 1;
   itr = l;
   first = NULL;
   setnext = NULL;
   while (itr != NULL) {
      nstr=(struct str3 *) malloc(sizeof(struct str3 ));
      nstr->next = NULL;
      nstr->last = nstr;
      if (setnext) {
         setnext->next = nstr;
      }
      setnext = nstr;
      if (first == NULL) {
         first = nstr;
      }
      nstr->item=(struct str_Signature *) malloc(sizeof(struct str_Signature ));
      (*nstr->item) = (*itr->item);
      id = itr->item->utype;
      entr = itr->item->entry;
      if (id == SIGID__NTID) {
         nstr->item->entry=(struct str__NTID *) malloc(sizeof(struct str__NTID ));
         (*((struct str__NTID *)(nstr->item->entry))) = (*((struct str__NTID *)entr));
         if (((struct str__NTID *)(nstr->item->entry))->isStructure1) {
            ((struct str__NTID *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str__NTID *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Sadd) {
         nstr->item->entry=(struct str_Sadd *) malloc(sizeof(struct str_Sadd ));
         (*((struct str_Sadd *)(nstr->item->entry))) = (*((struct str_Sadd *)entr));
         if (((struct str_Sadd *)(nstr->item->entry))->isStructure2) {
            ((struct str_Sadd *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Sadd *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Cadd) {
         nstr->item->entry=(struct str_Cadd *) malloc(sizeof(struct str_Cadd ));
         (*((struct str_Cadd *)(nstr->item->entry))) = (*((struct str_Cadd *)entr));
         if (((struct str_Cadd *)(nstr->item->entry))->isStructure1) {
            ((struct str_Cadd *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Cadd *)entr)->structure1);
         }
         if (((struct str_Cadd *)(nstr->item->entry))->isStructure2) {
            ((struct str_Cadd *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Cadd *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Is) {
         nstr->item->entry=(struct str_Is *) malloc(sizeof(struct str_Is ));
         (*((struct str_Is *)(nstr->item->entry))) = (*((struct str_Is *)entr));
         if (((struct str_Is *)(nstr->item->entry))->isStructure2) {
            ((struct str_Is *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Is *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Sr) {
         nstr->item->entry=(struct str_Sr *) malloc(sizeof(struct str_Sr ));
         (*((struct str_Sr *)(nstr->item->entry))) = (*((struct str_Sr *)entr));
         if (((struct str_Sr *)(nstr->item->entry))->isStructure2) {
            ((struct str_Sr *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Sr *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Hl) {
         nstr->item->entry=(struct str_Hl *) malloc(sizeof(struct str_Hl ));
         (*((struct str_Hl *)(nstr->item->entry))) = (*((struct str_Hl *)entr));
      } else 
      if (id == SIGID_Bl) {
         nstr->item->entry=(struct str_Bl *) malloc(sizeof(struct str_Bl ));
         (*((struct str_Bl *)(nstr->item->entry))) = (*((struct str_Bl *)entr));
         if (((struct str_Bl *)(nstr->item->entry))->isStructure5) {
            ((struct str_Bl *)(nstr->item->entry))->structure5 = copy_str_Signature(((struct str_Bl *)entr)->structure5);
         }
      } else 
      if (id == SIGID_Br) {
         nstr->item->entry=(struct str_Br *) malloc(sizeof(struct str_Br ));
         (*((struct str_Br *)(nstr->item->entry))) = (*((struct str_Br *)entr));
         if (((struct str_Br *)(nstr->item->entry))->isStructure3) {
            ((struct str_Br *)(nstr->item->entry))->structure3 = copy_str_Signature(((struct str_Br *)entr)->structure3);
         }
      } else 
      if (id == SIGID_Il) {
         nstr->item->entry=(struct str_Il *) malloc(sizeof(struct str_Il ));
         (*((struct str_Il *)(nstr->item->entry))) = (*((struct str_Il *)entr));
         if (((struct str_Il *)(nstr->item->entry))->isStructure5) {
            ((struct str_Il *)(nstr->item->entry))->structure5 = copy_str_Signature(((struct str_Il *)entr)->structure5);
         }
      } else 
      if (id == SIGID_Ml) {
         nstr->item->entry=(struct str_Ml *) malloc(sizeof(struct str_Ml ));
         (*((struct str_Ml *)(nstr->item->entry))) = (*((struct str_Ml *)entr));
         if (((struct str_Ml *)(nstr->item->entry))->isStructure3) {
            ((struct str_Ml *)(nstr->item->entry))->structure3 = copy_str_Signature(((struct str_Ml *)entr)->structure3);
         }
      } else 
      if (id == SIGID_Drem) {
         nstr->item->entry=(struct str_Drem *) malloc(sizeof(struct str_Drem ));
         (*((struct str_Drem *)(nstr->item->entry))) = (*((struct str_Drem *)entr));
         if (((struct str_Drem *)(nstr->item->entry))->isStructure1) {
            ((struct str_Drem *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Drem *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Cons) {
         nstr->item->entry=(struct str_Cons *) malloc(sizeof(struct str_Cons ));
         (*((struct str_Cons *)(nstr->item->entry))) = (*((struct str_Cons *)entr));
         if (((struct str_Cons *)(nstr->item->entry))->isStructure1) {
            ((struct str_Cons *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Cons *)entr)->structure1);
         }
         if (((struct str_Cons *)(nstr->item->entry))->isStructure2) {
            ((struct str_Cons *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Cons *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Ul) {
         nstr->item->entry=(struct str_Ul *) malloc(sizeof(struct str_Ul ));
         (*((struct str_Ul *)(nstr->item->entry))) = (*((struct str_Ul *)entr));
         if (((struct str_Ul *)(nstr->item->entry))->isStructure1) {
            ((struct str_Ul *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Ul *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Pul) {
         nstr->item->entry=(struct str_Pul *) malloc(sizeof(struct str_Pul ));
         (*((struct str_Pul *)(nstr->item->entry))) = (*((struct str_Pul *)entr));
         if (((struct str_Pul *)(nstr->item->entry))->isStructure1) {
            ((struct str_Pul *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Pul *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Addss) {
         nstr->item->entry=(struct str_Addss *) malloc(sizeof(struct str_Addss ));
         (*((struct str_Addss *)(nstr->item->entry))) = (*((struct str_Addss *)entr));
         if (((struct str_Addss *)(nstr->item->entry))->isStructure1) {
            ((struct str_Addss *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Addss *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Ssadd) {
         nstr->item->entry=(struct str_Ssadd *) malloc(sizeof(struct str_Ssadd ));
         (*((struct str_Ssadd *)(nstr->item->entry))) = (*((struct str_Ssadd *)entr));
         if (((struct str_Ssadd *)(nstr->item->entry))->isStructure3) {
            ((struct str_Ssadd *)(nstr->item->entry))->structure3 = copy_str_Signature(((struct str_Ssadd *)entr)->structure3);
         }
      } else 
      if (id == SIGID_Nil) {
         nstr->item->entry=(struct str_Nil *) malloc(sizeof(struct str_Nil ));
         (*((struct str_Nil *)(nstr->item->entry))) = (*((struct str_Nil *)entr));
      } else 
      if (id == SIGID_Combine) {
         nstr->item->entry=(struct str_Combine *) malloc(sizeof(struct str_Combine ));
         (*((struct str_Combine *)(nstr->item->entry))) = (*((struct str_Combine *)entr));
         if (((struct str_Combine *)(nstr->item->entry))->isStructure1) {
            ((struct str_Combine *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Combine *)entr)->structure1);
         }
         if (((struct str_Combine *)(nstr->item->entry))->isStructure2) {
            ((struct str_Combine *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Combine *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Sum) {
         nstr->item->entry=(struct str_Sum *) malloc(sizeof(struct str_Sum ));
         (*((struct str_Sum *)(nstr->item->entry))) = (*((struct str_Sum *)entr));
         if (((struct str_Sum *)(nstr->item->entry))->isStructure2) {
            ((struct str_Sum *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Sum *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Sumend) {
         nstr->item->entry=(struct str_Sumend *) malloc(sizeof(struct str_Sumend ));
         (*((struct str_Sumend *)(nstr->item->entry))) = (*((struct str_Sumend *)entr));
      } else 
      if (id == SIGID_Pk) {
         nstr->item->entry=(struct str_Pk *) malloc(sizeof(struct str_Pk ));
         (*((struct str_Pk *)(nstr->item->entry))) = (*((struct str_Pk *)entr));
         if (((struct str_Pk *)(nstr->item->entry))->isStructure1) {
            ((struct str_Pk *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Pk *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Pkml) {
         nstr->item->entry=(struct str_Pkml *) malloc(sizeof(struct str_Pkml ));
         (*((struct str_Pkml *)(nstr->item->entry))) = (*((struct str_Pkml *)entr));
         if (((struct str_Pkml *)(nstr->item->entry))->isStructure1) {
            ((struct str_Pkml *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Pkml *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Pk_Pr) {
         nstr->item->entry=(struct str_Pk_Pr *) malloc(sizeof(struct str_Pk_Pr ));
         (*((struct str_Pk_Pr *)(nstr->item->entry))) = (*((struct str_Pk_Pr *)entr));
         if (((struct str_Pk_Pr *)(nstr->item->entry))->isStructure4) {
            ((struct str_Pk_Pr *)(nstr->item->entry))->structure4 = copy_str_Signature(((struct str_Pk_Pr *)entr)->structure4);
         }
         if (((struct str_Pk_Pr *)(nstr->item->entry))->isStructure7) {
            ((struct str_Pk_Pr *)(nstr->item->entry))->structure7 = copy_str_Signature(((struct str_Pk_Pr *)entr)->structure7);
         }
         if (((struct str_Pk_Pr *)(nstr->item->entry))->isStructure10) {
            ((struct str_Pk_Pr *)(nstr->item->entry))->structure10 = copy_str_Signature(((struct str_Pk_Pr *)entr)->structure10);
         }
      } else 
      if (id == SIGID_Emptymid) {
         nstr->item->entry=(struct str_Emptymid *) malloc(sizeof(struct str_Emptymid ));
         (*((struct str_Emptymid *)(nstr->item->entry))) = (*((struct str_Emptymid *)entr));
      } else 
      if (id == SIGID_Midbase) {
         nstr->item->entry=(struct str_Midbase *) malloc(sizeof(struct str_Midbase ));
         (*((struct str_Midbase *)(nstr->item->entry))) = (*((struct str_Midbase *)entr));
      } else 
      if (id == SIGID_Midregion) {
         nstr->item->entry=(struct str_Midregion *) malloc(sizeof(struct str_Midregion ));
         (*((struct str_Midregion *)(nstr->item->entry))) = (*((struct str_Midregion *)entr));
         if (((struct str_Midregion *)(nstr->item->entry))->isStructure1) {
            ((struct str_Midregion *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Midregion *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Pss) {
         nstr->item->entry=(struct str_Pss *) malloc(sizeof(struct str_Pss ));
         (*((struct str_Pss *)(nstr->item->entry))) = (*((struct str_Pss *)entr));
      };
      itr = itr->next;
   }
   if (first) {
      last = nstr;
      itr = first;
      while (itr != NULL) {
         itr->last = last;
         itr = itr->next;
      }
   }
   copy_depth = copy_depth - 1;
   return(first);
}

/* free structures                                                                  */
/* -------------------------------------------------------------------------------- */
static void free_str_Signature(char rmAll, struct str3 *l)
{
   struct str3 *itr, *nitr;
   struct str_Signature *c;

   itr = l;
   while (itr != NULL) {
      c = itr->item;
      if (c != NULL) {
         if (c->utype == SIGID__NTID) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str__NTID *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str__NTID *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Sadd) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Sadd *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Sadd *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Cadd) {
            free_str_Signature(1, ((struct str_Cadd *)(c->entry))->pp_init_a1);
            free_str_Signature(1, ((struct str_Cadd *)(c->entry))->pp_init_a2);
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Is) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Is *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Is *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Sr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Sr *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Sr *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Hl) {
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Bl) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Bl *)(c->entry))->pp_init_a5);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Bl *)(c->entry))->a5);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Br) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Br *)(c->entry))->pp_init_a3);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Br *)(c->entry))->a3);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Il) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Il *)(c->entry))->pp_init_a5);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Il *)(c->entry))->a5);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Ml) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Ml *)(c->entry))->pp_init_a3);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Ml *)(c->entry))->a3);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Drem) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Drem *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Drem *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Cons) {
            free_str_Signature(1, ((struct str_Cons *)(c->entry))->pp_init_a1);
            free_str_Signature(1, ((struct str_Cons *)(c->entry))->pp_init_a2);
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Ul) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Ul *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Ul *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Pul) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Pul *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Pul *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Addss) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Addss *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Addss *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Ssadd) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Ssadd *)(c->entry))->pp_init_a3);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Ssadd *)(c->entry))->a3);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Nil) {
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Combine) {
            free_str_Signature(1, ((struct str_Combine *)(c->entry))->pp_init_a1);
            free_str_Signature(1, ((struct str_Combine *)(c->entry))->pp_init_a2);
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Sum) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Sum *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Sum *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Sumend) {
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Pk) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Pk *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Pk *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Pkml) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Pkml *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Pkml *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Pk_Pr) {
            free_str_Signature(1, ((struct str_Pk_Pr *)(c->entry))->pp_init_a4);
            free_str_Signature(1, ((struct str_Pk_Pr *)(c->entry))->pp_init_a7);
            free_str_Signature(1, ((struct str_Pk_Pr *)(c->entry))->pp_init_a10);
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Emptymid) {
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Midbase) {
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Midregion) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Midregion *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Midregion *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Pss) {
            free(c->entry);
            free(c);
         };
      }
      nitr = itr->next;
      free(itr);
      if (rmAll) {
         itr = nitr;
      }
      else {
         itr = NULL;
      }
   }
}

/* structure builder                                                                */
/* -------------------------------------------------------------------------------- */
static struct str3 *build_str_Signature(struct str3 *l)
{
   struct str_Signature *c;
   struct str3 *cl;

   if (l != NULL) {
      cl = l;
      c = cl->item;
      if (c->fcalled == 0) {
         c->fcalled = 1;
         if (c->utype == SIGID__NTID) {
            if (((struct str__NTID *)(c->entry))->isStructure1) {
               ((struct str__NTID *)(c->entry))->a1 = build_str_Signature(((struct str__NTID *)(c->entry))->structure1);
               ((struct str__NTID *)(c->entry))->pp_init_a1 = ((struct str__NTID *)(c->entry))->a1;
            }
            else {
               ((struct str__NTID *)(c->entry))->a1 = (*((struct str__NTID *)(c->entry))->f1)(((struct str__NTID *)(c->entry))->i1, ((struct str__NTID *)(c->entry))->j1, ((struct str__NTID *)(c->entry))->diff1);
               ((struct str__NTID *)(c->entry))->pp_init_a1 = ((struct str__NTID *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Sadd) {
            if (((struct str_Sadd *)(c->entry))->isStructure2) {
               ((struct str_Sadd *)(c->entry))->a2 = build_str_Signature(((struct str_Sadd *)(c->entry))->structure2);
               ((struct str_Sadd *)(c->entry))->pp_init_a2 = ((struct str_Sadd *)(c->entry))->a2;
            }
            else {
               ((struct str_Sadd *)(c->entry))->a2 = (*((struct str_Sadd *)(c->entry))->f2)(((struct str_Sadd *)(c->entry))->i2, ((struct str_Sadd *)(c->entry))->j2, ((struct str_Sadd *)(c->entry))->diff2);
               ((struct str_Sadd *)(c->entry))->pp_init_a2 = ((struct str_Sadd *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Cadd) {
            if (((struct str_Cadd *)(c->entry))->isStructure1) {
               ((struct str_Cadd *)(c->entry))->a1 = build_str_Signature(((struct str_Cadd *)(c->entry))->structure1);
               ((struct str_Cadd *)(c->entry))->pp_init_a1 = ((struct str_Cadd *)(c->entry))->a1;
            }
            else {
               ((struct str_Cadd *)(c->entry))->a1 = (*((struct str_Cadd *)(c->entry))->f1)(((struct str_Cadd *)(c->entry))->i1, ((struct str_Cadd *)(c->entry))->j1, ((struct str_Cadd *)(c->entry))->diff1);
               ((struct str_Cadd *)(c->entry))->pp_init_a1 = ((struct str_Cadd *)(c->entry))->a1;
            }
            if (((struct str_Cadd *)(c->entry))->isStructure2) {
               ((struct str_Cadd *)(c->entry))->a2 = build_str_Signature(((struct str_Cadd *)(c->entry))->structure2);
               ((struct str_Cadd *)(c->entry))->pp_init_a2 = ((struct str_Cadd *)(c->entry))->a2;
            }
            else {
               ((struct str_Cadd *)(c->entry))->a2 = (*((struct str_Cadd *)(c->entry))->f2)(((struct str_Cadd *)(c->entry))->i2, ((struct str_Cadd *)(c->entry))->j2, ((struct str_Cadd *)(c->entry))->diff2);
               ((struct str_Cadd *)(c->entry))->pp_init_a2 = ((struct str_Cadd *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Is) {
            if (((struct str_Is *)(c->entry))->isStructure2) {
               ((struct str_Is *)(c->entry))->a2 = build_str_Signature(((struct str_Is *)(c->entry))->structure2);
               ((struct str_Is *)(c->entry))->pp_init_a2 = ((struct str_Is *)(c->entry))->a2;
            }
            else {
               ((struct str_Is *)(c->entry))->a2 = (*((struct str_Is *)(c->entry))->f2)(((struct str_Is *)(c->entry))->i2, ((struct str_Is *)(c->entry))->j2, ((struct str_Is *)(c->entry))->diff2);
               ((struct str_Is *)(c->entry))->pp_init_a2 = ((struct str_Is *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Sr) {
            if (((struct str_Sr *)(c->entry))->isStructure2) {
               ((struct str_Sr *)(c->entry))->a2 = build_str_Signature(((struct str_Sr *)(c->entry))->structure2);
               ((struct str_Sr *)(c->entry))->pp_init_a2 = ((struct str_Sr *)(c->entry))->a2;
            }
            else {
               ((struct str_Sr *)(c->entry))->a2 = (*((struct str_Sr *)(c->entry))->f2)(((struct str_Sr *)(c->entry))->i2, ((struct str_Sr *)(c->entry))->j2, ((struct str_Sr *)(c->entry))->diff2);
               ((struct str_Sr *)(c->entry))->pp_init_a2 = ((struct str_Sr *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Hl) {
         } else 
         if (c->utype == SIGID_Bl) {
            if (((struct str_Bl *)(c->entry))->isStructure5) {
               ((struct str_Bl *)(c->entry))->a5 = build_str_Signature(((struct str_Bl *)(c->entry))->structure5);
               ((struct str_Bl *)(c->entry))->pp_init_a5 = ((struct str_Bl *)(c->entry))->a5;
            }
            else {
               ((struct str_Bl *)(c->entry))->a5 = (*((struct str_Bl *)(c->entry))->f5)(((struct str_Bl *)(c->entry))->i5, ((struct str_Bl *)(c->entry))->j5, ((struct str_Bl *)(c->entry))->diff5);
               ((struct str_Bl *)(c->entry))->pp_init_a5 = ((struct str_Bl *)(c->entry))->a5;
            }
         } else 
         if (c->utype == SIGID_Br) {
            if (((struct str_Br *)(c->entry))->isStructure3) {
               ((struct str_Br *)(c->entry))->a3 = build_str_Signature(((struct str_Br *)(c->entry))->structure3);
               ((struct str_Br *)(c->entry))->pp_init_a3 = ((struct str_Br *)(c->entry))->a3;
            }
            else {
               ((struct str_Br *)(c->entry))->a3 = (*((struct str_Br *)(c->entry))->f3)(((struct str_Br *)(c->entry))->i3, ((struct str_Br *)(c->entry))->j3, ((struct str_Br *)(c->entry))->diff3);
               ((struct str_Br *)(c->entry))->pp_init_a3 = ((struct str_Br *)(c->entry))->a3;
            }
         } else 
         if (c->utype == SIGID_Il) {
            if (((struct str_Il *)(c->entry))->isStructure5) {
               ((struct str_Il *)(c->entry))->a5 = build_str_Signature(((struct str_Il *)(c->entry))->structure5);
               ((struct str_Il *)(c->entry))->pp_init_a5 = ((struct str_Il *)(c->entry))->a5;
            }
            else {
               ((struct str_Il *)(c->entry))->a5 = (*((struct str_Il *)(c->entry))->f5)(((struct str_Il *)(c->entry))->i5, ((struct str_Il *)(c->entry))->j5, ((struct str_Il *)(c->entry))->diff5);
               ((struct str_Il *)(c->entry))->pp_init_a5 = ((struct str_Il *)(c->entry))->a5;
            }
         } else 
         if (c->utype == SIGID_Ml) {
            if (((struct str_Ml *)(c->entry))->isStructure3) {
               ((struct str_Ml *)(c->entry))->a3 = build_str_Signature(((struct str_Ml *)(c->entry))->structure3);
               ((struct str_Ml *)(c->entry))->pp_init_a3 = ((struct str_Ml *)(c->entry))->a3;
            }
            else {
               ((struct str_Ml *)(c->entry))->a3 = (*((struct str_Ml *)(c->entry))->f3)(((struct str_Ml *)(c->entry))->i3, ((struct str_Ml *)(c->entry))->j3, ((struct str_Ml *)(c->entry))->diff3);
               ((struct str_Ml *)(c->entry))->pp_init_a3 = ((struct str_Ml *)(c->entry))->a3;
            }
         } else 
         if (c->utype == SIGID_Drem) {
            if (((struct str_Drem *)(c->entry))->isStructure1) {
               ((struct str_Drem *)(c->entry))->a1 = build_str_Signature(((struct str_Drem *)(c->entry))->structure1);
               ((struct str_Drem *)(c->entry))->pp_init_a1 = ((struct str_Drem *)(c->entry))->a1;
            }
            else {
               ((struct str_Drem *)(c->entry))->a1 = (*((struct str_Drem *)(c->entry))->f1)(((struct str_Drem *)(c->entry))->i1, ((struct str_Drem *)(c->entry))->j1, ((struct str_Drem *)(c->entry))->diff1);
               ((struct str_Drem *)(c->entry))->pp_init_a1 = ((struct str_Drem *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Cons) {
            if (((struct str_Cons *)(c->entry))->isStructure1) {
               ((struct str_Cons *)(c->entry))->a1 = build_str_Signature(((struct str_Cons *)(c->entry))->structure1);
               ((struct str_Cons *)(c->entry))->pp_init_a1 = ((struct str_Cons *)(c->entry))->a1;
            }
            else {
               ((struct str_Cons *)(c->entry))->a1 = (*((struct str_Cons *)(c->entry))->f1)(((struct str_Cons *)(c->entry))->i1, ((struct str_Cons *)(c->entry))->j1, ((struct str_Cons *)(c->entry))->diff1);
               ((struct str_Cons *)(c->entry))->pp_init_a1 = ((struct str_Cons *)(c->entry))->a1;
            }
            if (((struct str_Cons *)(c->entry))->isStructure2) {
               ((struct str_Cons *)(c->entry))->a2 = build_str_Signature(((struct str_Cons *)(c->entry))->structure2);
               ((struct str_Cons *)(c->entry))->pp_init_a2 = ((struct str_Cons *)(c->entry))->a2;
            }
            else {
               ((struct str_Cons *)(c->entry))->a2 = (*((struct str_Cons *)(c->entry))->f2)(((struct str_Cons *)(c->entry))->i2, ((struct str_Cons *)(c->entry))->j2, ((struct str_Cons *)(c->entry))->diff2);
               ((struct str_Cons *)(c->entry))->pp_init_a2 = ((struct str_Cons *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Ul) {
            if (((struct str_Ul *)(c->entry))->isStructure1) {
               ((struct str_Ul *)(c->entry))->a1 = build_str_Signature(((struct str_Ul *)(c->entry))->structure1);
               ((struct str_Ul *)(c->entry))->pp_init_a1 = ((struct str_Ul *)(c->entry))->a1;
            }
            else {
               ((struct str_Ul *)(c->entry))->a1 = (*((struct str_Ul *)(c->entry))->f1)(((struct str_Ul *)(c->entry))->i1, ((struct str_Ul *)(c->entry))->j1, ((struct str_Ul *)(c->entry))->diff1);
               ((struct str_Ul *)(c->entry))->pp_init_a1 = ((struct str_Ul *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Pul) {
            if (((struct str_Pul *)(c->entry))->isStructure1) {
               ((struct str_Pul *)(c->entry))->a1 = build_str_Signature(((struct str_Pul *)(c->entry))->structure1);
               ((struct str_Pul *)(c->entry))->pp_init_a1 = ((struct str_Pul *)(c->entry))->a1;
            }
            else {
               ((struct str_Pul *)(c->entry))->a1 = (*((struct str_Pul *)(c->entry))->f1)(((struct str_Pul *)(c->entry))->i1, ((struct str_Pul *)(c->entry))->j1, ((struct str_Pul *)(c->entry))->diff1);
               ((struct str_Pul *)(c->entry))->pp_init_a1 = ((struct str_Pul *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Addss) {
            if (((struct str_Addss *)(c->entry))->isStructure1) {
               ((struct str_Addss *)(c->entry))->a1 = build_str_Signature(((struct str_Addss *)(c->entry))->structure1);
               ((struct str_Addss *)(c->entry))->pp_init_a1 = ((struct str_Addss *)(c->entry))->a1;
            }
            else {
               ((struct str_Addss *)(c->entry))->a1 = (*((struct str_Addss *)(c->entry))->f1)(((struct str_Addss *)(c->entry))->i1, ((struct str_Addss *)(c->entry))->j1, ((struct str_Addss *)(c->entry))->diff1);
               ((struct str_Addss *)(c->entry))->pp_init_a1 = ((struct str_Addss *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Ssadd) {
            if (((struct str_Ssadd *)(c->entry))->isStructure3) {
               ((struct str_Ssadd *)(c->entry))->a3 = build_str_Signature(((struct str_Ssadd *)(c->entry))->structure3);
               ((struct str_Ssadd *)(c->entry))->pp_init_a3 = ((struct str_Ssadd *)(c->entry))->a3;
            }
            else {
               ((struct str_Ssadd *)(c->entry))->a3 = (*((struct str_Ssadd *)(c->entry))->f3)(((struct str_Ssadd *)(c->entry))->i3, ((struct str_Ssadd *)(c->entry))->j3, ((struct str_Ssadd *)(c->entry))->diff3);
               ((struct str_Ssadd *)(c->entry))->pp_init_a3 = ((struct str_Ssadd *)(c->entry))->a3;
            }
         } else 
         if (c->utype == SIGID_Nil) {
         } else 
         if (c->utype == SIGID_Combine) {
            if (((struct str_Combine *)(c->entry))->isStructure1) {
               ((struct str_Combine *)(c->entry))->a1 = build_str_Signature(((struct str_Combine *)(c->entry))->structure1);
               ((struct str_Combine *)(c->entry))->pp_init_a1 = ((struct str_Combine *)(c->entry))->a1;
            }
            else {
               ((struct str_Combine *)(c->entry))->a1 = (*((struct str_Combine *)(c->entry))->f1)(((struct str_Combine *)(c->entry))->i1, ((struct str_Combine *)(c->entry))->j1, ((struct str_Combine *)(c->entry))->diff1);
               ((struct str_Combine *)(c->entry))->pp_init_a1 = ((struct str_Combine *)(c->entry))->a1;
            }
            if (((struct str_Combine *)(c->entry))->isStructure2) {
               ((struct str_Combine *)(c->entry))->a2 = build_str_Signature(((struct str_Combine *)(c->entry))->structure2);
               ((struct str_Combine *)(c->entry))->pp_init_a2 = ((struct str_Combine *)(c->entry))->a2;
            }
            else {
               ((struct str_Combine *)(c->entry))->a2 = (*((struct str_Combine *)(c->entry))->f2)(((struct str_Combine *)(c->entry))->i2, ((struct str_Combine *)(c->entry))->j2, ((struct str_Combine *)(c->entry))->diff2);
               ((struct str_Combine *)(c->entry))->pp_init_a2 = ((struct str_Combine *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Sum) {
            if (((struct str_Sum *)(c->entry))->isStructure2) {
               ((struct str_Sum *)(c->entry))->a2 = build_str_Signature(((struct str_Sum *)(c->entry))->structure2);
               ((struct str_Sum *)(c->entry))->pp_init_a2 = ((struct str_Sum *)(c->entry))->a2;
            }
            else {
               ((struct str_Sum *)(c->entry))->a2 = (*((struct str_Sum *)(c->entry))->f2)(((struct str_Sum *)(c->entry))->i2, ((struct str_Sum *)(c->entry))->j2, ((struct str_Sum *)(c->entry))->diff2);
               ((struct str_Sum *)(c->entry))->pp_init_a2 = ((struct str_Sum *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Sumend) {
         } else 
         if (c->utype == SIGID_Pk) {
            if (((struct str_Pk *)(c->entry))->isStructure1) {
               ((struct str_Pk *)(c->entry))->a1 = build_str_Signature(((struct str_Pk *)(c->entry))->structure1);
               ((struct str_Pk *)(c->entry))->pp_init_a1 = ((struct str_Pk *)(c->entry))->a1;
            }
            else {
               ((struct str_Pk *)(c->entry))->a1 = (*((struct str_Pk *)(c->entry))->f1)(((struct str_Pk *)(c->entry))->i1, ((struct str_Pk *)(c->entry))->j1, ((struct str_Pk *)(c->entry))->diff1);
               ((struct str_Pk *)(c->entry))->pp_init_a1 = ((struct str_Pk *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Pkml) {
            if (((struct str_Pkml *)(c->entry))->isStructure1) {
               ((struct str_Pkml *)(c->entry))->a1 = build_str_Signature(((struct str_Pkml *)(c->entry))->structure1);
               ((struct str_Pkml *)(c->entry))->pp_init_a1 = ((struct str_Pkml *)(c->entry))->a1;
            }
            else {
               ((struct str_Pkml *)(c->entry))->a1 = (*((struct str_Pkml *)(c->entry))->f1)(((struct str_Pkml *)(c->entry))->i1, ((struct str_Pkml *)(c->entry))->j1, ((struct str_Pkml *)(c->entry))->diff1);
               ((struct str_Pkml *)(c->entry))->pp_init_a1 = ((struct str_Pkml *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Pk_Pr) {
            if (((struct str_Pk_Pr *)(c->entry))->isStructure4) {
               ((struct str_Pk_Pr *)(c->entry))->a4 = build_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure4);
               ((struct str_Pk_Pr *)(c->entry))->pp_init_a4 = ((struct str_Pk_Pr *)(c->entry))->a4;
            }
            else {
               ((struct str_Pk_Pr *)(c->entry))->a4 = (*((struct str_Pk_Pr *)(c->entry))->f4)(((struct str_Pk_Pr *)(c->entry))->i4, ((struct str_Pk_Pr *)(c->entry))->j4, ((struct str_Pk_Pr *)(c->entry))->diff4);
               ((struct str_Pk_Pr *)(c->entry))->pp_init_a4 = ((struct str_Pk_Pr *)(c->entry))->a4;
            }
            if (((struct str_Pk_Pr *)(c->entry))->isStructure7) {
               ((struct str_Pk_Pr *)(c->entry))->a7 = build_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure7);
               ((struct str_Pk_Pr *)(c->entry))->pp_init_a7 = ((struct str_Pk_Pr *)(c->entry))->a7;
            }
            else {
               ((struct str_Pk_Pr *)(c->entry))->a7 = (*((struct str_Pk_Pr *)(c->entry))->f7)(((struct str_Pk_Pr *)(c->entry))->i7, ((struct str_Pk_Pr *)(c->entry))->j7, ((struct str_Pk_Pr *)(c->entry))->diff7);
               ((struct str_Pk_Pr *)(c->entry))->pp_init_a7 = ((struct str_Pk_Pr *)(c->entry))->a7;
            }
            if (((struct str_Pk_Pr *)(c->entry))->isStructure10) {
               ((struct str_Pk_Pr *)(c->entry))->a10 = build_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure10);
               ((struct str_Pk_Pr *)(c->entry))->pp_init_a10 = ((struct str_Pk_Pr *)(c->entry))->a10;
            }
            else {
               ((struct str_Pk_Pr *)(c->entry))->a10 = (*((struct str_Pk_Pr *)(c->entry))->f10)(((struct str_Pk_Pr *)(c->entry))->i10, ((struct str_Pk_Pr *)(c->entry))->j10, ((struct str_Pk_Pr *)(c->entry))->diff10);
               ((struct str_Pk_Pr *)(c->entry))->pp_init_a10 = ((struct str_Pk_Pr *)(c->entry))->a10;
            }
         } else 
         if (c->utype == SIGID_Emptymid) {
         } else 
         if (c->utype == SIGID_Midbase) {
         } else 
         if (c->utype == SIGID_Midregion) {
            if (((struct str_Midregion *)(c->entry))->isStructure1) {
               ((struct str_Midregion *)(c->entry))->a1 = build_str_Signature(((struct str_Midregion *)(c->entry))->structure1);
               ((struct str_Midregion *)(c->entry))->pp_init_a1 = ((struct str_Midregion *)(c->entry))->a1;
            }
            else {
               ((struct str_Midregion *)(c->entry))->a1 = (*((struct str_Midregion *)(c->entry))->f1)(((struct str_Midregion *)(c->entry))->i1, ((struct str_Midregion *)(c->entry))->j1, ((struct str_Midregion *)(c->entry))->diff1);
               ((struct str_Midregion *)(c->entry))->pp_init_a1 = ((struct str_Midregion *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Pss) {
         };
      }
   }
   return(l);
}

/* update subopt difference values                                                  */
/* -------------------------------------------------------------------------------- */
static void update_str_Signature(struct str_Signature *c, int diff)
{
   if (c != NULL) {
      if (c->utype == SIGID__NTID) {
         if (((struct str__NTID *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str__NTID *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str__NTID *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Sadd) {
         if (((struct str_Sadd *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Sadd *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Sadd *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Cadd) {
         if (((struct str_Cadd *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Cadd *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Cadd *)(c->entry))->diff1 = diff;
         }
         if (((struct str_Cadd *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Cadd *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Cadd *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Is) {
         if (((struct str_Is *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Is *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Is *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Sr) {
         if (((struct str_Sr *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Sr *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Sr *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Hl) {
         ((struct str_Hl *)(c->entry))->diff = diff;
      } else 
      if (c->utype == SIGID_Bl) {
         if (((struct str_Bl *)(c->entry))->isStructure5) {
            update_str_Signature(((struct str_Bl *)(c->entry))->structure5->item, diff);
         }
         else {
            ((struct str_Bl *)(c->entry))->diff5 = diff;
         }
      } else 
      if (c->utype == SIGID_Br) {
         if (((struct str_Br *)(c->entry))->isStructure3) {
            update_str_Signature(((struct str_Br *)(c->entry))->structure3->item, diff);
         }
         else {
            ((struct str_Br *)(c->entry))->diff3 = diff;
         }
      } else 
      if (c->utype == SIGID_Il) {
         if (((struct str_Il *)(c->entry))->isStructure5) {
            update_str_Signature(((struct str_Il *)(c->entry))->structure5->item, diff);
         }
         else {
            ((struct str_Il *)(c->entry))->diff5 = diff;
         }
      } else 
      if (c->utype == SIGID_Ml) {
         if (((struct str_Ml *)(c->entry))->isStructure3) {
            update_str_Signature(((struct str_Ml *)(c->entry))->structure3->item, diff);
         }
         else {
            ((struct str_Ml *)(c->entry))->diff3 = diff;
         }
      } else 
      if (c->utype == SIGID_Drem) {
         if (((struct str_Drem *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Drem *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Drem *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Cons) {
         if (((struct str_Cons *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Cons *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Cons *)(c->entry))->diff1 = diff;
         }
         if (((struct str_Cons *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Cons *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Cons *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Ul) {
         if (((struct str_Ul *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Ul *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Ul *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Pul) {
         if (((struct str_Pul *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Pul *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Pul *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Addss) {
         if (((struct str_Addss *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Addss *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Addss *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Ssadd) {
         if (((struct str_Ssadd *)(c->entry))->isStructure3) {
            update_str_Signature(((struct str_Ssadd *)(c->entry))->structure3->item, diff);
         }
         else {
            ((struct str_Ssadd *)(c->entry))->diff3 = diff;
         }
      } else 
      if (c->utype == SIGID_Nil) {
         ((struct str_Nil *)(c->entry))->diff = diff;
      } else 
      if (c->utype == SIGID_Combine) {
         if (((struct str_Combine *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Combine *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Combine *)(c->entry))->diff1 = diff;
         }
         if (((struct str_Combine *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Combine *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Combine *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Sum) {
         if (((struct str_Sum *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Sum *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Sum *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Sumend) {
         ((struct str_Sumend *)(c->entry))->diff = diff;
      } else 
      if (c->utype == SIGID_Pk) {
         if (((struct str_Pk *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Pk *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Pk *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Pkml) {
         if (((struct str_Pkml *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Pkml *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Pkml *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Pk_Pr) {
         if (((struct str_Pk_Pr *)(c->entry))->isStructure4) {
            update_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure4->item, diff);
         }
         else {
            ((struct str_Pk_Pr *)(c->entry))->diff4 = diff;
         }
         if (((struct str_Pk_Pr *)(c->entry))->isStructure7) {
            update_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure7->item, diff);
         }
         else {
            ((struct str_Pk_Pr *)(c->entry))->diff7 = diff;
         }
         if (((struct str_Pk_Pr *)(c->entry))->isStructure10) {
            update_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure10->item, diff);
         }
         else {
            ((struct str_Pk_Pr *)(c->entry))->diff10 = diff;
         }
      } else 
      if (c->utype == SIGID_Emptymid) {
         ((struct str_Emptymid *)(c->entry))->diff = diff;
      } else 
      if (c->utype == SIGID_Midbase) {
         ((struct str_Midbase *)(c->entry))->diff = diff;
      } else 
      if (c->utype == SIGID_Midregion) {
         if (((struct str_Midregion *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Midregion *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Midregion *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Pss) {
         ((struct str_Pss *)(c->entry))->diff = diff;
      };
   }
}

/* table access                                                                     */
/* -------------------------------------------------------------------------------- */

static int *offset;

#define tbl_struct(I, J) arr_struct[(I)]
#define tbl_structP(I, J) arr_structP[(I)]
#define tbl_edangle(I, J) arr_edangle[offset[(J)]+(I)]
#define tbl_edangle_Pr(I, J) arr_edangle_Pr[offset[(J)]+(I)]
#define tbl_closed(I, J) arr_closed[offset[(J)]+(I)]
#define tbl_closed_Pr(I, J) arr_closed_Pr[offset[(J)]+(I)]
#define tbl_comps(I, J) arr_comps[offset[(J)]+(I)]
#define tbl_comps_Pr(I, J) arr_comps_Pr[offset[(J)]+(I)]
#define tbl_block(I, J) arr_block[offset[(J)]+(I)]
#define tbl_block_Pr(I, J) arr_block_Pr[offset[(J)]+(I)]
#define tbl_knot(I, J) arr_knot[offset[(J)]+(I)]
#define tbl_stacklen(I, J) arr_stacklen[offset[(J)]+(I)]

/* table declarations                                                               */
/* -------------------------------------------------------------------------------- */

static int *arr_struct;
static int *arr_structP;
static int *arr_edangle;
static int *arr_edangle_Pr;
static int *arr_closed;
static int *arr_closed_Pr;
static int *arr_comps;
static int *arr_comps_Pr;
static int *arr_block;
static int *arr_block_Pr;
static struct str1 *arr_knot;
static struct str2 *arr_stacklen;

/* table calculations                                                               */
/* -------------------------------------------------------------------------------- */

/* table calculation for production struct                                          */
/* -------------------------------------------------------------------------------- */
static void calc_struct(int i, int j)
{
   int v1, v2, v3, v4, v5, v6;
   int k;

   if ((j-i) >= 0) {
      /* -------------------------------- start of -------------------------------- */
      /* -------------------- v1 = sadd <<< lbase ~~~ p struct -------------------- */
      if ((j-i) >= 1) {
         v1 = tbl_struct(i+1, j);
      }
      else {
         v1 = 1.0e7;
      }
      /* -------------------- v1 = sadd <<< lbase ~~~ p struct -------------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v3 = cadd <<< p edangle ~~~ p struct ------------------ */
      if ((j-i) >= 7) {
         v3 = 1.0e7;
         for (k=i+7; k<=j; k++) {
            v2 = tbl_edangle(i, k) + tbl_struct(k, j);
            v3 = v2 < v3 ? v2 : v3;
         }
      }
      else {
         v3 = 1.0e7;
      }
      /* ------------------ v3 = cadd <<< p edangle ~~~ p struct ------------------ */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------------------- v4 = nil <<< empty --------------------------- */
      if ((j-i) == 0) {
         v4 = 0;
      }
      else {
         v4 = 1.0e7;
      }
      /* --------------------------- v4 = nil <<< empty --------------------------- */
      /* -------------------------------- finished -------------------------------- */

      v5 = v3 < v4 ? v3 : v4;
      v6 = v1 < v5 ? v1 : v5;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_struct(i, j) = v6;
   }
}

/* table calculation for production structP                                         */
/* -------------------------------------------------------------------------------- */
static void calc_structP(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10;
   int k, k2, k3;

   if ((j-i) >= 11) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------------- v1 = sadd <<< lbase ~~~ p structP -------------------- */
      if ((j-i) >= 12) {
         v1 = tbl_structP(i+1, j);
      }
      else {
         v1 = 1.0e7;
      }
      /* ------------------- v1 = sadd <<< lbase ~~~ p structP -------------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ----------------- v3 = cadd <<< p edangle ~~~ p structP ------------------ */
      if ((j-i) >= 18) {
         v3 = 1.0e7;
         for (k=i+7; k<=j-11; k++) {
            v2 = tbl_edangle(i, k) + tbl_structP(k, j);
            v3 = v2 < v3 ? v2 : v3;
         }
      }
      else {
         v3 = 1.0e7;
      }
      /* ----------------- v3 = cadd <<< p edangle ~~~ p structP ------------------ */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v5 = cadd <<< p edangle_Pr ~~~ p struct ----------------- */
      v5 = 1.0e7;
      for (k2=i+11; k2<=j; k2++) {
         v4 = tbl_edangle_Pr(i, k2) + tbl_struct(k2, j);
         v5 = v4 < v5 ? v4 : v5;
      }
      /* ---------------- v5 = cadd <<< p edangle_Pr ~~~ p struct ----------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v7 = cadd <<< p edangle_Pr ~~~ p structP ---------------- */
      if ((j-i) >= 22) {
         v7 = 1.0e7;
         for (k3=i+11; k3<=j-11; k3++) {
            v6 = tbl_edangle_Pr(i, k3) + tbl_structP(k3, j);
            v7 = v6 < v7 ? v6 : v7;
         }
      }
      else {
         v7 = 1.0e7;
      }
      /* ---------------- v7 = cadd <<< p edangle_Pr ~~~ p structP ---------------- */
      /* -------------------------------- finished -------------------------------- */

      v8 = v5 < v7 ? v5 : v7;
      v9 = v3 < v8 ? v3 : v8;
      v10 = v1 < v9 ? v1 : v9;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_structP(i, j) = v10;
   }
}

/* table calculation for production edangle                                         */
/* -------------------------------------------------------------------------------- */
static void calc_edangle(int i, int j)
{
   int v1, v2, v3, v4;

   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------- v1 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v2 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      v2 = tbl_closed(i, j) + termaupenalty((i) + 1, j);
      /* ------------------ v2 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v1 = v2;
      /* ------------- v1 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------------------- v3 = pk <<< p knot --------------------------- */
      if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
         v3 = tbl_knot(i, j).tup1;
      }
      else {
         v3 = 1.0e7;
      }
      /* --------------------------- v3 = pk <<< p knot --------------------------- */
      /* -------------------------------- finished -------------------------------- */

      v4 = v1 < v3 ? v1 : v3;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_edangle(i, j) = v4;
   }
}

/* table calculation for production edangle_Pr                                      */
/* -------------------------------------------------------------------------------- */
static void calc_edangle_Pr(int i, int j)
{
   int v1, v2, v3, v4;

   if ((j-i) >= 11) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------ v1 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
      if ((j-i) >= 22) {
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v2 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         v2 = tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j);
         /* --------------- v2 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         /* ------------------------------- finished ------------------------------ */

         v1 = v2;
      }
      else {
         v1 = 1.0e7;
      }
      /* ------------ v1 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------------------- v3 = pk <<< p knot --------------------------- */
      if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
         v3 = tbl_knot(i, j).tup1;
      }
      else {
         v3 = 1.0e7;
      }
      /* --------------------------- v3 = pk <<< p knot --------------------------- */
      /* -------------------------------- finished -------------------------------- */

      v4 = v1 < v3 ? v1 : v3;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_edangle_Pr(i, j) = v4;
   }
}

/* table calculation for production closed                                          */
/* -------------------------------------------------------------------------------- */
static void calc_closed(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10;
   int v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21;
   int k, k2, k3, k4, k5;

   if ((j-i) >= 7) {
      if (basepairing(i, j)) {
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v1 = sr <<< lbase ~~~ p closed ~~~ lbase -------------- */
         if ((j-i) >= 9) {
            v1 = tbl_closed(i+1, j-1) + sr_energy(i+1, j);
         }
         else {
            v1 = 1.0e7;
         }
         /* --------------- v1 = sr <<< lbase ~~~ p closed ~~~ lbase -------------- */
         /* ------------------------------- finished ------------------------------ */

         v2 = v1;
      }
      else {
         v2 = 1.0e7;
      }
      if (stackpairing(i, j)) {
         /* ------------------------------- start of ------------------------------ */
         /*  v3 = hl <<< lbase ~~~ lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ~~~ lbase  */
         v3 = hl_energy(i+2, j-1) + sr_energy(i+1, j);
         /*  v3 = hl <<< lbase ~~~ lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v6 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 12) {
            v6 = 1.0e7;
            for (k=i+3; k<=j-9; k++) {
               /* ---------------------------- start of --------------------------- */
               /* -------------- v5 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               v5 = tbl_closed(k, j-2) + termaupenalty((k) + 1, j-2);
               /* -------------- v5 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               /* ---------------------------- finished --------------------------- */

               v4 = (v5 + bl_energy(i+2, i+2, k, j-1)) + sr_energy(i+1, j);
               v6 = v4 < v6 ? v4 : v6;
            }
         }
         else {
            v6 = 1.0e7;
         }
         /*  v6 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v9 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 12) {
            v9 = 1.0e7;
            for (k2=i+9; k2<=j-3; k2++) {
               /* ---------------------------- start of --------------------------- */
               /* -------------- v8 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               v8 = tbl_closed(i+2, k2) + termaupenalty((i+2) + 1, k2);
               /* -------------- v8 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               /* ---------------------------- finished --------------------------- */

               v7 = (v8 + br_energy(i+2, k2, j-2, j-1)) + sr_energy(i+1, j);
               v9 = v7 < v9 ? v7 : v9;
            }
         }
         else {
            v9 = 1.0e7;
         }
         /*  v9 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v11 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 13) {
            v11 = 1.0e7;
            for (k4=max(i+10, j-32); k4<=j-3; k4++) {
               for (k3=i+3; k3<=min(i+34, k4-7); k3++) {
                  v10 = (tbl_closed(k3, k4) + sr_energy(i+1, j)) + il_energy(i+2, k3, k4, j-2);
                  v11 = v10 < v11 ? v10 : v11;
               }
            }
         }
         else {
            v11 = 1.0e7;
         }
         /*  v11 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         if (stackpairing(i, j)) {
            /* ----------------------------- start of ----------------------------- */
            /*  v12 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
            if ((j-i) >= 18) {
               /* ---------------------------- start of --------------------------- */
               /* ------------- v14 = combine <<< p block ~~~ p comps ------------- */
               v14 = 1.0e7;
               for (k5=i+9; k5<=j-9; k5++) {
                  v13 = tbl_block(i+2, k5) + tbl_comps(k5, j-2);
                  v14 = v13 < v14 ? v13 : v14;
               }
               /* ------------- v14 = combine <<< p block ~~~ p comps ------------- */
               /* ---------------------------- finished --------------------------- */

               v12 = ((380 + v14) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            }
            else {
               v12 = 1.0e7;
            }
            /*  v12 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            v15 = v12;
         }
         else {
            v15 = 1.0e7;
         }
         v16 = v11 < v15 ? v11 : v15;
         v17 = v9 < v16 ? v9 : v16;
         v18 = v6 < v17 ? v6 : v17;
         v19 = v3 < v18 ? v3 : v18;
         v20 = v19;
      }
      else {
         v20 = 1.0e7;
      }
      v21 = v2 < v20 ? v2 : v20;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_closed(i, j) = v21;
   }
}

/* table calculation for production closed_Pr                                       */
/* -------------------------------------------------------------------------------- */
static void calc_closed_Pr(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12;
   int v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25;
   int k, k2, k3, k4, k5, k6, k7;

   if ((j-i) >= 22) {
      if (basepairing(i, j)) {
         /* ------------------------------- start of ------------------------------ */
         /* ------------- v1 = sr <<< lbase ~~~ p closed_Pr ~~~ lbase ------------- */
         if ((j-i) >= 24) {
            v1 = tbl_closed_Pr(i+1, j-1) + sr_energy(i+1, j);
         }
         else {
            v1 = 1.0e7;
         }
         /* ------------- v1 = sr <<< lbase ~~~ p closed_Pr ~~~ lbase ------------- */
         /* ------------------------------- finished ------------------------------ */

         v2 = v1;
      }
      else {
         v2 = 1.0e7;
      }
      if (stackpairing(i, j)) {
         /* ------------------------------- start of ------------------------------ */
         /*  v5 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 27) {
            v5 = 1.0e7;
            for (k=i+3; k<=j-24; k++) {
               /* ---------------------------- start of --------------------------- */
               /* ------------ v4 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
               v4 = tbl_closed_Pr(k, j-2) + termaupenalty((k) + 1, j-2);
               /* ------------ v4 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
               /* ---------------------------- finished --------------------------- */

               v3 = (v4 + bl_energy(i+2, i+2, k, j-1)) + sr_energy(i+1, j);
               v5 = v3 < v5 ? v3 : v5;
            }
         }
         else {
            v5 = 1.0e7;
         }
         /*  v5 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v8 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 27) {
            v8 = 1.0e7;
            for (k2=i+24; k2<=j-3; k2++) {
               /* ---------------------------- start of --------------------------- */
               /* ------------ v7 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
               v7 = tbl_closed_Pr(i+2, k2) + termaupenalty((i+2) + 1, k2);
               /* ------------ v7 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
               /* ---------------------------- finished --------------------------- */

               v6 = (v7 + br_energy(i+2, k2, j-2, j-1)) + sr_energy(i+1, j);
               v8 = v6 < v8 ? v6 : v8;
            }
         }
         else {
            v8 = 1.0e7;
         }
         /*  v8 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v10 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed_Pr ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 28) {
            v10 = 1.0e7;
            for (k4=max(i+25, j-32); k4<=j-3; k4++) {
               for (k3=i+3; k3<=min(i+34, k4-22); k3++) {
                  v9 = (tbl_closed_Pr(k3, k4) + sr_energy(i+1, j)) + il_energy(i+2, k3, k4, j-2);
                  v10 = v9 < v10 ? v9 : v10;
               }
            }
         }
         else {
            v10 = 1.0e7;
         }
         /*  v10 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed_Pr ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         if (stackpairing(i, j)) {
            /* ----------------------------- start of ----------------------------- */
            /*  v11 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
            /* ----------------------------- start of ----------------------------- */
            /* ----------- v13 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            if ((j-i-4) >= 22) {
               v13 = 1.0e7;
               for (k5=i+13; k5<=j-13; k5++) {
                  v12 = tbl_block_Pr(i+2, k5) + tbl_comps_Pr(k5, j-2);
                  v13 = v12 < v13 ? v12 : v13;
               }
            }
            else {
               v13 = 1.0e7;
            }
            /* ----------- v13 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v15 = combine <<< p block ~~~ p comps_Pr ------------- */
            v15 = 1.0e7;
            for (k6=i+9; k6<=j-13; k6++) {
               v14 = tbl_block(i+2, k6) + tbl_comps_Pr(k6, j-2);
               v15 = v14 < v15 ? v14 : v15;
            }
            /* ------------- v15 = combine <<< p block ~~~ p comps_Pr ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v17 = combine <<< p block_Pr ~~~ p comps ------------- */
            v17 = 1.0e7;
            for (k7=i+13; k7<=j-9; k7++) {
               v16 = tbl_block_Pr(i+2, k7) + tbl_comps(k7, j-2);
               v17 = v16 < v17 ? v16 : v17;
            }
            /* ------------- v17 = combine <<< p block_Pr ~~~ p comps ------------- */
            /* ----------------------------- finished ----------------------------- */

            v18 = v15 < v17 ? v15 : v17;
            v19 = v13 < v18 ? v13 : v18;
            v11 = ((380 + v19) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            /*  v11 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            v20 = v11;
         }
         else {
            v20 = 1.0e7;
         }
         v21 = v10 < v20 ? v10 : v20;
         v22 = v8 < v21 ? v8 : v21;
         v23 = v5 < v22 ? v5 : v22;
         v24 = v23;
      }
      else {
         v24 = 1.0e7;
      }
      v25 = v2 < v24 ? v2 : v24;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_closed_Pr(i, j) = v25;
   }
}

/* table calculation for production comps                                           */
/* -------------------------------------------------------------------------------- */
static void calc_comps(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7;
   int k, k2;

   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------------- v2 = cons <<< p block ~~~ p comps -------------------- */
      if ((j-i) >= 14) {
         v2 = 1.0e7;
         for (k=i+7; k<=j-7; k++) {
            v1 = tbl_block(i, k) + tbl_comps(k, j);
            v2 = v1 < v2 ? v1 : v2;
         }
      }
      else {
         v2 = 1.0e7;
      }
      /* ------------------- v2 = cons <<< p block ~~~ p comps -------------------- */
      /* -------------------------------- finished -------------------------------- */

      /* ------------------------------ v3 = p block ------------------------------ */
      v3 = tbl_block(i, j);
      /* -------------------------------- start of -------------------------------- */
      /* ------------------- v5 = addss <<< p block ~~~ region -------------------- */
      if ((j-i) >= 8) {
         v5 = 1.0e7;
         for (k2=i+7; k2<=j-1; k2++) {
            v4 = tbl_block(i, k2) + ss_energy(k2, j);
            v5 = v4 < v5 ? v4 : v5;
         }
      }
      else {
         v5 = 1.0e7;
      }
      /* ------------------- v5 = addss <<< p block ~~~ region -------------------- */
      /* -------------------------------- finished -------------------------------- */

      v6 = v3 < v5 ? v3 : v5;
      v7 = v2 < v6 ? v2 : v6;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_comps(i, j) = v7;
   }
}

/* table calculation for production comps_Pr                                        */
/* -------------------------------------------------------------------------------- */
static void calc_comps_Pr(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13;
   int k, k2, k3, k4;

   if ((j-i) >= 11) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v2 = cons <<< p block ~~~ p comps_Pr ------------------ */
      if ((j-i) >= 18) {
         v2 = 1.0e7;
         for (k=i+7; k<=j-11; k++) {
            v1 = tbl_block(i, k) + tbl_comps_Pr(k, j);
            v2 = v1 < v2 ? v1 : v2;
         }
      }
      else {
         v2 = 1.0e7;
      }
      /* ------------------ v2 = cons <<< p block ~~~ p comps_Pr ------------------ */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v4 = cons <<< p block_Pr ~~~ p comps ------------------ */
      if ((j-i) >= 18) {
         v4 = 1.0e7;
         for (k2=i+11; k2<=j-7; k2++) {
            v3 = tbl_block_Pr(i, k2) + tbl_comps(k2, j);
            v4 = v3 < v4 ? v3 : v4;
         }
      }
      else {
         v4 = 1.0e7;
      }
      /* ------------------ v4 = cons <<< p block_Pr ~~~ p comps ------------------ */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v6 = cons <<< p block_Pr ~~~ p comps_Pr ----------------- */
      if ((j-i) >= 22) {
         v6 = 1.0e7;
         for (k3=i+11; k3<=j-11; k3++) {
            v5 = tbl_block_Pr(i, k3) + tbl_comps_Pr(k3, j);
            v6 = v5 < v6 ? v5 : v6;
         }
      }
      else {
         v6 = 1.0e7;
      }
      /* ---------------- v6 = cons <<< p block_Pr ~~~ p comps_Pr ----------------- */
      /* -------------------------------- finished -------------------------------- */

      /* ---------------------------- v7 = p block_Pr ----------------------------- */
      v7 = tbl_block_Pr(i, j);
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v9 = addss <<< p block_Pr ~~~ region ------------------ */
      if ((j-i) >= 12) {
         v9 = 1.0e7;
         for (k4=i+11; k4<=j-1; k4++) {
            v8 = tbl_block_Pr(i, k4) + ss_energy(k4, j);
            v9 = v8 < v9 ? v8 : v9;
         }
      }
      else {
         v9 = 1.0e7;
      }
      /* ------------------ v9 = addss <<< p block_Pr ~~~ region ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v10 = v7 < v9 ? v7 : v9;
      v11 = v6 < v10 ? v6 : v10;
      v12 = v4 < v11 ? v4 : v11;
      v13 = v2 < v12 ? v2 : v12;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_comps_Pr(i, j) = v13;
   }
}

/* table calculation for production block                                           */
/* -------------------------------------------------------------------------------- */
static void calc_block(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8;
   int k;

   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ---------- v1 = ul <<< drem <<< is <<< loc ~~~ p closed ~~~ loc ---------- */
      /* -------------------------------- start of -------------------------------- */
      /* ------------- v2 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v3 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      v3 = tbl_closed(i, j) + termaupenalty((i) + 1, j);
      /* ------------------ v3 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v2 = v3;
      /* ------------- v2 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- finished -------------------------------- */

      v1 = 40 + v2;
      /* ---------- v1 = ul <<< drem <<< is <<< loc ~~~ p closed ~~~ loc ---------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* -- v7 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed ~~~ loc) -- */
      if ((j-i) >= 8) {
         v7 = 1.0e7;
         for (k=i+1; k<=j-7; k++) {
            /* ----------------------------- start of ----------------------------- */
            /* ---------- v5 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
            /* ----------------------------- start of ----------------------------- */
            /* --------------- v6 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            v6 = tbl_closed(k, j) + termaupenalty((k) + 1, j);
            /* --------------- v6 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v5 = v6;
            /* ---------- v5 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
            /* ----------------------------- finished ----------------------------- */

            v4 = (40 + v5) + ss_energy(i, k);
            v7 = v4 < v7 ? v4 : v7;
         }
      }
      else {
         v7 = 1.0e7;
      }
      /* -- v7 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed ~~~ loc) -- */
      /* -------------------------------- finished -------------------------------- */

      v8 = v1 < v7 ? v1 : v7;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_block(i, j) = v8;
   }
}

/* table calculation for production block_Pr                                        */
/* -------------------------------------------------------------------------------- */
static void calc_block_Pr(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10;
   int k;

   if ((j-i) >= 11) {
      /* -------------------------------- start of -------------------------------- */
      /* -------- v1 = ul <<< drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc --------- */
      if ((j-i) >= 22) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------- v2 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v3 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         v3 = tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j);
         /* --------------- v3 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         /* ------------------------------- finished ------------------------------ */

         v2 = v3;
         /* ----------- v2 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
         /* ------------------------------- finished ------------------------------ */

         v1 = 40 + v2;
      }
      else {
         v1 = 1.0e7;
      }
      /* -------- v1 = ul <<< drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc --------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v7 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc) - */
      if ((j-i) >= 23) {
         v7 = 1.0e7;
         for (k=i+1; k<=j-22; k++) {
            /* ----------------------------- start of ----------------------------- */
            /* --------- v5 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc --------- */
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v6 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            v6 = tbl_closed_Pr(k, j) + termaupenalty((k) + 1, j);
            /* ------------- v6 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            /* ----------------------------- finished ----------------------------- */

            v5 = v6;
            /* --------- v5 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc --------- */
            /* ----------------------------- finished ----------------------------- */

            v4 = (40 + v5) + ss_energy(i, k);
            v7 = v4 < v7 ? v4 : v7;
         }
      }
      else {
         v7 = 1.0e7;
      }
      /*  v7 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc) - */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* -------------------------- v8 = pkml <<< p knot -------------------------- */
      if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
         v8 = tbl_knot(i, j).tup1 + 600;
      }
      else {
         v8 = 1.0e7;
      }
      /* -------------------------- v8 = pkml <<< p knot -------------------------- */
      /* -------------------------------- finished -------------------------------- */

      v9 = v7 < v8 ? v7 : v8;
      v10 = v1 < v9 ? v1 : v9;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_block_Pr(i, j) = v10;
   }
}

/* table calculation for production knot                                            */
/* -------------------------------------------------------------------------------- */
static void calc_knot(int i, int j)
{
   int v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12;
   int v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24;
   struct str1 v1, v25;
   int lc_alphanrg, lc_betalen, lc_betanrg, lc_correctionterm, lc_energy;
   int lc_h, lc_h_Pr, lc_k, lc_l, lc_middle_k, lc_middle_l;

   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      /* -------------------------------- start of -------------------------------- */
      /* ----- v25 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
      v25.tup1 = 1.0e7;
      v25.tup2 = 0;
      v25.tup3 = 0;
      for (lc_l=i+2; lc_l<=j-1; lc_l++) {
         for (lc_k=lc_l+1; lc_k<=j-2; lc_k++) {
            lc_h = (lc_k-i) >= 5 ? tbl_stacklen(i, lc_k).tup2 : 0;
            if (lc_h >= 2) {
               lc_betalen = (j-lc_l) >= 5 ? tbl_stacklen(lc_l, j).tup2 : 0;
               lc_h_Pr = ((lc_betalen + lc_h) > (lc_k - lc_l)) ? (lc_k - lc_l) - lc_h : lc_betalen;
               if (lc_h_Pr >= 2) {
                  lc_betanrg = (j-lc_l) >= 5 ? tbl_stacklen(lc_l, j).tup1 : 1.0e7;
                  lc_alphanrg = (lc_k-i) >= 5 ? tbl_stacklen(i, lc_k).tup1 : 1.0e7;
                  lc_correctionterm = (min(j-lc_h_Pr+1, n)-(max(0, lc_l+lc_h_Pr-1))) >= 5 ? tbl_stacklen(lc_l+lc_h_Pr-1, min(j-lc_h_Pr+1, n)).tup1 : 1.0e7;
                  lc_middle_k = (j) - lc_h_Pr;
                  lc_middle_l = (i) + lc_h;
                  lc_energy = ((lc_alphanrg + lc_betanrg) - lc_correctionterm) + (pbp * (lc_h + lc_h_Pr));
                  /* -------------------------- start of -------------------------- */
                  /* ---------------- v2 = pul <<< pss <<< uregion ---------------- */
                  if ((lc_l-(i+lc_h)-1) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v3 = pss <<< uregion ------------------ */
                     v3 = sspenalty((lc_l) - (i+lc_h+1));
                     /* ------------------- v3 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v2 = v3;
                  }
                  else {
                     v2 = 1.0e7;
                  }
                  /* ---------------- v2 = pul <<< pss <<< uregion ---------------- */
                  /* -------------------------- finished -------------------------- */

                  /* ------------------------ v4 = p comps ------------------------ */
                  if ((lc_l-(i+lc_h)-1) >= 7) {
                     v4 = tbl_comps(i+lc_h+1, lc_l);
                  }
                  else {
                     v4 = 1.0e7;
                  }
                  /* ---------------------- v5 = p comps_Pr ----------------------- */
                  if ((lc_l-(i+lc_h)-1) >= 11) {
                     v5 = tbl_comps_Pr(i+lc_h+1, lc_l);
                  }
                  else {
                     v5 = 1.0e7;
                  }
                  v6 = v4 < v5 ? v4 : v5;
                  v7 = v2 < v6 ? v2 : v6;
                  /* -------------------------- start of -------------------------- */
                  /* ------ v8 = emptymid lc_middle_k lc_middle_l <<< empty ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 0) {
                     v8 = wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, lc_l+lc_h_Pr, (lc_l+lc_h_Pr) + 1);
                  }
                  else {
                     v8 = 1.0e7;
                  }
                  /* ------ v8 = emptymid lc_middle_k lc_middle_l <<< empty ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* ------- v9 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 1) {
                     v9 = (wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, (lc_k-lc_h) - 1, (lc_k-lc_h) + 1)) + npp;
                  }
                  else {
                     v9 = 1.0e7;
                  }
                  /* ------- v9 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v10 = midregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h_l - */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v11 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v12 = pss <<< region ------------------ */
                     v12 = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr));
                     /* ------------------- v12 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v11 = v12;
                     /* --------------- v11 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v13 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 7) {
                        v13 = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h);
                     }
                     else {
                        v13 = 1.0e7;
                     }
                     /* --------------------- v14 = p comps_Pr -------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 11) {
                        v14 = tbl_comps_Pr(lc_l+lc_h_Pr, lc_k-lc_h);
                     }
                     else {
                        v14 = 1.0e7;
                     }
                     v15 = v13 < v14 ? v13 : v14;
                     v16 = v11 < v15 ? v11 : v15;
                     v10 = v16;
                  }
                  else {
                     v10 = 1.0e7;
                  }
                  /*  v10 = midregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h_l - */
                  /* -------------------------- finished -------------------------- */

                  v17 = v9 < v10 ? v9 : v10;
                  v18 = v8 < v17 ? v8 : v17;
                  /* -------------------------- start of -------------------------- */
                  /* --------------- v19 = pul <<< pss <<< uregion ---------------- */
                  if ((j-lc_h_Pr-lc_k-2) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v20 = pss <<< uregion ------------------ */
                     v20 = sspenalty((j-lc_h_Pr-2) - (lc_k));
                     /* ------------------ v20 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v19 = v20;
                  }
                  else {
                     v19 = 1.0e7;
                  }
                  /* --------------- v19 = pul <<< pss <<< uregion ---------------- */
                  /* -------------------------- finished -------------------------- */

                  /* ----------------------- v21 = p comps ------------------------ */
                  if ((j-lc_h_Pr-lc_k-2) >= 7) {
                     v21 = tbl_comps(lc_k, j-lc_h_Pr-2);
                  }
                  else {
                     v21 = 1.0e7;
                  }
                  /* ---------------------- v22 = p comps_Pr ---------------------- */
                  if ((j-lc_h_Pr-lc_k-2) >= 11) {
                     v22 = tbl_comps_Pr(lc_k, j-lc_h_Pr-2);
                  }
                  else {
                     v22 = 1.0e7;
                  }
                  v23 = v21 < v22 ? v21 : v22;
                  v24 = v19 < v23 ? v19 : v23;
                  v1.tup1 = (((((pkinit + lc_energy) + (3 * npp)) + v7) + v18) + v24) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j);
                  v1.tup2 = lc_l;
                  v1.tup3 = lc_k;
               }
               else {
                  v1.tup1 = 1.0e7;
                  v1.tup2 = 0;
                  v1.tup3 = 0;
               }
            }
            else {
               v1.tup1 = 1.0e7;
               v1.tup2 = 0;
               v1.tup3 = 0;
            }
            /* ---------------------- v25 = minimum(v1, v25) ---------------------- */
            v25 = v1.tup1 < v25.tup1 ? v1 : v25;
         }
      }
      /* ----- v25 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
      /* -------------------------------- finished -------------------------------- */

      /* ----------------------- assign table entry result ------------------------ */
      tbl_knot(i, j) = v25;
   }
}

/* table calculation for production stacklen                                        */
/* -------------------------------------------------------------------------------- */
static void calc_stacklen(int i, int j)
{
   struct str2 v1, v2, v3, v4, v5;

   if ((j-i) >= 5) {
      if (basepairing(i, j)) {
         /* ------------------------------- start of ------------------------------ */
         /* ------------- v1 = sum <<< lbase ~~~ p stacklen ~~~ lbase ------------- */
         if ((j-i) >= 7) {
            v1.tup1 = tbl_stacklen(i+1, j-1).tup1 + sr_energy(i+1, j);
            v1.tup2 = tbl_stacklen(i+1, j-1).tup2 + 1;
         }
         else {
            v1.tup1 = 1.0e7;
            v1.tup2 = 0;
         }
         /* ------------- v1 = sum <<< lbase ~~~ p stacklen ~~~ lbase ------------- */
         /* ------------------------------- finished ------------------------------ */

         v2 = v1;
      }
      else {
         v2.tup1 = 1.0e7;
         v2.tup2 = 0;
      }
      if (basepairing(i, j)) {
         /* ------------------------------- start of ------------------------------ */
         /* -- v3 = sumend <<< lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase -- */
         v3.tup1 = 0;
         v3.tup2 = 1;
         /* -- v3 = sumend <<< lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase -- */
         /* ------------------------------- finished ------------------------------ */

         v4 = v3;
      }
      else {
         v4.tup1 = 1.0e7;
         v4.tup2 = 0;
      }
      /* -------------------------- v5 = minimum(v2, v4) -------------------------- */
      v5 = v2.tup1 < v4.tup1 ? v2 : v4;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_stacklen(i, j) = v5;
   }
}

/* forward declarations for backtracing functions                                   */
/* -------------------------------------------------------------------------------- */

static struct str3 *back_closed(int i, int j, int diff);

static struct str3 *back_closed_Pr(int i, int j, int diff);

static struct str3 *back_knot(int i, int j, int diff);

static struct str3 *back_stacklen(int i, int j, int diff);

static struct str3 *back_edangle(int i, int j, int diff);

static struct str3 *back_edangle_Pr(int i, int j, int diff);

static struct str3 *back_block(int i, int j, int diff);

static struct str3 *back_block_Pr(int i, int j, int diff);

static struct str3 *back_struct(int i, int j, int diff);

static struct str3 *back_structP(int i, int j, int diff);

static struct str3 *back_comps(int i, int j, int diff);

static struct str3 *back_comps_Pr(int i, int j, int diff);

/* backtracing code                                                                 */
/* -------------------------------------------------------------------------------- */

/* backtracing code for production struct                                           */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_struct(int i, int j, int diff)
{
   struct str3 *v12;
   int v8;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v9, *v10, *v11;
   int k;

   /* ---------------------------------- start of --------------------------------- */
   /* ---------------------- v1 = sadd <<< lbase ~~~ p struct --------------------- */
   if ((j-i) >= 1) {
      if (abs(tbl_struct(i, j) - tbl_struct(i+1, j)) <= diff) {
         v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v1->next = NULL;
         v1->last = v1;
         v1->item.alg_energy = tbl_struct(i+1, j);
         v1->item.alg_enum = new_Sadd_f(i+1, back_struct, i+1, j);
      }
      else {
         v1 = NULL;
      }
   }
   else {
      v1 = NULL;
   }
   /* ---------------------- v1 = sadd <<< lbase ~~~ p struct --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* -------------------- v3 = cadd <<< p edangle ~~~ p struct ------------------- */
   if ((j-i) >= 7) {
      v3 = NULL;
      for (k=i+7; k<=j; k++) {
         if (abs(tbl_struct(i, j) - (tbl_edangle(i, k) + tbl_struct(k, j))) <= diff) {
            v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v2->next = NULL;
            v2->last = v2;
            v2->item.alg_energy = tbl_edangle(i, k) + tbl_struct(k, j);
            v2->item.alg_enum = new_Cadd_ff(back_edangle, i, k, back_struct, k, j);
         }
         else {
            v2 = NULL;
         }
         /* ---------------------------- v3 = v2 ++ v3 ---------------------------- */
         if (v2 == NULL) {
         } else 
         if (v3 == NULL) {
            v3 = v2;
         }
         else {
            v2->last->next = v3;
            v2->last = v3->last;
            v3 = v2;
         }
      }
   }
   else {
      v3 = NULL;
   }
   /* -------------------- v3 = cadd <<< p edangle ~~~ p struct ------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------------- v4 = nil <<< empty ---------------------------- */
   if ((j-i) == 0) {
      if (abs(tbl_struct(i, j) - 0) <= diff) {
         v4=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v4->next = NULL;
         v4->last = v4;
         v4->item.alg_energy = 0;
         v4->item.alg_enum = new_Nil_(i);
      }
      else {
         v4 = NULL;
      }
   }
   else {
      v4 = NULL;
   }
   /* ----------------------------- v4 = nil <<< empty ---------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------- v5 = v3 ++ v4 ------------------------------- */
   if (v3 == NULL) {
      v5 = v4;
   } else 
   if (v4 == NULL) {
      v5 = v3;
   }
   else {
      v3->last->next = v4;
      v3->last = v4->last;
      v5 = v3;
   }
   /* ------------------------------- v6 = v1 ++ v5 ------------------------------- */
   if (v1 == NULL) {
      v6 = v5;
   } else 
   if (v5 == NULL) {
      v6 = v1;
   }
   else {
      v1->last->next = v5;
      v1->last = v5->last;
      v6 = v1;
   }
   /* ------------------------------ v8 = minimum(v6) ----------------------------- */
   v8 = 1.0e7;
   v7 = v6;
   while (v7 != NULL) {
      v8 = v8 < v7->item.alg_energy ? v8 : v7->item.alg_energy;
      v7 = v7->next;
   }
   v7 = v6;
   v10 = NULL;
   while (v7 != NULL) {
      if (abs(v8 - v7->item.alg_energy) <= diff) {
         update_str_Signature(v7->item.alg_enum->item, diff - abs(v8 - v7->item.alg_energy));
         v9=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v9->item = v7->item;
         v9->next = NULL;
         v9->last = v9;
         /* --------------------------- v10 = v9 ++ v10 --------------------------- */
         if (v9 == NULL) {
         } else 
         if (v10 == NULL) {
            v10 = v9;
         }
         else {
            v9->last->next = v10;
            v9->last = v10->last;
            v10 = v9;
         }
      }
      v7 = v7->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v11 = v10;
   v12 = NULL;
   while (v11 != NULL) {
      /* -------------------- v12 = v11->item.alg_enum ++ v12 --------------------- */
      if (v11->item.alg_enum == NULL) {
      } else 
      if (v12 == NULL) {
         v12 = v11->item.alg_enum;
      }
      else {
         v11->item.alg_enum->last->next = v12;
         v11->item.alg_enum->last = v12->last;
         v12 = v11->item.alg_enum;
      }
      v11 = v11->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v12)));
}

/* backtracing code for production structP                                          */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_structP(int i, int j, int diff)
{
   struct str3 *v16;
   int v12;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7;
   struct str5 *v8, *v9, *v10, *v11, *v13, *v14, *v15;
   int k, k2, k3;

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v1 = sadd <<< lbase ~~~ p structP --------------------- */
   if ((j-i) >= 12) {
      if (abs(tbl_structP(i, j) - tbl_structP(i+1, j)) <= diff) {
         v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v1->next = NULL;
         v1->last = v1;
         v1->item.alg_energy = tbl_structP(i+1, j);
         v1->item.alg_enum = new_Sadd_f(i+1, back_structP, i+1, j);
      }
      else {
         v1 = NULL;
      }
   }
   else {
      v1 = NULL;
   }
   /* --------------------- v1 = sadd <<< lbase ~~~ p structP --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------- v3 = cadd <<< p edangle ~~~ p structP ------------------- */
   if ((j-i) >= 18) {
      v3 = NULL;
      for (k=i+7; k<=j-11; k++) {
         if (abs(tbl_structP(i, j) - (tbl_edangle(i, k) + tbl_structP(k, j))) <= diff) {
            v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v2->next = NULL;
            v2->last = v2;
            v2->item.alg_energy = tbl_edangle(i, k) + tbl_structP(k, j);
            v2->item.alg_enum = new_Cadd_ff(back_edangle, i, k, back_structP, k, j);
         }
         else {
            v2 = NULL;
         }
         /* ---------------------------- v3 = v2 ++ v3 ---------------------------- */
         if (v2 == NULL) {
         } else 
         if (v3 == NULL) {
            v3 = v2;
         }
         else {
            v2->last->next = v3;
            v2->last = v3->last;
            v3 = v2;
         }
      }
   }
   else {
      v3 = NULL;
   }
   /* ------------------- v3 = cadd <<< p edangle ~~~ p structP ------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------ v5 = cadd <<< p edangle_Pr ~~~ p struct ------------------ */
   if ((j-i) >= 11) {
      v5 = NULL;
      for (k2=i+11; k2<=j; k2++) {
         if (abs(tbl_structP(i, j) - (tbl_edangle_Pr(i, k2) + tbl_struct(k2, j))) <= diff) {
            v4=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v4->next = NULL;
            v4->last = v4;
            v4->item.alg_energy = tbl_edangle_Pr(i, k2) + tbl_struct(k2, j);
            v4->item.alg_enum = new_Cadd_ff(back_edangle_Pr, i, k2, back_struct, k2, j);
         }
         else {
            v4 = NULL;
         }
         /* ---------------------------- v5 = v4 ++ v5 ---------------------------- */
         if (v4 == NULL) {
         } else 
         if (v5 == NULL) {
            v5 = v4;
         }
         else {
            v4->last->next = v5;
            v4->last = v5->last;
            v5 = v4;
         }
      }
   }
   else {
      v5 = NULL;
   }
   /* ------------------ v5 = cadd <<< p edangle_Pr ~~~ p struct ------------------ */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------ v7 = cadd <<< p edangle_Pr ~~~ p structP ----------------- */
   if ((j-i) >= 22) {
      v7 = NULL;
      for (k3=i+11; k3<=j-11; k3++) {
         if (abs(tbl_structP(i, j) - (tbl_edangle_Pr(i, k3) + tbl_structP(k3, j))) <= diff) {
            v6=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v6->next = NULL;
            v6->last = v6;
            v6->item.alg_energy = tbl_edangle_Pr(i, k3) + tbl_structP(k3, j);
            v6->item.alg_enum = new_Cadd_ff(back_edangle_Pr, i, k3, back_structP, k3, j);
         }
         else {
            v6 = NULL;
         }
         /* ---------------------------- v7 = v6 ++ v7 ---------------------------- */
         if (v6 == NULL) {
         } else 
         if (v7 == NULL) {
            v7 = v6;
         }
         else {
            v6->last->next = v7;
            v6->last = v7->last;
            v7 = v6;
         }
      }
   }
   else {
      v7 = NULL;
   }
   /* ------------------ v7 = cadd <<< p edangle_Pr ~~~ p structP ----------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------- v8 = v5 ++ v7 ------------------------------- */
   if (v5 == NULL) {
      v8 = v7;
   } else 
   if (v7 == NULL) {
      v8 = v5;
   }
   else {
      v5->last->next = v7;
      v5->last = v7->last;
      v8 = v5;
   }
   /* ------------------------------- v9 = v3 ++ v8 ------------------------------- */
   if (v3 == NULL) {
      v9 = v8;
   } else 
   if (v8 == NULL) {
      v9 = v3;
   }
   else {
      v3->last->next = v8;
      v3->last = v8->last;
      v9 = v3;
   }
   /* ------------------------------- v10 = v1 ++ v9 ------------------------------ */
   if (v1 == NULL) {
      v10 = v9;
   } else 
   if (v9 == NULL) {
      v10 = v1;
   }
   else {
      v1->last->next = v9;
      v1->last = v9->last;
      v10 = v1;
   }
   /* ----------------------------- v12 = minimum(v10) ---------------------------- */
   v12 = 1.0e7;
   v11 = v10;
   while (v11 != NULL) {
      v12 = v12 < v11->item.alg_energy ? v12 : v11->item.alg_energy;
      v11 = v11->next;
   }
   v11 = v10;
   v14 = NULL;
   while (v11 != NULL) {
      if (abs(v12 - v11->item.alg_energy) <= diff) {
         update_str_Signature(v11->item.alg_enum->item, diff - abs(v12 - v11->item.alg_energy));
         v13=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v13->item = v11->item;
         v13->next = NULL;
         v13->last = v13;
         /* --------------------------- v14 = v13 ++ v14 -------------------------- */
         if (v13 == NULL) {
         } else 
         if (v14 == NULL) {
            v14 = v13;
         }
         else {
            v13->last->next = v14;
            v13->last = v14->last;
            v14 = v13;
         }
      }
      v11 = v11->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v15 = v14;
   v16 = NULL;
   while (v15 != NULL) {
      /* -------------------- v16 = v15->item.alg_enum ++ v16 --------------------- */
      if (v15->item.alg_enum == NULL) {
      } else 
      if (v16 == NULL) {
         v16 = v15->item.alg_enum;
      }
      else {
         v15->item.alg_enum->last->next = v16;
         v15->item.alg_enum->last = v16->last;
         v16 = v15->item.alg_enum;
      }
      v15 = v15->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v16)));
}

/* backtracing code for production edangle                                          */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_edangle(int i, int j, int diff)
{
   struct str3 *v12;
   int v8;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v9, *v10, *v11;

   /* ---------------------------------- start of --------------------------------- */
   /* --------------- v3 = drem <<< is <<< loc ~~~ p closed ~~~ loc --------------- */
   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v2 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      if (abs(tbl_edangle(i, j) - (tbl_closed(i, j) + termaupenalty((i) + 1, j))) <= diff) {
         v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v2->next = NULL;
         v2->last = v2;
         v2->item.alg_energy = tbl_closed(i, j) + termaupenalty((i) + 1, j);
         v2->item.alg_enum = new_Is_f(i, back_closed, i, j, j);
      }
      else {
         v2 = NULL;
      }
      /* ------------------ v2 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v3 = NULL;
      /* +------------------------------------------------------------------------- */
      /* v1 stores the result of a single application of algebra function           */
      /* v2 holds the results of expression                                         */
      /*      is <<< loc ~~~ p closed ~~~ loc                                       */
      /*                                                                            */
      /* we use v4 to iterate over v2 and                                           */
      /* v3 to collect the results                                                  */
      /* +------------------------------------------------------------------------- */
      v4 = v2;
      while (v4 != NULL) {
         if (abs(tbl_edangle(i, j) - v4->item.alg_energy) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = v4->item.alg_energy;
            v1->item.alg_enum = new_Drem_s(v4->item.alg_enum);
         }
         else {
            v1 = NULL;
         }
         /* ---------------------------- v3 = v1 ++ v3 ---------------------------- */
         if (v1 == NULL) {
         } else 
         if (v3 == NULL) {
            v3 = v1;
         }
         else {
            v1->last->next = v3;
            v1->last = v3->last;
            v3 = v1;
         }
         v4 = v4->next;
      }
   }
   else {
      v3 = NULL;
   }
   /* --------------- v3 = drem <<< is <<< loc ~~~ p closed ~~~ loc --------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------------- v5 = pk <<< p knot ---------------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      if (abs(tbl_edangle(i, j) - tbl_knot(i, j).tup1) <= diff) {
         v5=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v5->next = NULL;
         v5->last = v5;
         v5->item.alg_energy = tbl_knot(i, j).tup1;
         v5->item.alg_enum = new_Pk_f(back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3);
      }
      else {
         v5 = NULL;
      }
   }
   else {
      v5 = NULL;
   }
   /* ----------------------------- v5 = pk <<< p knot ---------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------- v6 = v3 ++ v5 ------------------------------- */
   if (v3 == NULL) {
      v6 = v5;
   } else 
   if (v5 == NULL) {
      v6 = v3;
   }
   else {
      v3->last->next = v5;
      v3->last = v5->last;
      v6 = v3;
   }
   /* ------------------------------ v8 = minimum(v6) ----------------------------- */
   v8 = 1.0e7;
   v7 = v6;
   while (v7 != NULL) {
      v8 = v8 < v7->item.alg_energy ? v8 : v7->item.alg_energy;
      v7 = v7->next;
   }
   v7 = v6;
   v10 = NULL;
   while (v7 != NULL) {
      if (abs(v8 - v7->item.alg_energy) <= diff) {
         update_str_Signature(v7->item.alg_enum->item, diff - abs(v8 - v7->item.alg_energy));
         v9=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v9->item = v7->item;
         v9->next = NULL;
         v9->last = v9;
         /* --------------------------- v10 = v9 ++ v10 --------------------------- */
         if (v9 == NULL) {
         } else 
         if (v10 == NULL) {
            v10 = v9;
         }
         else {
            v9->last->next = v10;
            v9->last = v10->last;
            v10 = v9;
         }
      }
      v7 = v7->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v11 = v10;
   v12 = NULL;
   while (v11 != NULL) {
      /* -------------------- v12 = v11->item.alg_enum ++ v12 --------------------- */
      if (v11->item.alg_enum == NULL) {
      } else 
      if (v12 == NULL) {
         v12 = v11->item.alg_enum;
      }
      else {
         v11->item.alg_enum->last->next = v12;
         v11->item.alg_enum->last = v12->last;
         v12 = v11->item.alg_enum;
      }
      v11 = v11->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v12)));
}

/* backtracing code for production edangle_Pr                                       */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_edangle_Pr(int i, int j, int diff)
{
   struct str3 *v12;
   int v8;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v9, *v10, *v11;

   /* ---------------------------------- start of --------------------------------- */
   /* -------------- v3 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
   if ((j-i) >= 22) {
      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v2 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------------- */
      if (abs(tbl_edangle_Pr(i, j) - (tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j))) <= diff) {
         v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v2->next = NULL;
         v2->last = v2;
         v2->item.alg_energy = tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j);
         v2->item.alg_enum = new_Is_f(i, back_closed_Pr, i, j, j);
      }
      else {
         v2 = NULL;
      }
      /* ---------------- v2 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------------- */
      /* -------------------------------- finished -------------------------------- */

      v3 = NULL;
      /* +------------------------------------------------------------------------- */
      /* v1 stores the result of a single application of algebra function           */
      /* v2 holds the results of expression                                         */
      /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                    */
      /*                                                                            */
      /* we use v4 to iterate over v2 and                                           */
      /* v3 to collect the results                                                  */
      /* +------------------------------------------------------------------------- */
      v4 = v2;
      while (v4 != NULL) {
         if (abs(tbl_edangle_Pr(i, j) - v4->item.alg_energy) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = v4->item.alg_energy;
            v1->item.alg_enum = new_Drem_s(v4->item.alg_enum);
         }
         else {
            v1 = NULL;
         }
         /* ---------------------------- v3 = v1 ++ v3 ---------------------------- */
         if (v1 == NULL) {
         } else 
         if (v3 == NULL) {
            v3 = v1;
         }
         else {
            v1->last->next = v3;
            v1->last = v3->last;
            v3 = v1;
         }
         v4 = v4->next;
      }
   }
   else {
      v3 = NULL;
   }
   /* -------------- v3 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------------- v5 = pk <<< p knot ---------------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      if (abs(tbl_edangle_Pr(i, j) - tbl_knot(i, j).tup1) <= diff) {
         v5=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v5->next = NULL;
         v5->last = v5;
         v5->item.alg_energy = tbl_knot(i, j).tup1;
         v5->item.alg_enum = new_Pk_f(back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3);
      }
      else {
         v5 = NULL;
      }
   }
   else {
      v5 = NULL;
   }
   /* ----------------------------- v5 = pk <<< p knot ---------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------- v6 = v3 ++ v5 ------------------------------- */
   if (v3 == NULL) {
      v6 = v5;
   } else 
   if (v5 == NULL) {
      v6 = v3;
   }
   else {
      v3->last->next = v5;
      v3->last = v5->last;
      v6 = v3;
   }
   /* ------------------------------ v8 = minimum(v6) ----------------------------- */
   v8 = 1.0e7;
   v7 = v6;
   while (v7 != NULL) {
      v8 = v8 < v7->item.alg_energy ? v8 : v7->item.alg_energy;
      v7 = v7->next;
   }
   v7 = v6;
   v10 = NULL;
   while (v7 != NULL) {
      if (abs(v8 - v7->item.alg_energy) <= diff) {
         update_str_Signature(v7->item.alg_enum->item, diff - abs(v8 - v7->item.alg_energy));
         v9=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v9->item = v7->item;
         v9->next = NULL;
         v9->last = v9;
         /* --------------------------- v10 = v9 ++ v10 --------------------------- */
         if (v9 == NULL) {
         } else 
         if (v10 == NULL) {
            v10 = v9;
         }
         else {
            v9->last->next = v10;
            v9->last = v10->last;
            v10 = v9;
         }
      }
      v7 = v7->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v11 = v10;
   v12 = NULL;
   while (v11 != NULL) {
      /* -------------------- v12 = v11->item.alg_enum ++ v12 --------------------- */
      if (v11->item.alg_enum == NULL) {
      } else 
      if (v12 == NULL) {
         v12 = v11->item.alg_enum;
      }
      else {
         v11->item.alg_enum->last->next = v12;
         v11->item.alg_enum->last = v12->last;
         v12 = v11->item.alg_enum;
      }
      v11 = v11->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v12)));
}

/* backtracing code for production closed                                           */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_closed(int i, int j, int diff)
{
   struct str3 *v45;
   int v10, v19, v25, v41;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v11;
   struct str5 *v12, *v13, *v14, *v15, *v16, *v17, *v18, *v20, *v21, *v22;
   struct str5 *v23, *v24, *v26, *v27, *v28, *v29, *v30, *v31, *v32, *v33;
   struct str5 *v34, *v35, *v36, *v37, *v38, *v39, *v40, *v42, *v43, *v44;
   int k, k2, k3, k4, k5;

   if (basepairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v1 = sr <<< lbase ~~~ p closed ~~~ lbase ---------------- */
      if ((j-i) >= 9) {
         if (abs(tbl_closed(i, j) - (tbl_closed(i+1, j-1) + sr_energy(i+1, j))) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = tbl_closed(i+1, j-1) + sr_energy(i+1, j);
            v1->item.alg_enum = new_Sr_f(i+1, back_closed, i+1, j-1, j);
         }
         else {
            v1 = NULL;
         }
      }
      else {
         v1 = NULL;
      }
      /* ---------------- v1 = sr <<< lbase ~~~ p closed ~~~ lbase ---------------- */
      /* -------------------------------- finished -------------------------------- */

      v2 = v1;
   }
   else {
      v2 = NULL;
   }
   if (stackpairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /*  v3 = hl <<< lbase ~~~ lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 7) {
         if (abs(tbl_closed(i, j) - (hl_energy(i+2, j-1) + sr_energy(i+1, j))) <= diff) {
            v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v3->next = NULL;
            v3->last = v3;
            v3->item.alg_energy = hl_energy(i+2, j-1) + sr_energy(i+1, j);
            v3->item.alg_enum = new_Hl_(i+1, i+2, i+2, j-2, j-1, j);
         }
         else {
            v3 = NULL;
         }
      }
      else {
         v3 = NULL;
      }
      /*  v3 = hl <<< lbase ~~~ lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v8 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 12) {
         v8 = NULL;
         for (k=i+3; k<=j-9; k++) {
            /* ----------------------------- start of ----------------------------- */
            /* --------------- v5 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            if (abs(tbl_closed(i, j) - (((tbl_closed(k, j-2) + termaupenalty((k) + 1, j-2)) + bl_energy(i+2, i+2, k, j-1)) + sr_energy(i+1, j))) <= diff) {
               v5=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v5->next = NULL;
               v5->last = v5;
               v5->item.alg_energy = tbl_closed(k, j-2) + termaupenalty((k) + 1, j-2);
               v5->item.alg_enum = new_Is_f(k, back_closed, k, j-2, j-2);
            }
            else {
               v5 = NULL;
            }
            /* --------------- v5 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v6 = NULL;
            /* +------------------------------------------------------------------------- */
            /* v4 stores the result of a single application of algebra function           */
            /* v5 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed ~~~ loc                                       */
            /*                                                                            */
            /* we use v7 to iterate over v5 and                                           */
            /* v6 to collect the results                                                  */
            /* +------------------------------------------------------------------------- */
            v7 = v5;
            while (v7 != NULL) {
               if (abs(tbl_closed(i, j) - ((v7->item.alg_energy + bl_energy(i+2, i+2, k, j-1)) + sr_energy(i+1, j))) <= diff) {
                  v4=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v4->next = NULL;
                  v4->last = v4;
                  v4->item.alg_energy = (v7->item.alg_energy + bl_energy(i+2, i+2, k, j-1)) + sr_energy(i+1, j);
                  v4->item.alg_enum = new_Bl_s(i+1, i+2, i+2, k, v7->item.alg_enum, j-1, j);
               }
               else {
                  v4 = NULL;
               }
               /* ------------------------- v6 = v4 ++ v6 ------------------------- */
               if (v4 == NULL) {
               } else 
               if (v6 == NULL) {
                  v6 = v4;
               }
               else {
                  v4->last->next = v6;
                  v4->last = v6->last;
                  v6 = v4;
               }
               v7 = v7->next;
            }
            /* -------------------------- v8 = v6 ++ v8 --------------------------- */
            if (v6 == NULL) {
            } else 
            if (v8 == NULL) {
               v8 = v6;
            }
            else {
               v6->last->next = v8;
               v6->last = v8->last;
               v8 = v6;
            }
         }
      }
      else {
         v8 = NULL;
      }
      /*  v8 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* --------------------------- v10 = minimum(v8) ---------------------------- */
      v10 = 1.0e7;
      v9 = v8;
      while (v9 != NULL) {
         v10 = v10 < v9->item.alg_energy ? v10 : v9->item.alg_energy;
         v9 = v9->next;
      }
      v9 = v8;
      v12 = NULL;
      while (v9 != NULL) {
         if (abs(v10 - v9->item.alg_energy) <= diff) {
            update_str_Signature(v9->item.alg_enum->item, diff - abs(v10 - v9->item.alg_energy));
            v11=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v11->item = v9->item;
            v11->next = NULL;
            v11->last = v11;
            /* ------------------------- v12 = v11 ++ v12 ------------------------- */
            if (v11 == NULL) {
            } else 
            if (v12 == NULL) {
               v12 = v11;
            }
            else {
               v11->last->next = v12;
               v11->last = v12->last;
               v12 = v11;
            }
         }
         v9 = v9->next;
      }
      /* -------------------------------- start of -------------------------------- */
      /*  v17 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 12) {
         v17 = NULL;
         for (k2=i+9; k2<=j-3; k2++) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v14 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            if (abs(tbl_closed(i, j) - (((tbl_closed(i+2, k2) + termaupenalty((i+2) + 1, k2)) + br_energy(i+2, k2, j-2, j-1)) + sr_energy(i+1, j))) <= diff) {
               v14=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v14->next = NULL;
               v14->last = v14;
               v14->item.alg_energy = tbl_closed(i+2, k2) + termaupenalty((i+2) + 1, k2);
               v14->item.alg_enum = new_Is_f(i+2, back_closed, i+2, k2, k2);
            }
            else {
               v14 = NULL;
            }
            /* -------------- v14 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v15 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v13 stores the result of a single application of algebra function           */
            /* v14 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed ~~~ loc                                        */
            /*                                                                             */
            /* we use v16 to iterate over v14 and                                          */
            /* v15 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v16 = v14;
            while (v16 != NULL) {
               if (abs(tbl_closed(i, j) - ((v16->item.alg_energy + br_energy(i+2, k2, j-2, j-1)) + sr_energy(i+1, j))) <= diff) {
                  v13=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v13->next = NULL;
                  v13->last = v13;
                  v13->item.alg_energy = (v16->item.alg_energy + br_energy(i+2, k2, j-2, j-1)) + sr_energy(i+1, j);
                  v13->item.alg_enum = new_Br_s(i+1, i+2, v16->item.alg_enum, k2, j-2, j-1, j);
               }
               else {
                  v13 = NULL;
               }
               /* ------------------------ v15 = v13 ++ v15 ----------------------- */
               if (v13 == NULL) {
               } else 
               if (v15 == NULL) {
                  v15 = v13;
               }
               else {
                  v13->last->next = v15;
                  v13->last = v15->last;
                  v15 = v13;
               }
               v16 = v16->next;
            }
            /* ------------------------- v17 = v15 ++ v17 ------------------------- */
            if (v15 == NULL) {
            } else 
            if (v17 == NULL) {
               v17 = v15;
            }
            else {
               v15->last->next = v17;
               v15->last = v17->last;
               v17 = v15;
            }
         }
      }
      else {
         v17 = NULL;
      }
      /*  v17 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* --------------------------- v19 = minimum(v17) --------------------------- */
      v19 = 1.0e7;
      v18 = v17;
      while (v18 != NULL) {
         v19 = v19 < v18->item.alg_energy ? v19 : v18->item.alg_energy;
         v18 = v18->next;
      }
      v18 = v17;
      v21 = NULL;
      while (v18 != NULL) {
         if (abs(v19 - v18->item.alg_energy) <= diff) {
            update_str_Signature(v18->item.alg_enum->item, diff - abs(v19 - v18->item.alg_energy));
            v20=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v20->item = v18->item;
            v20->next = NULL;
            v20->last = v20;
            /* ------------------------- v21 = v20 ++ v21 ------------------------- */
            if (v20 == NULL) {
            } else 
            if (v21 == NULL) {
               v21 = v20;
            }
            else {
               v20->last->next = v21;
               v20->last = v21->last;
               v21 = v20;
            }
         }
         v18 = v18->next;
      }
      /* -------------------------------- start of -------------------------------- */
      /*  v23 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 13) {
         v23 = NULL;
         for (k4=max(i+10, j-32); k4<=j-3; k4++) {
            for (k3=i+3; k3<=min(i+34, k4-7); k3++) {
               if (abs(tbl_closed(i, j) - ((tbl_closed(k3, k4) + sr_energy(i+1, j)) + il_energy(i+2, k3, k4, j-2))) <= diff) {
                  v22=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v22->next = NULL;
                  v22->last = v22;
                  v22->item.alg_energy = (tbl_closed(k3, k4) + sr_energy(i+1, j)) + il_energy(i+2, k3, k4, j-2);
                  v22->item.alg_enum = new_Il_f(i+1, i+2, i+2, k3, back_closed, k3, k4, k4, j-2, j-1, j);
               }
               else {
                  v22 = NULL;
               }
               /* ------------------------ v23 = v22 ++ v23 ----------------------- */
               if (v22 == NULL) {
               } else 
               if (v23 == NULL) {
                  v23 = v22;
               }
               else {
                  v22->last->next = v23;
                  v22->last = v23->last;
                  v23 = v22;
               }
            }
         }
      }
      else {
         v23 = NULL;
      }
      /*  v23 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* --------------------------- v25 = minimum(v23) --------------------------- */
      v25 = 1.0e7;
      v24 = v23;
      while (v24 != NULL) {
         v25 = v25 < v24->item.alg_energy ? v25 : v24->item.alg_energy;
         v24 = v24->next;
      }
      v24 = v23;
      v27 = NULL;
      while (v24 != NULL) {
         if (abs(v25 - v24->item.alg_energy) <= diff) {
            update_str_Signature(v24->item.alg_enum->item, diff - abs(v25 - v24->item.alg_energy));
            v26=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v26->item = v24->item;
            v26->next = NULL;
            v26->last = v26;
            /* ------------------------- v27 = v26 ++ v27 ------------------------- */
            if (v26 == NULL) {
            } else 
            if (v27 == NULL) {
               v27 = v26;
            }
            else {
               v26->last->next = v27;
               v26->last = v27->last;
               v27 = v26;
            }
         }
         v24 = v24->next;
      }
      if (stackpairing(i, j)) {
         /* ------------------------------- start of ------------------------------ */
         /*  v31 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 18) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v30 = combine <<< p block ~~~ p comps --------------- */
            v30 = NULL;
            for (k5=i+9; k5<=j-9; k5++) {
               if (abs(tbl_closed(i, j) - (((380 + (tbl_block(i+2, k5) + tbl_comps(k5, j-2))) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v29=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v29->next = NULL;
                  v29->last = v29;
                  v29->item.alg_energy = tbl_block(i+2, k5) + tbl_comps(k5, j-2);
                  v29->item.alg_enum = new_Combine_ff(back_block, i+2, k5, back_comps, k5, j-2);
               }
               else {
                  v29 = NULL;
               }
               /* ------------------------ v30 = v29 ++ v30 ----------------------- */
               if (v29 == NULL) {
               } else 
               if (v30 == NULL) {
                  v30 = v29;
               }
               else {
                  v29->last->next = v30;
                  v29->last = v30->last;
                  v30 = v29;
               }
            }
            /* -------------- v30 = combine <<< p block ~~~ p comps --------------- */
            /* ----------------------------- finished ----------------------------- */

            v31 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v28 stores the result of a single application of algebra function           */
            /* v30 holds the results of expression                                         */
            /*      combine <<< p block ~~~ p comps                                        */
            /*                                                                             */
            /* we use v32 to iterate over v30 and                                          */
            /* v31 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v32 = v30;
            while (v32 != NULL) {
               if (abs(tbl_closed(i, j) - (((380 + v32->item.alg_energy) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v28=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v28->next = NULL;
                  v28->last = v28;
                  v28->item.alg_energy = ((380 + v32->item.alg_energy) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v28->item.alg_enum = new_Ml_s(i+1, i+2, v32->item.alg_enum, j-1, j);
               }
               else {
                  v28 = NULL;
               }
               /* ------------------------ v31 = v28 ++ v31 ----------------------- */
               if (v28 == NULL) {
               } else 
               if (v31 == NULL) {
                  v31 = v28;
               }
               else {
                  v28->last->next = v31;
                  v28->last = v31->last;
                  v31 = v28;
               }
               v32 = v32->next;
            }
         }
         else {
            v31 = NULL;
         }
         /*  v31 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         v33 = v31;
      }
      else {
         v33 = NULL;
      }
      /* ---------------------------- v34 = v27 ++ v33 ---------------------------- */
      if (v27 == NULL) {
         v34 = v33;
      } else 
      if (v33 == NULL) {
         v34 = v27;
      }
      else {
         v27->last->next = v33;
         v27->last = v33->last;
         v34 = v27;
      }
      /* ---------------------------- v35 = v21 ++ v34 ---------------------------- */
      if (v21 == NULL) {
         v35 = v34;
      } else 
      if (v34 == NULL) {
         v35 = v21;
      }
      else {
         v21->last->next = v34;
         v21->last = v34->last;
         v35 = v21;
      }
      /* ---------------------------- v36 = v12 ++ v35 ---------------------------- */
      if (v12 == NULL) {
         v36 = v35;
      } else 
      if (v35 == NULL) {
         v36 = v12;
      }
      else {
         v12->last->next = v35;
         v12->last = v35->last;
         v36 = v12;
      }
      /* ---------------------------- v37 = v3 ++ v36 ----------------------------- */
      if (v3 == NULL) {
         v37 = v36;
      } else 
      if (v36 == NULL) {
         v37 = v3;
      }
      else {
         v3->last->next = v36;
         v3->last = v36->last;
         v37 = v3;
      }
      v38 = v37;
   }
   else {
      v38 = NULL;
   }
   /* ------------------------------ v39 = v2 ++ v38 ------------------------------ */
   if (v2 == NULL) {
      v39 = v38;
   } else 
   if (v38 == NULL) {
      v39 = v2;
   }
   else {
      v2->last->next = v38;
      v2->last = v38->last;
      v39 = v2;
   }
   /* ----------------------------- v41 = minimum(v39) ---------------------------- */
   v41 = 1.0e7;
   v40 = v39;
   while (v40 != NULL) {
      v41 = v41 < v40->item.alg_energy ? v41 : v40->item.alg_energy;
      v40 = v40->next;
   }
   v40 = v39;
   v43 = NULL;
   while (v40 != NULL) {
      if (abs(v41 - v40->item.alg_energy) <= diff) {
         update_str_Signature(v40->item.alg_enum->item, diff - abs(v41 - v40->item.alg_energy));
         v42=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v42->item = v40->item;
         v42->next = NULL;
         v42->last = v42;
         /* --------------------------- v43 = v42 ++ v43 -------------------------- */
         if (v42 == NULL) {
         } else 
         if (v43 == NULL) {
            v43 = v42;
         }
         else {
            v42->last->next = v43;
            v42->last = v43->last;
            v43 = v42;
         }
      }
      v40 = v40->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v44 = v43;
   v45 = NULL;
   while (v44 != NULL) {
      /* -------------------- v45 = v44->item.alg_enum ++ v45 --------------------- */
      if (v44->item.alg_enum == NULL) {
      } else 
      if (v45 == NULL) {
         v45 = v44->item.alg_enum;
      }
      else {
         v44->item.alg_enum->last->next = v45;
         v44->item.alg_enum->last = v45->last;
         v45 = v44->item.alg_enum;
      }
      v44 = v44->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v45)));
}

/* backtracing code for production closed_Pr                                        */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_closed_Pr(int i, int j, int diff)
{
   struct str3 *v49;
   int v9, v18, v24, v45;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v10, *v11, *v12;
   struct str5 *v13, *v14, *v15, *v16, *v17, *v19, *v20, *v21, *v22, *v23, *v25;
   struct str5 *v26, *v27, *v28, *v29, *v30, *v31, *v32, *v33, *v34, *v35, *v36;
   struct str5 *v37, *v38, *v39, *v40, *v41, *v42, *v43, *v44, *v46, *v47, *v48;
   int k, k2, k3, k4, k5, k6, k7;

   if (basepairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /* -------------- v1 = sr <<< lbase ~~~ p closed_Pr ~~~ lbase --------------- */
      if ((j-i) >= 24) {
         if (abs(tbl_closed_Pr(i, j) - (tbl_closed_Pr(i+1, j-1) + sr_energy(i+1, j))) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = tbl_closed_Pr(i+1, j-1) + sr_energy(i+1, j);
            v1->item.alg_enum = new_Sr_f(i+1, back_closed_Pr, i+1, j-1, j);
         }
         else {
            v1 = NULL;
         }
      }
      else {
         v1 = NULL;
      }
      /* -------------- v1 = sr <<< lbase ~~~ p closed_Pr ~~~ lbase --------------- */
      /* -------------------------------- finished -------------------------------- */

      v2 = v1;
   }
   else {
      v2 = NULL;
   }
   if (stackpairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /*  v7 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 27) {
         v7 = NULL;
         for (k=i+3; k<=j-24; k++) {
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v4 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            if (abs(tbl_closed_Pr(i, j) - (((tbl_closed_Pr(k, j-2) + termaupenalty((k) + 1, j-2)) + bl_energy(i+2, i+2, k, j-1)) + sr_energy(i+1, j))) <= diff) {
               v4=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v4->next = NULL;
               v4->last = v4;
               v4->item.alg_energy = tbl_closed_Pr(k, j-2) + termaupenalty((k) + 1, j-2);
               v4->item.alg_enum = new_Is_f(k, back_closed_Pr, k, j-2, j-2);
            }
            else {
               v4 = NULL;
            }
            /* ------------- v4 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            /* ----------------------------- finished ----------------------------- */

            v5 = NULL;
            /* +------------------------------------------------------------------------- */
            /* v3 stores the result of a single application of algebra function           */
            /* v4 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                    */
            /*                                                                            */
            /* we use v6 to iterate over v4 and                                           */
            /* v5 to collect the results                                                  */
            /* +------------------------------------------------------------------------- */
            v6 = v4;
            while (v6 != NULL) {
               if (abs(tbl_closed_Pr(i, j) - ((v6->item.alg_energy + bl_energy(i+2, i+2, k, j-1)) + sr_energy(i+1, j))) <= diff) {
                  v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v3->next = NULL;
                  v3->last = v3;
                  v3->item.alg_energy = (v6->item.alg_energy + bl_energy(i+2, i+2, k, j-1)) + sr_energy(i+1, j);
                  v3->item.alg_enum = new_Bl_s(i+1, i+2, i+2, k, v6->item.alg_enum, j-1, j);
               }
               else {
                  v3 = NULL;
               }
               /* ------------------------- v5 = v3 ++ v5 ------------------------- */
               if (v3 == NULL) {
               } else 
               if (v5 == NULL) {
                  v5 = v3;
               }
               else {
                  v3->last->next = v5;
                  v3->last = v5->last;
                  v5 = v3;
               }
               v6 = v6->next;
            }
            /* -------------------------- v7 = v5 ++ v7 --------------------------- */
            if (v5 == NULL) {
            } else 
            if (v7 == NULL) {
               v7 = v5;
            }
            else {
               v5->last->next = v7;
               v5->last = v7->last;
               v7 = v5;
            }
         }
      }
      else {
         v7 = NULL;
      }
      /*  v7 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* ---------------------------- v9 = minimum(v7) ---------------------------- */
      v9 = 1.0e7;
      v8 = v7;
      while (v8 != NULL) {
         v9 = v9 < v8->item.alg_energy ? v9 : v8->item.alg_energy;
         v8 = v8->next;
      }
      v8 = v7;
      v11 = NULL;
      while (v8 != NULL) {
         if (abs(v9 - v8->item.alg_energy) <= diff) {
            update_str_Signature(v8->item.alg_enum->item, diff - abs(v9 - v8->item.alg_energy));
            v10=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v10->item = v8->item;
            v10->next = NULL;
            v10->last = v10;
            /* ------------------------- v11 = v10 ++ v11 ------------------------- */
            if (v10 == NULL) {
            } else 
            if (v11 == NULL) {
               v11 = v10;
            }
            else {
               v10->last->next = v11;
               v10->last = v11->last;
               v11 = v10;
            }
         }
         v8 = v8->next;
      }
      /* -------------------------------- start of -------------------------------- */
      /*  v16 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 27) {
         v16 = NULL;
         for (k2=i+24; k2<=j-3; k2++) {
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v13 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            if (abs(tbl_closed_Pr(i, j) - (((tbl_closed_Pr(i+2, k2) + termaupenalty((i+2) + 1, k2)) + br_energy(i+2, k2, j-2, j-1)) + sr_energy(i+1, j))) <= diff) {
               v13=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v13->next = NULL;
               v13->last = v13;
               v13->item.alg_energy = tbl_closed_Pr(i+2, k2) + termaupenalty((i+2) + 1, k2);
               v13->item.alg_enum = new_Is_f(i+2, back_closed_Pr, i+2, k2, k2);
            }
            else {
               v13 = NULL;
            }
            /* ------------- v13 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            /* ----------------------------- finished ----------------------------- */

            v14 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v12 stores the result of a single application of algebra function           */
            /* v13 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                     */
            /*                                                                             */
            /* we use v15 to iterate over v13 and                                          */
            /* v14 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v15 = v13;
            while (v15 != NULL) {
               if (abs(tbl_closed_Pr(i, j) - ((v15->item.alg_energy + br_energy(i+2, k2, j-2, j-1)) + sr_energy(i+1, j))) <= diff) {
                  v12=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v12->next = NULL;
                  v12->last = v12;
                  v12->item.alg_energy = (v15->item.alg_energy + br_energy(i+2, k2, j-2, j-1)) + sr_energy(i+1, j);
                  v12->item.alg_enum = new_Br_s(i+1, i+2, v15->item.alg_enum, k2, j-2, j-1, j);
               }
               else {
                  v12 = NULL;
               }
               /* ------------------------ v14 = v12 ++ v14 ----------------------- */
               if (v12 == NULL) {
               } else 
               if (v14 == NULL) {
                  v14 = v12;
               }
               else {
                  v12->last->next = v14;
                  v12->last = v14->last;
                  v14 = v12;
               }
               v15 = v15->next;
            }
            /* ------------------------- v16 = v14 ++ v16 ------------------------- */
            if (v14 == NULL) {
            } else 
            if (v16 == NULL) {
               v16 = v14;
            }
            else {
               v14->last->next = v16;
               v14->last = v16->last;
               v16 = v14;
            }
         }
      }
      else {
         v16 = NULL;
      }
      /*  v16 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* --------------------------- v18 = minimum(v16) --------------------------- */
      v18 = 1.0e7;
      v17 = v16;
      while (v17 != NULL) {
         v18 = v18 < v17->item.alg_energy ? v18 : v17->item.alg_energy;
         v17 = v17->next;
      }
      v17 = v16;
      v20 = NULL;
      while (v17 != NULL) {
         if (abs(v18 - v17->item.alg_energy) <= diff) {
            update_str_Signature(v17->item.alg_enum->item, diff - abs(v18 - v17->item.alg_energy));
            v19=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v19->item = v17->item;
            v19->next = NULL;
            v19->last = v19;
            /* ------------------------- v20 = v19 ++ v20 ------------------------- */
            if (v19 == NULL) {
            } else 
            if (v20 == NULL) {
               v20 = v19;
            }
            else {
               v19->last->next = v20;
               v19->last = v20->last;
               v20 = v19;
            }
         }
         v17 = v17->next;
      }
      /* -------------------------------- start of -------------------------------- */
      /*  v22 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed_Pr ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 28) {
         v22 = NULL;
         for (k4=max(i+25, j-32); k4<=j-3; k4++) {
            for (k3=i+3; k3<=min(i+34, k4-22); k3++) {
               if (abs(tbl_closed_Pr(i, j) - ((tbl_closed_Pr(k3, k4) + sr_energy(i+1, j)) + il_energy(i+2, k3, k4, j-2))) <= diff) {
                  v21=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v21->next = NULL;
                  v21->last = v21;
                  v21->item.alg_energy = (tbl_closed_Pr(k3, k4) + sr_energy(i+1, j)) + il_energy(i+2, k3, k4, j-2);
                  v21->item.alg_enum = new_Il_f(i+1, i+2, i+2, k3, back_closed_Pr, k3, k4, k4, j-2, j-1, j);
               }
               else {
                  v21 = NULL;
               }
               /* ------------------------ v22 = v21 ++ v22 ----------------------- */
               if (v21 == NULL) {
               } else 
               if (v22 == NULL) {
                  v22 = v21;
               }
               else {
                  v21->last->next = v22;
                  v21->last = v22->last;
                  v22 = v21;
               }
            }
         }
      }
      else {
         v22 = NULL;
      }
      /*  v22 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed_Pr ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* --------------------------- v24 = minimum(v22) --------------------------- */
      v24 = 1.0e7;
      v23 = v22;
      while (v23 != NULL) {
         v24 = v24 < v23->item.alg_energy ? v24 : v23->item.alg_energy;
         v23 = v23->next;
      }
      v23 = v22;
      v26 = NULL;
      while (v23 != NULL) {
         if (abs(v24 - v23->item.alg_energy) <= diff) {
            update_str_Signature(v23->item.alg_enum->item, diff - abs(v24 - v23->item.alg_energy));
            v25=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v25->item = v23->item;
            v25->next = NULL;
            v25->last = v25;
            /* ------------------------- v26 = v25 ++ v26 ------------------------- */
            if (v25 == NULL) {
            } else 
            if (v26 == NULL) {
               v26 = v25;
            }
            else {
               v25->last->next = v26;
               v25->last = v26->last;
               v26 = v25;
            }
         }
         v23 = v23->next;
      }
      if (stackpairing(i, j)) {
         /* ------------------------------- start of ------------------------------ */
         /*  v36 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 22) {
            /* ----------------------------- start of ----------------------------- */
            /* ----------- v29 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            if ((j-i-4) >= 22) {
               v29 = NULL;
               for (k5=i+13; k5<=j-13; k5++) {
                  if (abs(tbl_closed_Pr(i, j) - (((380 + (tbl_block_Pr(i+2, k5) + tbl_comps_Pr(k5, j-2))) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                     v28=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v28->next = NULL;
                     v28->last = v28;
                     v28->item.alg_energy = tbl_block_Pr(i+2, k5) + tbl_comps_Pr(k5, j-2);
                     v28->item.alg_enum = new_Combine_ff(back_block_Pr, i+2, k5, back_comps_Pr, k5, j-2);
                  }
                  else {
                     v28 = NULL;
                  }
                  /* ---------------------- v29 = v28 ++ v29 ---------------------- */
                  if (v28 == NULL) {
                  } else 
                  if (v29 == NULL) {
                     v29 = v28;
                  }
                  else {
                     v28->last->next = v29;
                     v28->last = v29->last;
                     v29 = v28;
                  }
               }
            }
            else {
               v29 = NULL;
            }
            /* ----------- v29 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v31 = combine <<< p block ~~~ p comps_Pr ------------- */
            v31 = NULL;
            for (k6=i+9; k6<=j-13; k6++) {
               if (abs(tbl_closed_Pr(i, j) - (((380 + (tbl_block(i+2, k6) + tbl_comps_Pr(k6, j-2))) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v30=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v30->next = NULL;
                  v30->last = v30;
                  v30->item.alg_energy = tbl_block(i+2, k6) + tbl_comps_Pr(k6, j-2);
                  v30->item.alg_enum = new_Combine_ff(back_block, i+2, k6, back_comps_Pr, k6, j-2);
               }
               else {
                  v30 = NULL;
               }
               /* ------------------------ v31 = v30 ++ v31 ----------------------- */
               if (v30 == NULL) {
               } else 
               if (v31 == NULL) {
                  v31 = v30;
               }
               else {
                  v30->last->next = v31;
                  v30->last = v31->last;
                  v31 = v30;
               }
            }
            /* ------------- v31 = combine <<< p block ~~~ p comps_Pr ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v33 = combine <<< p block_Pr ~~~ p comps ------------- */
            v33 = NULL;
            for (k7=i+13; k7<=j-9; k7++) {
               if (abs(tbl_closed_Pr(i, j) - (((380 + (tbl_block_Pr(i+2, k7) + tbl_comps(k7, j-2))) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v32=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v32->next = NULL;
                  v32->last = v32;
                  v32->item.alg_energy = tbl_block_Pr(i+2, k7) + tbl_comps(k7, j-2);
                  v32->item.alg_enum = new_Combine_ff(back_block_Pr, i+2, k7, back_comps, k7, j-2);
               }
               else {
                  v32 = NULL;
               }
               /* ------------------------ v33 = v32 ++ v33 ----------------------- */
               if (v32 == NULL) {
               } else 
               if (v33 == NULL) {
                  v33 = v32;
               }
               else {
                  v32->last->next = v33;
                  v32->last = v33->last;
                  v33 = v32;
               }
            }
            /* ------------- v33 = combine <<< p block_Pr ~~~ p comps ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ------------------------- v34 = v31 ++ v33 ------------------------- */
            if (v31 == NULL) {
               v34 = v33;
            } else 
            if (v33 == NULL) {
               v34 = v31;
            }
            else {
               v31->last->next = v33;
               v31->last = v33->last;
               v34 = v31;
            }
            /* ------------------------- v35 = v29 ++ v34 ------------------------- */
            if (v29 == NULL) {
               v35 = v34;
            } else 
            if (v34 == NULL) {
               v35 = v29;
            }
            else {
               v29->last->next = v34;
               v29->last = v34->last;
               v35 = v29;
            }
            v36 = NULL;
            /* +--------------------------------------------------------------------------------------------------------------------------------- */
            /* v27 stores the result of a single application of algebra function                                                                  */
            /* v35 holds the results of expression                                                                                                */
            /*      combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps           */
            /*                                                                                                                                    */
            /* we use v37 to iterate over v35 and                                                                                                 */
            /* v36 to collect the results                                                                                                         */
            /* +--------------------------------------------------------------------------------------------------------------------------------- */
            v37 = v35;
            while (v37 != NULL) {
               if (abs(tbl_closed_Pr(i, j) - (((380 + v37->item.alg_energy) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v27=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v27->next = NULL;
                  v27->last = v27;
                  v27->item.alg_energy = ((380 + v37->item.alg_energy) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v27->item.alg_enum = new_Ml_s(i+1, i+2, v37->item.alg_enum, j-1, j);
               }
               else {
                  v27 = NULL;
               }
               /* ------------------------ v36 = v27 ++ v36 ----------------------- */
               if (v27 == NULL) {
               } else 
               if (v36 == NULL) {
                  v36 = v27;
               }
               else {
                  v27->last->next = v36;
                  v27->last = v36->last;
                  v36 = v27;
               }
               v37 = v37->next;
            }
         }
         else {
            v36 = NULL;
         }
         /*  v36 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         v38 = v36;
      }
      else {
         v38 = NULL;
      }
      /* ---------------------------- v39 = v26 ++ v38 ---------------------------- */
      if (v26 == NULL) {
         v39 = v38;
      } else 
      if (v38 == NULL) {
         v39 = v26;
      }
      else {
         v26->last->next = v38;
         v26->last = v38->last;
         v39 = v26;
      }
      /* ---------------------------- v40 = v20 ++ v39 ---------------------------- */
      if (v20 == NULL) {
         v40 = v39;
      } else 
      if (v39 == NULL) {
         v40 = v20;
      }
      else {
         v20->last->next = v39;
         v20->last = v39->last;
         v40 = v20;
      }
      /* ---------------------------- v41 = v11 ++ v40 ---------------------------- */
      if (v11 == NULL) {
         v41 = v40;
      } else 
      if (v40 == NULL) {
         v41 = v11;
      }
      else {
         v11->last->next = v40;
         v11->last = v40->last;
         v41 = v11;
      }
      v42 = v41;
   }
   else {
      v42 = NULL;
   }
   /* ------------------------------ v43 = v2 ++ v42 ------------------------------ */
   if (v2 == NULL) {
      v43 = v42;
   } else 
   if (v42 == NULL) {
      v43 = v2;
   }
   else {
      v2->last->next = v42;
      v2->last = v42->last;
      v43 = v2;
   }
   /* ----------------------------- v45 = minimum(v43) ---------------------------- */
   v45 = 1.0e7;
   v44 = v43;
   while (v44 != NULL) {
      v45 = v45 < v44->item.alg_energy ? v45 : v44->item.alg_energy;
      v44 = v44->next;
   }
   v44 = v43;
   v47 = NULL;
   while (v44 != NULL) {
      if (abs(v45 - v44->item.alg_energy) <= diff) {
         update_str_Signature(v44->item.alg_enum->item, diff - abs(v45 - v44->item.alg_energy));
         v46=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v46->item = v44->item;
         v46->next = NULL;
         v46->last = v46;
         /* --------------------------- v47 = v46 ++ v47 -------------------------- */
         if (v46 == NULL) {
         } else 
         if (v47 == NULL) {
            v47 = v46;
         }
         else {
            v46->last->next = v47;
            v46->last = v47->last;
            v47 = v46;
         }
      }
      v44 = v44->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v48 = v47;
   v49 = NULL;
   while (v48 != NULL) {
      /* -------------------- v49 = v48->item.alg_enum ++ v49 --------------------- */
      if (v48->item.alg_enum == NULL) {
      } else 
      if (v49 == NULL) {
         v49 = v48->item.alg_enum;
      }
      else {
         v48->item.alg_enum->last->next = v49;
         v48->item.alg_enum->last = v49->last;
         v49 = v48->item.alg_enum;
      }
      v48 = v48->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v49)));
}

/* backtracing code for production comps                                            */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_comps(int i, int j, int diff)
{
   struct str3 *v13;
   int v9;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v10, *v11, *v12;
   int k, k2;

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v2 = cons <<< p block ~~~ p comps --------------------- */
   if ((j-i) >= 14) {
      v2 = NULL;
      for (k=i+7; k<=j-7; k++) {
         if (abs(tbl_comps(i, j) - (tbl_block(i, k) + tbl_comps(k, j))) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = tbl_block(i, k) + tbl_comps(k, j);
            v1->item.alg_enum = new_Cons_ff(back_block, i, k, back_comps, k, j);
         }
         else {
            v1 = NULL;
         }
         /* ---------------------------- v2 = v1 ++ v2 ---------------------------- */
         if (v1 == NULL) {
         } else 
         if (v2 == NULL) {
            v2 = v1;
         }
         else {
            v1->last->next = v2;
            v1->last = v2->last;
            v2 = v1;
         }
      }
   }
   else {
      v2 = NULL;
   }
   /* --------------------- v2 = cons <<< p block ~~~ p comps --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* -------------------------------- v3 = p block ------------------------------- */
   /* +---------------------------------------------------------------------------- */
   /* Nonterminal block is implemented as a tabulated                               */
   /* function which yields atomar results. Since we are in list context,           */
   /* we need to wrap the result of block into a single list element.               */
   /* +---------------------------------------------------------------------------- */
   if ((j-i) >= 7) {
      v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
      v3->item.alg_energy = tbl_block(i, j);
      v3->item.alg_enum = new__NTID(back_block, i, j);
      v3->next = NULL;
      v3->last = v3;
   }
   else {
      v3 = NULL;
   }
   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v5 = addss <<< p block ~~~ region --------------------- */
   if ((j-i) >= 8) {
      v5 = NULL;
      for (k2=i+7; k2<=j-1; k2++) {
         if (abs(tbl_comps(i, j) - (tbl_block(i, k2) + ss_energy(k2, j))) <= diff) {
            v4=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v4->next = NULL;
            v4->last = v4;
            v4->item.alg_energy = tbl_block(i, k2) + ss_energy(k2, j);
            v4->item.alg_enum = new_Addss_f(back_block, i, k2, k2, j);
         }
         else {
            v4 = NULL;
         }
         /* ---------------------------- v5 = v4 ++ v5 ---------------------------- */
         if (v4 == NULL) {
         } else 
         if (v5 == NULL) {
            v5 = v4;
         }
         else {
            v4->last->next = v5;
            v4->last = v5->last;
            v5 = v4;
         }
      }
   }
   else {
      v5 = NULL;
   }
   /* --------------------- v5 = addss <<< p block ~~~ region --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------- v6 = v3 ++ v5 ------------------------------- */
   if (v3 == NULL) {
      v6 = v5;
   } else 
   if (v5 == NULL) {
      v6 = v3;
   }
   else {
      v3->last->next = v5;
      v3->last = v5->last;
      v6 = v3;
   }
   /* ------------------------------- v7 = v2 ++ v6 ------------------------------- */
   if (v2 == NULL) {
      v7 = v6;
   } else 
   if (v6 == NULL) {
      v7 = v2;
   }
   else {
      v2->last->next = v6;
      v2->last = v6->last;
      v7 = v2;
   }
   /* ------------------------------ v9 = minimum(v7) ----------------------------- */
   v9 = 1.0e7;
   v8 = v7;
   while (v8 != NULL) {
      v9 = v9 < v8->item.alg_energy ? v9 : v8->item.alg_energy;
      v8 = v8->next;
   }
   v8 = v7;
   v11 = NULL;
   while (v8 != NULL) {
      if (abs(v9 - v8->item.alg_energy) <= diff) {
         update_str_Signature(v8->item.alg_enum->item, diff - abs(v9 - v8->item.alg_energy));
         v10=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v10->item = v8->item;
         v10->next = NULL;
         v10->last = v10;
         /* --------------------------- v11 = v10 ++ v11 -------------------------- */
         if (v10 == NULL) {
         } else 
         if (v11 == NULL) {
            v11 = v10;
         }
         else {
            v10->last->next = v11;
            v10->last = v11->last;
            v11 = v10;
         }
      }
      v8 = v8->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v12 = v11;
   v13 = NULL;
   while (v12 != NULL) {
      /* -------------------- v13 = v12->item.alg_enum ++ v13 --------------------- */
      if (v12->item.alg_enum == NULL) {
      } else 
      if (v13 == NULL) {
         v13 = v12->item.alg_enum;
      }
      else {
         v12->item.alg_enum->last->next = v13;
         v12->item.alg_enum->last = v13->last;
         v13 = v12->item.alg_enum;
      }
      v12 = v12->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v13)));
}

/* backtracing code for production comps_Pr                                         */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_comps_Pr(int i, int j, int diff)
{
   struct str3 *v19;
   int v15;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8;
   struct str5 *v9, *v10, *v11, *v12, *v13, *v14, *v16, *v17, *v18;
   int k, k2, k3, k4;

   /* ---------------------------------- start of --------------------------------- */
   /* -------------------- v2 = cons <<< p block ~~~ p comps_Pr ------------------- */
   if ((j-i) >= 18) {
      v2 = NULL;
      for (k=i+7; k<=j-11; k++) {
         if (abs(tbl_comps_Pr(i, j) - (tbl_block(i, k) + tbl_comps_Pr(k, j))) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = tbl_block(i, k) + tbl_comps_Pr(k, j);
            v1->item.alg_enum = new_Cons_ff(back_block, i, k, back_comps_Pr, k, j);
         }
         else {
            v1 = NULL;
         }
         /* ---------------------------- v2 = v1 ++ v2 ---------------------------- */
         if (v1 == NULL) {
         } else 
         if (v2 == NULL) {
            v2 = v1;
         }
         else {
            v1->last->next = v2;
            v1->last = v2->last;
            v2 = v1;
         }
      }
   }
   else {
      v2 = NULL;
   }
   /* -------------------- v2 = cons <<< p block ~~~ p comps_Pr ------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* -------------------- v4 = cons <<< p block_Pr ~~~ p comps ------------------- */
   if ((j-i) >= 18) {
      v4 = NULL;
      for (k2=i+11; k2<=j-7; k2++) {
         if (abs(tbl_comps_Pr(i, j) - (tbl_block_Pr(i, k2) + tbl_comps(k2, j))) <= diff) {
            v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v3->next = NULL;
            v3->last = v3;
            v3->item.alg_energy = tbl_block_Pr(i, k2) + tbl_comps(k2, j);
            v3->item.alg_enum = new_Cons_ff(back_block_Pr, i, k2, back_comps, k2, j);
         }
         else {
            v3 = NULL;
         }
         /* ---------------------------- v4 = v3 ++ v4 ---------------------------- */
         if (v3 == NULL) {
         } else 
         if (v4 == NULL) {
            v4 = v3;
         }
         else {
            v3->last->next = v4;
            v3->last = v4->last;
            v4 = v3;
         }
      }
   }
   else {
      v4 = NULL;
   }
   /* -------------------- v4 = cons <<< p block_Pr ~~~ p comps ------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------ v6 = cons <<< p block_Pr ~~~ p comps_Pr ------------------ */
   if ((j-i) >= 22) {
      v6 = NULL;
      for (k3=i+11; k3<=j-11; k3++) {
         if (abs(tbl_comps_Pr(i, j) - (tbl_block_Pr(i, k3) + tbl_comps_Pr(k3, j))) <= diff) {
            v5=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v5->next = NULL;
            v5->last = v5;
            v5->item.alg_energy = tbl_block_Pr(i, k3) + tbl_comps_Pr(k3, j);
            v5->item.alg_enum = new_Cons_ff(back_block_Pr, i, k3, back_comps_Pr, k3, j);
         }
         else {
            v5 = NULL;
         }
         /* ---------------------------- v6 = v5 ++ v6 ---------------------------- */
         if (v5 == NULL) {
         } else 
         if (v6 == NULL) {
            v6 = v5;
         }
         else {
            v5->last->next = v6;
            v5->last = v6->last;
            v6 = v5;
         }
      }
   }
   else {
      v6 = NULL;
   }
   /* ------------------ v6 = cons <<< p block_Pr ~~~ p comps_Pr ------------------ */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------ v7 = p block_Pr ------------------------------ */
   /* +---------------------------------------------------------------------------- */
   /* Nonterminal block_Pr is implemented as a tabulated                            */
   /* function which yields atomar results. Since we are in list context,           */
   /* we need to wrap the result of block_Pr into a single list element.            */
   /* +---------------------------------------------------------------------------- */
   if ((j-i) >= 11) {
      v7=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
      v7->item.alg_energy = tbl_block_Pr(i, j);
      v7->item.alg_enum = new__NTID(back_block_Pr, i, j);
      v7->next = NULL;
      v7->last = v7;
   }
   else {
      v7 = NULL;
   }
   /* ---------------------------------- start of --------------------------------- */
   /* -------------------- v9 = addss <<< p block_Pr ~~~ region ------------------- */
   if ((j-i) >= 12) {
      v9 = NULL;
      for (k4=i+11; k4<=j-1; k4++) {
         if (abs(tbl_comps_Pr(i, j) - (tbl_block_Pr(i, k4) + ss_energy(k4, j))) <= diff) {
            v8=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v8->next = NULL;
            v8->last = v8;
            v8->item.alg_energy = tbl_block_Pr(i, k4) + ss_energy(k4, j);
            v8->item.alg_enum = new_Addss_f(back_block_Pr, i, k4, k4, j);
         }
         else {
            v8 = NULL;
         }
         /* ---------------------------- v9 = v8 ++ v9 ---------------------------- */
         if (v8 == NULL) {
         } else 
         if (v9 == NULL) {
            v9 = v8;
         }
         else {
            v8->last->next = v9;
            v8->last = v9->last;
            v9 = v8;
         }
      }
   }
   else {
      v9 = NULL;
   }
   /* -------------------- v9 = addss <<< p block_Pr ~~~ region ------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------- v10 = v7 ++ v9 ------------------------------ */
   if (v7 == NULL) {
      v10 = v9;
   } else 
   if (v9 == NULL) {
      v10 = v7;
   }
   else {
      v7->last->next = v9;
      v7->last = v9->last;
      v10 = v7;
   }
   /* ------------------------------ v11 = v6 ++ v10 ------------------------------ */
   if (v6 == NULL) {
      v11 = v10;
   } else 
   if (v10 == NULL) {
      v11 = v6;
   }
   else {
      v6->last->next = v10;
      v6->last = v10->last;
      v11 = v6;
   }
   /* ------------------------------ v12 = v4 ++ v11 ------------------------------ */
   if (v4 == NULL) {
      v12 = v11;
   } else 
   if (v11 == NULL) {
      v12 = v4;
   }
   else {
      v4->last->next = v11;
      v4->last = v11->last;
      v12 = v4;
   }
   /* ------------------------------ v13 = v2 ++ v12 ------------------------------ */
   if (v2 == NULL) {
      v13 = v12;
   } else 
   if (v12 == NULL) {
      v13 = v2;
   }
   else {
      v2->last->next = v12;
      v2->last = v12->last;
      v13 = v2;
   }
   /* ----------------------------- v15 = minimum(v13) ---------------------------- */
   v15 = 1.0e7;
   v14 = v13;
   while (v14 != NULL) {
      v15 = v15 < v14->item.alg_energy ? v15 : v14->item.alg_energy;
      v14 = v14->next;
   }
   v14 = v13;
   v17 = NULL;
   while (v14 != NULL) {
      if (abs(v15 - v14->item.alg_energy) <= diff) {
         update_str_Signature(v14->item.alg_enum->item, diff - abs(v15 - v14->item.alg_energy));
         v16=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v16->item = v14->item;
         v16->next = NULL;
         v16->last = v16;
         /* --------------------------- v17 = v16 ++ v17 -------------------------- */
         if (v16 == NULL) {
         } else 
         if (v17 == NULL) {
            v17 = v16;
         }
         else {
            v16->last->next = v17;
            v16->last = v17->last;
            v17 = v16;
         }
      }
      v14 = v14->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v18 = v17;
   v19 = NULL;
   while (v18 != NULL) {
      /* -------------------- v19 = v18->item.alg_enum ++ v19 --------------------- */
      if (v18->item.alg_enum == NULL) {
      } else 
      if (v19 == NULL) {
         v19 = v18->item.alg_enum;
      }
      else {
         v18->item.alg_enum->last->next = v19;
         v18->item.alg_enum->last = v19->last;
         v19 = v18->item.alg_enum;
      }
      v18 = v18->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v19)));
}

/* backtracing code for production block                                            */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_block(int i, int j, int diff)
{
   struct str3 *v22;
   int v18;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10;
   struct str5 *v11, *v12, *v13, *v14, *v15, *v16, *v17, *v19, *v20, *v21;
   int k;

   /* ---------------------------------- start of --------------------------------- */
   /* ------------ v6 = ul <<< drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------- v4 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v3 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      if (abs(tbl_block(i, j) - (40 + (tbl_closed(i, j) + termaupenalty((i) + 1, j)))) <= diff) {
         v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v3->next = NULL;
         v3->last = v3;
         v3->item.alg_energy = tbl_closed(i, j) + termaupenalty((i) + 1, j);
         v3->item.alg_enum = new_Is_f(i, back_closed, i, j, j);
      }
      else {
         v3 = NULL;
      }
      /* ------------------ v3 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v4 = NULL;
      /* +------------------------------------------------------------------------- */
      /* v2 stores the result of a single application of algebra function           */
      /* v3 holds the results of expression                                         */
      /*      is <<< loc ~~~ p closed ~~~ loc                                       */
      /*                                                                            */
      /* we use v5 to iterate over v3 and                                           */
      /* v4 to collect the results                                                  */
      /* +------------------------------------------------------------------------- */
      v5 = v3;
      while (v5 != NULL) {
         if (abs(tbl_block(i, j) - (40 + v5->item.alg_energy)) <= diff) {
            v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v2->next = NULL;
            v2->last = v2;
            v2->item.alg_energy = v5->item.alg_energy;
            v2->item.alg_enum = new_Drem_s(v5->item.alg_enum);
         }
         else {
            v2 = NULL;
         }
         /* ---------------------------- v4 = v2 ++ v4 ---------------------------- */
         if (v2 == NULL) {
         } else 
         if (v4 == NULL) {
            v4 = v2;
         }
         else {
            v2->last->next = v4;
            v2->last = v4->last;
            v4 = v2;
         }
         v5 = v5->next;
      }
      /* ------------- v4 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- finished -------------------------------- */

      v6 = NULL;
      /* +------------------------------------------------------------------------- */
      /* v1 stores the result of a single application of algebra function           */
      /* v4 holds the results of expression                                         */
      /*      drem <<< is <<< loc ~~~ p closed ~~~ loc                              */
      /*                                                                            */
      /* we use v7 to iterate over v4 and                                           */
      /* v6 to collect the results                                                  */
      /* +------------------------------------------------------------------------- */
      v7 = v4;
      while (v7 != NULL) {
         if (abs(tbl_block(i, j) - (40 + v7->item.alg_energy)) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = 40 + v7->item.alg_energy;
            v1->item.alg_enum = new_Ul_s(v7->item.alg_enum);
         }
         else {
            v1 = NULL;
         }
         /* ---------------------------- v6 = v1 ++ v6 ---------------------------- */
         if (v1 == NULL) {
         } else 
         if (v6 == NULL) {
            v6 = v1;
         }
         else {
            v1->last->next = v6;
            v1->last = v6->last;
            v6 = v1;
         }
         v7 = v7->next;
      }
   }
   else {
      v6 = NULL;
   }
   /* ------------ v6 = ul <<< drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --- v15 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed ~~~ loc) --- */
   if ((j-i) >= 8) {
      v15 = NULL;
      for (k=i+1; k<=j-7; k++) {
         /* ------------------------------- start of ------------------------------ */
         /* ------------ v11 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
         /* ------------------------------- start of ------------------------------ */
         /* ---------------- v10 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         if (abs(tbl_block(i, j) - ((40 + (tbl_closed(k, j) + termaupenalty((k) + 1, j))) + ss_energy(i, k))) <= diff) {
            v10=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v10->next = NULL;
            v10->last = v10;
            v10->item.alg_energy = tbl_closed(k, j) + termaupenalty((k) + 1, j);
            v10->item.alg_enum = new_Is_f(k, back_closed, k, j, j);
         }
         else {
            v10 = NULL;
         }
         /* ---------------- v10 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v11 = NULL;
         /* +------------------------------------------------------------------------- */
         /* v9 stores the result of a single application of algebra function           */
         /* v10 holds the results of expression                                        */
         /*      is <<< loc ~~~ p closed ~~~ loc                                       */
         /*                                                                            */
         /* we use v12 to iterate over v10 and                                         */
         /* v11 to collect the results                                                 */
         /* +------------------------------------------------------------------------- */
         v12 = v10;
         while (v12 != NULL) {
            if (abs(tbl_block(i, j) - ((40 + v12->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v9=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v9->next = NULL;
               v9->last = v9;
               v9->item.alg_energy = v12->item.alg_energy;
               v9->item.alg_enum = new_Drem_s(v12->item.alg_enum);
            }
            else {
               v9 = NULL;
            }
            /* ------------------------- v11 = v9 ++ v11 -------------------------- */
            if (v9 == NULL) {
            } else 
            if (v11 == NULL) {
               v11 = v9;
            }
            else {
               v9->last->next = v11;
               v9->last = v11->last;
               v11 = v9;
            }
            v12 = v12->next;
         }
         /* ------------ v11 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
         /* ------------------------------- finished ------------------------------ */

         v13 = NULL;
         /* +------------------------------------------------------------------------- */
         /* v8 stores the result of a single application of algebra function           */
         /* v11 holds the results of expression                                        */
         /*      drem <<< is <<< loc ~~~ p closed ~~~ loc                              */
         /*                                                                            */
         /* we use v14 to iterate over v11 and                                         */
         /* v13 to collect the results                                                 */
         /* +------------------------------------------------------------------------- */
         v14 = v11;
         while (v14 != NULL) {
            if (abs(tbl_block(i, j) - ((40 + v14->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v8=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v8->next = NULL;
               v8->last = v8;
               v8->item.alg_energy = (40 + v14->item.alg_energy) + ss_energy(i, k);
               v8->item.alg_enum = new_Ssadd_s(i, k, v14->item.alg_enum);
            }
            else {
               v8 = NULL;
            }
            /* ------------------------- v13 = v8 ++ v13 -------------------------- */
            if (v8 == NULL) {
            } else 
            if (v13 == NULL) {
               v13 = v8;
            }
            else {
               v8->last->next = v13;
               v8->last = v13->last;
               v13 = v8;
            }
            v14 = v14->next;
         }
         /* --------------------------- v15 = v13 ++ v15 -------------------------- */
         if (v13 == NULL) {
         } else 
         if (v15 == NULL) {
            v15 = v13;
         }
         else {
            v13->last->next = v15;
            v13->last = v15->last;
            v15 = v13;
         }
      }
   }
   else {
      v15 = NULL;
   }
   /* --- v15 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed ~~~ loc) --- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------ v16 = v6 ++ v15 ------------------------------ */
   if (v6 == NULL) {
      v16 = v15;
   } else 
   if (v15 == NULL) {
      v16 = v6;
   }
   else {
      v6->last->next = v15;
      v6->last = v15->last;
      v16 = v6;
   }
   /* ----------------------------- v18 = minimum(v16) ---------------------------- */
   v18 = 1.0e7;
   v17 = v16;
   while (v17 != NULL) {
      v18 = v18 < v17->item.alg_energy ? v18 : v17->item.alg_energy;
      v17 = v17->next;
   }
   v17 = v16;
   v20 = NULL;
   while (v17 != NULL) {
      if (abs(v18 - v17->item.alg_energy) <= diff) {
         update_str_Signature(v17->item.alg_enum->item, diff - abs(v18 - v17->item.alg_energy));
         v19=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v19->item = v17->item;
         v19->next = NULL;
         v19->last = v19;
         /* --------------------------- v20 = v19 ++ v20 -------------------------- */
         if (v19 == NULL) {
         } else 
         if (v20 == NULL) {
            v20 = v19;
         }
         else {
            v19->last->next = v20;
            v19->last = v20->last;
            v20 = v19;
         }
      }
      v17 = v17->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v21 = v20;
   v22 = NULL;
   while (v21 != NULL) {
      /* -------------------- v22 = v21->item.alg_enum ++ v22 --------------------- */
      if (v21->item.alg_enum == NULL) {
      } else 
      if (v22 == NULL) {
         v22 = v21->item.alg_enum;
      }
      else {
         v21->item.alg_enum->last->next = v22;
         v21->item.alg_enum->last = v22->last;
         v22 = v21->item.alg_enum;
      }
      v21 = v21->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v22)));
}

/* backtracing code for production block_Pr                                         */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_block_Pr(int i, int j, int diff)
{
   struct str3 *v24;
   int v20;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10, *v11;
   struct str5 *v12, *v13, *v14, *v15, *v16, *v17, *v18, *v19, *v21, *v22, *v23;
   int k;

   /* ---------------------------------- start of --------------------------------- */
   /* ---------- v6 = ul <<< drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
   if ((j-i) >= 22) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------ v4 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v3 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------------- */
      if (abs(tbl_block_Pr(i, j) - (40 + (tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j)))) <= diff) {
         v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v3->next = NULL;
         v3->last = v3;
         v3->item.alg_energy = tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j);
         v3->item.alg_enum = new_Is_f(i, back_closed_Pr, i, j, j);
      }
      else {
         v3 = NULL;
      }
      /* ---------------- v3 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------------- */
      /* -------------------------------- finished -------------------------------- */

      v4 = NULL;
      /* +------------------------------------------------------------------------- */
      /* v2 stores the result of a single application of algebra function           */
      /* v3 holds the results of expression                                         */
      /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                    */
      /*                                                                            */
      /* we use v5 to iterate over v3 and                                           */
      /* v4 to collect the results                                                  */
      /* +------------------------------------------------------------------------- */
      v5 = v3;
      while (v5 != NULL) {
         if (abs(tbl_block_Pr(i, j) - (40 + v5->item.alg_energy)) <= diff) {
            v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v2->next = NULL;
            v2->last = v2;
            v2->item.alg_energy = v5->item.alg_energy;
            v2->item.alg_enum = new_Drem_s(v5->item.alg_enum);
         }
         else {
            v2 = NULL;
         }
         /* ---------------------------- v4 = v2 ++ v4 ---------------------------- */
         if (v2 == NULL) {
         } else 
         if (v4 == NULL) {
            v4 = v2;
         }
         else {
            v2->last->next = v4;
            v2->last = v4->last;
            v4 = v2;
         }
         v5 = v5->next;
      }
      /* ------------ v4 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
      /* -------------------------------- finished -------------------------------- */

      v6 = NULL;
      /* +------------------------------------------------------------------------- */
      /* v1 stores the result of a single application of algebra function           */
      /* v4 holds the results of expression                                         */
      /*      drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc                           */
      /*                                                                            */
      /* we use v7 to iterate over v4 and                                           */
      /* v6 to collect the results                                                  */
      /* +------------------------------------------------------------------------- */
      v7 = v4;
      while (v7 != NULL) {
         if (abs(tbl_block_Pr(i, j) - (40 + v7->item.alg_energy)) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = 40 + v7->item.alg_energy;
            v1->item.alg_enum = new_Ul_s(v7->item.alg_enum);
         }
         else {
            v1 = NULL;
         }
         /* ---------------------------- v6 = v1 ++ v6 ---------------------------- */
         if (v1 == NULL) {
         } else 
         if (v6 == NULL) {
            v6 = v1;
         }
         else {
            v1->last->next = v6;
            v1->last = v6->last;
            v6 = v1;
         }
         v7 = v7->next;
      }
   }
   else {
      v6 = NULL;
   }
   /* ---------- v6 = ul <<< drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* -- v15 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc) - */
   if ((j-i) >= 23) {
      v15 = NULL;
      for (k=i+1; k<=j-22; k++) {
         /* ------------------------------- start of ------------------------------ */
         /* ---------- v11 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v10 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
         if (abs(tbl_block_Pr(i, j) - ((40 + (tbl_closed_Pr(k, j) + termaupenalty((k) + 1, j))) + ss_energy(i, k))) <= diff) {
            v10=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v10->next = NULL;
            v10->last = v10;
            v10->item.alg_energy = tbl_closed_Pr(k, j) + termaupenalty((k) + 1, j);
            v10->item.alg_enum = new_Is_f(k, back_closed_Pr, k, j, j);
         }
         else {
            v10 = NULL;
         }
         /* --------------- v10 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
         /* ------------------------------- finished ------------------------------ */

         v11 = NULL;
         /* +------------------------------------------------------------------------- */
         /* v9 stores the result of a single application of algebra function           */
         /* v10 holds the results of expression                                        */
         /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                    */
         /*                                                                            */
         /* we use v12 to iterate over v10 and                                         */
         /* v11 to collect the results                                                 */
         /* +------------------------------------------------------------------------- */
         v12 = v10;
         while (v12 != NULL) {
            if (abs(tbl_block_Pr(i, j) - ((40 + v12->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v9=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v9->next = NULL;
               v9->last = v9;
               v9->item.alg_energy = v12->item.alg_energy;
               v9->item.alg_enum = new_Drem_s(v12->item.alg_enum);
            }
            else {
               v9 = NULL;
            }
            /* ------------------------- v11 = v9 ++ v11 -------------------------- */
            if (v9 == NULL) {
            } else 
            if (v11 == NULL) {
               v11 = v9;
            }
            else {
               v9->last->next = v11;
               v9->last = v11->last;
               v11 = v9;
            }
            v12 = v12->next;
         }
         /* ---------- v11 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
         /* ------------------------------- finished ------------------------------ */

         v13 = NULL;
         /* +------------------------------------------------------------------------- */
         /* v8 stores the result of a single application of algebra function           */
         /* v11 holds the results of expression                                        */
         /*      drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc                           */
         /*                                                                            */
         /* we use v14 to iterate over v11 and                                         */
         /* v13 to collect the results                                                 */
         /* +------------------------------------------------------------------------- */
         v14 = v11;
         while (v14 != NULL) {
            if (abs(tbl_block_Pr(i, j) - ((40 + v14->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v8=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v8->next = NULL;
               v8->last = v8;
               v8->item.alg_energy = (40 + v14->item.alg_energy) + ss_energy(i, k);
               v8->item.alg_enum = new_Ssadd_s(i, k, v14->item.alg_enum);
            }
            else {
               v8 = NULL;
            }
            /* ------------------------- v13 = v8 ++ v13 -------------------------- */
            if (v8 == NULL) {
            } else 
            if (v13 == NULL) {
               v13 = v8;
            }
            else {
               v8->last->next = v13;
               v8->last = v13->last;
               v13 = v8;
            }
            v14 = v14->next;
         }
         /* --------------------------- v15 = v13 ++ v15 -------------------------- */
         if (v13 == NULL) {
         } else 
         if (v15 == NULL) {
            v15 = v13;
         }
         else {
            v13->last->next = v15;
            v13->last = v15->last;
            v15 = v13;
         }
      }
   }
   else {
      v15 = NULL;
   }
   /* -- v15 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc) - */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------------- v16 = pkml <<< p knot --------------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      if (abs(tbl_block_Pr(i, j) - (tbl_knot(i, j).tup1 + 600)) <= diff) {
         v16=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v16->next = NULL;
         v16->last = v16;
         v16->item.alg_energy = tbl_knot(i, j).tup1 + 600;
         v16->item.alg_enum = new_Pkml_f(back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3);
      }
      else {
         v16 = NULL;
      }
   }
   else {
      v16 = NULL;
   }
   /* --------------------------- v16 = pkml <<< p knot --------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------ v17 = v15 ++ v16 ----------------------------- */
   if (v15 == NULL) {
      v17 = v16;
   } else 
   if (v16 == NULL) {
      v17 = v15;
   }
   else {
      v15->last->next = v16;
      v15->last = v16->last;
      v17 = v15;
   }
   /* ------------------------------ v18 = v6 ++ v17 ------------------------------ */
   if (v6 == NULL) {
      v18 = v17;
   } else 
   if (v17 == NULL) {
      v18 = v6;
   }
   else {
      v6->last->next = v17;
      v6->last = v17->last;
      v18 = v6;
   }
   /* ----------------------------- v20 = minimum(v18) ---------------------------- */
   v20 = 1.0e7;
   v19 = v18;
   while (v19 != NULL) {
      v20 = v20 < v19->item.alg_energy ? v20 : v19->item.alg_energy;
      v19 = v19->next;
   }
   v19 = v18;
   v22 = NULL;
   while (v19 != NULL) {
      if (abs(v20 - v19->item.alg_energy) <= diff) {
         update_str_Signature(v19->item.alg_enum->item, diff - abs(v20 - v19->item.alg_energy));
         v21=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v21->item = v19->item;
         v21->next = NULL;
         v21->last = v21;
         /* --------------------------- v22 = v21 ++ v22 -------------------------- */
         if (v21 == NULL) {
         } else 
         if (v22 == NULL) {
            v22 = v21;
         }
         else {
            v21->last->next = v22;
            v21->last = v22->last;
            v22 = v21;
         }
      }
      v19 = v19->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v23 = v22;
   v24 = NULL;
   while (v23 != NULL) {
      /* -------------------- v24 = v23->item.alg_enum ++ v24 --------------------- */
      if (v23->item.alg_enum == NULL) {
      } else 
      if (v24 == NULL) {
         v24 = v23->item.alg_enum;
      }
      else {
         v23->item.alg_enum->last->next = v24;
         v23->item.alg_enum->last = v24->last;
         v24 = v23->item.alg_enum;
      }
      v23 = v23->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v24)));
}

/* backtracing code for production knot                                             */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_knot(int i, int j, int diff)
{
   struct str3 *v59;
   struct str1 v55;
   int v11, v26, v34, v46;
   struct str5 *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10, *v12, *v13;
   struct str5 *v14, *v15, *v16, *v17, *v18, *v19, *v20, *v21, *v22, *v23, *v24;
   struct str5 *v25, *v27, *v28, *v29, *v30, *v31;
   struct str5 *v32, *v33, *v35, *v36, *v37, *v38;
   struct str5 *v39, *v40, *v41, *v42, *v43, *v44;
   struct str5 *v45, *v47, *v48, *v50, *v51, *v52;
   struct str7 *v1, *v49, *v53, *v54, *v56, *v57, *v58;
   int lc_alphanrg, lc_betalen, lc_betanrg, lc_correctionterm, lc_energy;
   int lc_h, lc_h_Pr, lc_k, lc_l, lc_middle_k, lc_middle_l;

   /* ---------------------------------- start of --------------------------------- */
   /* ------- v53 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------- */
   if ((j-i) >= 0) {
      v53 = NULL;
      for (lc_l=i+2; lc_l<=j-1; lc_l++) {
         for (lc_k=lc_l+1; lc_k<=j-2; lc_k++) {
            lc_h = (lc_k-i) >= 5 ? tbl_stacklen(i, lc_k).tup2 : 0;
            if (lc_h >= 2) {
               lc_betalen = (j-lc_l) >= 5 ? tbl_stacklen(lc_l, j).tup2 : 0;
               lc_h_Pr = ((lc_betalen + lc_h) > (lc_k - lc_l)) ? (lc_k - lc_l) - lc_h : lc_betalen;
               if (lc_h_Pr >= 2) {
                  lc_betanrg = (j-lc_l) >= 5 ? tbl_stacklen(lc_l, j).tup1 : 1.0e7;
                  lc_alphanrg = (lc_k-i) >= 5 ? tbl_stacklen(i, lc_k).tup1 : 1.0e7;
                  lc_correctionterm = (min(j-lc_h_Pr+1, n)-(max(0, lc_l+lc_h_Pr-1))) >= 5 ? tbl_stacklen(lc_l+lc_h_Pr-1, min(j-lc_h_Pr+1, n)).tup1 : 1.0e7;
                  lc_middle_k = (j) - lc_h_Pr;
                  lc_middle_l = (i) + lc_h;
                  lc_energy = ((lc_alphanrg + lc_betanrg) - lc_correctionterm) + (pbp * (lc_h + lc_h_Pr));
                  /* -------------------------- start of -------------------------- */
                  /* ---------------- v4 = pul <<< pss <<< uregion ---------------- */
                  if ((lc_l-(i+lc_h)-1) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v3 = pss <<< uregion ------------------ */
                     v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v3->next = NULL;
                     v3->last = v3;
                     v3->item.alg_energy = sspenalty((lc_l) - (i+lc_h+1));
                     v3->item.alg_enum = new_Pss_(i+lc_h+1, lc_l);
                     /* ------------------- v3 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v4 = NULL;
                     /* +------------------------------------------------------------------------- */
                     /* v2 stores the result of a single application of algebra function           */
                     /* v3 holds the results of expression                                         */
                     /*      pss <<< uregion                                                       */
                     /*                                                                            */
                     /* we use v5 to iterate over v3 and                                           */
                     /* v4 to collect the results                                                  */
                     /* +------------------------------------------------------------------------- */
                     v5 = v3;
                     while (v5 != NULL) {
                        v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v2->next = NULL;
                        v2->last = v2;
                        v2->item.alg_energy = v5->item.alg_energy;
                        v2->item.alg_enum = new_Pul_s(v5->item.alg_enum);
                        /* -------------------- v4 = v2 ++ v4 --------------------- */
                        if (v2 == NULL) {
                        } else 
                        if (v4 == NULL) {
                           v4 = v2;
                        }
                        else {
                           v2->last->next = v4;
                           v2->last = v4->last;
                           v4 = v2;
                        }
                        v5 = v5->next;
                     }
                  }
                  else {
                     v4 = NULL;
                  }
                  /* ---------------- v4 = pul <<< pss <<< uregion ---------------- */
                  /* -------------------------- finished -------------------------- */

                  /* ------------------------ v6 = p comps ------------------------ */
                  /* +---------------------------------------------------------------------------- */
                  /* Nonterminal comps is implemented as a tabulated                               */
                  /* function which yields atomar results. Since we are in list context,           */
                  /* we need to wrap the result of comps into a single list element.               */
                  /* +---------------------------------------------------------------------------- */
                  if ((lc_l-(i+lc_h)-1) >= 7) {
                     v6=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v6->item.alg_energy = tbl_comps(i+lc_h+1, lc_l);
                     v6->item.alg_enum = new__NTID(back_comps, i+lc_h+1, lc_l);
                     v6->next = NULL;
                     v6->last = v6;
                  }
                  else {
                     v6 = NULL;
                  }
                  /* ---------------------- v7 = p comps_Pr ----------------------- */
                  /* +---------------------------------------------------------------------------- */
                  /* Nonterminal comps_Pr is implemented as a tabulated                            */
                  /* function which yields atomar results. Since we are in list context,           */
                  /* we need to wrap the result of comps_Pr into a single list element.            */
                  /* +---------------------------------------------------------------------------- */
                  if ((lc_l-(i+lc_h)-1) >= 11) {
                     v7=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v7->item.alg_energy = tbl_comps_Pr(i+lc_h+1, lc_l);
                     v7->item.alg_enum = new__NTID(back_comps_Pr, i+lc_h+1, lc_l);
                     v7->next = NULL;
                     v7->last = v7;
                  }
                  else {
                     v7 = NULL;
                  }
                  /* ----------------------- v8 = v6 ++ v7 ------------------------ */
                  if (v6 == NULL) {
                     v8 = v7;
                  } else 
                  if (v7 == NULL) {
                     v8 = v6;
                  }
                  else {
                     v6->last->next = v7;
                     v6->last = v7->last;
                     v8 = v6;
                  }
                  /* ----------------------- v9 = v4 ++ v8 ------------------------ */
                  if (v4 == NULL) {
                     v9 = v8;
                  } else 
                  if (v8 == NULL) {
                     v9 = v4;
                  }
                  else {
                     v4->last->next = v8;
                     v4->last = v8->last;
                     v9 = v4;
                  }
                  /* --------------------- v11 = minimum(v9) ---------------------- */
                  v11 = 1.0e7;
                  v10 = v9;
                  while (v10 != NULL) {
                     v11 = v11 < v10->item.alg_energy ? v11 : v10->item.alg_energy;
                     v10 = v10->next;
                  }
                  v10 = v9;
                  v13 = NULL;
                  while (v10 != NULL) {
                     if (abs(v11 - v10->item.alg_energy) <= diff) {
                        update_str_Signature(v10->item.alg_enum->item, diff - abs(v11 - v10->item.alg_energy));
                        v12=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v12->item = v10->item;
                        v12->next = NULL;
                        v12->last = v12;
                        /* ------------------- v13 = v12 ++ v13 ------------------- */
                        if (v12 == NULL) {
                        } else 
                        if (v13 == NULL) {
                           v13 = v12;
                        }
                        else {
                           v12->last->next = v13;
                           v12->last = v13->last;
                           v13 = v12;
                        }
                     }
                     v10 = v10->next;
                  }
                  /* -------------------------- start of -------------------------- */
                  /* ------ v14 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 0) {
                     v14=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v14->next = NULL;
                     v14->last = v14;
                     v14->item.alg_energy = wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, lc_l+lc_h_Pr, (lc_l+lc_h_Pr) + 1);
                     v14->item.alg_enum = new_Emptymid_(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr);
                  }
                  else {
                     v14 = NULL;
                  }
                  /* ------ v14 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* ------ v15 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 1) {
                     v15=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v15->next = NULL;
                     v15->last = v15;
                     v15->item.alg_energy = (wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, (lc_k-lc_h) - 1, (lc_k-lc_h) + 1)) + npp;
                     v15->item.alg_enum = new_Midbase_(lc_middle_k, lc_middle_l, lc_k-lc_h);
                  }
                  else {
                     v15 = NULL;
                  }
                  /* ------ v15 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v29 = midregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h_l - */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v19 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v18 = pss <<< region ------------------ */
                     v18=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v18->next = NULL;
                     v18->last = v18;
                     v18->item.alg_energy = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr));
                     v18->item.alg_enum = new_Pss_(lc_l+lc_h_Pr, lc_k-lc_h);
                     /* ------------------- v18 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v19 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v17 stores the result of a single application of algebra function           */
                     /* v18 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v20 to iterate over v18 and                                          */
                     /* v19 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v20 = v18;
                     while (v20 != NULL) {
                        v17=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v17->next = NULL;
                        v17->last = v17;
                        v17->item.alg_energy = v20->item.alg_energy;
                        v17->item.alg_enum = new_Pul_s(v20->item.alg_enum);
                        /* ------------------- v19 = v17 ++ v19 ------------------- */
                        if (v17 == NULL) {
                        } else 
                        if (v19 == NULL) {
                           v19 = v17;
                        }
                        else {
                           v17->last->next = v19;
                           v17->last = v19->last;
                           v19 = v17;
                        }
                        v20 = v20->next;
                     }
                     /* --------------- v19 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v21 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 7) {
                        v21=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v21->item.alg_energy = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h);
                        v21->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr, lc_k-lc_h);
                        v21->next = NULL;
                        v21->last = v21;
                     }
                     else {
                        v21 = NULL;
                     }
                     /* --------------------- v22 = p comps_Pr -------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps_Pr is implemented as a tabulated                            */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps_Pr into a single list element.            */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 11) {
                        v22=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v22->item.alg_energy = tbl_comps_Pr(lc_l+lc_h_Pr, lc_k-lc_h);
                        v22->item.alg_enum = new__NTID(back_comps_Pr, lc_l+lc_h_Pr, lc_k-lc_h);
                        v22->next = NULL;
                        v22->last = v22;
                     }
                     else {
                        v22 = NULL;
                     }
                     /* --------------------- v23 = v21 ++ v22 -------------------- */
                     if (v21 == NULL) {
                        v23 = v22;
                     } else 
                     if (v22 == NULL) {
                        v23 = v21;
                     }
                     else {
                        v21->last->next = v22;
                        v21->last = v22->last;
                        v23 = v21;
                     }
                     /* --------------------- v24 = v19 ++ v23 -------------------- */
                     if (v19 == NULL) {
                        v24 = v23;
                     } else 
                     if (v23 == NULL) {
                        v24 = v19;
                     }
                     else {
                        v19->last->next = v23;
                        v19->last = v23->last;
                        v24 = v19;
                     }
                     /* -------------------- v26 = minimum(v24) ------------------- */
                     v26 = 1.0e7;
                     v25 = v24;
                     while (v25 != NULL) {
                        v26 = v26 < v25->item.alg_energy ? v26 : v25->item.alg_energy;
                        v25 = v25->next;
                     }
                     v25 = v24;
                     v28 = NULL;
                     while (v25 != NULL) {
                        if (abs(v26 - v25->item.alg_energy) <= diff) {
                           update_str_Signature(v25->item.alg_enum->item, diff - abs(v26 - v25->item.alg_energy));
                           v27=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                           v27->item = v25->item;
                           v27->next = NULL;
                           v27->last = v27;
                           /* ------------------ v28 = v27 ++ v28 ----------------- */
                           if (v27 == NULL) {
                           } else 
                           if (v28 == NULL) {
                              v28 = v27;
                           }
                           else {
                              v27->last->next = v28;
                              v27->last = v28->last;
                              v28 = v27;
                           }
                        }
                        v25 = v25->next;
                     }
                     v29 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v16 stores the result of a single application of algebra function           */
                     /* v28 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h_l              */
                     /*                                                                             */
                     /* we use v30 to iterate over v28 and                                          */
                     /* v29 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v30 = v28;
                     while (v30 != NULL) {
                        v16=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v16->next = NULL;
                        v16->last = v16;
                        v16->item.alg_energy = v30->item.alg_energy;
                        v16->item.alg_enum = new_Midregion_s(v30->item.alg_enum);
                        /* ------------------- v29 = v16 ++ v29 ------------------- */
                        if (v16 == NULL) {
                        } else 
                        if (v29 == NULL) {
                           v29 = v16;
                        }
                        else {
                           v16->last->next = v29;
                           v16->last = v29->last;
                           v29 = v16;
                        }
                        v30 = v30->next;
                     }
                  }
                  else {
                     v29 = NULL;
                  }
                  /*  v29 = midregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h_l - */
                  /* -------------------------- finished -------------------------- */

                  /* ---------------------- v31 = v15 ++ v29 ---------------------- */
                  if (v15 == NULL) {
                     v31 = v29;
                  } else 
                  if (v29 == NULL) {
                     v31 = v15;
                  }
                  else {
                     v15->last->next = v29;
                     v15->last = v29->last;
                     v31 = v15;
                  }
                  /* ---------------------- v32 = v14 ++ v31 ---------------------- */
                  if (v14 == NULL) {
                     v32 = v31;
                  } else 
                  if (v31 == NULL) {
                     v32 = v14;
                  }
                  else {
                     v14->last->next = v31;
                     v14->last = v31->last;
                     v32 = v14;
                  }
                  /* --------------------- v34 = minimum(v32) --------------------- */
                  v34 = 1.0e7;
                  v33 = v32;
                  while (v33 != NULL) {
                     v34 = v34 < v33->item.alg_energy ? v34 : v33->item.alg_energy;
                     v33 = v33->next;
                  }
                  v33 = v32;
                  v36 = NULL;
                  while (v33 != NULL) {
                     if (abs(v34 - v33->item.alg_energy) <= diff) {
                        update_str_Signature(v33->item.alg_enum->item, diff - abs(v34 - v33->item.alg_energy));
                        v35=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v35->item = v33->item;
                        v35->next = NULL;
                        v35->last = v35;
                        /* ------------------- v36 = v35 ++ v36 ------------------- */
                        if (v35 == NULL) {
                        } else 
                        if (v36 == NULL) {
                           v36 = v35;
                        }
                        else {
                           v35->last->next = v36;
                           v35->last = v36->last;
                           v36 = v35;
                        }
                     }
                     v33 = v33->next;
                  }
                  /* -------------------------- start of -------------------------- */
                  /* --------------- v39 = pul <<< pss <<< uregion ---------------- */
                  if ((j-lc_h_Pr-lc_k-2) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v38 = pss <<< uregion ------------------ */
                     v38=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v38->next = NULL;
                     v38->last = v38;
                     v38->item.alg_energy = sspenalty((j-lc_h_Pr-2) - (lc_k));
                     v38->item.alg_enum = new_Pss_(lc_k, j-lc_h_Pr-2);
                     /* ------------------ v38 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v39 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v37 stores the result of a single application of algebra function           */
                     /* v38 holds the results of expression                                         */
                     /*      pss <<< uregion                                                        */
                     /*                                                                             */
                     /* we use v40 to iterate over v38 and                                          */
                     /* v39 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v40 = v38;
                     while (v40 != NULL) {
                        v37=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v37->next = NULL;
                        v37->last = v37;
                        v37->item.alg_energy = v40->item.alg_energy;
                        v37->item.alg_enum = new_Pul_s(v40->item.alg_enum);
                        /* ------------------- v39 = v37 ++ v39 ------------------- */
                        if (v37 == NULL) {
                        } else 
                        if (v39 == NULL) {
                           v39 = v37;
                        }
                        else {
                           v37->last->next = v39;
                           v37->last = v39->last;
                           v39 = v37;
                        }
                        v40 = v40->next;
                     }
                  }
                  else {
                     v39 = NULL;
                  }
                  /* --------------- v39 = pul <<< pss <<< uregion ---------------- */
                  /* -------------------------- finished -------------------------- */

                  /* ----------------------- v41 = p comps ------------------------ */
                  /* +---------------------------------------------------------------------------- */
                  /* Nonterminal comps is implemented as a tabulated                               */
                  /* function which yields atomar results. Since we are in list context,           */
                  /* we need to wrap the result of comps into a single list element.               */
                  /* +---------------------------------------------------------------------------- */
                  if ((j-lc_h_Pr-lc_k-2) >= 7) {
                     v41=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v41->item.alg_energy = tbl_comps(lc_k, j-lc_h_Pr-2);
                     v41->item.alg_enum = new__NTID(back_comps, lc_k, j-lc_h_Pr-2);
                     v41->next = NULL;
                     v41->last = v41;
                  }
                  else {
                     v41 = NULL;
                  }
                  /* ---------------------- v42 = p comps_Pr ---------------------- */
                  /* +---------------------------------------------------------------------------- */
                  /* Nonterminal comps_Pr is implemented as a tabulated                            */
                  /* function which yields atomar results. Since we are in list context,           */
                  /* we need to wrap the result of comps_Pr into a single list element.            */
                  /* +---------------------------------------------------------------------------- */
                  if ((j-lc_h_Pr-lc_k-2) >= 11) {
                     v42=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v42->item.alg_energy = tbl_comps_Pr(lc_k, j-lc_h_Pr-2);
                     v42->item.alg_enum = new__NTID(back_comps_Pr, lc_k, j-lc_h_Pr-2);
                     v42->next = NULL;
                     v42->last = v42;
                  }
                  else {
                     v42 = NULL;
                  }
                  /* ---------------------- v43 = v41 ++ v42 ---------------------- */
                  if (v41 == NULL) {
                     v43 = v42;
                  } else 
                  if (v42 == NULL) {
                     v43 = v41;
                  }
                  else {
                     v41->last->next = v42;
                     v41->last = v42->last;
                     v43 = v41;
                  }
                  /* ---------------------- v44 = v39 ++ v43 ---------------------- */
                  if (v39 == NULL) {
                     v44 = v43;
                  } else 
                  if (v43 == NULL) {
                     v44 = v39;
                  }
                  else {
                     v39->last->next = v43;
                     v39->last = v43->last;
                     v44 = v39;
                  }
                  /* --------------------- v46 = minimum(v44) --------------------- */
                  v46 = 1.0e7;
                  v45 = v44;
                  while (v45 != NULL) {
                     v46 = v46 < v45->item.alg_energy ? v46 : v45->item.alg_energy;
                     v45 = v45->next;
                  }
                  v45 = v44;
                  v48 = NULL;
                  while (v45 != NULL) {
                     if (abs(v46 - v45->item.alg_energy) <= diff) {
                        update_str_Signature(v45->item.alg_enum->item, diff - abs(v46 - v45->item.alg_energy));
                        v47=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v47->item = v45->item;
                        v47->next = NULL;
                        v47->last = v47;
                        /* ------------------- v48 = v47 ++ v48 ------------------- */
                        if (v47 == NULL) {
                        } else 
                        if (v48 == NULL) {
                           v48 = v47;
                        }
                        else {
                           v47->last->next = v48;
                           v47->last = v48->last;
                           v48 = v47;
                        }
                     }
                     v45 = v45->next;
                  }
                  v49 = NULL;
                  /* +------------------------------------------------------------------------- */
                  /* v1 stores the result of a single application of algebra function           */
                  /* v13 holds the results of expression                                        */
                  /*      pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h_l            */
                  /*                                                                            */
                  /* we use v52 to iterate over v13 and                                         */
                  /* v49 to collect the results                                                 */
                  /* +------------------------------------------------------------------------- */
                  v52 = v13;
                  while (v52 != NULL) {
                     /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
                     /* v1 stores the result of a single application of algebra function                                                                                                                            */
                     /* v36 holds the results of expression                                                                                                                                                         */
                     /*      emptymid lc_middle_k lc_middle_l <<< empty ||| midbase lc_middle_k lc_middle_l <<< lbase ||| midregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h_l ... h_l           */
                     /*                                                                                                                                                                                             */
                     /* we use v51 to iterate over v36 and                                                                                                                                                          */
                     /* v49 to collect the results                                                                                                                                                                  */
                     /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
                     v51 = v36;
                     while (v51 != NULL) {
                        /* +------------------------------------------------------------------------- */
                        /* v1 stores the result of a single application of algebra function           */
                        /* v48 holds the results of expression                                        */
                        /*      pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h_l            */
                        /*                                                                            */
                        /* we use v50 to iterate over v48 and                                         */
                        /* v49 to collect the results                                                 */
                        /* +------------------------------------------------------------------------- */
                        v50 = v48;
                        while (v50 != NULL) {
                           if (abs(tbl_knot(i, j).tup1 - ((((((pkinit + lc_energy) + (3 * npp)) + v52->item.alg_energy) + v51->item.alg_energy) + v50->item.alg_energy) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j))) <= diff) {
                              v1=(struct str7 *) myalloc(adp_dynmem, sizeof(struct str7 ));
                              v1->next = NULL;
                              v1->last = v1;
                              v1->item.alg_energy.tup1 = (((((pkinit + lc_energy) + (3 * npp)) + v52->item.alg_energy) + v51->item.alg_energy) + v50->item.alg_energy) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j);
                              v1->item.alg_energy.tup2 = lc_l;
                              v1->item.alg_energy.tup3 = lc_k;
                              v1->item.alg_enum = new_Pk_Pr_sss(lc_energy, i, i+lc_h, v52->item.alg_enum, lc_l, lc_l+lc_h_Pr, v51->item.alg_enum, lc_k-lc_h, lc_k, v50->item.alg_enum, j-lc_h_Pr, j);
                           }
                           else {
                              v1 = NULL;
                           }
                           /* ------------------ v49 = v1 ++ v49 ------------------ */
                           if (v1 == NULL) {
                           } else 
                           if (v49 == NULL) {
                              v49 = v1;
                           }
                           else {
                              v1->last->next = v49;
                              v1->last = v49->last;
                              v49 = v1;
                           }
                           v50 = v50->next;
                        }
                        v51 = v51->next;
                     }
                     v52 = v52->next;
                  }
               }
               else {
                  v49 = NULL;
               }
            }
            else {
               v49 = NULL;
            }
            /* ------------------------- v53 = v49 ++ v53 ------------------------- */
            if (v49 == NULL) {
            } else 
            if (v53 == NULL) {
               v53 = v49;
            }
            else {
               v49->last->next = v53;
               v49->last = v53->last;
               v53 = v49;
            }
         }
      }
   }
   else {
      v53 = NULL;
   }
   /* ------- v53 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ----------------------------- v55 = minimum(v53) ---------------------------- */
   v55.tup1 = 1.0e7;
   v55.tup2 = 0;
   v55.tup3 = 0;
   v54 = v53;
   while (v54 != NULL) {
      /* ---------------- v55 = minimum(v55, v54->item.alg_energy) ---------------- */
      v55 = v55.tup1 < v54->item.alg_energy.tup1 ? v55 : v54->item.alg_energy;
      v54 = v54->next;
   }
   v54 = v53;
   v57 = NULL;
   while (v54 != NULL) {
      if (abs(v55.tup1 - v54->item.alg_energy.tup1) <= diff) {
         update_str_Signature(v54->item.alg_enum->item, diff - abs(v55.tup1 - v54->item.alg_energy.tup1));
         v56=(struct str7 *) myalloc(adp_dynmem, sizeof(struct str7 ));
         v56->item = v54->item;
         v56->next = NULL;
         v56->last = v56;
         /* --------------------------- v57 = v56 ++ v57 -------------------------- */
         if (v56 == NULL) {
         } else 
         if (v57 == NULL) {
            v57 = v56;
         }
         else {
            v56->last->next = v57;
            v56->last = v57->last;
            v57 = v56;
         }
      }
      v54 = v54->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v58 = v57;
   v59 = NULL;
   while (v58 != NULL) {
      /* -------------------- v59 = v58->item.alg_enum ++ v59 --------------------- */
      if (v58->item.alg_enum == NULL) {
      } else 
      if (v59 == NULL) {
         v59 = v58->item.alg_enum;
      }
      else {
         v58->item.alg_enum->last->next = v59;
         v58->item.alg_enum->last = v59->last;
         v59 = v58->item.alg_enum;
      }
      v58 = v58->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v59)));
}

/* backtracing code for production stacklen                                         */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_stacklen(int i, int j, int diff)
{
   struct str3 *v11;
   struct str2 v7;
   struct str9 *v1, *v2, *v3, *v4, *v5, *v6, *v8, *v9, *v10;

   if (basepairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /* -------------- v1 = sum <<< lbase ~~~ p stacklen ~~~ lbase --------------- */
      if ((j-i) >= 7) {
         if (abs(tbl_stacklen(i, j).tup1 - (tbl_stacklen(i+1, j-1).tup1 + sr_energy(i+1, j))) <= diff) {
            v1=(struct str9 *) myalloc(adp_dynmem, sizeof(struct str9 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy.tup1 = tbl_stacklen(i+1, j-1).tup1 + sr_energy(i+1, j);
            v1->item.alg_energy.tup2 = tbl_stacklen(i+1, j-1).tup2 + 1;
            v1->item.alg_enum = new_Sum_f(i+1, back_stacklen, i+1, j-1, tbl_stacklen(i+1, j-1).tup2, j);
         }
         else {
            v1 = NULL;
         }
      }
      else {
         v1 = NULL;
      }
      /* -------------- v1 = sum <<< lbase ~~~ p stacklen ~~~ lbase --------------- */
      /* -------------------------------- finished -------------------------------- */

      v2 = v1;
   }
   else {
      v2 = NULL;
   }
   if (basepairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /* --- v3 = sumend <<< lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ---- */
      if ((j-i) >= 5) {
         if (abs(tbl_stacklen(i, j).tup1 - 0) <= diff) {
            v3=(struct str9 *) myalloc(adp_dynmem, sizeof(struct str9 ));
            v3->next = NULL;
            v3->last = v3;
            v3->item.alg_energy.tup1 = 0;
            v3->item.alg_energy.tup2 = 1;
            v3->item.alg_enum = new_Sumend_(i+1, i+1, j-1, j);
         }
         else {
            v3 = NULL;
         }
      }
      else {
         v3 = NULL;
      }
      /* --- v3 = sumend <<< lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ---- */
      /* -------------------------------- finished -------------------------------- */

      v4 = v3;
   }
   else {
      v4 = NULL;
   }
   /* ------------------------------- v5 = v2 ++ v4 ------------------------------- */
   if (v2 == NULL) {
      v5 = v4;
   } else 
   if (v4 == NULL) {
      v5 = v2;
   }
   else {
      v2->last->next = v4;
      v2->last = v4->last;
      v5 = v2;
   }
   /* ------------------------------ v7 = minimum(v5) ----------------------------- */
   v7.tup1 = 1.0e7;
   v7.tup2 = 0;
   v6 = v5;
   while (v6 != NULL) {
      /* ----------------- v7 = minimum(v7, v6->item.alg_energy) ------------------ */
      v7 = v7.tup1 < v6->item.alg_energy.tup1 ? v7 : v6->item.alg_energy;
      v6 = v6->next;
   }
   v6 = v5;
   v9 = NULL;
   while (v6 != NULL) {
      if (abs(v7.tup1 - v6->item.alg_energy.tup1) <= diff) {
         update_str_Signature(v6->item.alg_enum->item, diff - abs(v7.tup1 - v6->item.alg_energy.tup1));
         v8=(struct str9 *) myalloc(adp_dynmem, sizeof(struct str9 ));
         v8->item = v6->item;
         v8->next = NULL;
         v8->last = v8;
         /* ---------------------------- v9 = v8 ++ v9 ---------------------------- */
         if (v8 == NULL) {
         } else 
         if (v9 == NULL) {
            v9 = v8;
         }
         else {
            v8->last->next = v9;
            v8->last = v9->last;
            v9 = v8;
         }
      }
      v6 = v6->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v10 = v9;
   v11 = NULL;
   while (v10 != NULL) {
      /* -------------------- v11 = v10->item.alg_enum ++ v11 --------------------- */
      if (v10->item.alg_enum == NULL) {
      } else 
      if (v11 == NULL) {
         v11 = v10->item.alg_enum;
      }
      else {
         v10->item.alg_enum->last->next = v11;
         v10->item.alg_enum->last = v11->last;
         v11 = v10->item.alg_enum;
      }
      v10 = v10->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v11)));
}

/* table memory allocation                                                          */
/* -------------------------------------------------------------------------------- */

static void tableAlloc()
{
   int i, dim1, dim2;

   /* calculate offset */
   offset=(int *) myalloc(adp_statmem, (n+1) * sizeof(int ));
   for (i=0; i<=n; i++) {
      offset[i] = (i*(i+1))/2;
   }
   arr_closed=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_closed_Pr=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_knot=(struct str1 *) malloc((offset[n]+n+1) * sizeof(struct str1 ));
   arr_stacklen=(struct str2 *) malloc((offset[n]+n+1) * sizeof(struct str2 ));
   arr_edangle=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_edangle_Pr=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_block=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_block_Pr=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_struct=(int *) malloc((n+1) * sizeof(int ));
   arr_structP=(int *) malloc((n+1) * sizeof(int ));
   arr_comps=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_comps_Pr=(int *) malloc((offset[n]+n+1) * sizeof(int ));
}

/* free memory                                                                      */
/* -------------------------------------------------------------------------------- */

static void freeall()
{
   adplib_free(opts, seq);
   rnalib_free();

   free(arr_closed);
   free(arr_closed_Pr);
   free(arr_knot);
   free(arr_stacklen);
   free(arr_edangle);
   free(arr_edangle_Pr);
   free(arr_block);
   free(arr_block_Pr);
   free(arr_struct);
   free(arr_structP);
   free(arr_comps);
   free(arr_comps_Pr);
}

/* table move for window mode                                                       */
/* -------------------------------------------------------------------------------- */

static void movetables(int p)
{
   int i, j;

   for (j=0; j<=n; j++) {
      for (i=0; i<=j; i++) {
         if ((i >= p) && (j >= p)) {
            tbl_closed(i-p, j-p) = tbl_closed(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_closed_Pr(i-p, j-p) = tbl_closed_Pr(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_knot(i-p, j-p) = move_str1(tbl_knot(i, j));
         }
         if ((i >= p) && (j >= p)) {
            tbl_stacklen(i-p, j-p) = tbl_stacklen(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_edangle(i-p, j-p) = tbl_edangle(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_edangle_Pr(i-p, j-p) = tbl_edangle_Pr(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_block(i-p, j-p) = tbl_block(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_block_Pr(i-p, j-p) = tbl_block_Pr(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_comps(i-p, j-p) = tbl_comps(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_comps_Pr(i-p, j-p) = tbl_comps_Pr(i, j);
         }
      }
   }
}

/* main dynamic programming loop                                                    */
/* -------------------------------------------------------------------------------- */

static void mainloop()
{
   int i, j;
   int v2, result_score;
   struct str3 *l;
   struct str3 *next;
   int score;
   int pos, startj;

   tableAlloc();
   pp_init=(struct str3 ***) myalloc(adp_statmem, (n*2) * sizeof(struct str3 **));
   pp_initA=(struct str3 **) myalloc(adp_statmem, (n*2) * sizeof(struct str3 *));

   for (pos=0; pos<=seq->original_length-opts->window_size; pos += opts->window_step) {
      opts->window_pos = pos;
      if (pos == 0) {
         startj = 0;
      }
      else {
         startj = n-opts->window_step+1;
      }
      if (pos > 0) {
         movetables(opts->window_step);
         shift_input(opts, seq, 1);
      }
      for (j=startj; j<=n; j++) {
         for (i=j; i>=0; i--) {
            calc_closed(i, j);
            calc_closed_Pr(i, j);
            calc_knot(i, j);
            calc_stacklen(i, j);
            calc_edangle(i, j);
            calc_edangle_Pr(i, j);
            calc_block(i, j);
            calc_block_Pr(i, j);
            if ((j) == (n)) {
               calc_struct(i, j);
            }
            if ((j) == (n)) {
               calc_structP(i, j);
            }
            calc_comps(i, j);
            calc_comps_Pr(i, j);
         }
      }
      /* -------------------------- show axiom: structP --------------------------- */
      result_score = tbl_structP(0, n);
      if ((n >= 11) && (result_score < 100000)) {
         if (opts->traceback_percent) traceback_diff = abs(result_score * opts->traceback_percent / -100);
         rna_output_optimal(opts, seq, "energy", result_score, result_score, result_score + traceback_diff);
         rna_output_subopt_start(opts, seq, "energy", result_score, result_score, result_score + traceback_diff);
         copy_depth = 0;
         l = back_structP(0, n, traceback_diff);
         while ((l != NULL) || (pp_next != NULL)) {
            pp_next = NULL;
            pp_initC = (-1);
            result_prettyprint[0] = 0;
            pp_outp = result_prettyprint;
            rmAllowed = 1;
            removeAddr = NULL;
            score = pp_str_Signature(l);
            if (abs(result_score - score) <= traceback_diff) {
               rna_output_subopt(opts, seq, "energy", score, result_prettyprint);
            }
            if (pp_next != NULL) {
               build_str_Signature((*pp_next)->next);
               next = (*pp_next)->next;
               if (removeAddr != NULL) {
                  free_str_Signature(0, (*removeAddr));
               }
               (*pp_next) = next;
               if (pp_initC != (-1)) {
                  for (i=0; i<=pp_initC; i++) {
                     (*pp_init[i]) = pp_initA[i];
                  }
               }
            }
            else {
               next = l->next;
               if (l->next) {
                  build_str_Signature(l->next);
               }
               free_str_Signature(0, l);
               l = next;
            }
         }
         rna_output_subopt_end(opts, seq, "energy", result_score, result_score, result_score + traceback_diff);
      }
      else printf("The input sequence contains no pseudoknot!\n");
   }
}

int main_pk_enf_so_nd(toptions *_opts, tsequence *_seq)
{
   opts = _opts;
   seq  = _seq;
   z    = _seq->seq - 1;
   n    = _seq->length;

   if (opts->debug) printf("pk-enf-so-nd.c\n");

   adplib_init(opts,seq,&z,&n);
   result_prettyprint = (char *) myalloc(adp_statmem, 30*n*sizeof(char));
   traceback_diff = opts->traceback_diff * 100;
   rnalib_init(opts,seq);
   if (opts->window_mode) rna_output_descr(opts,seq);
   mainloop();
   freeall();
}


