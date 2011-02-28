/* ---------------------------------------------------------------------------
pknotsRG 1.3
Copyright (C) 2004-2006 Jens Reeder, Robert Giegerich, Peter Steffen
--------------------------------------------------------------------------- */
/* compiled by the ADP compiler, version 0.8 (rev 690)    Tue Sep 12 13:31:03 MEST 2006 */
/* source file: pknotsRG-loc-nd.lhs                                                 */
/* command:                                                                         */
/* adpcompile -c pknotsRG-loc-nd.lhs -al energy enum -cs energy -alpp pp -O -lcf -ta bto -bt so -gc cc -iuc -W */
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

#define RFACTOR 1000
int pknot_start, pknot_end;
int scorePerBase;
char pksOnly;

/* data structures                                                                  */
/* -------------------------------------------------------------------------------- */

struct str1 {
   int tup1;
   int tup2;
   int tup3;
   int tup4;
};

static struct str1 move_str1(struct str1 s){
  s.tup3 -= opts->window_step;
  s.tup4 -= opts->window_step;
  return s;
}

struct str2 {
   int tup1;
   int tup2;
   int tup3;
};

static struct str2 move_str2(struct str2 s){
  s.tup2 -= opts->window_step;
  s.tup3 -= opts->window_step;
  return s;
}

struct str3 {
   int tup1;
   int tup2;
};
struct str4 {
   struct str4 *next;
   struct str4 *last;
   struct str_Signature *item;
};
struct str5 {
   int alg_energy;
   struct str4 *alg_enum;
};
struct str6 {
   struct str6 *next;
   struct str6 *last;
   struct str5 item;
};
struct str7 {
   struct str1 alg_energy;
   struct str4 *alg_enum;
};
struct str8 {
   struct str8 *next;
   struct str8 *last;
   struct str7 item;
};
struct str9 {
   struct str2 alg_energy;
   struct str4 *alg_enum;
};
struct str10 {
   struct str10 *next;
   struct str10 *last;
   struct str9 item;
};
struct str11 {
   struct str3 alg_energy;
   struct str4 *alg_enum;
};
struct str12 {
   struct str12 *next;
   struct str12 *last;
   struct str11 item;
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

static struct str4 **pp_next, **pp_initA, **removeAddr;
static struct str4 ***pp_init;
static int pp_initC;
static int copy_depth;
static char *pp_outp, *result_prettyprint;
static int traceback_diff;
static char rmAllowed;

/* signature                                                                        */
/* -------------------------------------------------------------------------------- */

#define SIGID__NTID 1
#define SIGID_Is 2
#define SIGID_Sr 3
#define SIGID_Hl 4
#define SIGID_Bl 5
#define SIGID_Br 6
#define SIGID_Il 7
#define SIGID_Ml 8
#define SIGID_Drem 9
#define SIGID_Cons 10
#define SIGID_Ul 11
#define SIGID_Pul 12
#define SIGID_Addss 13
#define SIGID_Ssadd 14
#define SIGID_Combine 15
#define SIGID_Sum 16
#define SIGID_Sumend 17
#define SIGID_Pkml 18
#define SIGID_Pk_Pr 19
#define SIGID_Scale 20
#define SIGID_Unscale 21
#define SIGID_Emptymid 22
#define SIGID_Midbase 23
#define SIGID_Midregion 24
#define SIGID_Pss 25
#define SIGID_Skipleft 26
#define SIGID_Skipright 27

struct str_Signature {
   int utype;
   void *entry;
   char fcalled;
};

static struct str4 *new_Signature(int u, void *entry)
{
   struct str_Signature *t;
   struct str4 *l;

   t=(struct str_Signature *) myalloc(adp_dynmem, sizeof(struct str_Signature ));
   t->utype = u;
   t->entry = entry;
   t->fcalled = 0;
   l=(struct str4 *) myalloc(adp_dynmem, sizeof(struct str4 ));
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
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};

static struct str4 *new__NTID(struct str4 *(*f1)(int , int , int ), int i1, int j1)
{
   struct str__NTID *t;

   t=(struct str__NTID *) myalloc(adp_dynmem, sizeof(struct str__NTID ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   return(new_Signature(SIGID__NTID, t));
}

/* operator Is                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Is {
   int a1;
   int isStructure2;
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
};

static struct str4 *new_Is_f(int a1, struct str4 *(*f2)(int , int , int ), int i2, int j2, int a3)
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
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
};

static struct str4 *new_Sr_f(int a1, struct str4 *(*f2)(int , int , int ), int i2, int j2, int a3)
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

static struct str4 *new_Hl_(int a1, int a2, int a3, int a4, int a5, int a6)
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
   struct str4 *structure5;
   struct str4 *a5;
   struct str4 *pp_init_a5;
   struct str4 *(*f5)(int , int , int );
   int i5, j5;
   int diff5;
   int a6;
   int a7;
};


static struct str4 *new_Bl_s(int a1, int a2, int a3, int a4, struct str4 *structure5, int a6, int a7)
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
   struct str4 *structure3;
   struct str4 *a3;
   struct str4 *pp_init_a3;
   struct str4 *(*f3)(int , int , int );
   int i3, j3;
   int diff3;
   int a4;
   int a5;
   int a6;
   int a7;
};


static struct str4 *new_Br_s(int a1, int a2, struct str4 *structure3, int a4, int a5, int a6, int a7)
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
   struct str4 *structure5;
   struct str4 *a5;
   struct str4 *pp_init_a5;
   struct str4 *(*f5)(int , int , int );
   int i5, j5;
   int diff5;
   int a6;
   int a7;
   int a8;
   int a9;
};

static struct str4 *new_Il_f(int a1, int a2, int a3, int a4, struct str4 *(*f5)(int , int , int ), int i5, int j5, int a6, int a7, int a8, int a9)
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
   struct str4 *structure3;
   struct str4 *a3;
   struct str4 *pp_init_a3;
   struct str4 *(*f3)(int , int , int );
   int i3, j3;
   int diff3;
   int a4;
   int a5;
};


static struct str4 *new_Ml_s(int a1, int a2, struct str4 *structure3, int a4, int a5)
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
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str4 *new_Drem_s(struct str4 *structure1)
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
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int isStructure2;
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
};

static struct str4 *new_Cons_ff(struct str4 *(*f1)(int , int , int ), int i1, int j1, struct str4 *(*f2)(int , int , int ), int i2, int j2)
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
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str4 *new_Ul_s(struct str4 *structure1)
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
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str4 *new_Pul_s(struct str4 *structure1)
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
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int a2;
   int a3;
};

static struct str4 *new_Addss_f(struct str4 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3)
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
   struct str4 *structure3;
   struct str4 *a3;
   struct str4 *pp_init_a3;
   struct str4 *(*f3)(int , int , int );
   int i3, j3;
   int diff3;
};


static struct str4 *new_Ssadd_s(int a1, int a2, struct str4 *structure3)
{
   struct str_Ssadd *t;

   t=(struct str_Ssadd *) myalloc(adp_dynmem, sizeof(struct str_Ssadd ));
   t->a1 = a1;
   t->a2 = a2;
   t->isStructure3 = 1;
   t->structure3 = structure3;
   return(new_Signature(SIGID_Ssadd, t));
}

/* operator Combine                                                                 */
/* -------------------------------------------------------------------------------- */

struct str_Combine {
   int isStructure1;
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int isStructure2;
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
};

static struct str4 *new_Combine_ff(struct str4 *(*f1)(int , int , int ), int i1, int j1, struct str4 *(*f2)(int , int , int ), int i2, int j2)
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
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
   int a4;
};

static struct str4 *new_Sum_f(int a1, struct str4 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4)
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

static struct str4 *new_Sumend_(int a1, int a2, int a3, int a4)
{
   struct str_Sumend *t;

   t=(struct str_Sumend *) myalloc(adp_dynmem, sizeof(struct str_Sumend ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   return(new_Signature(SIGID_Sumend, t));
}

/* operator Pkml                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Pkml {
   int isStructure1;
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int a2;
   int a3;
};

static struct str4 *new_Pkml_f(struct str4 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3)
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
   struct str4 *structure4;
   struct str4 *a4;
   struct str4 *pp_init_a4;
   struct str4 *(*f4)(int , int , int );
   int i4, j4;
   int diff4;
   int a5;
   int a6;
   int isStructure7;
   struct str4 *structure7;
   struct str4 *a7;
   struct str4 *pp_init_a7;
   struct str4 *(*f7)(int , int , int );
   int i7, j7;
   int diff7;
   int a8;
   int a9;
   int isStructure10;
   struct str4 *structure10;
   struct str4 *a10;
   struct str4 *pp_init_a10;
   struct str4 *(*f10)(int , int , int );
   int i10, j10;
   int diff10;
   int a11;
   int a12;
};








static struct str4 *new_Pk_Pr_sss(int a1, int a2, int a3, struct str4 *structure4, int a5, int a6, struct str4 *structure7, int a8, int a9, struct str4 *structure10, int a11, int a12)
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

/* operator Scale                                                                   */
/* -------------------------------------------------------------------------------- */

struct str_Scale {
   int a1;
   int isStructure2;
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
   int a4;
   int a5;
};

static struct str4 *new_Scale_f(int a1, struct str4 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4, int a5)
{
   struct str_Scale *t;

   t=(struct str_Scale *) myalloc(adp_dynmem, sizeof(struct str_Scale ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   t->a4 = a4;
   t->a5 = a5;
   return(new_Signature(SIGID_Scale, t));
}


/* operator Unscale                                                                 */
/* -------------------------------------------------------------------------------- */

struct str_Unscale {
   int isStructure1;
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int a2;
   int a3;
   int a4;
};

static struct str4 *new_Unscale_f(struct str4 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3, int a4)
{
   struct str_Unscale *t;

   t=(struct str_Unscale *) myalloc(adp_dynmem, sizeof(struct str_Unscale ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   return(new_Signature(SIGID_Unscale, t));
}


/* operator Emptymid                                                                */
/* -------------------------------------------------------------------------------- */

struct str_Emptymid {
   int a1;
   int a2;
   int a3;
   int diff;
};

static struct str4 *new_Emptymid_(int a1, int a2, int a3)
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

static struct str4 *new_Midbase_(int a1, int a2, int a3)
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
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str4 *new_Midregion_s(struct str4 *structure1)
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

static struct str4 *new_Pss_(int a1, int a2)
{
   struct str_Pss *t;

   t=(struct str_Pss *) myalloc(adp_dynmem, sizeof(struct str_Pss ));
   t->a1 = a1;
   t->a2 = a2;
   return(new_Signature(SIGID_Pss, t));
}

/* operator Skipleft                                                                */
/* -------------------------------------------------------------------------------- */

struct str_Skipleft {
   int a1;
   int isStructure2;
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
   int a4;
   int a5;
};

static struct str4 *new_Skipleft_f(int a1, struct str4 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4, int a5)
{
   struct str_Skipleft *t;

   t=(struct str_Skipleft *) myalloc(adp_dynmem, sizeof(struct str_Skipleft ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   t->a4 = a4;
   t->a5 = a5;
   return(new_Signature(SIGID_Skipleft, t));
}


/* operator Skipright                                                               */
/* -------------------------------------------------------------------------------- */

struct str_Skipright {
   int isStructure1;
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int a2;
   int a3;
   int a4;
   int a5;
};

static struct str4 *new_Skipright_f(struct str4 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3, int a4, int a5)
{
   struct str_Skipright *t;

   t=(struct str_Skipright *) myalloc(adp_dynmem, sizeof(struct str_Skipright ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   t->a5 = a5;
   return(new_Signature(SIGID_Skipright, t));
}


/* signature pretty printer                                                         */
/* -------------------------------------------------------------------------------- */
static int pp_str_Signature(struct str4 *l)
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
      if (c->utype == SIGID_Scale) {
         if (((struct str_Scale *)(c->entry))->a2 != NULL) {
            if (((struct str_Scale *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Scale *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Scale *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Scale *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Scale *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Scale *)(c->entry))->a2);
            score = (score2 * RFACTOR) / (((struct str_Scale *)(c->entry))->a5 - ((struct str_Scale *)(c->entry))->a1);
            pknot_start=((struct str_Scale *)(c->entry))->a1;
            pknot_end=((struct str_Scale *)(c->entry))->a5;
         }
      } else 
      if (c->utype == SIGID_Unscale) {
         if (((struct str_Unscale *)(c->entry))->a1 != NULL) {
            if (((struct str_Unscale *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Unscale *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Unscale *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Unscale *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Unscale *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Unscale *)(c->entry))->a1);
            // score = (score1 * ((struct str_Unscale *)(c->entry))->a2) / RFACTOR;
            // we have to multiply with the correct length ....
            score = (score1 * (pknot_end-pknot_start)) / RFACTOR;
            scorePerBase = score1;
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
      } else 
      if (c->utype == SIGID_Skipleft) {
         if (((struct str_Skipleft *)(c->entry))->a2 != NULL) {
            if (((struct str_Skipleft *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Skipleft *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Skipleft *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Skipleft *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Skipleft *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Skipleft *)(c->entry))->a2);
            score = score2;
         }
      } else 
      if (c->utype == SIGID_Skipright) {
         if (((struct str_Skipright *)(c->entry))->a1 != NULL) {
            if (((struct str_Skipright *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Skipright *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Skipright *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Skipright *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Skipright *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Skipright *)(c->entry))->a1);
            score = score1;
         }
      };
   }
   return(score);
}

/* copy structures                                                                  */
/* -------------------------------------------------------------------------------- */
static struct str4 *copy_str_Signature(struct str4 *l)
{
   struct str4 *itr, *nstr, *last, *first, *setnext;
   void *entr;
   int id;

   copy_depth = copy_depth + 1;
   itr = l;
   first = NULL;
   setnext = NULL;
   while (itr != NULL) {
      nstr=(struct str4 *) malloc(sizeof(struct str4 ));
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
      if (id == SIGID_Scale) {
         nstr->item->entry=(struct str_Scale *) malloc(sizeof(struct str_Scale ));
         (*((struct str_Scale *)(nstr->item->entry))) = (*((struct str_Scale *)entr));
         if (((struct str_Scale *)(nstr->item->entry))->isStructure2) {
            ((struct str_Scale *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Scale *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Unscale) {
         nstr->item->entry=(struct str_Unscale *) malloc(sizeof(struct str_Unscale ));
         (*((struct str_Unscale *)(nstr->item->entry))) = (*((struct str_Unscale *)entr));
         if (((struct str_Unscale *)(nstr->item->entry))->isStructure1) {
            ((struct str_Unscale *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Unscale *)entr)->structure1);
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
      } else 
      if (id == SIGID_Skipleft) {
         nstr->item->entry=(struct str_Skipleft *) malloc(sizeof(struct str_Skipleft ));
         (*((struct str_Skipleft *)(nstr->item->entry))) = (*((struct str_Skipleft *)entr));
         if (((struct str_Skipleft *)(nstr->item->entry))->isStructure2) {
            ((struct str_Skipleft *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Skipleft *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Skipright) {
         nstr->item->entry=(struct str_Skipright *) malloc(sizeof(struct str_Skipright ));
         (*((struct str_Skipright *)(nstr->item->entry))) = (*((struct str_Skipright *)entr));
         if (((struct str_Skipright *)(nstr->item->entry))->isStructure1) {
            ((struct str_Skipright *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Skipright *)entr)->structure1);
         }
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
static void free_str_Signature(char rmAll, struct str4 *l)
{
   struct str4 *itr, *nitr;
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
         if (c->utype == SIGID_Scale) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Scale *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Scale *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Unscale) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Unscale *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Unscale *)(c->entry))->a1);
            }
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
         } else 
         if (c->utype == SIGID_Skipleft) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Skipleft *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Skipleft *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Skipright) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Skipright *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Skipright *)(c->entry))->a1);
            }
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
static struct str4 *build_str_Signature(struct str4 *l)
{
   struct str_Signature *c;
   struct str4 *cl;

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
         if (c->utype == SIGID_Scale) {
            if (((struct str_Scale *)(c->entry))->isStructure2) {
               ((struct str_Scale *)(c->entry))->a2 = build_str_Signature(((struct str_Scale *)(c->entry))->structure2);
               ((struct str_Scale *)(c->entry))->pp_init_a2 = ((struct str_Scale *)(c->entry))->a2;
            }
            else {
               ((struct str_Scale *)(c->entry))->a2 = (*((struct str_Scale *)(c->entry))->f2)(((struct str_Scale *)(c->entry))->i2, ((struct str_Scale *)(c->entry))->j2, ((struct str_Scale *)(c->entry))->diff2);
               ((struct str_Scale *)(c->entry))->pp_init_a2 = ((struct str_Scale *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Unscale) {
            if (((struct str_Unscale *)(c->entry))->isStructure1) {
               ((struct str_Unscale *)(c->entry))->a1 = build_str_Signature(((struct str_Unscale *)(c->entry))->structure1);
               ((struct str_Unscale *)(c->entry))->pp_init_a1 = ((struct str_Unscale *)(c->entry))->a1;
            }
            else {
               ((struct str_Unscale *)(c->entry))->a1 = (*((struct str_Unscale *)(c->entry))->f1)(((struct str_Unscale *)(c->entry))->i1, ((struct str_Unscale *)(c->entry))->j1, ((struct str_Unscale *)(c->entry))->diff1);
               ((struct str_Unscale *)(c->entry))->pp_init_a1 = ((struct str_Unscale *)(c->entry))->a1;
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
         } else 
         if (c->utype == SIGID_Skipleft) {
            if (((struct str_Skipleft *)(c->entry))->isStructure2) {
               ((struct str_Skipleft *)(c->entry))->a2 = build_str_Signature(((struct str_Skipleft *)(c->entry))->structure2);
               ((struct str_Skipleft *)(c->entry))->pp_init_a2 = ((struct str_Skipleft *)(c->entry))->a2;
            }
            else {
               ((struct str_Skipleft *)(c->entry))->a2 = (*((struct str_Skipleft *)(c->entry))->f2)(((struct str_Skipleft *)(c->entry))->i2, ((struct str_Skipleft *)(c->entry))->j2, ((struct str_Skipleft *)(c->entry))->diff2);
               ((struct str_Skipleft *)(c->entry))->pp_init_a2 = ((struct str_Skipleft *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Skipright) {
            if (((struct str_Skipright *)(c->entry))->isStructure1) {
               ((struct str_Skipright *)(c->entry))->a1 = build_str_Signature(((struct str_Skipright *)(c->entry))->structure1);
               ((struct str_Skipright *)(c->entry))->pp_init_a1 = ((struct str_Skipright *)(c->entry))->a1;
            }
            else {
               ((struct str_Skipright *)(c->entry))->a1 = (*((struct str_Skipright *)(c->entry))->f1)(((struct str_Skipright *)(c->entry))->i1, ((struct str_Skipright *)(c->entry))->j1, ((struct str_Skipright *)(c->entry))->diff1);
               ((struct str_Skipright *)(c->entry))->pp_init_a1 = ((struct str_Skipright *)(c->entry))->a1;
            }
         };
      }
   }
   return(l);
}

/* pksOnly defines whether we need to do a suboptimal backtrace inside a pseudoknot */
#define whichDiff(D) ((pksOnly) ? 0 : (D))

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
            update_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure4->item, whichDiff(diff));
         }
         else {
            ((struct str_Pk_Pr *)(c->entry))->diff4 = whichDiff(diff);
         }
         if (((struct str_Pk_Pr *)(c->entry))->isStructure7) {
            update_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure7->item, whichDiff(diff));
         }
         else {
            ((struct str_Pk_Pr *)(c->entry))->diff7 = whichDiff(diff);
         }
         if (((struct str_Pk_Pr *)(c->entry))->isStructure10) {
            update_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure10->item, whichDiff(diff));
         }
         else {
            ((struct str_Pk_Pr *)(c->entry))->diff10 = whichDiff(diff);
         }
      } else 
      if (c->utype == SIGID_Scale) {
         if (((struct str_Scale *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Scale *)(c->entry))->structure2->item, diff);
         }
         else {
	   // scale the suboptimal diff value also (a5-a1 holds the length of the pseudoknot):
            ((struct str_Scale *)(c->entry))->diff2 = 
               (diff * (((struct str_Scale *)(c->entry))->a5 - ((struct str_Scale *)(c->entry))->a1)) / RFACTOR;
         }
      } else 
      if (c->utype == SIGID_Unscale) {
         if (((struct str_Unscale *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Unscale *)(c->entry))->structure1->item, diff);
         }
         else {
	   // unscale the suboptimal diff value also (a2 holds the length of the pseudoknot):
            ((struct str_Unscale *)(c->entry))->diff1 = (diff * RFACTOR) / ((struct str_Unscale *)(c->entry))->a2;
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
      } else 
      if (c->utype == SIGID_Skipleft) {
         if (((struct str_Skipleft *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Skipleft *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Skipleft *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Skipright) {
         if (((struct str_Skipright *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Skipright *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Skipright *)(c->entry))->diff1 = diff;
         }
      };
   }
}

/* table access                                                                     */
/* -------------------------------------------------------------------------------- */

static int *offset;

#define tbl_bestPK(I, J) arr_bestPK[(I)]
#define tbl_bestPK1(I, J) arr_bestPK1[offset[(J)]+(I)]
#define tbl_closed(I, J) arr_closed[offset[(J)]+(I)]
#define tbl_comps(I, J) arr_comps[offset[(J)]+(I)]
#define tbl_block(I, J) arr_block[offset[(J)]+(I)]
#define tbl_knot(I, J) arr_knot[offset[(J)]+(I)]
#define tbl_stacklen(I, J) arr_stacklen[offset[(J)]+(I)]

/* table declarations                                                               */
/* -------------------------------------------------------------------------------- */

static struct str1 *arr_bestPK;
static struct str1 *arr_bestPK1;
static int *arr_closed;
static int *arr_comps;
static int *arr_block;
static struct str2 *arr_knot;
static struct str3 *arr_stacklen;

/* forward declarations                                                             */
/* -------------------------------------------------------------------------------- */

static int calc_bestPK_Ax(int i, int j);

/* table calculations                                                               */
/* -------------------------------------------------------------------------------- */

/* table calculation for production bestPK_Ax                                       */
/* -------------------------------------------------------------------------------- */
static int calc_bestPK_Ax(int i, int j)
{
   int v1;

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------------- v1 = unscale <<< p bestPK ------------------------- */
   if ((j-i) >= 11) {
      v1 = (tbl_bestPK(i, j).tup1 * tbl_bestPK(i, j).tup2) / RFACTOR;
   }
   else {
      v1 = 1.0e7;
   }
   /* ------------------------- v1 = unscale <<< p bestPK ------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   return(v1);
}

/* table calculation for production bestPK                                          */
/* -------------------------------------------------------------------------------- */
static void calc_bestPK(int i, int j)
{
   struct str1 v1, v2, v3;

   if ((j-i) >= 11) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v1 = skipleft <<< lbase ~~~ p bestPK ------------------ */
      if ((j-i) >= 12) {
         v1.tup1 = tbl_bestPK(i+1, j).tup1;
         v1.tup2 = tbl_bestPK(i+1, j).tup2;
         v1.tup3 = tbl_bestPK(i+1, j).tup3;
         v1.tup4 = tbl_bestPK(i+1, j).tup4;
      }
      else {
         v1.tup1 = 1.0e7;
         v1.tup2 = 0;
         v1.tup3 = 0;
         v1.tup4 = 0;
      }
      /* ------------------ v1 = skipleft <<< lbase ~~~ p bestPK ------------------ */
      /* -------------------------------- finished -------------------------------- */

      /* ----------------------------- v2 = p bestPK1 ----------------------------- */
      v2 = tbl_bestPK1(i, j);
      /* -------------------------- v3 = minimum(v1, v2) -------------------------- */
      v3 = v1.tup1 < v2.tup1 ? v1 : v2;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_bestPK(i, j) = v3;
   }
}

/* table calculation for production bestPK1                                         */
/* -------------------------------------------------------------------------------- */
static void calc_bestPK1(int i, int j)
{
   struct str1 v1, v2, v3;

   if ((j-i) >= 11) {
      /* -------------------------------- start of -------------------------------- */
      /* ----------------- v1 = skipright <<< p bestPK1 ~~~ lbase ----------------- */
      if ((j-i) >= 12) {
         v1.tup1 = tbl_bestPK1(i, j-1).tup1;
         v1.tup2 = tbl_bestPK1(i, j-1).tup2;
         v1.tup3 = tbl_bestPK1(i, j-1).tup3;
         v1.tup4 = tbl_bestPK1(i, j-1).tup4;
      }
      else {
         v1.tup1 = 1.0e7;
         v1.tup2 = 0;
         v1.tup3 = 0;
         v1.tup4 = 0;
      }
      /* ----------------- v1 = skipright <<< p bestPK1 ~~~ lbase ----------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ----------------- v2 = scale <<< loc ~~~ p knot ~~~ loc ------------------ */
      if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
         v2.tup1 = (tbl_knot(i, j).tup1 * RFACTOR) / ((j) - (i));
         v2.tup2 = (j) - (i);
         v2.tup3 = i;
         v2.tup4 = j;
      }
      else {
         v2.tup1 = 1.0e7;
         v2.tup2 = 0;
         v2.tup3 = 0;
         v2.tup4 = 0;
      }
      /* ----------------- v2 = scale <<< loc ~~~ p knot ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------- v3 = minimum(v1, v2) -------------------------- */
      v3 = v1.tup1 < v2.tup1 ? v1 : v2;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_bestPK1(i, j) = v3;
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

/* table calculation for production block                                           */
/* -------------------------------------------------------------------------------- */
static void calc_block(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10;
   int k;

   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ------ v1 = ul <<< drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s ------ */
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
      /* ------ v1 = ul <<< drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s ------ */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* 7 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s */
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
      /* 7 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s */
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
      tbl_block(i, j) = v10;
   }
}

/* table calculation for production knot                                            */
/* -------------------------------------------------------------------------------- */
static void calc_knot(int i, int j)
{
   int v2, v3, v4, v5, v6, v7, v8, v9;
   int v10, v11, v12, v13, v14, v15, v16, v17, v18;
   struct str2 v1, v19;
   int lc_alphanrg, lc_betalen, lc_betanrg, lc_correctionterm, lc_energy;
   int lc_h, lc_h_Pr, lc_k, lc_l, lc_middle_k, lc_middle_l;

   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      /* -------------------------------- start of -------------------------------- */
      /* ----- v19 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
      v19.tup1 = 1.0e7;
      v19.tup2 = 0;
      v19.tup3 = 0;
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
                  v5 = v2 < v4 ? v2 : v4;
                  /* -------------------------- start of -------------------------- */
                  /* ------ v6 = emptymid lc_middle_k lc_middle_l <<< empty ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 0) {
                     v6 = wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, lc_l+lc_h_Pr, (lc_l+lc_h_Pr) + 1);
                  }
                  else {
                     v6 = 1.0e7;
                  }
                  /* ------ v6 = emptymid lc_middle_k lc_middle_l <<< empty ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* ------- v7 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 1) {
                     v7 = (wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, (lc_k-lc_h) - 1, (lc_k-lc_h) + 1)) + npp;
                  }
                  else {
                     v7 = 1.0e7;
                  }
                  /* ------- v7 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* v8 = midregion <<< pul <<< pss <<< region ||| p comps ... h_l  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v9 = pul <<< pss <<< region --------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v10 = pss <<< region ------------------ */
                     v10 = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr));
                     /* ------------------- v10 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v9 = v10;
                     /* --------------- v9 = pul <<< pss <<< region --------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v11 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 7) {
                        v11 = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h);
                     }
                     else {
                        v11 = 1.0e7;
                     }
                     v12 = v9 < v11 ? v9 : v11;
                     v8 = v12;
                  }
                  else {
                     v8 = 1.0e7;
                  }
                  /* v8 = midregion <<< pul <<< pss <<< region ||| p comps ... h_l  */
                  /* -------------------------- finished -------------------------- */

                  v13 = v7 < v8 ? v7 : v8;
                  v14 = v6 < v13 ? v6 : v13;
                  /* -------------------------- start of -------------------------- */
                  /* --------------- v15 = pul <<< pss <<< uregion ---------------- */
                  if ((j-lc_h_Pr-lc_k-2) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v16 = pss <<< uregion ------------------ */
                     v16 = sspenalty((j-lc_h_Pr-2) - (lc_k));
                     /* ------------------ v16 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v15 = v16;
                  }
                  else {
                     v15 = 1.0e7;
                  }
                  /* --------------- v15 = pul <<< pss <<< uregion ---------------- */
                  /* -------------------------- finished -------------------------- */

                  /* ----------------------- v17 = p comps ------------------------ */
                  if ((j-lc_h_Pr-lc_k-2) >= 7) {
                     v17 = tbl_comps(lc_k, j-lc_h_Pr-2);
                  }
                  else {
                     v17 = 1.0e7;
                  }
                  v18 = v15 < v17 ? v15 : v17;
                  v1.tup1 = (((((pkinit + lc_energy) + (3 * npp)) + v5) + v14) + v18) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j);
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
            /* ---------------------- v19 = minimum(v1, v19) ---------------------- */
            v19 = v1.tup1 < v19.tup1 ? v1 : v19;
         }
      }
      /* ----- v19 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
      /* -------------------------------- finished -------------------------------- */

      /* ----------------------- assign table entry result ------------------------ */
      tbl_knot(i, j) = v19;
   }
}

/* table calculation for production stacklen                                        */
/* -------------------------------------------------------------------------------- */
static void calc_stacklen(int i, int j)
{
   struct str3 v1, v2, v3, v4, v5;

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

static struct str4 *back_closed(int i, int j, int diff);

static struct str4 *back_knot(int i, int j, int diff);

static struct str4 *back_stacklen(int i, int j, int diff);

static struct str4 *back_bestPK1(int i, int j, int diff);

static struct str4 *back_block(int i, int j, int diff);

static struct str4 *back_bestPK(int i, int j, int diff);

static struct str4 *back_comps(int i, int j, int diff);

static struct str4 *back_bestPK_Ax(int i, int j, int diff);

/* backtracing code                                                                 */
/* -------------------------------------------------------------------------------- */

/* backtracing code for production bestPK_Ax                                        */
/* -------------------------------------------------------------------------------- */
static struct str4 *back_bestPK_Ax(int i, int j, int diff)
{
   struct str4 *v7;
   int v3;
   struct str6 *v1, *v2, *v4, *v5, *v6;

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------------- v1 = unscale <<< p bestPK ------------------------- */
   if ((j-i) >= 11) {
      v1=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
      v1->next = NULL;
      v1->last = v1;
      v1->item.alg_energy = (tbl_bestPK(i, j).tup1 * tbl_bestPK(i, j).tup2) / RFACTOR;
      v1->item.alg_enum = new_Unscale_f(back_bestPK, i, j, tbl_bestPK(i, j).tup2, tbl_bestPK(i, j).tup3, tbl_bestPK(i, j).tup4);
   }
   else {
      v1 = NULL;
   }
   /* ------------------------- v1 = unscale <<< p bestPK ------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------ v3 = minimum(v1) ----------------------------- */
   v3 = 1.0e7;
   v2 = v1;
   while (v2 != NULL) {
      v3 = v3 < v2->item.alg_energy ? v3 : v2->item.alg_energy;
      v2 = v2->next;
   }
   v2 = v1;
   v5 = NULL;
   while (v2 != NULL) {
      if (abs(v3 - v2->item.alg_energy) <= diff) {
         update_str_Signature(v2->item.alg_enum->item, diff - abs(v3 - v2->item.alg_energy));
         v4=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
         v4->item = v2->item;
         v4->next = NULL;
         v4->last = v4;
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
      v2 = v2->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v6 = v5;
   v7 = NULL;
   while (v6 != NULL) {
      /* ---------------------- v7 = v6->item.alg_enum ++ v7 ---------------------- */
      if (v6->item.alg_enum == NULL) {
      } else 
      if (v7 == NULL) {
         v7 = v6->item.alg_enum;
      }
      else {
         v6->item.alg_enum->last->next = v7;
         v6->item.alg_enum->last = v7->last;
         v7 = v6->item.alg_enum;
      }
      v6 = v6->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v7)));
}

/* backtracing code for production bestPK                                           */
/* -------------------------------------------------------------------------------- */
static struct str4 *back_bestPK(int i, int j, int diff)
{
   struct str4 *v9;
   struct str1 v5;
   struct str8 *v1, *v2, *v3, *v4, *v6, *v7, *v8;

   /* ---------------------------------- start of --------------------------------- */
   /* -------------------- v1 = skipleft <<< lbase ~~~ p bestPK ------------------- */
   if ((j-i) >= 12) {
      if (abs(tbl_bestPK(i, j).tup1 - tbl_bestPK(i+1, j).tup1) <= diff) {
         v1=(struct str8 *) myalloc(adp_dynmem, sizeof(struct str8 ));
         v1->next = NULL;
         v1->last = v1;
         v1->item.alg_energy.tup1 = tbl_bestPK(i+1, j).tup1;
         v1->item.alg_energy.tup2 = tbl_bestPK(i+1, j).tup2;
         v1->item.alg_energy.tup3 = tbl_bestPK(i+1, j).tup3;
         v1->item.alg_energy.tup4 = tbl_bestPK(i+1, j).tup4;
         v1->item.alg_enum = new_Skipleft_f(i+1, back_bestPK, i+1, j, tbl_bestPK(i+1, j).tup2, tbl_bestPK(i+1, j).tup3, tbl_bestPK(i+1, j).tup4);
      }
      else {
         v1 = NULL;
      }
   }
   else {
      v1 = NULL;
   }
   /* -------------------- v1 = skipleft <<< lbase ~~~ p bestPK ------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------- v2 = p bestPK1 ------------------------------ */
   /* +---------------------------------------------------------------------------- */
   /* Nonterminal bestPK1 is implemented as a tabulated                             */
   /* function which yields atomar results. Since we are in list context,           */
   /* we need to wrap the result of bestPK1 into a single list element.             */
   /* +---------------------------------------------------------------------------- */
   if ((j-i) >= 11) {
      v2=(struct str8 *) myalloc(adp_dynmem, sizeof(struct str8 ));
      v2->item.alg_energy = tbl_bestPK1(i, j);
      v2->item.alg_enum = new__NTID(back_bestPK1, i, j);
      v2->next = NULL;
      v2->last = v2;
   }
   else {
      v2 = NULL;
   }
   /* ------------------------------- v3 = v1 ++ v2 ------------------------------- */
   if (v1 == NULL) {
      v3 = v2;
   } else 
   if (v2 == NULL) {
      v3 = v1;
   }
   else {
      v1->last->next = v2;
      v1->last = v2->last;
      v3 = v1;
   }
   /* ------------------------------ v5 = minimum(v3) ----------------------------- */
   v5.tup1 = 1.0e7;
   v5.tup2 = 0;
   v5.tup3 = 0;
   v5.tup4 = 0;
   v4 = v3;
   while (v4 != NULL) {
      /* ----------------- v5 = minimum(v5, v4->item.alg_energy) ------------------ */
      v5 = v5.tup1 < v4->item.alg_energy.tup1 ? v5 : v4->item.alg_energy;
      v4 = v4->next;
   }
   v4 = v3;
   v7 = NULL;
   while (v4 != NULL) {
      if (abs(v5.tup1 - v4->item.alg_energy.tup1) <= diff) {
         update_str_Signature(v4->item.alg_enum->item, diff - abs(v5.tup1 - v4->item.alg_energy.tup1));
         v6=(struct str8 *) myalloc(adp_dynmem, sizeof(struct str8 ));
         v6->item = v4->item;
         v6->next = NULL;
         v6->last = v6;
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
      v4 = v4->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v8 = v7;
   v9 = NULL;
   while (v8 != NULL) {
      /* ---------------------- v9 = v8->item.alg_enum ++ v9 ---------------------- */
      if (v8->item.alg_enum == NULL) {
      } else 
      if (v9 == NULL) {
         v9 = v8->item.alg_enum;
      }
      else {
         v8->item.alg_enum->last->next = v9;
         v8->item.alg_enum->last = v9->last;
         v9 = v8->item.alg_enum;
      }
      v8 = v8->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v9)));
}

/* backtracing code for production bestPK1                                          */
/* -------------------------------------------------------------------------------- */
static struct str4 *back_bestPK1(int i, int j, int diff)
{
   struct str4 *v9;
   struct str1 v5;
   struct str8 *v1, *v2, *v3, *v4, *v6, *v7, *v8;

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------- v1 = skipright <<< p bestPK1 ~~~ lbase ------------------ */
   if ((j-i) >= 12) {
      if (abs(tbl_bestPK1(i, j).tup1 - tbl_bestPK1(i, j-1).tup1) <= diff) {
         v1=(struct str8 *) myalloc(adp_dynmem, sizeof(struct str8 ));
         v1->next = NULL;
         v1->last = v1;
         v1->item.alg_energy.tup1 = tbl_bestPK1(i, j-1).tup1;
         v1->item.alg_energy.tup2 = tbl_bestPK1(i, j-1).tup2;
         v1->item.alg_energy.tup3 = tbl_bestPK1(i, j-1).tup3;
         v1->item.alg_energy.tup4 = tbl_bestPK1(i, j-1).tup4;
         v1->item.alg_enum = new_Skipright_f(back_bestPK1, i, j-1, tbl_bestPK1(i, j-1).tup2, tbl_bestPK1(i, j-1).tup3, tbl_bestPK1(i, j-1).tup4, j);
      }
      else {
         v1 = NULL;
      }
   }
   else {
      v1 = NULL;
   }
   /* ------------------- v1 = skipright <<< p bestPK1 ~~~ lbase ------------------ */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------- v2 = scale <<< loc ~~~ p knot ~~~ loc ------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      if (abs(tbl_bestPK1(i, j).tup1 - ((tbl_knot(i, j).tup1 * RFACTOR) / ((j) - (i)))) <= diff) {
         v2=(struct str8 *) myalloc(adp_dynmem, sizeof(struct str8 ));
         v2->next = NULL;
         v2->last = v2;
         v2->item.alg_energy.tup1 = (tbl_knot(i, j).tup1 * RFACTOR) / ((j) - (i));
         v2->item.alg_energy.tup2 = (j) - (i);
         v2->item.alg_energy.tup3 = i;
         v2->item.alg_energy.tup4 = j;
         v2->item.alg_enum = new_Scale_f(i, back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3, j);
      }
      else {
         v2 = NULL;
      }
   }
   else {
      v2 = NULL;
   }
   /* ------------------- v2 = scale <<< loc ~~~ p knot ~~~ loc ------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------- v3 = v1 ++ v2 ------------------------------- */
   if (v1 == NULL) {
      v3 = v2;
   } else 
   if (v2 == NULL) {
      v3 = v1;
   }
   else {
      v1->last->next = v2;
      v1->last = v2->last;
      v3 = v1;
   }
   /* ------------------------------ v5 = minimum(v3) ----------------------------- */
   v5.tup1 = 1.0e7;
   v5.tup2 = 0;
   v5.tup3 = 0;
   v5.tup4 = 0;
   v4 = v3;
   while (v4 != NULL) {
      /* ----------------- v5 = minimum(v5, v4->item.alg_energy) ------------------ */
      v5 = v5.tup1 < v4->item.alg_energy.tup1 ? v5 : v4->item.alg_energy;
      v4 = v4->next;
   }
   v4 = v3;
   v7 = NULL;
   while (v4 != NULL) {
      if (abs(v5.tup1 - v4->item.alg_energy.tup1) <= diff) {
         update_str_Signature(v4->item.alg_enum->item, diff - abs(v5.tup1 - v4->item.alg_energy.tup1));
         v6=(struct str8 *) myalloc(adp_dynmem, sizeof(struct str8 ));
         v6->item = v4->item;
         v6->next = NULL;
         v6->last = v6;
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
      v4 = v4->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v8 = v7;
   v9 = NULL;
   while (v8 != NULL) {
      /* ---------------------- v9 = v8->item.alg_enum ++ v9 ---------------------- */
      if (v8->item.alg_enum == NULL) {
      } else 
      if (v9 == NULL) {
         v9 = v8->item.alg_enum;
      }
      else {
         v8->item.alg_enum->last->next = v9;
         v8->item.alg_enum->last = v9->last;
         v9 = v8->item.alg_enum;
      }
      v8 = v8->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v9)));
}

/* backtracing code for production closed                                           */
/* -------------------------------------------------------------------------------- */
static struct str4 *back_closed(int i, int j, int diff)
{
   struct str4 *v49;
   int v10, v19, v25, v35, v45;
   struct str6 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v11;
   struct str6 *v12, *v13, *v14, *v15, *v16, *v17, *v18, *v20, *v21, *v22, *v23;
   struct str6 *v24, *v26, *v27, *v28, *v29, *v30, *v31, *v32, *v33, *v34, *v36;
   struct str6 *v37, *v38, *v39, *v40, *v41, *v42, *v43, *v44, *v46, *v47, *v48;
   int k, k2, k3, k4, k5;

   if (basepairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v1 = sr <<< lbase ~~~ p closed ~~~ lbase ---------------- */
      if ((j-i) >= 9) {
         if (abs(tbl_closed(i, j) - (tbl_closed(i+1, j-1) + sr_energy(i+1, j))) <= diff) {
            v1=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v3=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
               v5=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v4=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v11=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
               v14=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v13=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v20=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v22=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v26=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v29=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v28=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
      /* --------------------------- v35 = minimum(v33) --------------------------- */
      v35 = 1.0e7;
      v34 = v33;
      while (v34 != NULL) {
         v35 = v35 < v34->item.alg_energy ? v35 : v34->item.alg_energy;
         v34 = v34->next;
      }
      v34 = v33;
      v37 = NULL;
      while (v34 != NULL) {
         if (abs(v35 - v34->item.alg_energy) <= diff) {
            update_str_Signature(v34->item.alg_enum->item, diff - abs(v35 - v34->item.alg_energy));
            v36=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
            v36->item = v34->item;
            v36->next = NULL;
            v36->last = v36;
            /* ------------------------- v37 = v36 ++ v37 ------------------------- */
            if (v36 == NULL) {
            } else 
            if (v37 == NULL) {
               v37 = v36;
            }
            else {
               v36->last->next = v37;
               v36->last = v37->last;
               v37 = v36;
            }
         }
         v34 = v34->next;
      }
      /* ---------------------------- v38 = v27 ++ v37 ---------------------------- */
      if (v27 == NULL) {
         v38 = v37;
      } else 
      if (v37 == NULL) {
         v38 = v27;
      }
      else {
         v27->last->next = v37;
         v27->last = v37->last;
         v38 = v27;
      }
      /* ---------------------------- v39 = v21 ++ v38 ---------------------------- */
      if (v21 == NULL) {
         v39 = v38;
      } else 
      if (v38 == NULL) {
         v39 = v21;
      }
      else {
         v21->last->next = v38;
         v21->last = v38->last;
         v39 = v21;
      }
      /* ---------------------------- v40 = v12 ++ v39 ---------------------------- */
      if (v12 == NULL) {
         v40 = v39;
      } else 
      if (v39 == NULL) {
         v40 = v12;
      }
      else {
         v12->last->next = v39;
         v12->last = v39->last;
         v40 = v12;
      }
      /* ---------------------------- v41 = v3 ++ v40 ----------------------------- */
      if (v3 == NULL) {
         v41 = v40;
      } else 
      if (v40 == NULL) {
         v41 = v3;
      }
      else {
         v3->last->next = v40;
         v3->last = v40->last;
         v41 = v3;
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
         v46=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
static struct str4 *back_comps(int i, int j, int diff)
{
   struct str4 *v13;
   int v9;
   struct str6 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v10, *v11, *v12;
   int k, k2;

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v2 = cons <<< p block ~~~ p comps --------------------- */
   if ((j-i) >= 14) {
      v2 = NULL;
      for (k=i+7; k<=j-7; k++) {
         if (abs(tbl_comps(i, j) - (tbl_block(i, k) + tbl_comps(k, j))) <= diff) {
            v1=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
      v3=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v4=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
         v10=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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

/* backtracing code for production block                                            */
/* -------------------------------------------------------------------------------- */
static struct str4 *back_block(int i, int j, int diff)
{
   struct str4 *v32;
   int v7, v18, v28;
   struct str6 *v1, *v2, *v3, *v4, *v5, *v6, *v8, *v9, *v10;
   struct str6 *v11, *v12, *v13, *v14, *v15, *v16, *v17, *v19, *v20;
   struct str6 *v21, *v22, *v23, *v24, *v25, *v26, *v27, *v29, *v30, *v31;
   int k;

   /* ---------------------------------- start of --------------------------------- */
   /* ------- v10 = ul <<< drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s ------- */
   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------- v4 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v3 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      if (abs(tbl_block(i, j) - (40 + (tbl_closed(i, j) + termaupenalty((i) + 1, j)))) <= diff) {
         v3=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v2=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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

      /* ---------------------------- v7 = minimum(v4) ---------------------------- */
      v7 = 1.0e7;
      v6 = v4;
      while (v6 != NULL) {
         v7 = v7 < v6->item.alg_energy ? v7 : v6->item.alg_energy;
         v6 = v6->next;
      }
      v6 = v4;
      v9 = NULL;
      while (v6 != NULL) {
         if (abs(v7 - v6->item.alg_energy) <= diff) {
            update_str_Signature(v6->item.alg_enum->item, diff - abs(v7 - v6->item.alg_energy));
            v8=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
            v8->item = v6->item;
            v8->next = NULL;
            v8->last = v8;
            /* -------------------------- v9 = v8 ++ v9 --------------------------- */
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
      v10 = NULL;
      /* +------------------------------------------------------------------------- */
      /* v1 stores the result of a single application of algebra function           */
      /* v9 holds the results of expression                                         */
      /*      drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s                      */
      /*                                                                            */
      /* we use v11 to iterate over v9 and                                          */
      /* v10 to collect the results                                                 */
      /* +------------------------------------------------------------------------- */
      v11 = v9;
      while (v11 != NULL) {
         if (abs(tbl_block(i, j) - (40 + v11->item.alg_energy)) <= diff) {
            v1=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = 40 + v11->item.alg_energy;
            v1->item.alg_enum = new_Ul_s(v11->item.alg_enum);
         }
         else {
            v1 = NULL;
         }
         /* --------------------------- v10 = v1 ++ v10 --------------------------- */
         if (v1 == NULL) {
         } else 
         if (v10 == NULL) {
            v10 = v1;
         }
         else {
            v1->last->next = v10;
            v1->last = v10->last;
            v10 = v1;
         }
         v11 = v11->next;
      }
   }
   else {
      v10 = NULL;
   }
   /* ------- v10 = ul <<< drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s ------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /*  v23 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s) - */
   if ((j-i) >= 8) {
      v23 = NULL;
      for (k=i+1; k<=j-7; k++) {
         /* ------------------------------- start of ------------------------------ */
         /* ------------ v15 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
         /* ------------------------------- start of ------------------------------ */
         /* ---------------- v14 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         if (abs(tbl_block(i, j) - ((40 + (tbl_closed(k, j) + termaupenalty((k) + 1, j))) + ss_energy(i, k))) <= diff) {
            v14=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
            v14->next = NULL;
            v14->last = v14;
            v14->item.alg_energy = tbl_closed(k, j) + termaupenalty((k) + 1, j);
            v14->item.alg_enum = new_Is_f(k, back_closed, k, j, j);
         }
         else {
            v14 = NULL;
         }
         /* ---------------- v14 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

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
            if (abs(tbl_block(i, j) - ((40 + v16->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v13=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
               v13->next = NULL;
               v13->last = v13;
               v13->item.alg_energy = v16->item.alg_energy;
               v13->item.alg_enum = new_Drem_s(v16->item.alg_enum);
            }
            else {
               v13 = NULL;
            }
            /* ------------------------- v15 = v13 ++ v15 ------------------------- */
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
         /* ------------ v15 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
         /* ------------------------------- finished ------------------------------ */

         /* -------------------------- v18 = minimum(v15) ------------------------- */
         v18 = 1.0e7;
         v17 = v15;
         while (v17 != NULL) {
            v18 = v18 < v17->item.alg_energy ? v18 : v17->item.alg_energy;
            v17 = v17->next;
         }
         v17 = v15;
         v20 = NULL;
         while (v17 != NULL) {
            if (abs(v18 - v17->item.alg_energy) <= diff) {
               update_str_Signature(v17->item.alg_enum->item, diff - abs(v18 - v17->item.alg_energy));
               v19=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
               v19->item = v17->item;
               v19->next = NULL;
               v19->last = v19;
               /* ------------------------ v20 = v19 ++ v20 ----------------------- */
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
         v21 = NULL;
         /* +-------------------------------------------------------------------------- */
         /* v12 stores the result of a single application of algebra function           */
         /* v20 holds the results of expression                                         */
         /*      drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s                       */
         /*                                                                             */
         /* we use v22 to iterate over v20 and                                          */
         /* v21 to collect the results                                                  */
         /* +-------------------------------------------------------------------------- */
         v22 = v20;
         while (v22 != NULL) {
            if (abs(tbl_block(i, j) - ((40 + v22->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v12=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
               v12->next = NULL;
               v12->last = v12;
               v12->item.alg_energy = (40 + v22->item.alg_energy) + ss_energy(i, k);
               v12->item.alg_enum = new_Ssadd_s(i, k, v22->item.alg_enum);
            }
            else {
               v12 = NULL;
            }
            /* ------------------------- v21 = v12 ++ v21 ------------------------- */
            if (v12 == NULL) {
            } else 
            if (v21 == NULL) {
               v21 = v12;
            }
            else {
               v12->last->next = v21;
               v12->last = v21->last;
               v21 = v12;
            }
            v22 = v22->next;
         }
         /* --------------------------- v23 = v21 ++ v23 -------------------------- */
         if (v21 == NULL) {
         } else 
         if (v23 == NULL) {
            v23 = v21;
         }
         else {
            v21->last->next = v23;
            v21->last = v23->last;
            v23 = v21;
         }
      }
   }
   else {
      v23 = NULL;
   }
   /*  v23 = ssadd <<< region ~~~ (drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s) - */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------------- v24 = pkml <<< p knot --------------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      if (abs(tbl_block(i, j) - (tbl_knot(i, j).tup1 + 600)) <= diff) {
         v24=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
         v24->next = NULL;
         v24->last = v24;
         v24->item.alg_energy = tbl_knot(i, j).tup1 + 600;
         v24->item.alg_enum = new_Pkml_f(back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3);
      }
      else {
         v24 = NULL;
      }
   }
   else {
      v24 = NULL;
   }
   /* --------------------------- v24 = pkml <<< p knot --------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------ v25 = v23 ++ v24 ----------------------------- */
   if (v23 == NULL) {
      v25 = v24;
   } else 
   if (v24 == NULL) {
      v25 = v23;
   }
   else {
      v23->last->next = v24;
      v23->last = v24->last;
      v25 = v23;
   }
   /* ------------------------------ v26 = v10 ++ v25 ----------------------------- */
   if (v10 == NULL) {
      v26 = v25;
   } else 
   if (v25 == NULL) {
      v26 = v10;
   }
   else {
      v10->last->next = v25;
      v10->last = v25->last;
      v26 = v10;
   }
   /* ----------------------------- v28 = minimum(v26) ---------------------------- */
   v28 = 1.0e7;
   v27 = v26;
   while (v27 != NULL) {
      v28 = v28 < v27->item.alg_energy ? v28 : v27->item.alg_energy;
      v27 = v27->next;
   }
   v27 = v26;
   v30 = NULL;
   while (v27 != NULL) {
      if (abs(v28 - v27->item.alg_energy) <= diff) {
         update_str_Signature(v27->item.alg_enum->item, diff - abs(v28 - v27->item.alg_energy));
         v29=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
         v29->item = v27->item;
         v29->next = NULL;
         v29->last = v29;
         /* --------------------------- v30 = v29 ++ v30 -------------------------- */
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
      v27 = v27->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v31 = v30;
   v32 = NULL;
   while (v31 != NULL) {
      /* -------------------- v32 = v31->item.alg_enum ++ v32 --------------------- */
      if (v31->item.alg_enum == NULL) {
      } else 
      if (v32 == NULL) {
         v32 = v31->item.alg_enum;
      }
      else {
         v31->item.alg_enum->last->next = v32;
         v31->item.alg_enum->last = v32->last;
         v32 = v31->item.alg_enum;
      }
      v31 = v31->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v32)));
}

/* backtracing code for production knot                                             */
/* -------------------------------------------------------------------------------- */
static struct str4 *back_knot(int i, int j, int diff)
{
   struct str4 *v53;
   struct str2 v49;
   int v9, v22, v30, v40;
   struct str6 *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v10, *v11, *v12;
   struct str6 *v13, *v14, *v15, *v16, *v17, *v18, *v19, *v20, *v21, *v23;
   struct str6 *v24, *v25, *v26, *v27, *v28, *v29, *v31, *v32, *v33, *v34;
   struct str6 *v35, *v36, *v37, *v38, *v39, *v41, *v42, *v44, *v45, *v46;
   struct str10 *v1, *v43, *v47, *v48, *v50, *v51, *v52;
   int lc_alphanrg, lc_betalen, lc_betanrg, lc_correctionterm, lc_energy;
   int lc_h, lc_h_Pr, lc_k, lc_l, lc_middle_k, lc_middle_l;

   /* ---------------------------------- start of --------------------------------- */
   /* ------- v47 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------- */
   if ((j-i) >= 0) {
      v47 = NULL;
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
                     v3=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                        v2=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                     v6=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v6->item.alg_energy = tbl_comps(i+lc_h+1, lc_l);
                     v6->item.alg_enum = new__NTID(back_comps, i+lc_h+1, lc_l);
                     v6->next = NULL;
                     v6->last = v6;
                  }
                  else {
                     v6 = NULL;
                  }
                  /* ----------------------- v7 = v4 ++ v6 ------------------------ */
                  if (v4 == NULL) {
                     v7 = v6;
                  } else 
                  if (v6 == NULL) {
                     v7 = v4;
                  }
                  else {
                     v4->last->next = v6;
                     v4->last = v6->last;
                     v7 = v4;
                  }
                  /* ---------------------- v9 = minimum(v7) ---------------------- */
                  v9 = 1.0e7;
                  v8 = v7;
                  while (v8 != NULL) {
                     v9 = v9 < v8->item.alg_energy ? v9 : v8->item.alg_energy;
                     v8 = v8->next;
                  }
                  v8 = v7;
                  v11 = NULL;
                  while (v8 != NULL) {
                     if (abs(v9 - v8->item.alg_energy) <= whichDiff(diff)) {
                        update_str_Signature(v8->item.alg_enum->item, diff - abs(v9 - v8->item.alg_energy));
                        v10=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v10->item = v8->item;
                        v10->next = NULL;
                        v10->last = v10;
                        /* ------------------- v11 = v10 ++ v11 ------------------- */
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
                  /* -------------------------- start of -------------------------- */
                  /* ------ v12 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 0) {
                     v12=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v12->next = NULL;
                     v12->last = v12;
                     v12->item.alg_energy = wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, lc_l+lc_h_Pr, (lc_l+lc_h_Pr) + 1);
                     v12->item.alg_enum = new_Emptymid_(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr);
                  }
                  else {
                     v12 = NULL;
                  }
                  /* ------ v12 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* ------ v13 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 1) {
                     v13=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v13->next = NULL;
                     v13->last = v13;
                     v13->item.alg_energy = (wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, (lc_k-lc_h) - 1, (lc_k-lc_h) + 1)) + npp;
                     v13->item.alg_enum = new_Midbase_(lc_middle_k, lc_middle_l, lc_k-lc_h);
                  }
                  else {
                     v13 = NULL;
                  }
                  /* ------ v13 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* v25 = midregion <<< pul <<< pss <<< region ||| p comps ... h_l */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v17 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v16 = pss <<< region ------------------ */
                     v16=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v16->next = NULL;
                     v16->last = v16;
                     v16->item.alg_energy = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr));
                     v16->item.alg_enum = new_Pss_(lc_l+lc_h_Pr, lc_k-lc_h);
                     /* ------------------- v16 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v17 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v15 stores the result of a single application of algebra function           */
                     /* v16 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v18 to iterate over v16 and                                          */
                     /* v17 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v18 = v16;
                     while (v18 != NULL) {
                        v15=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v15->next = NULL;
                        v15->last = v15;
                        v15->item.alg_energy = v18->item.alg_energy;
                        v15->item.alg_enum = new_Pul_s(v18->item.alg_enum);
                        /* ------------------- v17 = v15 ++ v17 ------------------- */
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
                        v18 = v18->next;
                     }
                     /* --------------- v17 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v19 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 7) {
                        v19=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v19->item.alg_energy = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h);
                        v19->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr, lc_k-lc_h);
                        v19->next = NULL;
                        v19->last = v19;
                     }
                     else {
                        v19 = NULL;
                     }
                     /* --------------------- v20 = v17 ++ v19 -------------------- */
                     if (v17 == NULL) {
                        v20 = v19;
                     } else 
                     if (v19 == NULL) {
                        v20 = v17;
                     }
                     else {
                        v17->last->next = v19;
                        v17->last = v19->last;
                        v20 = v17;
                     }
                     /* -------------------- v22 = minimum(v20) ------------------- */
                     v22 = 1.0e7;
                     v21 = v20;
                     while (v21 != NULL) {
                        v22 = v22 < v21->item.alg_energy ? v22 : v21->item.alg_energy;
                        v21 = v21->next;
                     }
                     v21 = v20;
                     v24 = NULL;
                     while (v21 != NULL) {
                        if (abs(v22 - v21->item.alg_energy) <= whichDiff(diff)) {
                           update_str_Signature(v21->item.alg_enum->item, diff - abs(v22 - v21->item.alg_energy));
                           v23=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                           v23->item = v21->item;
                           v23->next = NULL;
                           v23->last = v23;
                           /* ------------------ v24 = v23 ++ v24 ----------------- */
                           if (v23 == NULL) {
                           } else 
                           if (v24 == NULL) {
                              v24 = v23;
                           }
                           else {
                              v23->last->next = v24;
                              v23->last = v24->last;
                              v24 = v23;
                           }
                        }
                        v21 = v21->next;
                     }
                     v25 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v14 stores the result of a single application of algebra function           */
                     /* v24 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ... h_l                             */
                     /*                                                                             */
                     /* we use v26 to iterate over v24 and                                          */
                     /* v25 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v26 = v24;
                     while (v26 != NULL) {
                        v14=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v14->next = NULL;
                        v14->last = v14;
                        v14->item.alg_energy = v26->item.alg_energy;
                        v14->item.alg_enum = new_Midregion_s(v26->item.alg_enum);
                        /* ------------------- v25 = v14 ++ v25 ------------------- */
                        if (v14 == NULL) {
                        } else 
                        if (v25 == NULL) {
                           v25 = v14;
                        }
                        else {
                           v14->last->next = v25;
                           v14->last = v25->last;
                           v25 = v14;
                        }
                        v26 = v26->next;
                     }
                  }
                  else {
                     v25 = NULL;
                  }
                  /* v25 = midregion <<< pul <<< pss <<< region ||| p comps ... h_l */
                  /* -------------------------- finished -------------------------- */

                  /* ---------------------- v27 = v13 ++ v25 ---------------------- */
                  if (v13 == NULL) {
                     v27 = v25;
                  } else 
                  if (v25 == NULL) {
                     v27 = v13;
                  }
                  else {
                     v13->last->next = v25;
                     v13->last = v25->last;
                     v27 = v13;
                  }
                  /* ---------------------- v28 = v12 ++ v27 ---------------------- */
                  if (v12 == NULL) {
                     v28 = v27;
                  } else 
                  if (v27 == NULL) {
                     v28 = v12;
                  }
                  else {
                     v12->last->next = v27;
                     v12->last = v27->last;
                     v28 = v12;
                  }
                  /* --------------------- v30 = minimum(v28) --------------------- */
                  v30 = 1.0e7;
                  v29 = v28;
                  while (v29 != NULL) {
                     v30 = v30 < v29->item.alg_energy ? v30 : v29->item.alg_energy;
                     v29 = v29->next;
                  }
                  v29 = v28;
                  v32 = NULL;
                  while (v29 != NULL) {
                     if (abs(v30 - v29->item.alg_energy) <= whichDiff(diff)) {
                        update_str_Signature(v29->item.alg_enum->item, diff - abs(v30 - v29->item.alg_energy));
                        v31=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v31->item = v29->item;
                        v31->next = NULL;
                        v31->last = v31;
                        /* ------------------- v32 = v31 ++ v32 ------------------- */
                        if (v31 == NULL) {
                        } else 
                        if (v32 == NULL) {
                           v32 = v31;
                        }
                        else {
                           v31->last->next = v32;
                           v31->last = v32->last;
                           v32 = v31;
                        }
                     }
                     v29 = v29->next;
                  }
                  /* -------------------------- start of -------------------------- */
                  /* --------------- v35 = pul <<< pss <<< uregion ---------------- */
                  if ((j-lc_h_Pr-lc_k-2) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v34 = pss <<< uregion ------------------ */
                     v34=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v34->next = NULL;
                     v34->last = v34;
                     v34->item.alg_energy = sspenalty((j-lc_h_Pr-2) - (lc_k));
                     v34->item.alg_enum = new_Pss_(lc_k, j-lc_h_Pr-2);
                     /* ------------------ v34 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v35 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v33 stores the result of a single application of algebra function           */
                     /* v34 holds the results of expression                                         */
                     /*      pss <<< uregion                                                        */
                     /*                                                                             */
                     /* we use v36 to iterate over v34 and                                          */
                     /* v35 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v36 = v34;
                     while (v36 != NULL) {
                        v33=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v33->next = NULL;
                        v33->last = v33;
                        v33->item.alg_energy = v36->item.alg_energy;
                        v33->item.alg_enum = new_Pul_s(v36->item.alg_enum);
                        /* ------------------- v35 = v33 ++ v35 ------------------- */
                        if (v33 == NULL) {
                        } else 
                        if (v35 == NULL) {
                           v35 = v33;
                        }
                        else {
                           v33->last->next = v35;
                           v33->last = v35->last;
                           v35 = v33;
                        }
                        v36 = v36->next;
                     }
                  }
                  else {
                     v35 = NULL;
                  }
                  /* --------------- v35 = pul <<< pss <<< uregion ---------------- */
                  /* -------------------------- finished -------------------------- */

                  /* ----------------------- v37 = p comps ------------------------ */
                  /* +---------------------------------------------------------------------------- */
                  /* Nonterminal comps is implemented as a tabulated                               */
                  /* function which yields atomar results. Since we are in list context,           */
                  /* we need to wrap the result of comps into a single list element.               */
                  /* +---------------------------------------------------------------------------- */
                  if ((j-lc_h_Pr-lc_k-2) >= 7) {
                     v37=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v37->item.alg_energy = tbl_comps(lc_k, j-lc_h_Pr-2);
                     v37->item.alg_enum = new__NTID(back_comps, lc_k, j-lc_h_Pr-2);
                     v37->next = NULL;
                     v37->last = v37;
                  }
                  else {
                     v37 = NULL;
                  }
                  /* ---------------------- v38 = v35 ++ v37 ---------------------- */
                  if (v35 == NULL) {
                     v38 = v37;
                  } else 
                  if (v37 == NULL) {
                     v38 = v35;
                  }
                  else {
                     v35->last->next = v37;
                     v35->last = v37->last;
                     v38 = v35;
                  }
                  /* --------------------- v40 = minimum(v38) --------------------- */
                  v40 = 1.0e7;
                  v39 = v38;
                  while (v39 != NULL) {
                     v40 = v40 < v39->item.alg_energy ? v40 : v39->item.alg_energy;
                     v39 = v39->next;
                  }
                  v39 = v38;
                  v42 = NULL;
                  while (v39 != NULL) {
                     if (abs(v40 - v39->item.alg_energy) <= whichDiff(diff)) {
                        update_str_Signature(v39->item.alg_enum->item, diff - abs(v40 - v39->item.alg_energy));
                        v41=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v41->item = v39->item;
                        v41->next = NULL;
                        v41->last = v41;
                        /* ------------------- v42 = v41 ++ v42 ------------------- */
                        if (v41 == NULL) {
                        } else 
                        if (v42 == NULL) {
                           v42 = v41;
                        }
                        else {
                           v41->last->next = v42;
                           v41->last = v42->last;
                           v42 = v41;
                        }
                     }
                     v39 = v39->next;
                  }
                  v43 = NULL;
                  /* +------------------------------------------------------------------------- */
                  /* v1 stores the result of a single application of algebra function           */
                  /* v11 holds the results of expression                                        */
                  /*      pul <<< pss <<< uregion ||| p comps ... h_l                           */
                  /*                                                                            */
                  /* we use v46 to iterate over v11 and                                         */
                  /* v43 to collect the results                                                 */
                  /* +------------------------------------------------------------------------- */
                  v46 = v11;
                  while (v46 != NULL) {
                     /* +--------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                     /* v1 stores the result of a single application of algebra function                                                                                                             */
                     /* v32 holds the results of expression                                                                                                                                          */
                     /*      emptymid lc_middle_k lc_middle_l <<< empty ||| midbase lc_middle_k lc_middle_l <<< lbase ||| midregion <<< pul <<< pss <<< region ||| p comps ... h_l ... h_l           */
                     /*                                                                                                                                                                              */
                     /* we use v45 to iterate over v32 and                                                                                                                                           */
                     /* v43 to collect the results                                                                                                                                                   */
                     /* +--------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                     v45 = v32;
                     while (v45 != NULL) {
                        /* +------------------------------------------------------------------------- */
                        /* v1 stores the result of a single application of algebra function           */
                        /* v42 holds the results of expression                                        */
                        /*      pul <<< pss <<< uregion ||| p comps ... h_l                           */
                        /*                                                                            */
                        /* we use v44 to iterate over v42 and                                         */
                        /* v43 to collect the results                                                 */
                        /* +------------------------------------------------------------------------- */
                        v44 = v42;
                        while (v44 != NULL) {
                           if (abs(tbl_knot(i, j).tup1 - ((((((pkinit + lc_energy) + (3 * npp)) + v46->item.alg_energy) + v45->item.alg_energy) + v44->item.alg_energy) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j))) <= diff) {
                              v1=(struct str10 *) myalloc(adp_dynmem, sizeof(struct str10 ));
                              v1->next = NULL;
                              v1->last = v1;
                              v1->item.alg_energy.tup1 = (((((pkinit + lc_energy) + (3 * npp)) + v46->item.alg_energy) + v45->item.alg_energy) + v44->item.alg_energy) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j);
                              v1->item.alg_energy.tup2 = lc_l;
                              v1->item.alg_energy.tup3 = lc_k;
                              v1->item.alg_enum = new_Pk_Pr_sss(lc_energy, i, i+lc_h, v46->item.alg_enum, lc_l, lc_l+lc_h_Pr, v45->item.alg_enum, lc_k-lc_h, lc_k, v44->item.alg_enum, j-lc_h_Pr, j);
                           }
                           else {
                              v1 = NULL;
                           }
                           /* ------------------ v43 = v1 ++ v43 ------------------ */
                           if (v1 == NULL) {
                           } else 
                           if (v43 == NULL) {
                              v43 = v1;
                           }
                           else {
                              v1->last->next = v43;
                              v1->last = v43->last;
                              v43 = v1;
                           }
                           v44 = v44->next;
                        }
                        v45 = v45->next;
                     }
                     v46 = v46->next;
                  }
               }
               else {
                  v43 = NULL;
               }
            }
            else {
               v43 = NULL;
            }
            /* ------------------------- v47 = v43 ++ v47 ------------------------- */
            if (v43 == NULL) {
            } else 
            if (v47 == NULL) {
               v47 = v43;
            }
            else {
               v43->last->next = v47;
               v43->last = v47->last;
               v47 = v43;
            }
         }
      }
   }
   else {
      v47 = NULL;
   }
   /* ------- v47 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ----------------------------- v49 = minimum(v47) ---------------------------- */
   v49.tup1 = 1.0e7;
   v49.tup2 = 0;
   v49.tup3 = 0;
   v48 = v47;
   while (v48 != NULL) {
      /* ---------------- v49 = minimum(v49, v48->item.alg_energy) ---------------- */
      v49 = v49.tup1 < v48->item.alg_energy.tup1 ? v49 : v48->item.alg_energy;
      v48 = v48->next;
   }
   v48 = v47;
   v51 = NULL;
   while (v48 != NULL) {
      if (abs(v49.tup1 - v48->item.alg_energy.tup1) <= diff) {
         update_str_Signature(v48->item.alg_enum->item, diff - abs(v49.tup1 - v48->item.alg_energy.tup1));
         v50=(struct str10 *) myalloc(adp_dynmem, sizeof(struct str10 ));
         v50->item = v48->item;
         v50->next = NULL;
         v50->last = v50;
         /* --------------------------- v51 = v50 ++ v51 -------------------------- */
         if (v50 == NULL) {
         } else 
         if (v51 == NULL) {
            v51 = v50;
         }
         else {
            v50->last->next = v51;
            v50->last = v51->last;
            v51 = v50;
         }
      }
      v48 = v48->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v52 = v51;
   v53 = NULL;
   while (v52 != NULL) {
      /* -------------------- v53 = v52->item.alg_enum ++ v53 --------------------- */
      if (v52->item.alg_enum == NULL) {
      } else 
      if (v53 == NULL) {
         v53 = v52->item.alg_enum;
      }
      else {
         v52->item.alg_enum->last->next = v53;
         v52->item.alg_enum->last = v53->last;
         v53 = v52->item.alg_enum;
      }
      v52 = v52->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v53)));
}

/* backtracing code for production stacklen                                         */
/* -------------------------------------------------------------------------------- */
static struct str4 *back_stacklen(int i, int j, int diff)
{
   struct str4 *v11;
   struct str3 v7;
   struct str12 *v1, *v2, *v3, *v4, *v5, *v6, *v8, *v9, *v10;

   if (basepairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /* -------------- v1 = sum <<< lbase ~~~ p stacklen ~~~ lbase --------------- */
      if ((j-i) >= 7) {
         if (abs(tbl_stacklen(i, j).tup1 - (tbl_stacklen(i+1, j-1).tup1 + sr_energy(i+1, j))) <= diff) {
            v1=(struct str12 *) myalloc(adp_dynmem, sizeof(struct str12 ));
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
            v3=(struct str12 *) myalloc(adp_dynmem, sizeof(struct str12 ));
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
         v8=(struct str12 *) myalloc(adp_dynmem, sizeof(struct str12 ));
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
   arr_knot=(struct str2 *) malloc((offset[n]+n+1) * sizeof(struct str2 ));
   arr_stacklen=(struct str3 *) malloc((offset[n]+n+1) * sizeof(struct str3 ));
   arr_bestPK1=(struct str1 *) malloc((offset[n]+n+1) * sizeof(struct str1 ));
   arr_block=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_bestPK=(struct str1 *) malloc((n+1) * sizeof(struct str1 ));
   arr_comps=(int *) malloc((offset[n]+n+1) * sizeof(int ));
}

/* free memory                                                                      */
/* -------------------------------------------------------------------------------- */

static void freeall()
{
   adplib_free(opts, seq);
   rnalib_free();

   free(arr_closed);
   free(arr_knot);
   free(arr_stacklen);
   free(arr_bestPK1);
   free(arr_block);
   free(arr_bestPK);
   free(arr_comps);
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
            tbl_knot(i-p, j-p) = move_str2(tbl_knot(i, j));
         }
         if ((i >= p) && (j >= p)) {
            tbl_stacklen(i-p, j-p) = tbl_stacklen(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_bestPK1(i-p, j-p) = move_str1(tbl_bestPK1(i, j));
         }
         if ((i >= p) && (j >= p)) {
            tbl_block(i-p, j-p) = tbl_block(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_comps(i-p, j-p) = tbl_comps(i, j);
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
   struct str4 *l;
   struct str4 *next;
   int score;
   int bestLength, bestScorePerBase;
   int pos, startj;

   tableAlloc();
   pp_init=(struct str4 ***) myalloc(adp_statmem, (n*2) * sizeof(struct str4 **));
   pp_initA=(struct str4 **) myalloc(adp_statmem, (n*2) * sizeof(struct str4 *));

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
         shift_input(opts, seq, 0);
      }
      for (j=startj; j<=n; j++) {
         for (i=j; i>=0; i--) {
            calc_closed(i, j);
            calc_knot(i, j);
            calc_stacklen(i, j);
            calc_bestPK1(i, j);
            calc_block(i, j);
            if ((j) == (n)) {
               calc_bestPK(i, j);
            }
            calc_comps(i, j);
         }
      }
      /* ------------------------- show axiom: bestPK_Ax -------------------------- */
      v2 = calc_bestPK_Ax(0, n);

      if ((n >= 11) && (tbl_bestPK(0, n).tup1 != 10000000) && (tbl_bestPK(0, n).tup2 != 0)) {
         bestLength = tbl_bestPK(0,n).tup2;
         bestScorePerBase = (v2 * RFACTOR) / bestLength;
         
         copy_depth = 0;
         
         if (opts->traceback_percent) traceback_diff = abs(v2 * opts->traceback_percent / -100);
         printf("optimal:      %8.2f kcal/mol  (%6.2f kcal/mol/base)    length: %d \n", 
             ((double) v2) /100, 
             (((double) bestScorePerBase / RFACTOR)/100),
             bestLength);
         printf("energy range: %8.2f kcal/mol  (%6.2f kcal/mol/base)\n", 
             ((double)traceback_diff) / 100, 
            (((double)traceback_diff) / bestLength)/100);
         
         l = back_bestPK_Ax(0, n, traceback_diff);
         while ((l != NULL) || (pp_next != NULL)) {
            pp_next = NULL;
            pp_initC = (-1);
            result_prettyprint[0] = 0;
            pp_outp = result_prettyprint;
            rmAllowed = 1;
            removeAddr = NULL;
            score = pp_str_Signature(l);
            if (abs(bestScorePerBase - scorePerBase) <= ((traceback_diff * RFACTOR) / bestLength)) {
               printf("%d", pknot_start+1+pos);
               for (i=1; i<=pknot_end - pknot_start - 4; i++) printf(" ");
               printf("%d", pknot_end+pos);
               printf("\n");
               for (i=pknot_start+1; i<= pknot_end; i++) printf("%c",seq->original_seq[i-1+pos]);
               printf("\n");
         
               printf("%s", result_prettyprint);
               //printf("  (%.2f)\n", ((double) score) /100);
               printf("  (%.2f) (%.2f)\n", ((double) score) /100, (((double) scorePerBase)/RFACTOR)/100);
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
      }
      else printf("The input sequence contains no pseudoknot!\n");
   }
}


int main_pk_loc_so_nd(toptions *_opts, tsequence *_seq)
{
   opts = _opts;
   seq  = _seq;
   z    = _seq->seq - 1;
   n    = _seq->length;

   if (opts->debug) printf("pk-loc-so-nd.c\n");
   pksOnly = opts->pksOnly;

   adplib_init(opts,seq,&z,&n);
   result_prettyprint = (char *) myalloc(adp_statmem, 30*n*sizeof(char));
   traceback_diff = opts->traceback_diff * 100;
   rnalib_init(opts,seq);
   rna_output_descr(opts,seq);
   mainloop();
   freeall();
}


