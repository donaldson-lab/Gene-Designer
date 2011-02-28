/* ---------------------------------------------------------------------------
pknotsRG 1.3
Copyright (C) 2004-2006 Jens Reeder, Robert Giegerich, Peter Steffen
--------------------------------------------------------------------------- */
/* compiled by the ADP compiler, version 0.8 (rev 690)    Tue Sep 12 13:29:44 MEST 2006 */
/* source file: pknotsRG-enf.lhs                                                    */
/* command:                                                                         */
/* adpcompile -c pknotsRG-enf.lhs -al energy enum -cs energy -alpp pp -O -lcf -ta bto -bt so -gc cc -iuc -W */
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
#define SIGID_Mldl 11
#define SIGID_Mldr 12
#define SIGID_Mldlr 13
#define SIGID_Dl 14
#define SIGID_Dr 15
#define SIGID_Dlr 16
#define SIGID_Edl 17
#define SIGID_Edr 18
#define SIGID_Edlr 19
#define SIGID_Drem 20
#define SIGID_Cons 21
#define SIGID_Ul 22
#define SIGID_Pul 23
#define SIGID_Addss 24
#define SIGID_Ssadd 25
#define SIGID_Nil 26
#define SIGID_Combine 27
#define SIGID_Sum 28
#define SIGID_Sumend 29
#define SIGID_Co 30
#define SIGID_Pk 31
#define SIGID_Pkmldl 32
#define SIGID_Pkmldr 33
#define SIGID_Pkmldlr 34
#define SIGID_Pkml 35
#define SIGID_Pk_Pr 36
#define SIGID_Kndl 37
#define SIGID_Kndr 38
#define SIGID_Kndlr 39
#define SIGID_Frd 40
#define SIGID_Bkd 41
#define SIGID_Emptymid 42
#define SIGID_Midbase 43
#define SIGID_Middlro 44
#define SIGID_Middl 45
#define SIGID_Middr 46
#define SIGID_Middlr 47
#define SIGID_Midregion 48
#define SIGID_Pss 49

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

/* operator Mldl                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Mldl {
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
};


static struct str3 *new_Mldl_s(int a1, int a2, int a3, struct str3 *structure4, int a5, int a6)
{
   struct str_Mldl *t;

   t=(struct str_Mldl *) myalloc(adp_dynmem, sizeof(struct str_Mldl ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->isStructure4 = 1;
   t->structure4 = structure4;
   t->a5 = a5;
   t->a6 = a6;
   return(new_Signature(SIGID_Mldl, t));
}

/* operator Mldr                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Mldr {
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
};


static struct str3 *new_Mldr_s(int a1, int a2, struct str3 *structure3, int a4, int a5, int a6)
{
   struct str_Mldr *t;

   t=(struct str_Mldr *) myalloc(adp_dynmem, sizeof(struct str_Mldr ));
   t->a1 = a1;
   t->a2 = a2;
   t->isStructure3 = 1;
   t->structure3 = structure3;
   t->a4 = a4;
   t->a5 = a5;
   t->a6 = a6;
   return(new_Signature(SIGID_Mldr, t));
}

/* operator Mldlr                                                                   */
/* -------------------------------------------------------------------------------- */

struct str_Mldlr {
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
   int a7;
};


static struct str3 *new_Mldlr_s(int a1, int a2, int a3, struct str3 *structure4, int a5, int a6, int a7)
{
   struct str_Mldlr *t;

   t=(struct str_Mldlr *) myalloc(adp_dynmem, sizeof(struct str_Mldlr ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->isStructure4 = 1;
   t->structure4 = structure4;
   t->a5 = a5;
   t->a6 = a6;
   t->a7 = a7;
   return(new_Signature(SIGID_Mldlr, t));
}

/* operator Dl                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Dl {
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


static struct str3 *new_Dl_s(int a1, struct str3 *structure2, int a3)
{
   struct str_Dl *t;

   t=(struct str_Dl *) myalloc(adp_dynmem, sizeof(struct str_Dl ));
   t->a1 = a1;
   t->isStructure2 = 1;
   t->structure2 = structure2;
   t->a3 = a3;
   return(new_Signature(SIGID_Dl, t));
}

/* operator Dr                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Dr {
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


static struct str3 *new_Dr_s(int a1, struct str3 *structure2, int a3)
{
   struct str_Dr *t;

   t=(struct str_Dr *) myalloc(adp_dynmem, sizeof(struct str_Dr ));
   t->a1 = a1;
   t->isStructure2 = 1;
   t->structure2 = structure2;
   t->a3 = a3;
   return(new_Signature(SIGID_Dr, t));
}

/* operator Dlr                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Dlr {
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


static struct str3 *new_Dlr_s(int a1, struct str3 *structure2, int a3)
{
   struct str_Dlr *t;

   t=(struct str_Dlr *) myalloc(adp_dynmem, sizeof(struct str_Dlr ));
   t->a1 = a1;
   t->isStructure2 = 1;
   t->structure2 = structure2;
   t->a3 = a3;
   return(new_Signature(SIGID_Dlr, t));
}

/* operator Edl                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Edl {
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

static struct str3 *new_Edl_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3)
{
   struct str_Edl *t;

   t=(struct str_Edl *) myalloc(adp_dynmem, sizeof(struct str_Edl ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   return(new_Signature(SIGID_Edl, t));
}


/* operator Edr                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Edr {
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

static struct str3 *new_Edr_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3)
{
   struct str_Edr *t;

   t=(struct str_Edr *) myalloc(adp_dynmem, sizeof(struct str_Edr ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   return(new_Signature(SIGID_Edr, t));
}


/* operator Edlr                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Edlr {
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

static struct str3 *new_Edlr_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3)
{
   struct str_Edlr *t;

   t=(struct str_Edlr *) myalloc(adp_dynmem, sizeof(struct str_Edlr ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   return(new_Signature(SIGID_Edlr, t));
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

/* operator Co                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Co {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str3 *new_Co_s(struct str3 *structure1)
{
   struct str_Co *t;

   t=(struct str_Co *) myalloc(adp_dynmem, sizeof(struct str_Co ));
   t->isStructure1 = 1;
   t->structure1 = structure1;
   return(new_Signature(SIGID_Co, t));
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


/* operator Pkmldl                                                                  */
/* -------------------------------------------------------------------------------- */

struct str_Pkmldl {
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

static struct str3 *new_Pkmldl_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4)
{
   struct str_Pkmldl *t;

   t=(struct str_Pkmldl *) myalloc(adp_dynmem, sizeof(struct str_Pkmldl ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   t->a4 = a4;
   return(new_Signature(SIGID_Pkmldl, t));
}


/* operator Pkmldr                                                                  */
/* -------------------------------------------------------------------------------- */

struct str_Pkmldr {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int a2;
   int a3;
   int a4;
};

static struct str3 *new_Pkmldr_f(struct str3 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3, int a4)
{
   struct str_Pkmldr *t;

   t=(struct str_Pkmldr *) myalloc(adp_dynmem, sizeof(struct str_Pkmldr ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   return(new_Signature(SIGID_Pkmldr, t));
}


/* operator Pkmldlr                                                                 */
/* -------------------------------------------------------------------------------- */

struct str_Pkmldlr {
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
   int a5;
};

static struct str3 *new_Pkmldlr_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4, int a5)
{
   struct str_Pkmldlr *t;

   t=(struct str_Pkmldlr *) myalloc(adp_dynmem, sizeof(struct str_Pkmldlr ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   t->a4 = a4;
   t->a5 = a5;
   return(new_Signature(SIGID_Pkmldlr, t));
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

/* operator Kndl                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Kndl {
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

static struct str3 *new_Kndl_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4)
{
   struct str_Kndl *t;

   t=(struct str_Kndl *) myalloc(adp_dynmem, sizeof(struct str_Kndl ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   t->a4 = a4;
   return(new_Signature(SIGID_Kndl, t));
}


/* operator Kndr                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Kndr {
   int isStructure1;
   struct str3 *structure1;
   struct str3 *a1;
   struct str3 *pp_init_a1;
   struct str3 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
   int a2;
   int a3;
   int a4;
};

static struct str3 *new_Kndr_f(struct str3 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3, int a4)
{
   struct str_Kndr *t;

   t=(struct str_Kndr *) myalloc(adp_dynmem, sizeof(struct str_Kndr ));
   t->isStructure1 = 0;
   t->f1 = f1;
   t->i1 = i1;
   t->j1 = j1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   return(new_Signature(SIGID_Kndr, t));
}


/* operator Kndlr                                                                   */
/* -------------------------------------------------------------------------------- */

struct str_Kndlr {
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
   int a5;
};

static struct str3 *new_Kndlr_f(int a1, struct str3 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4, int a5)
{
   struct str_Kndlr *t;

   t=(struct str_Kndlr *) myalloc(adp_dynmem, sizeof(struct str_Kndlr ));
   t->a1 = a1;
   t->isStructure2 = 0;
   t->f2 = f2;
   t->i2 = i2;
   t->j2 = j2;
   t->a3 = a3;
   t->a4 = a4;
   t->a5 = a5;
   return(new_Signature(SIGID_Kndlr, t));
}


/* operator Frd                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Frd {
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


static struct str3 *new_Frd_s(int a1, struct str3 *structure2, int a3)
{
   struct str_Frd *t;

   t=(struct str_Frd *) myalloc(adp_dynmem, sizeof(struct str_Frd ));
   t->a1 = a1;
   t->isStructure2 = 1;
   t->structure2 = structure2;
   t->a3 = a3;
   return(new_Signature(SIGID_Frd, t));
}

/* operator Bkd                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Bkd {
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


static struct str3 *new_Bkd_s(int a1, int a2, struct str3 *structure3)
{
   struct str_Bkd *t;

   t=(struct str_Bkd *) myalloc(adp_dynmem, sizeof(struct str_Bkd ));
   t->a1 = a1;
   t->a2 = a2;
   t->isStructure3 = 1;
   t->structure3 = structure3;
   return(new_Signature(SIGID_Bkd, t));
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

/* operator Middlro                                                                 */
/* -------------------------------------------------------------------------------- */

struct str_Middlro {
   int a1;
   int a2;
   int a3;
   int a4;
   int diff;
};

static struct str3 *new_Middlro_(int a1, int a2, int a3, int a4)
{
   struct str_Middlro *t;

   t=(struct str_Middlro *) myalloc(adp_dynmem, sizeof(struct str_Middlro ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->a4 = a4;
   return(new_Signature(SIGID_Middlro, t));
}

/* operator Middl                                                                   */
/* -------------------------------------------------------------------------------- */

struct str_Middl {
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


static struct str3 *new_Middl_s(int a1, int a2, struct str3 *structure3)
{
   struct str_Middl *t;

   t=(struct str_Middl *) myalloc(adp_dynmem, sizeof(struct str_Middl ));
   t->a1 = a1;
   t->a2 = a2;
   t->isStructure3 = 1;
   t->structure3 = structure3;
   return(new_Signature(SIGID_Middl, t));
}

/* operator Middr                                                                   */
/* -------------------------------------------------------------------------------- */

struct str_Middr {
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


static struct str3 *new_Middr_s(int a1, struct str3 *structure2, int a3)
{
   struct str_Middr *t;

   t=(struct str_Middr *) myalloc(adp_dynmem, sizeof(struct str_Middr ));
   t->a1 = a1;
   t->isStructure2 = 1;
   t->structure2 = structure2;
   t->a3 = a3;
   return(new_Signature(SIGID_Middr, t));
}

/* operator Middlr                                                                  */
/* -------------------------------------------------------------------------------- */

struct str_Middlr {
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
};


static struct str3 *new_Middlr_s(int a1, int a2, int a3, struct str3 *structure4, int a5)
{
   struct str_Middlr *t;

   t=(struct str_Middlr *) myalloc(adp_dynmem, sizeof(struct str_Middlr ));
   t->a1 = a1;
   t->a2 = a2;
   t->a3 = a3;
   t->isStructure4 = 1;
   t->structure4 = structure4;
   t->a5 = a5;
   return(new_Signature(SIGID_Middlr, t));
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
      if (c->utype == SIGID_Mldl) {
         if (((struct str_Mldl *)(c->entry))->a4 != NULL) {
            sprintf(pp_outp, "((.");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Mldl *)(c->entry))->a4->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Mldl *)(c->entry))->a4);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Mldl *)(c->entry))->a4);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Mldl *)(c->entry))->a4);
                  pp_initA[pp_initC] = ((struct str_Mldl *)(c->entry))->pp_init_a4;
               }
            }
            score4 = pp_str_Signature(((struct str_Mldl *)(c->entry))->a4);
            sprintf(pp_outp, "))");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (((380 + score4) + dli_energy(((struct str_Mldl *)(c->entry))->a2, ((struct str_Mldl *)(c->entry))->a5)) + sr_energy(((struct str_Mldl *)(c->entry))->a1, ((struct str_Mldl *)(c->entry))->a6)) + termaupenalty(((struct str_Mldl *)(c->entry))->a2, ((struct str_Mldl *)(c->entry))->a5);
         }
      } else 
      if (c->utype == SIGID_Mldr) {
         if (((struct str_Mldr *)(c->entry))->a3 != NULL) {
            sprintf(pp_outp, "((");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Mldr *)(c->entry))->a3->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Mldr *)(c->entry))->a3);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Mldr *)(c->entry))->a3);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Mldr *)(c->entry))->a3);
                  pp_initA[pp_initC] = ((struct str_Mldr *)(c->entry))->pp_init_a3;
               }
            }
            score3 = pp_str_Signature(((struct str_Mldr *)(c->entry))->a3);
            sprintf(pp_outp, ".))");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (((380 + score3) + dri_energy(((struct str_Mldr *)(c->entry))->a2, ((struct str_Mldr *)(c->entry))->a5)) + sr_energy(((struct str_Mldr *)(c->entry))->a1, ((struct str_Mldr *)(c->entry))->a6)) + termaupenalty(((struct str_Mldr *)(c->entry))->a2, ((struct str_Mldr *)(c->entry))->a5);
         }
      } else 
      if (c->utype == SIGID_Mldlr) {
         if (((struct str_Mldlr *)(c->entry))->a4 != NULL) {
            sprintf(pp_outp, "((.");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Mldlr *)(c->entry))->a4->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Mldlr *)(c->entry))->a4);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Mldlr *)(c->entry))->a4);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Mldlr *)(c->entry))->a4);
                  pp_initA[pp_initC] = ((struct str_Mldlr *)(c->entry))->pp_init_a4;
               }
            }
            score4 = pp_str_Signature(((struct str_Mldlr *)(c->entry))->a4);
            sprintf(pp_outp, ".))");
            pp_outp = pp_outp + strlen(pp_outp);
            score = ((((380 + score4) + dli_energy(((struct str_Mldlr *)(c->entry))->a2, ((struct str_Mldlr *)(c->entry))->a6)) + dri_energy(((struct str_Mldlr *)(c->entry))->a2, ((struct str_Mldlr *)(c->entry))->a6)) + sr_energy(((struct str_Mldlr *)(c->entry))->a1, ((struct str_Mldlr *)(c->entry))->a7)) + termaupenalty(((struct str_Mldlr *)(c->entry))->a2, ((struct str_Mldlr *)(c->entry))->a6);
         }
      } else 
      if (c->utype == SIGID_Dl) {
         if (((struct str_Dl *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Dl *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Dl *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Dl *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Dl *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Dl *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Dl *)(c->entry))->a2);
            score = score2 + dl_energy(((struct str_Dl *)(c->entry))->a1 + 1, ((struct str_Dl *)(c->entry))->a3);
         }
      } else 
      if (c->utype == SIGID_Dr) {
         if (((struct str_Dr *)(c->entry))->a2 != NULL) {
            if (((struct str_Dr *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Dr *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Dr *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Dr *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Dr *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Dr *)(c->entry))->a2);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = score2 + dr_energy(((struct str_Dr *)(c->entry))->a1 + 1, ((struct str_Dr *)(c->entry))->a3 - 1);
         }
      } else 
      if (c->utype == SIGID_Dlr) {
         if (((struct str_Dlr *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Dlr *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Dlr *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Dlr *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Dlr *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Dlr *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Dlr *)(c->entry))->a2);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score2 + dl_energy(((struct str_Dlr *)(c->entry))->a1 + 1, ((struct str_Dlr *)(c->entry))->a3 - 1)) + dr_energy(((struct str_Dlr *)(c->entry))->a1 + 1, ((struct str_Dlr *)(c->entry))->a3 - 1);
         }
      } else 
      if (c->utype == SIGID_Edl) {
         if (((struct str_Edl *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Edl *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Edl *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Edl *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Edl *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Edl *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Edl *)(c->entry))->a2);
            score = (score2 + dl_energy(((struct str_Edl *)(c->entry))->a1 + 1, ((struct str_Edl *)(c->entry))->a3)) + termaupenalty(((struct str_Edl *)(c->entry))->a1 + 1, ((struct str_Edl *)(c->entry))->a3);
         }
      } else 
      if (c->utype == SIGID_Edr) {
         if (((struct str_Edr *)(c->entry))->a2 != NULL) {
            if (((struct str_Edr *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Edr *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Edr *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Edr *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Edr *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Edr *)(c->entry))->a2);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score2 + dr_energy(((struct str_Edr *)(c->entry))->a1 + 1, ((struct str_Edr *)(c->entry))->a3 - 1)) + termaupenalty(((struct str_Edr *)(c->entry))->a1 + 1, ((struct str_Edr *)(c->entry))->a3 - 1);
         }
      } else 
      if (c->utype == SIGID_Edlr) {
         if (((struct str_Edlr *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Edlr *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Edlr *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Edlr *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Edlr *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Edlr *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Edlr *)(c->entry))->a2);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = ((score2 + dl_energy(((struct str_Edlr *)(c->entry))->a1 + 1, ((struct str_Edlr *)(c->entry))->a3 - 1)) + dr_energy(((struct str_Edlr *)(c->entry))->a1 + 1, ((struct str_Edlr *)(c->entry))->a3 - 1)) + termaupenalty(((struct str_Edlr *)(c->entry))->a1 + 1, ((struct str_Edlr *)(c->entry))->a3 - 1);
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
      if (c->utype == SIGID_Co) {
         if (((struct str_Co *)(c->entry))->a1 != NULL) {
            if (((struct str_Co *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Co *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Co *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Co *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Co *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Co *)(c->entry))->a1);
            score = score1;
         }
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
      if (c->utype == SIGID_Pkmldl) {
         if (((struct str_Pkmldl *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Pkmldl *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Pkmldl *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Pkmldl *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Pkmldl *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Pkmldl *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Pkmldl *)(c->entry))->a2);
            score = (score2 + 600) + (wkn * dl_energy(((struct str_Pkmldl *)(c->entry))->a1 + 1, ((struct str_Pkmldl *)(c->entry))->a4));
         }
      } else 
      if (c->utype == SIGID_Pkmldr) {
         if (((struct str_Pkmldr *)(c->entry))->a1 != NULL) {
            if (((struct str_Pkmldr *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Pkmldr *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Pkmldr *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Pkmldr *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Pkmldr *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Pkmldr *)(c->entry))->a1);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score1 + 600) + (wkn * dr_energy(((struct str_Pkmldr *)(c->entry))->a2 + 1, ((struct str_Pkmldr *)(c->entry))->a4 - 1));
         }
      } else 
      if (c->utype == SIGID_Pkmldlr) {
         if (((struct str_Pkmldlr *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Pkmldlr *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Pkmldlr *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Pkmldlr *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Pkmldlr *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Pkmldlr *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Pkmldlr *)(c->entry))->a2);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score2 + 600) + (wkn * (dl_energy(((struct str_Pkmldlr *)(c->entry))->a1 + 1, ((struct str_Pkmldlr *)(c->entry))->a4) + dr_energy(((struct str_Pkmldlr *)(c->entry))->a3 + 1, ((struct str_Pkmldlr *)(c->entry))->a5 - 1)));
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
      if (c->utype == SIGID_Kndl) {
         if (((struct str_Kndl *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Kndl *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Kndl *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Kndl *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Kndl *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Kndl *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Kndl *)(c->entry))->a2);
            score = (score2 + npp) + (wkn * dl_energy(((struct str_Kndl *)(c->entry))->a1 + 1, ((struct str_Kndl *)(c->entry))->a4));
         }
      } else 
      if (c->utype == SIGID_Kndr) {
         if (((struct str_Kndr *)(c->entry))->a1 != NULL) {
            if (((struct str_Kndr *)(c->entry))->a1->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Kndr *)(c->entry))->a1);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Kndr *)(c->entry))->a1);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Kndr *)(c->entry))->a1);
                  pp_initA[pp_initC] = ((struct str_Kndr *)(c->entry))->pp_init_a1;
               }
            }
            score1 = pp_str_Signature(((struct str_Kndr *)(c->entry))->a1);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score1 + npp) + (wkn * dr_energy(((struct str_Kndr *)(c->entry))->a2 + 1, ((struct str_Kndr *)(c->entry))->a4 - 1));
         }
      } else 
      if (c->utype == SIGID_Kndlr) {
         if (((struct str_Kndlr *)(c->entry))->a2 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Kndlr *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Kndlr *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Kndlr *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Kndlr *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Kndlr *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Kndlr *)(c->entry))->a2);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score2 + (2 * npp)) + (wkn * (dl_energy(((struct str_Kndlr *)(c->entry))->a1 + 1, ((struct str_Kndlr *)(c->entry))->a4) + dr_energy(((struct str_Kndlr *)(c->entry))->a3 + 1, ((struct str_Kndlr *)(c->entry))->a5 - 1)));
         }
      } else 
      if (c->utype == SIGID_Frd) {
         if (((struct str_Frd *)(c->entry))->a2 != NULL) {
            if (((struct str_Frd *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Frd *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Frd *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Frd *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Frd *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Frd *)(c->entry))->a2);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score2 + (wkn * dl_energy(((struct str_Frd *)(c->entry))->a3 + 1, ((struct str_Frd *)(c->entry))->a1))) + npp;
         }
      } else 
      if (c->utype == SIGID_Bkd) {
         if (((struct str_Bkd *)(c->entry))->a3 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Bkd *)(c->entry))->a3->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Bkd *)(c->entry))->a3);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Bkd *)(c->entry))->a3);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Bkd *)(c->entry))->a3);
                  pp_initA[pp_initC] = ((struct str_Bkd *)(c->entry))->pp_init_a3;
               }
            }
            score3 = pp_str_Signature(((struct str_Bkd *)(c->entry))->a3);
            score = (score3 + (wkn * dr_energy(((struct str_Bkd *)(c->entry))->a1 + 1, ((struct str_Bkd *)(c->entry))->a2 - 1))) + npp;
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
      if (c->utype == SIGID_Middlro) {
         sprintf(pp_outp, "..");
         pp_outp = pp_outp + strlen(pp_outp);
         score = (2 * npp) + (wkn * (dri_energy(((struct str_Middlro *)(c->entry))->a2, ((struct str_Middlro *)(c->entry))->a3 + 2) + dli_energy(((struct str_Middlro *)(c->entry))->a3 - 1, ((struct str_Middlro *)(c->entry))->a1 + 1)));
      } else 
      if (c->utype == SIGID_Middl) {
         if (((struct str_Middl *)(c->entry))->a3 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Middl *)(c->entry))->a3->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Middl *)(c->entry))->a3);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Middl *)(c->entry))->a3);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Middl *)(c->entry))->a3);
                  pp_initA[pp_initC] = ((struct str_Middl *)(c->entry))->pp_init_a3;
               }
            }
            score3 = pp_str_Signature(((struct str_Middl *)(c->entry))->a3);
            score = (score3 + npp) + (wkn * dli_energy(((struct str_Middl *)(c->entry))->a2 - 1, ((struct str_Middl *)(c->entry))->a1 + 1));
         }
      } else 
      if (c->utype == SIGID_Middr) {
         if (((struct str_Middr *)(c->entry))->a2 != NULL) {
            if (((struct str_Middr *)(c->entry))->a2->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Middr *)(c->entry))->a2);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Middr *)(c->entry))->a2);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Middr *)(c->entry))->a2);
                  pp_initA[pp_initC] = ((struct str_Middr *)(c->entry))->pp_init_a2;
               }
            }
            score2 = pp_str_Signature(((struct str_Middr *)(c->entry))->a2);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score2 + npp) + (wkn * dri_energy(((struct str_Middr *)(c->entry))->a1, ((struct str_Middr *)(c->entry))->a3 + 1));
         }
      } else 
      if (c->utype == SIGID_Middlr) {
         if (((struct str_Middlr *)(c->entry))->a4 != NULL) {
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            if (((struct str_Middlr *)(c->entry))->a4->next != NULL) {
               if (rmAllowed) {
                  removeAddr = &(((struct str_Middlr *)(c->entry))->a4);
               }
               else {
                  removeAddr = NULL;
               }
               pp_next = &(((struct str_Middlr *)(c->entry))->a4);
               pp_initC = (-1);
            }
            else {
               if (removeAddr == NULL) {
                  pp_initC = pp_initC + 1;
                  pp_init[pp_initC] = &(((struct str_Middlr *)(c->entry))->a4);
                  pp_initA[pp_initC] = ((struct str_Middlr *)(c->entry))->pp_init_a4;
               }
            }
            score4 = pp_str_Signature(((struct str_Middlr *)(c->entry))->a4);
            sprintf(pp_outp, ".");
            pp_outp = pp_outp + strlen(pp_outp);
            score = (score4 + (2 * npp)) + (wkn * (dri_energy(((struct str_Middlr *)(c->entry))->a2, ((struct str_Middlr *)(c->entry))->a5 + 1) + dli_energy(((struct str_Middlr *)(c->entry))->a3 - 1, ((struct str_Middlr *)(c->entry))->a1 + 1)));
         }
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
      if (id == SIGID_Mldl) {
         nstr->item->entry=(struct str_Mldl *) malloc(sizeof(struct str_Mldl ));
         (*((struct str_Mldl *)(nstr->item->entry))) = (*((struct str_Mldl *)entr));
         if (((struct str_Mldl *)(nstr->item->entry))->isStructure4) {
            ((struct str_Mldl *)(nstr->item->entry))->structure4 = copy_str_Signature(((struct str_Mldl *)entr)->structure4);
         }
      } else 
      if (id == SIGID_Mldr) {
         nstr->item->entry=(struct str_Mldr *) malloc(sizeof(struct str_Mldr ));
         (*((struct str_Mldr *)(nstr->item->entry))) = (*((struct str_Mldr *)entr));
         if (((struct str_Mldr *)(nstr->item->entry))->isStructure3) {
            ((struct str_Mldr *)(nstr->item->entry))->structure3 = copy_str_Signature(((struct str_Mldr *)entr)->structure3);
         }
      } else 
      if (id == SIGID_Mldlr) {
         nstr->item->entry=(struct str_Mldlr *) malloc(sizeof(struct str_Mldlr ));
         (*((struct str_Mldlr *)(nstr->item->entry))) = (*((struct str_Mldlr *)entr));
         if (((struct str_Mldlr *)(nstr->item->entry))->isStructure4) {
            ((struct str_Mldlr *)(nstr->item->entry))->structure4 = copy_str_Signature(((struct str_Mldlr *)entr)->structure4);
         }
      } else 
      if (id == SIGID_Dl) {
         nstr->item->entry=(struct str_Dl *) malloc(sizeof(struct str_Dl ));
         (*((struct str_Dl *)(nstr->item->entry))) = (*((struct str_Dl *)entr));
         if (((struct str_Dl *)(nstr->item->entry))->isStructure2) {
            ((struct str_Dl *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Dl *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Dr) {
         nstr->item->entry=(struct str_Dr *) malloc(sizeof(struct str_Dr ));
         (*((struct str_Dr *)(nstr->item->entry))) = (*((struct str_Dr *)entr));
         if (((struct str_Dr *)(nstr->item->entry))->isStructure2) {
            ((struct str_Dr *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Dr *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Dlr) {
         nstr->item->entry=(struct str_Dlr *) malloc(sizeof(struct str_Dlr ));
         (*((struct str_Dlr *)(nstr->item->entry))) = (*((struct str_Dlr *)entr));
         if (((struct str_Dlr *)(nstr->item->entry))->isStructure2) {
            ((struct str_Dlr *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Dlr *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Edl) {
         nstr->item->entry=(struct str_Edl *) malloc(sizeof(struct str_Edl ));
         (*((struct str_Edl *)(nstr->item->entry))) = (*((struct str_Edl *)entr));
         if (((struct str_Edl *)(nstr->item->entry))->isStructure2) {
            ((struct str_Edl *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Edl *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Edr) {
         nstr->item->entry=(struct str_Edr *) malloc(sizeof(struct str_Edr ));
         (*((struct str_Edr *)(nstr->item->entry))) = (*((struct str_Edr *)entr));
         if (((struct str_Edr *)(nstr->item->entry))->isStructure2) {
            ((struct str_Edr *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Edr *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Edlr) {
         nstr->item->entry=(struct str_Edlr *) malloc(sizeof(struct str_Edlr ));
         (*((struct str_Edlr *)(nstr->item->entry))) = (*((struct str_Edlr *)entr));
         if (((struct str_Edlr *)(nstr->item->entry))->isStructure2) {
            ((struct str_Edlr *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Edlr *)entr)->structure2);
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
      if (id == SIGID_Co) {
         nstr->item->entry=(struct str_Co *) malloc(sizeof(struct str_Co ));
         (*((struct str_Co *)(nstr->item->entry))) = (*((struct str_Co *)entr));
         if (((struct str_Co *)(nstr->item->entry))->isStructure1) {
            ((struct str_Co *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Co *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Pk) {
         nstr->item->entry=(struct str_Pk *) malloc(sizeof(struct str_Pk ));
         (*((struct str_Pk *)(nstr->item->entry))) = (*((struct str_Pk *)entr));
         if (((struct str_Pk *)(nstr->item->entry))->isStructure1) {
            ((struct str_Pk *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Pk *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Pkmldl) {
         nstr->item->entry=(struct str_Pkmldl *) malloc(sizeof(struct str_Pkmldl ));
         (*((struct str_Pkmldl *)(nstr->item->entry))) = (*((struct str_Pkmldl *)entr));
         if (((struct str_Pkmldl *)(nstr->item->entry))->isStructure2) {
            ((struct str_Pkmldl *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Pkmldl *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Pkmldr) {
         nstr->item->entry=(struct str_Pkmldr *) malloc(sizeof(struct str_Pkmldr ));
         (*((struct str_Pkmldr *)(nstr->item->entry))) = (*((struct str_Pkmldr *)entr));
         if (((struct str_Pkmldr *)(nstr->item->entry))->isStructure1) {
            ((struct str_Pkmldr *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Pkmldr *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Pkmldlr) {
         nstr->item->entry=(struct str_Pkmldlr *) malloc(sizeof(struct str_Pkmldlr ));
         (*((struct str_Pkmldlr *)(nstr->item->entry))) = (*((struct str_Pkmldlr *)entr));
         if (((struct str_Pkmldlr *)(nstr->item->entry))->isStructure2) {
            ((struct str_Pkmldlr *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Pkmldlr *)entr)->structure2);
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
      if (id == SIGID_Kndl) {
         nstr->item->entry=(struct str_Kndl *) malloc(sizeof(struct str_Kndl ));
         (*((struct str_Kndl *)(nstr->item->entry))) = (*((struct str_Kndl *)entr));
         if (((struct str_Kndl *)(nstr->item->entry))->isStructure2) {
            ((struct str_Kndl *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Kndl *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Kndr) {
         nstr->item->entry=(struct str_Kndr *) malloc(sizeof(struct str_Kndr ));
         (*((struct str_Kndr *)(nstr->item->entry))) = (*((struct str_Kndr *)entr));
         if (((struct str_Kndr *)(nstr->item->entry))->isStructure1) {
            ((struct str_Kndr *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Kndr *)entr)->structure1);
         }
      } else 
      if (id == SIGID_Kndlr) {
         nstr->item->entry=(struct str_Kndlr *) malloc(sizeof(struct str_Kndlr ));
         (*((struct str_Kndlr *)(nstr->item->entry))) = (*((struct str_Kndlr *)entr));
         if (((struct str_Kndlr *)(nstr->item->entry))->isStructure2) {
            ((struct str_Kndlr *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Kndlr *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Frd) {
         nstr->item->entry=(struct str_Frd *) malloc(sizeof(struct str_Frd ));
         (*((struct str_Frd *)(nstr->item->entry))) = (*((struct str_Frd *)entr));
         if (((struct str_Frd *)(nstr->item->entry))->isStructure2) {
            ((struct str_Frd *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Frd *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Bkd) {
         nstr->item->entry=(struct str_Bkd *) malloc(sizeof(struct str_Bkd ));
         (*((struct str_Bkd *)(nstr->item->entry))) = (*((struct str_Bkd *)entr));
         if (((struct str_Bkd *)(nstr->item->entry))->isStructure3) {
            ((struct str_Bkd *)(nstr->item->entry))->structure3 = copy_str_Signature(((struct str_Bkd *)entr)->structure3);
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
      if (id == SIGID_Middlro) {
         nstr->item->entry=(struct str_Middlro *) malloc(sizeof(struct str_Middlro ));
         (*((struct str_Middlro *)(nstr->item->entry))) = (*((struct str_Middlro *)entr));
      } else 
      if (id == SIGID_Middl) {
         nstr->item->entry=(struct str_Middl *) malloc(sizeof(struct str_Middl ));
         (*((struct str_Middl *)(nstr->item->entry))) = (*((struct str_Middl *)entr));
         if (((struct str_Middl *)(nstr->item->entry))->isStructure3) {
            ((struct str_Middl *)(nstr->item->entry))->structure3 = copy_str_Signature(((struct str_Middl *)entr)->structure3);
         }
      } else 
      if (id == SIGID_Middr) {
         nstr->item->entry=(struct str_Middr *) malloc(sizeof(struct str_Middr ));
         (*((struct str_Middr *)(nstr->item->entry))) = (*((struct str_Middr *)entr));
         if (((struct str_Middr *)(nstr->item->entry))->isStructure2) {
            ((struct str_Middr *)(nstr->item->entry))->structure2 = copy_str_Signature(((struct str_Middr *)entr)->structure2);
         }
      } else 
      if (id == SIGID_Middlr) {
         nstr->item->entry=(struct str_Middlr *) malloc(sizeof(struct str_Middlr ));
         (*((struct str_Middlr *)(nstr->item->entry))) = (*((struct str_Middlr *)entr));
         if (((struct str_Middlr *)(nstr->item->entry))->isStructure4) {
            ((struct str_Middlr *)(nstr->item->entry))->structure4 = copy_str_Signature(((struct str_Middlr *)entr)->structure4);
         }
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
         if (c->utype == SIGID_Mldl) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Mldl *)(c->entry))->pp_init_a4);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Mldl *)(c->entry))->a4);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Mldr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Mldr *)(c->entry))->pp_init_a3);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Mldr *)(c->entry))->a3);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Mldlr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Mldlr *)(c->entry))->pp_init_a4);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Mldlr *)(c->entry))->a4);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Dl) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Dl *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Dl *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Dr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Dr *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Dr *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Dlr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Dlr *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Dlr *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Edl) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Edl *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Edl *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Edr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Edr *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Edr *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Edlr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Edlr *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Edlr *)(c->entry))->a2);
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
         if (c->utype == SIGID_Co) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Co *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Co *)(c->entry))->a1);
            }
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
         if (c->utype == SIGID_Pkmldl) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Pkmldl *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Pkmldl *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Pkmldr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Pkmldr *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Pkmldr *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Pkmldlr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Pkmldlr *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Pkmldlr *)(c->entry))->a2);
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
         if (c->utype == SIGID_Kndl) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Kndl *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Kndl *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Kndr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Kndr *)(c->entry))->pp_init_a1);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Kndr *)(c->entry))->a1);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Kndlr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Kndlr *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Kndlr *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Frd) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Frd *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Frd *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Bkd) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Bkd *)(c->entry))->pp_init_a3);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Bkd *)(c->entry))->a3);
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
         if (c->utype == SIGID_Middlro) {
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Middl) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Middl *)(c->entry))->pp_init_a3);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Middl *)(c->entry))->a3);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Middr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Middr *)(c->entry))->pp_init_a2);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Middr *)(c->entry))->a2);
            }
            free(c->entry);
            free(c);
         } else 
         if (c->utype == SIGID_Middlr) {
            if (rmAll) {
               free_str_Signature(rmAll, ((struct str_Middlr *)(c->entry))->pp_init_a4);
            }
            else {
               free_str_Signature(rmAll, ((struct str_Middlr *)(c->entry))->a4);
            }
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
         if (c->utype == SIGID_Mldl) {
            if (((struct str_Mldl *)(c->entry))->isStructure4) {
               ((struct str_Mldl *)(c->entry))->a4 = build_str_Signature(((struct str_Mldl *)(c->entry))->structure4);
               ((struct str_Mldl *)(c->entry))->pp_init_a4 = ((struct str_Mldl *)(c->entry))->a4;
            }
            else {
               ((struct str_Mldl *)(c->entry))->a4 = (*((struct str_Mldl *)(c->entry))->f4)(((struct str_Mldl *)(c->entry))->i4, ((struct str_Mldl *)(c->entry))->j4, ((struct str_Mldl *)(c->entry))->diff4);
               ((struct str_Mldl *)(c->entry))->pp_init_a4 = ((struct str_Mldl *)(c->entry))->a4;
            }
         } else 
         if (c->utype == SIGID_Mldr) {
            if (((struct str_Mldr *)(c->entry))->isStructure3) {
               ((struct str_Mldr *)(c->entry))->a3 = build_str_Signature(((struct str_Mldr *)(c->entry))->structure3);
               ((struct str_Mldr *)(c->entry))->pp_init_a3 = ((struct str_Mldr *)(c->entry))->a3;
            }
            else {
               ((struct str_Mldr *)(c->entry))->a3 = (*((struct str_Mldr *)(c->entry))->f3)(((struct str_Mldr *)(c->entry))->i3, ((struct str_Mldr *)(c->entry))->j3, ((struct str_Mldr *)(c->entry))->diff3);
               ((struct str_Mldr *)(c->entry))->pp_init_a3 = ((struct str_Mldr *)(c->entry))->a3;
            }
         } else 
         if (c->utype == SIGID_Mldlr) {
            if (((struct str_Mldlr *)(c->entry))->isStructure4) {
               ((struct str_Mldlr *)(c->entry))->a4 = build_str_Signature(((struct str_Mldlr *)(c->entry))->structure4);
               ((struct str_Mldlr *)(c->entry))->pp_init_a4 = ((struct str_Mldlr *)(c->entry))->a4;
            }
            else {
               ((struct str_Mldlr *)(c->entry))->a4 = (*((struct str_Mldlr *)(c->entry))->f4)(((struct str_Mldlr *)(c->entry))->i4, ((struct str_Mldlr *)(c->entry))->j4, ((struct str_Mldlr *)(c->entry))->diff4);
               ((struct str_Mldlr *)(c->entry))->pp_init_a4 = ((struct str_Mldlr *)(c->entry))->a4;
            }
         } else 
         if (c->utype == SIGID_Dl) {
            if (((struct str_Dl *)(c->entry))->isStructure2) {
               ((struct str_Dl *)(c->entry))->a2 = build_str_Signature(((struct str_Dl *)(c->entry))->structure2);
               ((struct str_Dl *)(c->entry))->pp_init_a2 = ((struct str_Dl *)(c->entry))->a2;
            }
            else {
               ((struct str_Dl *)(c->entry))->a2 = (*((struct str_Dl *)(c->entry))->f2)(((struct str_Dl *)(c->entry))->i2, ((struct str_Dl *)(c->entry))->j2, ((struct str_Dl *)(c->entry))->diff2);
               ((struct str_Dl *)(c->entry))->pp_init_a2 = ((struct str_Dl *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Dr) {
            if (((struct str_Dr *)(c->entry))->isStructure2) {
               ((struct str_Dr *)(c->entry))->a2 = build_str_Signature(((struct str_Dr *)(c->entry))->structure2);
               ((struct str_Dr *)(c->entry))->pp_init_a2 = ((struct str_Dr *)(c->entry))->a2;
            }
            else {
               ((struct str_Dr *)(c->entry))->a2 = (*((struct str_Dr *)(c->entry))->f2)(((struct str_Dr *)(c->entry))->i2, ((struct str_Dr *)(c->entry))->j2, ((struct str_Dr *)(c->entry))->diff2);
               ((struct str_Dr *)(c->entry))->pp_init_a2 = ((struct str_Dr *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Dlr) {
            if (((struct str_Dlr *)(c->entry))->isStructure2) {
               ((struct str_Dlr *)(c->entry))->a2 = build_str_Signature(((struct str_Dlr *)(c->entry))->structure2);
               ((struct str_Dlr *)(c->entry))->pp_init_a2 = ((struct str_Dlr *)(c->entry))->a2;
            }
            else {
               ((struct str_Dlr *)(c->entry))->a2 = (*((struct str_Dlr *)(c->entry))->f2)(((struct str_Dlr *)(c->entry))->i2, ((struct str_Dlr *)(c->entry))->j2, ((struct str_Dlr *)(c->entry))->diff2);
               ((struct str_Dlr *)(c->entry))->pp_init_a2 = ((struct str_Dlr *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Edl) {
            if (((struct str_Edl *)(c->entry))->isStructure2) {
               ((struct str_Edl *)(c->entry))->a2 = build_str_Signature(((struct str_Edl *)(c->entry))->structure2);
               ((struct str_Edl *)(c->entry))->pp_init_a2 = ((struct str_Edl *)(c->entry))->a2;
            }
            else {
               ((struct str_Edl *)(c->entry))->a2 = (*((struct str_Edl *)(c->entry))->f2)(((struct str_Edl *)(c->entry))->i2, ((struct str_Edl *)(c->entry))->j2, ((struct str_Edl *)(c->entry))->diff2);
               ((struct str_Edl *)(c->entry))->pp_init_a2 = ((struct str_Edl *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Edr) {
            if (((struct str_Edr *)(c->entry))->isStructure2) {
               ((struct str_Edr *)(c->entry))->a2 = build_str_Signature(((struct str_Edr *)(c->entry))->structure2);
               ((struct str_Edr *)(c->entry))->pp_init_a2 = ((struct str_Edr *)(c->entry))->a2;
            }
            else {
               ((struct str_Edr *)(c->entry))->a2 = (*((struct str_Edr *)(c->entry))->f2)(((struct str_Edr *)(c->entry))->i2, ((struct str_Edr *)(c->entry))->j2, ((struct str_Edr *)(c->entry))->diff2);
               ((struct str_Edr *)(c->entry))->pp_init_a2 = ((struct str_Edr *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Edlr) {
            if (((struct str_Edlr *)(c->entry))->isStructure2) {
               ((struct str_Edlr *)(c->entry))->a2 = build_str_Signature(((struct str_Edlr *)(c->entry))->structure2);
               ((struct str_Edlr *)(c->entry))->pp_init_a2 = ((struct str_Edlr *)(c->entry))->a2;
            }
            else {
               ((struct str_Edlr *)(c->entry))->a2 = (*((struct str_Edlr *)(c->entry))->f2)(((struct str_Edlr *)(c->entry))->i2, ((struct str_Edlr *)(c->entry))->j2, ((struct str_Edlr *)(c->entry))->diff2);
               ((struct str_Edlr *)(c->entry))->pp_init_a2 = ((struct str_Edlr *)(c->entry))->a2;
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
         if (c->utype == SIGID_Co) {
            if (((struct str_Co *)(c->entry))->isStructure1) {
               ((struct str_Co *)(c->entry))->a1 = build_str_Signature(((struct str_Co *)(c->entry))->structure1);
               ((struct str_Co *)(c->entry))->pp_init_a1 = ((struct str_Co *)(c->entry))->a1;
            }
            else {
               ((struct str_Co *)(c->entry))->a1 = (*((struct str_Co *)(c->entry))->f1)(((struct str_Co *)(c->entry))->i1, ((struct str_Co *)(c->entry))->j1, ((struct str_Co *)(c->entry))->diff1);
               ((struct str_Co *)(c->entry))->pp_init_a1 = ((struct str_Co *)(c->entry))->a1;
            }
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
         if (c->utype == SIGID_Pkmldl) {
            if (((struct str_Pkmldl *)(c->entry))->isStructure2) {
               ((struct str_Pkmldl *)(c->entry))->a2 = build_str_Signature(((struct str_Pkmldl *)(c->entry))->structure2);
               ((struct str_Pkmldl *)(c->entry))->pp_init_a2 = ((struct str_Pkmldl *)(c->entry))->a2;
            }
            else {
               ((struct str_Pkmldl *)(c->entry))->a2 = (*((struct str_Pkmldl *)(c->entry))->f2)(((struct str_Pkmldl *)(c->entry))->i2, ((struct str_Pkmldl *)(c->entry))->j2, ((struct str_Pkmldl *)(c->entry))->diff2);
               ((struct str_Pkmldl *)(c->entry))->pp_init_a2 = ((struct str_Pkmldl *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Pkmldr) {
            if (((struct str_Pkmldr *)(c->entry))->isStructure1) {
               ((struct str_Pkmldr *)(c->entry))->a1 = build_str_Signature(((struct str_Pkmldr *)(c->entry))->structure1);
               ((struct str_Pkmldr *)(c->entry))->pp_init_a1 = ((struct str_Pkmldr *)(c->entry))->a1;
            }
            else {
               ((struct str_Pkmldr *)(c->entry))->a1 = (*((struct str_Pkmldr *)(c->entry))->f1)(((struct str_Pkmldr *)(c->entry))->i1, ((struct str_Pkmldr *)(c->entry))->j1, ((struct str_Pkmldr *)(c->entry))->diff1);
               ((struct str_Pkmldr *)(c->entry))->pp_init_a1 = ((struct str_Pkmldr *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Pkmldlr) {
            if (((struct str_Pkmldlr *)(c->entry))->isStructure2) {
               ((struct str_Pkmldlr *)(c->entry))->a2 = build_str_Signature(((struct str_Pkmldlr *)(c->entry))->structure2);
               ((struct str_Pkmldlr *)(c->entry))->pp_init_a2 = ((struct str_Pkmldlr *)(c->entry))->a2;
            }
            else {
               ((struct str_Pkmldlr *)(c->entry))->a2 = (*((struct str_Pkmldlr *)(c->entry))->f2)(((struct str_Pkmldlr *)(c->entry))->i2, ((struct str_Pkmldlr *)(c->entry))->j2, ((struct str_Pkmldlr *)(c->entry))->diff2);
               ((struct str_Pkmldlr *)(c->entry))->pp_init_a2 = ((struct str_Pkmldlr *)(c->entry))->a2;
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
         if (c->utype == SIGID_Kndl) {
            if (((struct str_Kndl *)(c->entry))->isStructure2) {
               ((struct str_Kndl *)(c->entry))->a2 = build_str_Signature(((struct str_Kndl *)(c->entry))->structure2);
               ((struct str_Kndl *)(c->entry))->pp_init_a2 = ((struct str_Kndl *)(c->entry))->a2;
            }
            else {
               ((struct str_Kndl *)(c->entry))->a2 = (*((struct str_Kndl *)(c->entry))->f2)(((struct str_Kndl *)(c->entry))->i2, ((struct str_Kndl *)(c->entry))->j2, ((struct str_Kndl *)(c->entry))->diff2);
               ((struct str_Kndl *)(c->entry))->pp_init_a2 = ((struct str_Kndl *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Kndr) {
            if (((struct str_Kndr *)(c->entry))->isStructure1) {
               ((struct str_Kndr *)(c->entry))->a1 = build_str_Signature(((struct str_Kndr *)(c->entry))->structure1);
               ((struct str_Kndr *)(c->entry))->pp_init_a1 = ((struct str_Kndr *)(c->entry))->a1;
            }
            else {
               ((struct str_Kndr *)(c->entry))->a1 = (*((struct str_Kndr *)(c->entry))->f1)(((struct str_Kndr *)(c->entry))->i1, ((struct str_Kndr *)(c->entry))->j1, ((struct str_Kndr *)(c->entry))->diff1);
               ((struct str_Kndr *)(c->entry))->pp_init_a1 = ((struct str_Kndr *)(c->entry))->a1;
            }
         } else 
         if (c->utype == SIGID_Kndlr) {
            if (((struct str_Kndlr *)(c->entry))->isStructure2) {
               ((struct str_Kndlr *)(c->entry))->a2 = build_str_Signature(((struct str_Kndlr *)(c->entry))->structure2);
               ((struct str_Kndlr *)(c->entry))->pp_init_a2 = ((struct str_Kndlr *)(c->entry))->a2;
            }
            else {
               ((struct str_Kndlr *)(c->entry))->a2 = (*((struct str_Kndlr *)(c->entry))->f2)(((struct str_Kndlr *)(c->entry))->i2, ((struct str_Kndlr *)(c->entry))->j2, ((struct str_Kndlr *)(c->entry))->diff2);
               ((struct str_Kndlr *)(c->entry))->pp_init_a2 = ((struct str_Kndlr *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Frd) {
            if (((struct str_Frd *)(c->entry))->isStructure2) {
               ((struct str_Frd *)(c->entry))->a2 = build_str_Signature(((struct str_Frd *)(c->entry))->structure2);
               ((struct str_Frd *)(c->entry))->pp_init_a2 = ((struct str_Frd *)(c->entry))->a2;
            }
            else {
               ((struct str_Frd *)(c->entry))->a2 = (*((struct str_Frd *)(c->entry))->f2)(((struct str_Frd *)(c->entry))->i2, ((struct str_Frd *)(c->entry))->j2, ((struct str_Frd *)(c->entry))->diff2);
               ((struct str_Frd *)(c->entry))->pp_init_a2 = ((struct str_Frd *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Bkd) {
            if (((struct str_Bkd *)(c->entry))->isStructure3) {
               ((struct str_Bkd *)(c->entry))->a3 = build_str_Signature(((struct str_Bkd *)(c->entry))->structure3);
               ((struct str_Bkd *)(c->entry))->pp_init_a3 = ((struct str_Bkd *)(c->entry))->a3;
            }
            else {
               ((struct str_Bkd *)(c->entry))->a3 = (*((struct str_Bkd *)(c->entry))->f3)(((struct str_Bkd *)(c->entry))->i3, ((struct str_Bkd *)(c->entry))->j3, ((struct str_Bkd *)(c->entry))->diff3);
               ((struct str_Bkd *)(c->entry))->pp_init_a3 = ((struct str_Bkd *)(c->entry))->a3;
            }
         } else 
         if (c->utype == SIGID_Emptymid) {
         } else 
         if (c->utype == SIGID_Midbase) {
         } else 
         if (c->utype == SIGID_Middlro) {
         } else 
         if (c->utype == SIGID_Middl) {
            if (((struct str_Middl *)(c->entry))->isStructure3) {
               ((struct str_Middl *)(c->entry))->a3 = build_str_Signature(((struct str_Middl *)(c->entry))->structure3);
               ((struct str_Middl *)(c->entry))->pp_init_a3 = ((struct str_Middl *)(c->entry))->a3;
            }
            else {
               ((struct str_Middl *)(c->entry))->a3 = (*((struct str_Middl *)(c->entry))->f3)(((struct str_Middl *)(c->entry))->i3, ((struct str_Middl *)(c->entry))->j3, ((struct str_Middl *)(c->entry))->diff3);
               ((struct str_Middl *)(c->entry))->pp_init_a3 = ((struct str_Middl *)(c->entry))->a3;
            }
         } else 
         if (c->utype == SIGID_Middr) {
            if (((struct str_Middr *)(c->entry))->isStructure2) {
               ((struct str_Middr *)(c->entry))->a2 = build_str_Signature(((struct str_Middr *)(c->entry))->structure2);
               ((struct str_Middr *)(c->entry))->pp_init_a2 = ((struct str_Middr *)(c->entry))->a2;
            }
            else {
               ((struct str_Middr *)(c->entry))->a2 = (*((struct str_Middr *)(c->entry))->f2)(((struct str_Middr *)(c->entry))->i2, ((struct str_Middr *)(c->entry))->j2, ((struct str_Middr *)(c->entry))->diff2);
               ((struct str_Middr *)(c->entry))->pp_init_a2 = ((struct str_Middr *)(c->entry))->a2;
            }
         } else 
         if (c->utype == SIGID_Middlr) {
            if (((struct str_Middlr *)(c->entry))->isStructure4) {
               ((struct str_Middlr *)(c->entry))->a4 = build_str_Signature(((struct str_Middlr *)(c->entry))->structure4);
               ((struct str_Middlr *)(c->entry))->pp_init_a4 = ((struct str_Middlr *)(c->entry))->a4;
            }
            else {
               ((struct str_Middlr *)(c->entry))->a4 = (*((struct str_Middlr *)(c->entry))->f4)(((struct str_Middlr *)(c->entry))->i4, ((struct str_Middlr *)(c->entry))->j4, ((struct str_Middlr *)(c->entry))->diff4);
               ((struct str_Middlr *)(c->entry))->pp_init_a4 = ((struct str_Middlr *)(c->entry))->a4;
            }
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
      if (c->utype == SIGID_Mldl) {
         if (((struct str_Mldl *)(c->entry))->isStructure4) {
            update_str_Signature(((struct str_Mldl *)(c->entry))->structure4->item, diff);
         }
         else {
            ((struct str_Mldl *)(c->entry))->diff4 = diff;
         }
      } else 
      if (c->utype == SIGID_Mldr) {
         if (((struct str_Mldr *)(c->entry))->isStructure3) {
            update_str_Signature(((struct str_Mldr *)(c->entry))->structure3->item, diff);
         }
         else {
            ((struct str_Mldr *)(c->entry))->diff3 = diff;
         }
      } else 
      if (c->utype == SIGID_Mldlr) {
         if (((struct str_Mldlr *)(c->entry))->isStructure4) {
            update_str_Signature(((struct str_Mldlr *)(c->entry))->structure4->item, diff);
         }
         else {
            ((struct str_Mldlr *)(c->entry))->diff4 = diff;
         }
      } else 
      if (c->utype == SIGID_Dl) {
         if (((struct str_Dl *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Dl *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Dl *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Dr) {
         if (((struct str_Dr *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Dr *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Dr *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Dlr) {
         if (((struct str_Dlr *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Dlr *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Dlr *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Edl) {
         if (((struct str_Edl *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Edl *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Edl *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Edr) {
         if (((struct str_Edr *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Edr *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Edr *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Edlr) {
         if (((struct str_Edlr *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Edlr *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Edlr *)(c->entry))->diff2 = diff;
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
      if (c->utype == SIGID_Co) {
         if (((struct str_Co *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Co *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Co *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Pk) {
         if (((struct str_Pk *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Pk *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Pk *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Pkmldl) {
         if (((struct str_Pkmldl *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Pkmldl *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Pkmldl *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Pkmldr) {
         if (((struct str_Pkmldr *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Pkmldr *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Pkmldr *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Pkmldlr) {
         if (((struct str_Pkmldlr *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Pkmldlr *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Pkmldlr *)(c->entry))->diff2 = diff;
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
      if (c->utype == SIGID_Kndl) {
         if (((struct str_Kndl *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Kndl *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Kndl *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Kndr) {
         if (((struct str_Kndr *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Kndr *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Kndr *)(c->entry))->diff1 = diff;
         }
      } else 
      if (c->utype == SIGID_Kndlr) {
         if (((struct str_Kndlr *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Kndlr *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Kndlr *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Frd) {
         if (((struct str_Frd *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Frd *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Frd *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Bkd) {
         if (((struct str_Bkd *)(c->entry))->isStructure3) {
            update_str_Signature(((struct str_Bkd *)(c->entry))->structure3->item, diff);
         }
         else {
            ((struct str_Bkd *)(c->entry))->diff3 = diff;
         }
      } else 
      if (c->utype == SIGID_Emptymid) {
         ((struct str_Emptymid *)(c->entry))->diff = diff;
      } else 
      if (c->utype == SIGID_Midbase) {
         ((struct str_Midbase *)(c->entry))->diff = diff;
      } else 
      if (c->utype == SIGID_Middlro) {
         ((struct str_Middlro *)(c->entry))->diff = diff;
      } else 
      if (c->utype == SIGID_Middl) {
         if (((struct str_Middl *)(c->entry))->isStructure3) {
            update_str_Signature(((struct str_Middl *)(c->entry))->structure3->item, diff);
         }
         else {
            ((struct str_Middl *)(c->entry))->diff3 = diff;
         }
      } else 
      if (c->utype == SIGID_Middr) {
         if (((struct str_Middr *)(c->entry))->isStructure2) {
            update_str_Signature(((struct str_Middr *)(c->entry))->structure2->item, diff);
         }
         else {
            ((struct str_Middr *)(c->entry))->diff2 = diff;
         }
      } else 
      if (c->utype == SIGID_Middlr) {
         if (((struct str_Middlr *)(c->entry))->isStructure4) {
            update_str_Signature(((struct str_Middlr *)(c->entry))->structure4->item, diff);
         }
         else {
            ((struct str_Middlr *)(c->entry))->diff4 = diff;
         }
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
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16;

   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v1 = edl <<< lbase ~~~ p closed ~~~ loc ----------------- */
      if ((j-i) >= 8) {
         v1 = (tbl_closed(i+1, j) + dl_energy((i+1) + 1, j)) + termaupenalty((i+1) + 1, j);
      }
      else {
         v1 = 1.0e7;
      }
      /* ---------------- v1 = edl <<< lbase ~~~ p closed ~~~ loc ----------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v2 = edr <<< loc ~~~ p closed ~~~ lbase ----------------- */
      if ((j-i) >= 8) {
         v2 = (tbl_closed(i, j-1) + dr_energy((i) + 1, (j) - 1)) + termaupenalty((i) + 1, (j) - 1);
      }
      else {
         v2 = 1.0e7;
      }
      /* ---------------- v2 = edr <<< loc ~~~ p closed ~~~ lbase ----------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------- v3 = edlr <<< lbase ~~~ p closed ~~~ lbase --------------- */
      if ((j-i) >= 9) {
         v3 = ((tbl_closed(i+1, j-1) + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)) + termaupenalty((i+1) + 1, (j) - 1);
      }
      else {
         v3 = 1.0e7;
      }
      /* --------------- v3 = edlr <<< lbase ~~~ p closed ~~~ lbase --------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------- v4 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v5 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      v5 = tbl_closed(i, j) + termaupenalty((i) + 1, j);
      /* ------------------ v5 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v4 = v5;
      /* ------------- v4 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------------- v6 = kndr <<< p knot ~~~ lbase --------------------- */
      if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
         v6 = (tbl_knot(i, j-1).tup1 + npp) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1));
      }
      else {
         v6 = 1.0e7;
      }
      /* --------------------- v6 = kndr <<< p knot ~~~ lbase --------------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------------- v7 = kndl <<< lbase ~~~ p knot --------------------- */
      if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
         v7 = (tbl_knot(i+1, j).tup1 + npp) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3));
      }
      else {
         v7 = 1.0e7;
      }
      /* --------------------- v7 = kndl <<< lbase ~~~ p knot --------------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------- v8 = kndlr <<< lbase ~~~ p knot ~~~ lbase ---------------- */
      if (((j-i) >= 13) && ((j-i) <= (max_pknot_length+2))) {
         v8 = (tbl_knot(i+1, j-1).tup1 + (2 * npp)) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1)));
      }
      else {
         v8 = 1.0e7;
      }
      /* --------------- v8 = kndlr <<< lbase ~~~ p knot ~~~ lbase ---------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------------------- v9 = pk <<< p knot --------------------------- */
      if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
         v9 = tbl_knot(i, j).tup1;
      }
      else {
         v9 = 1.0e7;
      }
      /* --------------------------- v9 = pk <<< p knot --------------------------- */
      /* -------------------------------- finished -------------------------------- */

      v10 = v8 < v9 ? v8 : v9;
      v11 = v7 < v10 ? v7 : v10;
      v12 = v6 < v11 ? v6 : v11;
      v13 = v4 < v12 ? v4 : v12;
      v14 = v3 < v13 ? v3 : v13;
      v15 = v2 < v14 ? v2 : v14;
      v16 = v1 < v15 ? v1 : v15;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_edangle(i, j) = v16;
   }
}

/* table calculation for production edangle_Pr                                      */
/* -------------------------------------------------------------------------------- */
static void calc_edangle_Pr(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16;

   if ((j-i) >= 11) {
      /* -------------------------------- start of -------------------------------- */
      /* --------------- v1 = edl <<< lbase ~~~ p closed_Pr ~~~ loc --------------- */
      if ((j-i) >= 23) {
         v1 = (tbl_closed_Pr(i+1, j) + dl_energy((i+1) + 1, j)) + termaupenalty((i+1) + 1, j);
      }
      else {
         v1 = 1.0e7;
      }
      /* --------------- v1 = edl <<< lbase ~~~ p closed_Pr ~~~ loc --------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------- v2 = edr <<< loc ~~~ p closed_Pr ~~~ lbase --------------- */
      if ((j-i) >= 23) {
         v2 = (tbl_closed_Pr(i, j-1) + dr_energy((i) + 1, (j) - 1)) + termaupenalty((i) + 1, (j) - 1);
      }
      else {
         v2 = 1.0e7;
      }
      /* --------------- v2 = edr <<< loc ~~~ p closed_Pr ~~~ lbase --------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------- v3 = edlr <<< lbase ~~~ p closed_Pr ~~~ lbase -------------- */
      if ((j-i) >= 24) {
         v3 = ((tbl_closed_Pr(i+1, j-1) + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)) + termaupenalty((i+1) + 1, (j) - 1);
      }
      else {
         v3 = 1.0e7;
      }
      /* ------------- v3 = edlr <<< lbase ~~~ p closed_Pr ~~~ lbase -------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------ v4 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
      if ((j-i) >= 22) {
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v5 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         v5 = tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j);
         /* --------------- v5 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         /* ------------------------------- finished ------------------------------ */

         v4 = v5;
      }
      else {
         v4 = 1.0e7;
      }
      /* ------------ v4 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------------- v6 = kndr <<< p knot ~~~ lbase --------------------- */
      if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
         v6 = (tbl_knot(i, j-1).tup1 + npp) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1));
      }
      else {
         v6 = 1.0e7;
      }
      /* --------------------- v6 = kndr <<< p knot ~~~ lbase --------------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------------- v7 = kndl <<< lbase ~~~ p knot --------------------- */
      if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
         v7 = (tbl_knot(i+1, j).tup1 + npp) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3));
      }
      else {
         v7 = 1.0e7;
      }
      /* --------------------- v7 = kndl <<< lbase ~~~ p knot --------------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------- v8 = kndlr <<< lbase ~~~ p knot ~~~ lbase ---------------- */
      if (((j-i) >= 13) && ((j-i) <= (max_pknot_length+2))) {
         v8 = (tbl_knot(i+1, j-1).tup1 + (2 * npp)) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1)));
      }
      else {
         v8 = 1.0e7;
      }
      /* --------------- v8 = kndlr <<< lbase ~~~ p knot ~~~ lbase ---------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --------------------------- v9 = pk <<< p knot --------------------------- */
      if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
         v9 = tbl_knot(i, j).tup1;
      }
      else {
         v9 = 1.0e7;
      }
      /* --------------------------- v9 = pk <<< p knot --------------------------- */
      /* -------------------------------- finished -------------------------------- */

      v10 = v8 < v9 ? v8 : v9;
      v11 = v7 < v10 ? v7 : v10;
      v12 = v6 < v11 ? v6 : v11;
      v13 = v4 < v12 ? v4 : v12;
      v14 = v3 < v13 ? v3 : v13;
      v15 = v2 < v14 ? v2 : v14;
      v16 = v1 < v15 ? v1 : v15;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_edangle_Pr(i, j) = v16;
   }
}

/* table calculation for production closed                                          */
/* -------------------------------------------------------------------------------- */
static void calc_closed(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;
   int v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22;
   int v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33;
   int k, k2, k3, k4, k5, k6, k7, k8;

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
            /*  v12 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
            if ((j-i) >= 19) {
               /* ---------------------------- start of --------------------------- */
               /* ------------- v14 = combine <<< p block ~~~ p comps ------------- */
               v14 = 1.0e7;
               for (k5=i+10; k5<=j-9; k5++) {
                  v13 = tbl_block(i+3, k5) + tbl_comps(k5, j-2);
                  v14 = v13 < v14 ? v13 : v14;
               }
               /* ------------- v14 = combine <<< p block ~~~ p comps ------------- */
               /* ---------------------------- finished --------------------------- */

               v12 = (((380 + v14) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            }
            else {
               v12 = 1.0e7;
            }
            /*  v12 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /*  v15 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
            if ((j-i) >= 19) {
               /* ---------------------------- start of --------------------------- */
               /* ------------- v17 = combine <<< p block ~~~ p comps ------------- */
               v17 = 1.0e7;
               for (k6=i+9; k6<=j-10; k6++) {
                  v16 = tbl_block(i+2, k6) + tbl_comps(k6, j-3);
                  v17 = v16 < v17 ? v16 : v17;
               }
               /* ------------- v17 = combine <<< p block ~~~ p comps ------------- */
               /* ---------------------------- finished --------------------------- */

               v15 = (((380 + v17) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            }
            else {
               v15 = 1.0e7;
            }
            /*  v15 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /*  v18 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
            if ((j-i) >= 20) {
               /* ---------------------------- start of --------------------------- */
               /* ------------- v20 = combine <<< p block ~~~ p comps ------------- */
               v20 = 1.0e7;
               for (k7=i+10; k7<=j-10; k7++) {
                  v19 = tbl_block(i+3, k7) + tbl_comps(k7, j-3);
                  v20 = v19 < v20 ? v19 : v20;
               }
               /* ------------- v20 = combine <<< p block ~~~ p comps ------------- */
               /* ---------------------------- finished --------------------------- */

               v18 = ((((380 + v20) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            }
            else {
               v18 = 1.0e7;
            }
            /*  v18 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /*  v21 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
            if ((j-i) >= 18) {
               /* ---------------------------- start of --------------------------- */
               /* ------------- v23 = combine <<< p block ~~~ p comps ------------- */
               v23 = 1.0e7;
               for (k8=i+9; k8<=j-9; k8++) {
                  v22 = tbl_block(i+2, k8) + tbl_comps(k8, j-2);
                  v23 = v22 < v23 ? v22 : v23;
               }
               /* ------------- v23 = combine <<< p block ~~~ p comps ------------- */
               /* ---------------------------- finished --------------------------- */

               v21 = ((380 + v23) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            }
            else {
               v21 = 1.0e7;
            }
            /*  v21 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            v24 = v18 < v21 ? v18 : v21;
            v25 = v15 < v24 ? v15 : v24;
            v26 = v12 < v25 ? v12 : v25;
            v27 = v26;
         }
         else {
            v27 = 1.0e7;
         }
         v28 = v11 < v27 ? v11 : v27;
         v29 = v9 < v28 ? v9 : v28;
         v30 = v6 < v29 ? v6 : v29;
         v31 = v3 < v30 ? v3 : v30;
         v32 = v31;
      }
      else {
         v32 = 1.0e7;
      }
      v33 = v2 < v32 ? v2 : v32;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_closed(i, j) = v33;
   }
}

/* table calculation for production closed_Pr                                       */
/* -------------------------------------------------------------------------------- */
static void calc_closed_Pr(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13;
   int v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27;
   int v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41;
   int v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55;
   int k, k10, k11, k12, k13, k14, k15, k16, k2, k3, k4, k5, k6, k7, k8, k9;

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
            /*  v11 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
            if ((j-i) >= 23) {
               /* ---------------------------- start of --------------------------- */
               /* ---------- v13 = combine <<< p block_Pr ~~~ p comps_Pr ---------- */
               if ((j-i-5) >= 22) {
                  v13 = 1.0e7;
                  for (k5=i+14; k5<=j-13; k5++) {
                     v12 = tbl_block_Pr(i+3, k5) + tbl_comps_Pr(k5, j-2);
                     v13 = v12 < v13 ? v12 : v13;
                  }
               }
               else {
                  v13 = 1.0e7;
               }
               /* ---------- v13 = combine <<< p block_Pr ~~~ p comps_Pr ---------- */
               /* ---------------------------- finished --------------------------- */

               /* ---------------------------- start of --------------------------- */
               /* ------------ v15 = combine <<< p block ~~~ p comps_Pr ----------- */
               v15 = 1.0e7;
               for (k6=i+10; k6<=j-13; k6++) {
                  v14 = tbl_block(i+3, k6) + tbl_comps_Pr(k6, j-2);
                  v15 = v14 < v15 ? v14 : v15;
               }
               /* ------------ v15 = combine <<< p block ~~~ p comps_Pr ----------- */
               /* ---------------------------- finished --------------------------- */

               /* ---------------------------- start of --------------------------- */
               /* ------------ v17 = combine <<< p block_Pr ~~~ p comps ----------- */
               v17 = 1.0e7;
               for (k7=i+14; k7<=j-9; k7++) {
                  v16 = tbl_block_Pr(i+3, k7) + tbl_comps(k7, j-2);
                  v17 = v16 < v17 ? v16 : v17;
               }
               /* ------------ v17 = combine <<< p block_Pr ~~~ p comps ----------- */
               /* ---------------------------- finished --------------------------- */

               v18 = v15 < v17 ? v15 : v17;
               v19 = v13 < v18 ? v13 : v18;
               v11 = (((380 + v19) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            }
            else {
               v11 = 1.0e7;
            }
            /*  v11 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /*  v20 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
            if ((j-i) >= 23) {
               /* ---------------------------- start of --------------------------- */
               /* ---------- v22 = combine <<< p block_Pr ~~~ p comps_Pr ---------- */
               if ((j-i-5) >= 22) {
                  v22 = 1.0e7;
                  for (k8=i+13; k8<=j-14; k8++) {
                     v21 = tbl_block_Pr(i+2, k8) + tbl_comps_Pr(k8, j-3);
                     v22 = v21 < v22 ? v21 : v22;
                  }
               }
               else {
                  v22 = 1.0e7;
               }
               /* ---------- v22 = combine <<< p block_Pr ~~~ p comps_Pr ---------- */
               /* ---------------------------- finished --------------------------- */

               /* ---------------------------- start of --------------------------- */
               /* ------------ v24 = combine <<< p block ~~~ p comps_Pr ----------- */
               v24 = 1.0e7;
               for (k9=i+9; k9<=j-14; k9++) {
                  v23 = tbl_block(i+2, k9) + tbl_comps_Pr(k9, j-3);
                  v24 = v23 < v24 ? v23 : v24;
               }
               /* ------------ v24 = combine <<< p block ~~~ p comps_Pr ----------- */
               /* ---------------------------- finished --------------------------- */

               /* ---------------------------- start of --------------------------- */
               /* ------------ v26 = combine <<< p block_Pr ~~~ p comps ----------- */
               v26 = 1.0e7;
               for (k10=i+13; k10<=j-10; k10++) {
                  v25 = tbl_block_Pr(i+2, k10) + tbl_comps(k10, j-3);
                  v26 = v25 < v26 ? v25 : v26;
               }
               /* ------------ v26 = combine <<< p block_Pr ~~~ p comps ----------- */
               /* ---------------------------- finished --------------------------- */

               v27 = v24 < v26 ? v24 : v26;
               v28 = v22 < v27 ? v22 : v27;
               v20 = (((380 + v28) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            }
            else {
               v20 = 1.0e7;
            }
            /*  v20 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /*  v29 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
            if ((j-i) >= 24) {
               /* ---------------------------- start of --------------------------- */
               /* ---------- v31 = combine <<< p block_Pr ~~~ p comps_Pr ---------- */
               if ((j-i-6) >= 22) {
                  v31 = 1.0e7;
                  for (k11=i+14; k11<=j-14; k11++) {
                     v30 = tbl_block_Pr(i+3, k11) + tbl_comps_Pr(k11, j-3);
                     v31 = v30 < v31 ? v30 : v31;
                  }
               }
               else {
                  v31 = 1.0e7;
               }
               /* ---------- v31 = combine <<< p block_Pr ~~~ p comps_Pr ---------- */
               /* ---------------------------- finished --------------------------- */

               /* ---------------------------- start of --------------------------- */
               /* ------------ v33 = combine <<< p block ~~~ p comps_Pr ----------- */
               v33 = 1.0e7;
               for (k12=i+10; k12<=j-14; k12++) {
                  v32 = tbl_block(i+3, k12) + tbl_comps_Pr(k12, j-3);
                  v33 = v32 < v33 ? v32 : v33;
               }
               /* ------------ v33 = combine <<< p block ~~~ p comps_Pr ----------- */
               /* ---------------------------- finished --------------------------- */

               /* ---------------------------- start of --------------------------- */
               /* ------------ v35 = combine <<< p block_Pr ~~~ p comps ----------- */
               v35 = 1.0e7;
               for (k13=i+14; k13<=j-10; k13++) {
                  v34 = tbl_block_Pr(i+3, k13) + tbl_comps(k13, j-3);
                  v35 = v34 < v35 ? v34 : v35;
               }
               /* ------------ v35 = combine <<< p block_Pr ~~~ p comps ----------- */
               /* ---------------------------- finished --------------------------- */

               v36 = v33 < v35 ? v33 : v35;
               v37 = v31 < v36 ? v31 : v36;
               v29 = ((((380 + v37) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            }
            else {
               v29 = 1.0e7;
            }
            /*  v29 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /*  v38 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
            /* ----------------------------- start of ----------------------------- */
            /* ----------- v40 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            if ((j-i-4) >= 22) {
               v40 = 1.0e7;
               for (k14=i+13; k14<=j-13; k14++) {
                  v39 = tbl_block_Pr(i+2, k14) + tbl_comps_Pr(k14, j-2);
                  v40 = v39 < v40 ? v39 : v40;
               }
            }
            else {
               v40 = 1.0e7;
            }
            /* ----------- v40 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v42 = combine <<< p block ~~~ p comps_Pr ------------- */
            v42 = 1.0e7;
            for (k15=i+9; k15<=j-13; k15++) {
               v41 = tbl_block(i+2, k15) + tbl_comps_Pr(k15, j-2);
               v42 = v41 < v42 ? v41 : v42;
            }
            /* ------------- v42 = combine <<< p block ~~~ p comps_Pr ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v44 = combine <<< p block_Pr ~~~ p comps ------------- */
            v44 = 1.0e7;
            for (k16=i+13; k16<=j-9; k16++) {
               v43 = tbl_block_Pr(i+2, k16) + tbl_comps(k16, j-2);
               v44 = v43 < v44 ? v43 : v44;
            }
            /* ------------- v44 = combine <<< p block_Pr ~~~ p comps ------------- */
            /* ----------------------------- finished ----------------------------- */

            v45 = v42 < v44 ? v42 : v44;
            v46 = v40 < v45 ? v40 : v45;
            v38 = ((380 + v46) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
            /*  v38 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            v47 = v29 < v38 ? v29 : v38;
            v48 = v20 < v47 ? v20 : v47;
            v49 = v11 < v48 ? v11 : v48;
            v50 = v49;
         }
         else {
            v50 = 1.0e7;
         }
         v51 = v10 < v50 ? v10 : v50;
         v52 = v8 < v51 ? v8 : v51;
         v53 = v5 < v52 ? v5 : v52;
         v54 = v53;
      }
      else {
         v54 = 1.0e7;
      }
      v55 = v2 < v54 ? v2 : v54;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_closed_Pr(i, j) = v55;
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
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13;
   int v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26;
   int k;

   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /*  v1 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h  */
      /* -------------------------------- start of -------------------------------- */
      /* ---- v2 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ----- */
      if ((j-i) >= 8) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------------- v3 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         v3 = tbl_closed(i+1, j) + termaupenalty((i+1) + 1, j);
         /* ----------------- v3 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v2 = v3 + dl_energy((i+1) + 1, j);
      }
      else {
         v2 = 1.0e7;
      }
      /* ---- v2 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ----- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ---- v4 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ----- */
      if ((j-i) >= 8) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------------- v5 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         v5 = tbl_closed(i, j-1) + termaupenalty((i) + 1, j-1);
         /* ----------------- v5 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v4 = v5 + dr_energy((i) + 1, (j) - 1);
      }
      else {
         v4 = 1.0e7;
      }
      /* ---- v4 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ----- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --- v6 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase --- */
      if ((j-i) >= 9) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------------- v7 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         v7 = tbl_closed(i+1, j-1) + termaupenalty((i+1) + 1, j-1);
         /* ----------------- v7 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v6 = (v7 + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1);
      }
      else {
         v6 = 1.0e7;
      }
      /* --- v6 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase --- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------- v8 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v9 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      v9 = tbl_closed(i, j) + termaupenalty((i) + 1, j);
      /* ------------------ v9 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v8 = v9;
      /* ------------- v8 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- finished -------------------------------- */

      v10 = v6 < v8 ? v6 : v8;
      v11 = v4 < v10 ? v4 : v10;
      v12 = v2 < v11 ? v2 : v11;
      v1 = 40 + v12;
      /*  v1 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v25 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h)  */
      if ((j-i) >= 8) {
         v25 = 1.0e7;
         for (k=i+1; k<=j-7; k++) {
            /* ----------------------------- start of ----------------------------- */
            /* - v14 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc - */
            if ((j-k) >= 8) {
               /* ---------------------------- start of --------------------------- */
               /* ------------- v15 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               v15 = tbl_closed(k+1, j) + termaupenalty((k+1) + 1, j);
               /* ------------- v15 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               /* ---------------------------- finished --------------------------- */

               v14 = v15 + dl_energy((k+1) + 1, j);
            }
            else {
               v14 = 1.0e7;
            }
            /* - v14 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc - */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* - v16 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase - */
            if ((j-k) >= 8) {
               /* ---------------------------- start of --------------------------- */
               /* ------------- v17 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               v17 = tbl_closed(k, j-1) + termaupenalty((k) + 1, j-1);
               /* ------------- v17 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               /* ---------------------------- finished --------------------------- */

               v16 = v17 + dr_energy((k) + 1, (j) - 1);
            }
            else {
               v16 = 1.0e7;
            }
            /* - v16 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase - */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* v18 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase  */
            if ((j-k) >= 9) {
               /* ---------------------------- start of --------------------------- */
               /* ------------- v19 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               v19 = tbl_closed(k+1, j-1) + termaupenalty((k+1) + 1, j-1);
               /* ------------- v19 = is <<< loc ~~~ p closed ~~~ loc ------------- */
               /* ---------------------------- finished --------------------------- */

               v18 = (v19 + dl_energy((k+1) + 1, (j) - 1)) + dr_energy((k+1) + 1, (j) - 1);
            }
            else {
               v18 = 1.0e7;
            }
            /* v18 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ---------- v20 = drem <<< is <<< loc ~~~ p closed ~~~ loc ---------- */
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v21 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            v21 = tbl_closed(k, j) + termaupenalty((k) + 1, j);
            /* -------------- v21 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v20 = v21;
            /* ---------- v20 = drem <<< is <<< loc ~~~ p closed ~~~ loc ---------- */
            /* ----------------------------- finished ----------------------------- */

            v22 = v18 < v20 ? v18 : v20;
            v23 = v16 < v22 ? v16 : v22;
            v24 = v14 < v23 ? v14 : v23;
            v13 = (40 + v24) + ss_energy(i, k);
            v25 = v13 < v25 ? v13 : v25;
         }
      }
      else {
         v25 = 1.0e7;
      }
      /*  v25 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h)  */
      /* -------------------------------- finished -------------------------------- */

      v26 = v1 < v25 ? v1 : v25;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_block(i, j) = v26;
   }
}

/* table calculation for production block_Pr                                        */
/* -------------------------------------------------------------------------------- */
static void calc_block_Pr(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;
   int v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22;
   int v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34;
   int k;

   if ((j-i) >= 11) {
      /* -------------------------------- start of -------------------------------- */
      /*  v1 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h  */
      if ((j-i) >= 22) {
         /* ------------------------------- start of ------------------------------ */
         /* -- v2 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc - */
         if ((j-i) >= 23) {
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v3 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            v3 = tbl_closed_Pr(i+1, j) + termaupenalty((i+1) + 1, j);
            /* ------------- v3 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            /* ----------------------------- finished ----------------------------- */

            v2 = v3 + dl_energy((i+1) + 1, j);
         }
         else {
            v2 = 1.0e7;
         }
         /* -- v2 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc - */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* -- v4 = dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase - */
         if ((j-i) >= 23) {
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v5 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            v5 = tbl_closed_Pr(i, j-1) + termaupenalty((i) + 1, j-1);
            /* ------------- v5 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            /* ----------------------------- finished ----------------------------- */

            v4 = v5 + dr_energy((i) + 1, (j) - 1);
         }
         else {
            v4 = 1.0e7;
         }
         /* -- v4 = dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase - */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v6 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase  */
         if ((j-i) >= 24) {
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v7 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            v7 = tbl_closed_Pr(i+1, j-1) + termaupenalty((i+1) + 1, j-1);
            /* ------------- v7 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
            /* ----------------------------- finished ----------------------------- */

            v6 = (v7 + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1);
         }
         else {
            v6 = 1.0e7;
         }
         /*  v6 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* ----------- v8 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v9 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         v9 = tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j);
         /* --------------- v9 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         /* ------------------------------- finished ------------------------------ */

         v8 = v9;
         /* ----------- v8 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
         /* ------------------------------- finished ------------------------------ */

         v10 = v6 < v8 ? v6 : v8;
         v11 = v4 < v10 ? v4 : v10;
         v12 = v2 < v11 ? v2 : v11;
         v1 = 40 + v12;
      }
      else {
         v1 = 1.0e7;
      }
      /*  v1 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v25 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h)  */
      if ((j-i) >= 23) {
         v25 = 1.0e7;
         for (k=i+1; k<=j-22; k++) {
            /* ----------------------------- start of ----------------------------- */
            /* v14 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc  */
            if ((j-k) >= 23) {
               /* ---------------------------- start of --------------------------- */
               /* ------------ v15 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------- */
               v15 = tbl_closed_Pr(k+1, j) + termaupenalty((k+1) + 1, j);
               /* ------------ v15 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------- */
               /* ---------------------------- finished --------------------------- */

               v14 = v15 + dl_energy((k+1) + 1, j);
            }
            else {
               v14 = 1.0e7;
            }
            /* v14 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc  */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* v16 = dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase  */
            if ((j-k) >= 23) {
               /* ---------------------------- start of --------------------------- */
               /* ------------ v17 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------- */
               v17 = tbl_closed_Pr(k, j-1) + termaupenalty((k) + 1, j-1);
               /* ------------ v17 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------- */
               /* ---------------------------- finished --------------------------- */

               v16 = v17 + dr_energy((k) + 1, (j) - 1);
            }
            else {
               v16 = 1.0e7;
            }
            /* v16 = dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase  */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* 18 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbas */
            if ((j-k) >= 24) {
               /* ---------------------------- start of --------------------------- */
               /* ------------ v19 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------- */
               v19 = tbl_closed_Pr(k+1, j-1) + termaupenalty((k+1) + 1, j-1);
               /* ------------ v19 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------- */
               /* ---------------------------- finished --------------------------- */

               v18 = (v19 + dl_energy((k+1) + 1, (j) - 1)) + dr_energy((k+1) + 1, (j) - 1);
            }
            else {
               v18 = 1.0e7;
            }
            /* 18 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbas */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* -------- v20 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc --------- */
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v21 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            v21 = tbl_closed_Pr(k, j) + termaupenalty((k) + 1, j);
            /* ------------- v21 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            /* ----------------------------- finished ----------------------------- */

            v20 = v21;
            /* -------- v20 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc --------- */
            /* ----------------------------- finished ----------------------------- */

            v22 = v18 < v20 ? v18 : v20;
            v23 = v16 < v22 ? v16 : v22;
            v24 = v14 < v23 ? v14 : v23;
            v13 = (40 + v24) + ss_energy(i, k);
            v25 = v13 < v25 ? v13 : v25;
         }
      }
      else {
         v25 = 1.0e7;
      }
      /*  v25 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h)  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------------- v26 = pkmldl <<< lbase ~~~ p knot -------------------- */
      if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
         v26 = (tbl_knot(i+1, j).tup1 + 600) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3));
      }
      else {
         v26 = 1.0e7;
      }
      /* ------------------- v26 = pkmldl <<< lbase ~~~ p knot -------------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------------- v27 = pkmldr <<< p knot ~~~ lbase -------------------- */
      if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
         v27 = (tbl_knot(i, j-1).tup1 + 600) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1));
      }
      else {
         v27 = 1.0e7;
      }
      /* ------------------- v27 = pkmldr <<< p knot ~~~ lbase -------------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* -------------- v28 = pkmldlr <<< lbase ~~~ p knot ~~~ lbase -------------- */
      if (((j-i) >= 13) && ((j-i) <= (max_pknot_length+2))) {
         v28 = (tbl_knot(i+1, j-1).tup1 + 600) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1)));
      }
      else {
         v28 = 1.0e7;
      }
      /* -------------- v28 = pkmldlr <<< lbase ~~~ p knot ~~~ lbase -------------- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------------------- v29 = pkml <<< p knot -------------------------- */
      if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
         v29 = tbl_knot(i, j).tup1 + 600;
      }
      else {
         v29 = 1.0e7;
      }
      /* ------------------------- v29 = pkml <<< p knot -------------------------- */
      /* -------------------------------- finished -------------------------------- */

      v30 = v28 < v29 ? v28 : v29;
      v31 = v27 < v30 ? v27 : v30;
      v32 = v26 < v31 ? v26 : v31;
      v33 = v25 < v32 ? v25 : v32;
      v34 = v1 < v33 ? v1 : v33;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_block_Pr(i, j) = v34;
   }
}

/* table calculation for production knot                                            */
/* -------------------------------------------------------------------------------- */
static void calc_knot(int i, int j)
{
   int v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14;
   int v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27;
   int v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40;
   int v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54;
   int v55, v56, v57, v58, v59, v60, v61, v62, v63, v64, v65, v66, v67, v68;
   struct str1 v1, v69;
   int lc_alphanrg, lc_betalen, lc_betanrg, lc_correctionterm, lc_energy;
   int lc_h, lc_h_Pr, lc_k, lc_l, lc_middle_k, lc_middle_l;

   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      /* -------------------------------- start of -------------------------------- */
      /* ----- v69 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
      v69.tup1 = 1.0e7;
      v69.tup2 = 0;
      v69.tup3 = 0;
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
                  /* = co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr .. */
                  if ((lc_l-(i+lc_h)-1) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v3 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v4 = pss <<< uregion ------------------ */
                     v4 = sspenalty((lc_l) - (i+lc_h+1));
                     /* ------------------- v4 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v3 = v4;
                     /* --------------- v3 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ----------------------- v5 = p comps ---------------------- */
                     if ((lc_l-(i+lc_h)-1) >= 7) {
                        v5 = tbl_comps(i+lc_h+1, lc_l);
                     }
                     else {
                        v5 = 1.0e7;
                     }
                     /* --------------------- v6 = p comps_Pr --------------------- */
                     if ((lc_l-(i+lc_h)-1) >= 11) {
                        v6 = tbl_comps_Pr(i+lc_h+1, lc_l);
                     }
                     else {
                        v6 = 1.0e7;
                     }
                     v7 = v5 < v6 ? v5 : v6;
                     v8 = v3 < v7 ? v3 : v7;
                     v2 = v8;
                  }
                  else {
                     v2 = 1.0e7;
                  }
                  /* = co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr .. */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v9 = frd j <<< (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  if ((lc_l-(i+lc_h)-1) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v10 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v11 = pss <<< uregion ------------------ */
                     v11 = sspenalty((lc_l-1) - (i+lc_h+1));
                     /* ------------------ v11 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v10 = v11;
                     /* -------------- v10 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v12 = p comps ---------------------- */
                     if ((lc_l-(i+lc_h)-2) >= 7) {
                        v12 = tbl_comps(i+lc_h+1, lc_l-1);
                     }
                     else {
                        v12 = 1.0e7;
                     }
                     /* --------------------- v13 = p comps_Pr -------------------- */
                     if ((lc_l-(i+lc_h)-2) >= 11) {
                        v13 = tbl_comps_Pr(i+lc_h+1, lc_l-1);
                     }
                     else {
                        v13 = 1.0e7;
                     }
                     v14 = v12 < v13 ? v12 : v13;
                     v15 = v10 < v14 ? v10 : v14;
                     v9 = (v15 + (wkn * dl_energy((lc_l) + 1, j))) + npp;
                  }
                  else {
                     v9 = 1.0e7;
                  }
                  /*  v9 = frd j <<< (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  v16 = v2 < v9 ? v2 : v9;
                  /* -------------------------- start of -------------------------- */
                  /* ------ v17 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 0) {
                     v17 = wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, lc_l+lc_h_Pr, (lc_l+lc_h_Pr) + 1);
                  }
                  else {
                     v17 = 1.0e7;
                  }
                  /* ------ v17 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* ------ v18 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 1) {
                     v18 = (wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, (lc_k-lc_h) - 1, (lc_k-lc_h) + 1)) + npp;
                  }
                  else {
                     v18 = 1.0e7;
                  }
                  /* ------ v18 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* - v19 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 2) {
                     v19 = (2 * npp) + (wkn * (dri_energy(lc_middle_l, (lc_l+lc_h_Pr+1) + 2) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                  }
                  else {
                     v19 = 1.0e7;
                  }
                  /* - v19 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v20 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h)  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v21 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v22 = pss <<< region ------------------ */
                     v22 = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr+1));
                     /* ------------------- v22 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v21 = v22;
                     /* --------------- v21 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v23 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v23 = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h);
                     }
                     else {
                        v23 = 1.0e7;
                     }
                     /* --------------------- v24 = p comps_Pr -------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 11) {
                        v24 = tbl_comps_Pr(lc_l+lc_h_Pr+1, lc_k-lc_h);
                     }
                     else {
                        v24 = 1.0e7;
                     }
                     v25 = v23 < v24 ? v23 : v24;
                     v26 = v21 < v25 ? v21 : v25;
                     v20 = (v26 + npp) + (wkn * dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1));
                  }
                  else {
                     v20 = 1.0e7;
                  }
                  /*  v20 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h)  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v27 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v28 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v29 = pss <<< region ------------------ */
                     v29 = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr));
                     /* ------------------- v29 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v28 = v29;
                     /* --------------- v28 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v30 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v30 = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h-1);
                     }
                     else {
                        v30 = 1.0e7;
                     }
                     /* --------------------- v31 = p comps_Pr -------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 11) {
                        v31 = tbl_comps_Pr(lc_l+lc_h_Pr, lc_k-lc_h-1);
                     }
                     else {
                        v31 = 1.0e7;
                     }
                     v32 = v30 < v31 ? v30 : v31;
                     v33 = v28 < v32 ? v28 : v32;
                     v27 = (v33 + npp) + (wkn * dri_energy(lc_middle_l, (lc_k-lc_h) + 1));
                  }
                  else {
                     v27 = 1.0e7;
                  }
                  /*  v27 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v34 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 3) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v35 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v36 = pss <<< region ------------------ */
                     v36 = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr+1));
                     /* ------------------- v36 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v35 = v36;
                     /* --------------- v35 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v37 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-2) >= 7) {
                        v37 = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                     }
                     else {
                        v37 = 1.0e7;
                     }
                     /* --------------------- v38 = p comps_Pr -------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-2) >= 11) {
                        v38 = tbl_comps_Pr(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                     }
                     else {
                        v38 = 1.0e7;
                     }
                     v39 = v37 < v38 ? v37 : v38;
                     v40 = v35 < v39 ? v35 : v39;
                     v34 = (v40 + (2 * npp)) + (wkn * (dri_energy(lc_middle_l, (lc_k-lc_h) + 1) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                  }
                  else {
                     v34 = 1.0e7;
                  }
                  /*  v34 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* idregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v42 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v43 = pss <<< region ------------------ */
                     v43 = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr));
                     /* ------------------- v43 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v42 = v43;
                     /* --------------- v42 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v44 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 7) {
                        v44 = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h);
                     }
                     else {
                        v44 = 1.0e7;
                     }
                     /* --------------------- v45 = p comps_Pr -------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 11) {
                        v45 = tbl_comps_Pr(lc_l+lc_h_Pr, lc_k-lc_h);
                     }
                     else {
                        v45 = 1.0e7;
                     }
                     v46 = v44 < v45 ? v44 : v45;
                     v47 = v42 < v46 ? v42 : v46;
                     v41 = v47;
                  }
                  else {
                     v41 = 1.0e7;
                  }
                  /* idregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr */
                  /* -------------------------- finished -------------------------- */

                  v48 = v34 < v41 ? v34 : v41;
                  v49 = v27 < v48 ? v27 : v48;
                  v50 = v20 < v49 ? v20 : v49;
                  v51 = v19 < v50 ? v19 : v50;
                  v52 = v18 < v51 ? v18 : v51;
                  v53 = v17 < v52 ? v17 : v52;
                  /* -------------------------- start of -------------------------- */
                  /* = co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr .. */
                  if ((j-lc_h_Pr-lc_k-2) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v55 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v56 = pss <<< uregion ------------------ */
                     v56 = sspenalty((j-lc_h_Pr-2) - (lc_k));
                     /* ------------------ v56 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v55 = v56;
                     /* -------------- v55 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v57 = p comps ---------------------- */
                     if ((j-lc_h_Pr-lc_k-2) >= 7) {
                        v57 = tbl_comps(lc_k, j-lc_h_Pr-2);
                     }
                     else {
                        v57 = 1.0e7;
                     }
                     /* --------------------- v58 = p comps_Pr -------------------- */
                     if ((j-lc_h_Pr-lc_k-2) >= 11) {
                        v58 = tbl_comps_Pr(lc_k, j-lc_h_Pr-2);
                     }
                     else {
                        v58 = 1.0e7;
                     }
                     v59 = v57 < v58 ? v57 : v58;
                     v60 = v55 < v59 ? v55 : v59;
                     v54 = v60;
                  }
                  else {
                     v54 = 1.0e7;
                  }
                  /* = co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr .. */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v61 = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h)  */
                  if ((j-lc_h_Pr-lc_k-2) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v62 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v63 = pss <<< uregion ------------------ */
                     v63 = sspenalty((j-lc_h_Pr-2) - (lc_k+1));
                     /* ------------------ v63 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v62 = v63;
                     /* -------------- v62 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v64 = p comps ---------------------- */
                     if ((j-lc_h_Pr-lc_k-3) >= 7) {
                        v64 = tbl_comps(lc_k+1, j-lc_h_Pr-2);
                     }
                     else {
                        v64 = 1.0e7;
                     }
                     /* --------------------- v65 = p comps_Pr -------------------- */
                     if ((j-lc_h_Pr-lc_k-3) >= 11) {
                        v65 = tbl_comps_Pr(lc_k+1, j-lc_h_Pr-2);
                     }
                     else {
                        v65 = 1.0e7;
                     }
                     v66 = v64 < v65 ? v64 : v65;
                     v67 = v62 < v66 ? v62 : v66;
                     v61 = (v67 + (wkn * dr_energy(i + 1, (lc_k+1) - 1))) + npp;
                  }
                  else {
                     v61 = 1.0e7;
                  }
                  /*  v61 = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h)  */
                  /* -------------------------- finished -------------------------- */

                  v68 = v54 < v61 ? v54 : v61;
                  v1.tup1 = (((((pkinit + lc_energy) + (3 * npp)) + v16) + v53) + v68) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j);
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
            /* ---------------------- v69 = minimum(v1, v69) ---------------------- */
            v69 = v1.tup1 < v69.tup1 ? v1 : v69;
         }
      }
      /* ----- v69 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
      /* -------------------------------- finished -------------------------------- */

      /* ----------------------- assign table entry result ------------------------ */
      tbl_knot(i, j) = v69;
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
   struct str3 *v24;
   int v20;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10, *v11;
   struct str5 *v12, *v13, *v14, *v15, *v16, *v17, *v18, *v19, *v21, *v22, *v23;

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------ v1 = edl <<< lbase ~~~ p closed ~~~ loc ------------------ */
   if ((j-i) >= 8) {
      if (abs(tbl_edangle(i, j) - ((tbl_closed(i+1, j) + dl_energy((i+1) + 1, j)) + termaupenalty((i+1) + 1, j))) <= diff) {
         v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v1->next = NULL;
         v1->last = v1;
         v1->item.alg_energy = (tbl_closed(i+1, j) + dl_energy((i+1) + 1, j)) + termaupenalty((i+1) + 1, j);
         v1->item.alg_enum = new_Edl_f(i+1, back_closed, i+1, j, j);
      }
      else {
         v1 = NULL;
      }
   }
   else {
      v1 = NULL;
   }
   /* ------------------ v1 = edl <<< lbase ~~~ p closed ~~~ loc ------------------ */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------ v2 = edr <<< loc ~~~ p closed ~~~ lbase ------------------ */
   if ((j-i) >= 8) {
      if (abs(tbl_edangle(i, j) - ((tbl_closed(i, j-1) + dr_energy((i) + 1, (j) - 1)) + termaupenalty((i) + 1, (j) - 1))) <= diff) {
         v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v2->next = NULL;
         v2->last = v2;
         v2->item.alg_energy = (tbl_closed(i, j-1) + dr_energy((i) + 1, (j) - 1)) + termaupenalty((i) + 1, (j) - 1);
         v2->item.alg_enum = new_Edr_f(i, back_closed, i, j-1, j);
      }
      else {
         v2 = NULL;
      }
   }
   else {
      v2 = NULL;
   }
   /* ------------------ v2 = edr <<< loc ~~~ p closed ~~~ lbase ------------------ */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------- v3 = edlr <<< lbase ~~~ p closed ~~~ lbase ---------------- */
   if ((j-i) >= 9) {
      if (abs(tbl_edangle(i, j) - (((tbl_closed(i+1, j-1) + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)) + termaupenalty((i+1) + 1, (j) - 1))) <= diff) {
         v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v3->next = NULL;
         v3->last = v3;
         v3->item.alg_energy = ((tbl_closed(i+1, j-1) + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)) + termaupenalty((i+1) + 1, (j) - 1);
         v3->item.alg_enum = new_Edlr_f(i+1, back_closed, i+1, j-1, j);
      }
      else {
         v3 = NULL;
      }
   }
   else {
      v3 = NULL;
   }
   /* ----------------- v3 = edlr <<< lbase ~~~ p closed ~~~ lbase ---------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------- v6 = drem <<< is <<< loc ~~~ p closed ~~~ loc --------------- */
   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v5 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      if (abs(tbl_edangle(i, j) - (tbl_closed(i, j) + termaupenalty((i) + 1, j))) <= diff) {
         v5=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v5->next = NULL;
         v5->last = v5;
         v5->item.alg_energy = tbl_closed(i, j) + termaupenalty((i) + 1, j);
         v5->item.alg_enum = new_Is_f(i, back_closed, i, j, j);
      }
      else {
         v5 = NULL;
      }
      /* ------------------ v5 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

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
         if (abs(tbl_edangle(i, j) - v7->item.alg_energy) <= diff) {
            v4=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v4->next = NULL;
            v4->last = v4;
            v4->item.alg_energy = v7->item.alg_energy;
            v4->item.alg_enum = new_Drem_s(v7->item.alg_enum);
         }
         else {
            v4 = NULL;
         }
         /* ---------------------------- v6 = v4 ++ v6 ---------------------------- */
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
   }
   else {
      v6 = NULL;
   }
   /* --------------- v6 = drem <<< is <<< loc ~~~ p closed ~~~ loc --------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------- v8 = kndr <<< p knot ~~~ lbase ---------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      if (abs(tbl_edangle(i, j) - ((tbl_knot(i, j-1).tup1 + npp) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1)))) <= diff) {
         v8=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v8->next = NULL;
         v8->last = v8;
         v8->item.alg_energy = (tbl_knot(i, j-1).tup1 + npp) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1));
         v8->item.alg_enum = new_Kndr_f(back_knot, i, j-1, tbl_knot(i, j-1).tup2, tbl_knot(i, j-1).tup3, j);
      }
      else {
         v8 = NULL;
      }
   }
   else {
      v8 = NULL;
   }
   /* ----------------------- v8 = kndr <<< p knot ~~~ lbase ---------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------- v9 = kndl <<< lbase ~~~ p knot ---------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      if (abs(tbl_edangle(i, j) - ((tbl_knot(i+1, j).tup1 + npp) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3)))) <= diff) {
         v9=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v9->next = NULL;
         v9->last = v9;
         v9->item.alg_energy = (tbl_knot(i+1, j).tup1 + npp) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3));
         v9->item.alg_enum = new_Kndl_f(i+1, back_knot, i+1, j, tbl_knot(i+1, j).tup2, tbl_knot(i+1, j).tup3);
      }
      else {
         v9 = NULL;
      }
   }
   else {
      v9 = NULL;
   }
   /* ----------------------- v9 = kndl <<< lbase ~~~ p knot ---------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------- v10 = kndlr <<< lbase ~~~ p knot ~~~ lbase ---------------- */
   if (((j-i) >= 13) && ((j-i) <= (max_pknot_length+2))) {
      if (abs(tbl_edangle(i, j) - ((tbl_knot(i+1, j-1).tup1 + (2 * npp)) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1))))) <= diff) {
         v10=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v10->next = NULL;
         v10->last = v10;
         v10->item.alg_energy = (tbl_knot(i+1, j-1).tup1 + (2 * npp)) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1)));
         v10->item.alg_enum = new_Kndlr_f(i+1, back_knot, i+1, j-1, tbl_knot(i+1, j-1).tup2, tbl_knot(i+1, j-1).tup3, j);
      }
      else {
         v10 = NULL;
      }
   }
   else {
      v10 = NULL;
   }
   /* ----------------- v10 = kndlr <<< lbase ~~~ p knot ~~~ lbase ---------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ---------------------------- v11 = pk <<< p knot ---------------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      if (abs(tbl_edangle(i, j) - tbl_knot(i, j).tup1) <= diff) {
         v11=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v11->next = NULL;
         v11->last = v11;
         v11->item.alg_energy = tbl_knot(i, j).tup1;
         v11->item.alg_enum = new_Pk_f(back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3);
      }
      else {
         v11 = NULL;
      }
   }
   else {
      v11 = NULL;
   }
   /* ---------------------------- v11 = pk <<< p knot ---------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------ v12 = v10 ++ v11 ----------------------------- */
   if (v10 == NULL) {
      v12 = v11;
   } else 
   if (v11 == NULL) {
      v12 = v10;
   }
   else {
      v10->last->next = v11;
      v10->last = v11->last;
      v12 = v10;
   }
   /* ------------------------------ v13 = v9 ++ v12 ------------------------------ */
   if (v9 == NULL) {
      v13 = v12;
   } else 
   if (v12 == NULL) {
      v13 = v9;
   }
   else {
      v9->last->next = v12;
      v9->last = v12->last;
      v13 = v9;
   }
   /* ------------------------------ v14 = v8 ++ v13 ------------------------------ */
   if (v8 == NULL) {
      v14 = v13;
   } else 
   if (v13 == NULL) {
      v14 = v8;
   }
   else {
      v8->last->next = v13;
      v8->last = v13->last;
      v14 = v8;
   }
   /* ------------------------------ v15 = v6 ++ v14 ------------------------------ */
   if (v6 == NULL) {
      v15 = v14;
   } else 
   if (v14 == NULL) {
      v15 = v6;
   }
   else {
      v6->last->next = v14;
      v6->last = v14->last;
      v15 = v6;
   }
   /* ------------------------------ v16 = v3 ++ v15 ------------------------------ */
   if (v3 == NULL) {
      v16 = v15;
   } else 
   if (v15 == NULL) {
      v16 = v3;
   }
   else {
      v3->last->next = v15;
      v3->last = v15->last;
      v16 = v3;
   }
   /* ------------------------------ v17 = v2 ++ v16 ------------------------------ */
   if (v2 == NULL) {
      v17 = v16;
   } else 
   if (v16 == NULL) {
      v17 = v2;
   }
   else {
      v2->last->next = v16;
      v2->last = v16->last;
      v17 = v2;
   }
   /* ------------------------------ v18 = v1 ++ v17 ------------------------------ */
   if (v1 == NULL) {
      v18 = v17;
   } else 
   if (v17 == NULL) {
      v18 = v1;
   }
   else {
      v1->last->next = v17;
      v1->last = v17->last;
      v18 = v1;
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

/* backtracing code for production edangle_Pr                                       */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_edangle_Pr(int i, int j, int diff)
{
   struct str3 *v24;
   int v20;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10, *v11;
   struct str5 *v12, *v13, *v14, *v15, *v16, *v17, *v18, *v19, *v21, *v22, *v23;

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------- v1 = edl <<< lbase ~~~ p closed_Pr ~~~ loc ---------------- */
   if ((j-i) >= 23) {
      if (abs(tbl_edangle_Pr(i, j) - ((tbl_closed_Pr(i+1, j) + dl_energy((i+1) + 1, j)) + termaupenalty((i+1) + 1, j))) <= diff) {
         v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v1->next = NULL;
         v1->last = v1;
         v1->item.alg_energy = (tbl_closed_Pr(i+1, j) + dl_energy((i+1) + 1, j)) + termaupenalty((i+1) + 1, j);
         v1->item.alg_enum = new_Edl_f(i+1, back_closed_Pr, i+1, j, j);
      }
      else {
         v1 = NULL;
      }
   }
   else {
      v1 = NULL;
   }
   /* ----------------- v1 = edl <<< lbase ~~~ p closed_Pr ~~~ loc ---------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------- v2 = edr <<< loc ~~~ p closed_Pr ~~~ lbase ---------------- */
   if ((j-i) >= 23) {
      if (abs(tbl_edangle_Pr(i, j) - ((tbl_closed_Pr(i, j-1) + dr_energy((i) + 1, (j) - 1)) + termaupenalty((i) + 1, (j) - 1))) <= diff) {
         v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v2->next = NULL;
         v2->last = v2;
         v2->item.alg_energy = (tbl_closed_Pr(i, j-1) + dr_energy((i) + 1, (j) - 1)) + termaupenalty((i) + 1, (j) - 1);
         v2->item.alg_enum = new_Edr_f(i, back_closed_Pr, i, j-1, j);
      }
      else {
         v2 = NULL;
      }
   }
   else {
      v2 = NULL;
   }
   /* ----------------- v2 = edr <<< loc ~~~ p closed_Pr ~~~ lbase ---------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------- v3 = edlr <<< lbase ~~~ p closed_Pr ~~~ lbase --------------- */
   if ((j-i) >= 24) {
      if (abs(tbl_edangle_Pr(i, j) - (((tbl_closed_Pr(i+1, j-1) + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)) + termaupenalty((i+1) + 1, (j) - 1))) <= diff) {
         v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v3->next = NULL;
         v3->last = v3;
         v3->item.alg_energy = ((tbl_closed_Pr(i+1, j-1) + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)) + termaupenalty((i+1) + 1, (j) - 1);
         v3->item.alg_enum = new_Edlr_f(i+1, back_closed_Pr, i+1, j-1, j);
      }
      else {
         v3 = NULL;
      }
   }
   else {
      v3 = NULL;
   }
   /* --------------- v3 = edlr <<< lbase ~~~ p closed_Pr ~~~ lbase --------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* -------------- v6 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
   if ((j-i) >= 22) {
      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v5 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------------- */
      if (abs(tbl_edangle_Pr(i, j) - (tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j))) <= diff) {
         v5=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v5->next = NULL;
         v5->last = v5;
         v5->item.alg_energy = tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j);
         v5->item.alg_enum = new_Is_f(i, back_closed_Pr, i, j, j);
      }
      else {
         v5 = NULL;
      }
      /* ---------------- v5 = is <<< loc ~~~ p closed_Pr ~~~ loc ----------------- */
      /* -------------------------------- finished -------------------------------- */

      v6 = NULL;
      /* +------------------------------------------------------------------------- */
      /* v4 stores the result of a single application of algebra function           */
      /* v5 holds the results of expression                                         */
      /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                    */
      /*                                                                            */
      /* we use v7 to iterate over v5 and                                           */
      /* v6 to collect the results                                                  */
      /* +------------------------------------------------------------------------- */
      v7 = v5;
      while (v7 != NULL) {
         if (abs(tbl_edangle_Pr(i, j) - v7->item.alg_energy) <= diff) {
            v4=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v4->next = NULL;
            v4->last = v4;
            v4->item.alg_energy = v7->item.alg_energy;
            v4->item.alg_enum = new_Drem_s(v7->item.alg_enum);
         }
         else {
            v4 = NULL;
         }
         /* ---------------------------- v6 = v4 ++ v6 ---------------------------- */
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
   }
   else {
      v6 = NULL;
   }
   /* -------------- v6 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------- v8 = kndr <<< p knot ~~~ lbase ---------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      if (abs(tbl_edangle_Pr(i, j) - ((tbl_knot(i, j-1).tup1 + npp) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1)))) <= diff) {
         v8=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v8->next = NULL;
         v8->last = v8;
         v8->item.alg_energy = (tbl_knot(i, j-1).tup1 + npp) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1));
         v8->item.alg_enum = new_Kndr_f(back_knot, i, j-1, tbl_knot(i, j-1).tup2, tbl_knot(i, j-1).tup3, j);
      }
      else {
         v8 = NULL;
      }
   }
   else {
      v8 = NULL;
   }
   /* ----------------------- v8 = kndr <<< p knot ~~~ lbase ---------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------- v9 = kndl <<< lbase ~~~ p knot ---------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      if (abs(tbl_edangle_Pr(i, j) - ((tbl_knot(i+1, j).tup1 + npp) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3)))) <= diff) {
         v9=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v9->next = NULL;
         v9->last = v9;
         v9->item.alg_energy = (tbl_knot(i+1, j).tup1 + npp) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3));
         v9->item.alg_enum = new_Kndl_f(i+1, back_knot, i+1, j, tbl_knot(i+1, j).tup2, tbl_knot(i+1, j).tup3);
      }
      else {
         v9 = NULL;
      }
   }
   else {
      v9 = NULL;
   }
   /* ----------------------- v9 = kndl <<< lbase ~~~ p knot ---------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------- v10 = kndlr <<< lbase ~~~ p knot ~~~ lbase ---------------- */
   if (((j-i) >= 13) && ((j-i) <= (max_pknot_length+2))) {
      if (abs(tbl_edangle_Pr(i, j) - ((tbl_knot(i+1, j-1).tup1 + (2 * npp)) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1))))) <= diff) {
         v10=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v10->next = NULL;
         v10->last = v10;
         v10->item.alg_energy = (tbl_knot(i+1, j-1).tup1 + (2 * npp)) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1)));
         v10->item.alg_enum = new_Kndlr_f(i+1, back_knot, i+1, j-1, tbl_knot(i+1, j-1).tup2, tbl_knot(i+1, j-1).tup3, j);
      }
      else {
         v10 = NULL;
      }
   }
   else {
      v10 = NULL;
   }
   /* ----------------- v10 = kndlr <<< lbase ~~~ p knot ~~~ lbase ---------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ---------------------------- v11 = pk <<< p knot ---------------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      if (abs(tbl_edangle_Pr(i, j) - tbl_knot(i, j).tup1) <= diff) {
         v11=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v11->next = NULL;
         v11->last = v11;
         v11->item.alg_energy = tbl_knot(i, j).tup1;
         v11->item.alg_enum = new_Pk_f(back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3);
      }
      else {
         v11 = NULL;
      }
   }
   else {
      v11 = NULL;
   }
   /* ---------------------------- v11 = pk <<< p knot ---------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------ v12 = v10 ++ v11 ----------------------------- */
   if (v10 == NULL) {
      v12 = v11;
   } else 
   if (v11 == NULL) {
      v12 = v10;
   }
   else {
      v10->last->next = v11;
      v10->last = v11->last;
      v12 = v10;
   }
   /* ------------------------------ v13 = v9 ++ v12 ------------------------------ */
   if (v9 == NULL) {
      v13 = v12;
   } else 
   if (v12 == NULL) {
      v13 = v9;
   }
   else {
      v9->last->next = v12;
      v9->last = v12->last;
      v13 = v9;
   }
   /* ------------------------------ v14 = v8 ++ v13 ------------------------------ */
   if (v8 == NULL) {
      v14 = v13;
   } else 
   if (v13 == NULL) {
      v14 = v8;
   }
   else {
      v8->last->next = v13;
      v8->last = v13->last;
      v14 = v8;
   }
   /* ------------------------------ v15 = v6 ++ v14 ------------------------------ */
   if (v6 == NULL) {
      v15 = v14;
   } else 
   if (v14 == NULL) {
      v15 = v6;
   }
   else {
      v6->last->next = v14;
      v6->last = v14->last;
      v15 = v6;
   }
   /* ------------------------------ v16 = v3 ++ v15 ------------------------------ */
   if (v3 == NULL) {
      v16 = v15;
   } else 
   if (v15 == NULL) {
      v16 = v3;
   }
   else {
      v3->last->next = v15;
      v3->last = v15->last;
      v16 = v3;
   }
   /* ------------------------------ v17 = v2 ++ v16 ------------------------------ */
   if (v2 == NULL) {
      v17 = v16;
   } else 
   if (v16 == NULL) {
      v17 = v2;
   }
   else {
      v2->last->next = v16;
      v2->last = v16->last;
      v17 = v2;
   }
   /* ------------------------------ v18 = v1 ++ v17 ------------------------------ */
   if (v1 == NULL) {
      v18 = v17;
   } else 
   if (v17 == NULL) {
      v18 = v1;
   }
   else {
      v1->last->next = v17;
      v1->last = v17->last;
      v18 = v1;
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

/* backtracing code for production closed                                           */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_closed(int i, int j, int diff)
{
   struct str3 *v67;
   int v10, v19, v25, v53, v63;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v11, *v12, *v13;
   struct str5 *v14, *v15, *v16, *v17, *v18, *v20;
   struct str5 *v21, *v22, *v23, *v24, *v26, *v27;
   struct str5 *v28, *v29, *v30, *v31, *v32, *v33;
   struct str5 *v34, *v35, *v36, *v37, *v38, *v39;
   struct str5 *v40, *v41, *v42, *v43, *v44, *v45;
   struct str5 *v46, *v47, *v48, *v49, *v50, *v51;
   struct str5 *v52, *v54, *v55, *v56, *v57, *v58;
   struct str5 *v59, *v60, *v61, *v62, *v64, *v65, *v66;
   int k, k2, k3, k4, k5, k6, k7, k8;

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
         /*  v31 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 19) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v30 = combine <<< p block ~~~ p comps --------------- */
            v30 = NULL;
            for (k5=i+10; k5<=j-9; k5++) {
               if (abs(tbl_closed(i, j) - ((((380 + (tbl_block(i+3, k5) + tbl_comps(k5, j-2))) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v29=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v29->next = NULL;
                  v29->last = v29;
                  v29->item.alg_energy = tbl_block(i+3, k5) + tbl_comps(k5, j-2);
                  v29->item.alg_enum = new_Combine_ff(back_block, i+3, k5, back_comps, k5, j-2);
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
               if (abs(tbl_closed(i, j) - ((((380 + v32->item.alg_energy) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v28=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v28->next = NULL;
                  v28->last = v28;
                  v28->item.alg_energy = (((380 + v32->item.alg_energy) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v28->item.alg_enum = new_Mldl_s(i+1, i+2, i+3, v32->item.alg_enum, j-1, j);
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
         /*  v31 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v36 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 19) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v35 = combine <<< p block ~~~ p comps --------------- */
            v35 = NULL;
            for (k6=i+9; k6<=j-10; k6++) {
               if (abs(tbl_closed(i, j) - ((((380 + (tbl_block(i+2, k6) + tbl_comps(k6, j-3))) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v34=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v34->next = NULL;
                  v34->last = v34;
                  v34->item.alg_energy = tbl_block(i+2, k6) + tbl_comps(k6, j-3);
                  v34->item.alg_enum = new_Combine_ff(back_block, i+2, k6, back_comps, k6, j-3);
               }
               else {
                  v34 = NULL;
               }
               /* ------------------------ v35 = v34 ++ v35 ----------------------- */
               if (v34 == NULL) {
               } else 
               if (v35 == NULL) {
                  v35 = v34;
               }
               else {
                  v34->last->next = v35;
                  v34->last = v35->last;
                  v35 = v34;
               }
            }
            /* -------------- v35 = combine <<< p block ~~~ p comps --------------- */
            /* ----------------------------- finished ----------------------------- */

            v36 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v33 stores the result of a single application of algebra function           */
            /* v35 holds the results of expression                                         */
            /*      combine <<< p block ~~~ p comps                                        */
            /*                                                                             */
            /* we use v37 to iterate over v35 and                                          */
            /* v36 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v37 = v35;
            while (v37 != NULL) {
               if (abs(tbl_closed(i, j) - ((((380 + v37->item.alg_energy) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v33=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v33->next = NULL;
                  v33->last = v33;
                  v33->item.alg_energy = (((380 + v37->item.alg_energy) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v33->item.alg_enum = new_Mldr_s(i+1, i+2, v37->item.alg_enum, j-2, j-1, j);
               }
               else {
                  v33 = NULL;
               }
               /* ------------------------ v36 = v33 ++ v36 ----------------------- */
               if (v33 == NULL) {
               } else 
               if (v36 == NULL) {
                  v36 = v33;
               }
               else {
                  v33->last->next = v36;
                  v33->last = v36->last;
                  v36 = v33;
               }
               v37 = v37->next;
            }
         }
         else {
            v36 = NULL;
         }
         /*  v36 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v41 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 20) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v40 = combine <<< p block ~~~ p comps --------------- */
            v40 = NULL;
            for (k7=i+10; k7<=j-10; k7++) {
               if (abs(tbl_closed(i, j) - (((((380 + (tbl_block(i+3, k7) + tbl_comps(k7, j-3))) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v39=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v39->next = NULL;
                  v39->last = v39;
                  v39->item.alg_energy = tbl_block(i+3, k7) + tbl_comps(k7, j-3);
                  v39->item.alg_enum = new_Combine_ff(back_block, i+3, k7, back_comps, k7, j-3);
               }
               else {
                  v39 = NULL;
               }
               /* ------------------------ v40 = v39 ++ v40 ----------------------- */
               if (v39 == NULL) {
               } else 
               if (v40 == NULL) {
                  v40 = v39;
               }
               else {
                  v39->last->next = v40;
                  v39->last = v40->last;
                  v40 = v39;
               }
            }
            /* -------------- v40 = combine <<< p block ~~~ p comps --------------- */
            /* ----------------------------- finished ----------------------------- */

            v41 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v38 stores the result of a single application of algebra function           */
            /* v40 holds the results of expression                                         */
            /*      combine <<< p block ~~~ p comps                                        */
            /*                                                                             */
            /* we use v42 to iterate over v40 and                                          */
            /* v41 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v42 = v40;
            while (v42 != NULL) {
               if (abs(tbl_closed(i, j) - (((((380 + v42->item.alg_energy) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v38=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v38->next = NULL;
                  v38->last = v38;
                  v38->item.alg_energy = ((((380 + v42->item.alg_energy) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v38->item.alg_enum = new_Mldlr_s(i+1, i+2, i+3, v42->item.alg_enum, j-2, j-1, j);
               }
               else {
                  v38 = NULL;
               }
               /* ------------------------ v41 = v38 ++ v41 ----------------------- */
               if (v38 == NULL) {
               } else 
               if (v41 == NULL) {
                  v41 = v38;
               }
               else {
                  v38->last->next = v41;
                  v38->last = v41->last;
                  v41 = v38;
               }
               v42 = v42->next;
            }
         }
         else {
            v41 = NULL;
         }
         /*  v41 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v46 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 18) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v45 = combine <<< p block ~~~ p comps --------------- */
            v45 = NULL;
            for (k8=i+9; k8<=j-9; k8++) {
               if (abs(tbl_closed(i, j) - (((380 + (tbl_block(i+2, k8) + tbl_comps(k8, j-2))) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v44=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v44->next = NULL;
                  v44->last = v44;
                  v44->item.alg_energy = tbl_block(i+2, k8) + tbl_comps(k8, j-2);
                  v44->item.alg_enum = new_Combine_ff(back_block, i+2, k8, back_comps, k8, j-2);
               }
               else {
                  v44 = NULL;
               }
               /* ------------------------ v45 = v44 ++ v45 ----------------------- */
               if (v44 == NULL) {
               } else 
               if (v45 == NULL) {
                  v45 = v44;
               }
               else {
                  v44->last->next = v45;
                  v44->last = v45->last;
                  v45 = v44;
               }
            }
            /* -------------- v45 = combine <<< p block ~~~ p comps --------------- */
            /* ----------------------------- finished ----------------------------- */

            v46 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v43 stores the result of a single application of algebra function           */
            /* v45 holds the results of expression                                         */
            /*      combine <<< p block ~~~ p comps                                        */
            /*                                                                             */
            /* we use v47 to iterate over v45 and                                          */
            /* v46 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v47 = v45;
            while (v47 != NULL) {
               if (abs(tbl_closed(i, j) - (((380 + v47->item.alg_energy) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v43=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v43->next = NULL;
                  v43->last = v43;
                  v43->item.alg_energy = ((380 + v47->item.alg_energy) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v43->item.alg_enum = new_Ml_s(i+1, i+2, v47->item.alg_enum, j-1, j);
               }
               else {
                  v43 = NULL;
               }
               /* ------------------------ v46 = v43 ++ v46 ----------------------- */
               if (v43 == NULL) {
               } else 
               if (v46 == NULL) {
                  v46 = v43;
               }
               else {
                  v43->last->next = v46;
                  v43->last = v46->last;
                  v46 = v43;
               }
               v47 = v47->next;
            }
         }
         else {
            v46 = NULL;
         }
         /*  v46 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* --------------------------- v48 = v41 ++ v46 -------------------------- */
         if (v41 == NULL) {
            v48 = v46;
         } else 
         if (v46 == NULL) {
            v48 = v41;
         }
         else {
            v41->last->next = v46;
            v41->last = v46->last;
            v48 = v41;
         }
         /* --------------------------- v49 = v36 ++ v48 -------------------------- */
         if (v36 == NULL) {
            v49 = v48;
         } else 
         if (v48 == NULL) {
            v49 = v36;
         }
         else {
            v36->last->next = v48;
            v36->last = v48->last;
            v49 = v36;
         }
         /* --------------------------- v50 = v31 ++ v49 -------------------------- */
         if (v31 == NULL) {
            v50 = v49;
         } else 
         if (v49 == NULL) {
            v50 = v31;
         }
         else {
            v31->last->next = v49;
            v31->last = v49->last;
            v50 = v31;
         }
         v51 = v50;
      }
      else {
         v51 = NULL;
      }
      /* --------------------------- v53 = minimum(v51) --------------------------- */
      v53 = 1.0e7;
      v52 = v51;
      while (v52 != NULL) {
         v53 = v53 < v52->item.alg_energy ? v53 : v52->item.alg_energy;
         v52 = v52->next;
      }
      v52 = v51;
      v55 = NULL;
      while (v52 != NULL) {
         if (abs(v53 - v52->item.alg_energy) <= diff) {
            update_str_Signature(v52->item.alg_enum->item, diff - abs(v53 - v52->item.alg_energy));
            v54=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v54->item = v52->item;
            v54->next = NULL;
            v54->last = v54;
            /* ------------------------- v55 = v54 ++ v55 ------------------------- */
            if (v54 == NULL) {
            } else 
            if (v55 == NULL) {
               v55 = v54;
            }
            else {
               v54->last->next = v55;
               v54->last = v55->last;
               v55 = v54;
            }
         }
         v52 = v52->next;
      }
      /* ---------------------------- v56 = v27 ++ v55 ---------------------------- */
      if (v27 == NULL) {
         v56 = v55;
      } else 
      if (v55 == NULL) {
         v56 = v27;
      }
      else {
         v27->last->next = v55;
         v27->last = v55->last;
         v56 = v27;
      }
      /* ---------------------------- v57 = v21 ++ v56 ---------------------------- */
      if (v21 == NULL) {
         v57 = v56;
      } else 
      if (v56 == NULL) {
         v57 = v21;
      }
      else {
         v21->last->next = v56;
         v21->last = v56->last;
         v57 = v21;
      }
      /* ---------------------------- v58 = v12 ++ v57 ---------------------------- */
      if (v12 == NULL) {
         v58 = v57;
      } else 
      if (v57 == NULL) {
         v58 = v12;
      }
      else {
         v12->last->next = v57;
         v12->last = v57->last;
         v58 = v12;
      }
      /* ---------------------------- v59 = v3 ++ v58 ----------------------------- */
      if (v3 == NULL) {
         v59 = v58;
      } else 
      if (v58 == NULL) {
         v59 = v3;
      }
      else {
         v3->last->next = v58;
         v3->last = v58->last;
         v59 = v3;
      }
      v60 = v59;
   }
   else {
      v60 = NULL;
   }
   /* ------------------------------ v61 = v2 ++ v60 ------------------------------ */
   if (v2 == NULL) {
      v61 = v60;
   } else 
   if (v60 == NULL) {
      v61 = v2;
   }
   else {
      v2->last->next = v60;
      v2->last = v60->last;
      v61 = v2;
   }
   /* ----------------------------- v63 = minimum(v61) ---------------------------- */
   v63 = 1.0e7;
   v62 = v61;
   while (v62 != NULL) {
      v63 = v63 < v62->item.alg_energy ? v63 : v62->item.alg_energy;
      v62 = v62->next;
   }
   v62 = v61;
   v65 = NULL;
   while (v62 != NULL) {
      if (abs(v63 - v62->item.alg_energy) <= diff) {
         update_str_Signature(v62->item.alg_enum->item, diff - abs(v63 - v62->item.alg_energy));
         v64=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v64->item = v62->item;
         v64->next = NULL;
         v64->last = v64;
         /* --------------------------- v65 = v64 ++ v65 -------------------------- */
         if (v64 == NULL) {
         } else 
         if (v65 == NULL) {
            v65 = v64;
         }
         else {
            v64->last->next = v65;
            v64->last = v65->last;
            v65 = v64;
         }
      }
      v62 = v62->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v66 = v65;
   v67 = NULL;
   while (v66 != NULL) {
      /* -------------------- v67 = v66->item.alg_enum ++ v67 --------------------- */
      if (v66->item.alg_enum == NULL) {
      } else 
      if (v67 == NULL) {
         v67 = v66->item.alg_enum;
      }
      else {
         v66->item.alg_enum->last->next = v67;
         v66->item.alg_enum->last = v67->last;
         v67 = v66->item.alg_enum;
      }
      v66 = v66->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v67)));
}

/* backtracing code for production closed_Pr                                        */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_closed_Pr(int i, int j, int diff)
{
   struct str3 *v89;
   int v9, v18, v24, v76, v85;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v10, *v11, *v12;
   struct str5 *v13, *v14, *v15, *v16, *v17, *v19;
   struct str5 *v20, *v21, *v22, *v23, *v25, *v26;
   struct str5 *v27, *v28, *v29, *v30, *v31, *v32;
   struct str5 *v33, *v34, *v35, *v36, *v37, *v38;
   struct str5 *v39, *v40, *v41, *v42, *v43, *v44;
   struct str5 *v45, *v46, *v47, *v48, *v49, *v50;
   struct str5 *v51, *v52, *v53, *v54, *v55, *v56;
   struct str5 *v57, *v58, *v59, *v60, *v61, *v62;
   struct str5 *v63, *v64, *v65, *v66, *v67, *v68;
   struct str5 *v69, *v70, *v71, *v72, *v73, *v74;
   struct str5 *v75, *v77, *v78, *v79, *v80, *v81;
   struct str5 *v82, *v83, *v84, *v86, *v87, *v88;
   int k, k10, k11, k12, k13, k14, k15, k16, k2, k3, k4, k5, k6, k7, k8, k9;

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
         /*  v36 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 23) {
            /* ----------------------------- start of ----------------------------- */
            /* ----------- v29 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            if ((j-i-5) >= 22) {
               v29 = NULL;
               for (k5=i+14; k5<=j-13; k5++) {
                  if (abs(tbl_closed_Pr(i, j) - ((((380 + (tbl_block_Pr(i+3, k5) + tbl_comps_Pr(k5, j-2))) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                     v28=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v28->next = NULL;
                     v28->last = v28;
                     v28->item.alg_energy = tbl_block_Pr(i+3, k5) + tbl_comps_Pr(k5, j-2);
                     v28->item.alg_enum = new_Combine_ff(back_block_Pr, i+3, k5, back_comps_Pr, k5, j-2);
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
            for (k6=i+10; k6<=j-13; k6++) {
               if (abs(tbl_closed_Pr(i, j) - ((((380 + (tbl_block(i+3, k6) + tbl_comps_Pr(k6, j-2))) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v30=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v30->next = NULL;
                  v30->last = v30;
                  v30->item.alg_energy = tbl_block(i+3, k6) + tbl_comps_Pr(k6, j-2);
                  v30->item.alg_enum = new_Combine_ff(back_block, i+3, k6, back_comps_Pr, k6, j-2);
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
            for (k7=i+14; k7<=j-9; k7++) {
               if (abs(tbl_closed_Pr(i, j) - ((((380 + (tbl_block_Pr(i+3, k7) + tbl_comps(k7, j-2))) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v32=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v32->next = NULL;
                  v32->last = v32;
                  v32->item.alg_energy = tbl_block_Pr(i+3, k7) + tbl_comps(k7, j-2);
                  v32->item.alg_enum = new_Combine_ff(back_block_Pr, i+3, k7, back_comps, k7, j-2);
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
               if (abs(tbl_closed_Pr(i, j) - ((((380 + v37->item.alg_energy) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v27=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v27->next = NULL;
                  v27->last = v27;
                  v27->item.alg_energy = (((380 + v37->item.alg_energy) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v27->item.alg_enum = new_Mldl_s(i+1, i+2, i+3, v37->item.alg_enum, j-1, j);
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
         /*  v36 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v47 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 23) {
            /* ----------------------------- start of ----------------------------- */
            /* ----------- v40 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            if ((j-i-5) >= 22) {
               v40 = NULL;
               for (k8=i+13; k8<=j-14; k8++) {
                  if (abs(tbl_closed_Pr(i, j) - ((((380 + (tbl_block_Pr(i+2, k8) + tbl_comps_Pr(k8, j-3))) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                     v39=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v39->next = NULL;
                     v39->last = v39;
                     v39->item.alg_energy = tbl_block_Pr(i+2, k8) + tbl_comps_Pr(k8, j-3);
                     v39->item.alg_enum = new_Combine_ff(back_block_Pr, i+2, k8, back_comps_Pr, k8, j-3);
                  }
                  else {
                     v39 = NULL;
                  }
                  /* ---------------------- v40 = v39 ++ v40 ---------------------- */
                  if (v39 == NULL) {
                  } else 
                  if (v40 == NULL) {
                     v40 = v39;
                  }
                  else {
                     v39->last->next = v40;
                     v39->last = v40->last;
                     v40 = v39;
                  }
               }
            }
            else {
               v40 = NULL;
            }
            /* ----------- v40 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v42 = combine <<< p block ~~~ p comps_Pr ------------- */
            v42 = NULL;
            for (k9=i+9; k9<=j-14; k9++) {
               if (abs(tbl_closed_Pr(i, j) - ((((380 + (tbl_block(i+2, k9) + tbl_comps_Pr(k9, j-3))) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v41=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v41->next = NULL;
                  v41->last = v41;
                  v41->item.alg_energy = tbl_block(i+2, k9) + tbl_comps_Pr(k9, j-3);
                  v41->item.alg_enum = new_Combine_ff(back_block, i+2, k9, back_comps_Pr, k9, j-3);
               }
               else {
                  v41 = NULL;
               }
               /* ------------------------ v42 = v41 ++ v42 ----------------------- */
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
            /* ------------- v42 = combine <<< p block ~~~ p comps_Pr ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v44 = combine <<< p block_Pr ~~~ p comps ------------- */
            v44 = NULL;
            for (k10=i+13; k10<=j-10; k10++) {
               if (abs(tbl_closed_Pr(i, j) - ((((380 + (tbl_block_Pr(i+2, k10) + tbl_comps(k10, j-3))) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v43=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v43->next = NULL;
                  v43->last = v43;
                  v43->item.alg_energy = tbl_block_Pr(i+2, k10) + tbl_comps(k10, j-3);
                  v43->item.alg_enum = new_Combine_ff(back_block_Pr, i+2, k10, back_comps, k10, j-3);
               }
               else {
                  v43 = NULL;
               }
               /* ------------------------ v44 = v43 ++ v44 ----------------------- */
               if (v43 == NULL) {
               } else 
               if (v44 == NULL) {
                  v44 = v43;
               }
               else {
                  v43->last->next = v44;
                  v43->last = v44->last;
                  v44 = v43;
               }
            }
            /* ------------- v44 = combine <<< p block_Pr ~~~ p comps ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ------------------------- v45 = v42 ++ v44 ------------------------- */
            if (v42 == NULL) {
               v45 = v44;
            } else 
            if (v44 == NULL) {
               v45 = v42;
            }
            else {
               v42->last->next = v44;
               v42->last = v44->last;
               v45 = v42;
            }
            /* ------------------------- v46 = v40 ++ v45 ------------------------- */
            if (v40 == NULL) {
               v46 = v45;
            } else 
            if (v45 == NULL) {
               v46 = v40;
            }
            else {
               v40->last->next = v45;
               v40->last = v45->last;
               v46 = v40;
            }
            v47 = NULL;
            /* +--------------------------------------------------------------------------------------------------------------------------------- */
            /* v38 stores the result of a single application of algebra function                                                                  */
            /* v46 holds the results of expression                                                                                                */
            /*      combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps           */
            /*                                                                                                                                    */
            /* we use v48 to iterate over v46 and                                                                                                 */
            /* v47 to collect the results                                                                                                         */
            /* +--------------------------------------------------------------------------------------------------------------------------------- */
            v48 = v46;
            while (v48 != NULL) {
               if (abs(tbl_closed_Pr(i, j) - ((((380 + v48->item.alg_energy) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v38=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v38->next = NULL;
                  v38->last = v38;
                  v38->item.alg_energy = (((380 + v48->item.alg_energy) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v38->item.alg_enum = new_Mldr_s(i+1, i+2, v48->item.alg_enum, j-2, j-1, j);
               }
               else {
                  v38 = NULL;
               }
               /* ------------------------ v47 = v38 ++ v47 ----------------------- */
               if (v38 == NULL) {
               } else 
               if (v47 == NULL) {
                  v47 = v38;
               }
               else {
                  v38->last->next = v47;
                  v38->last = v47->last;
                  v47 = v38;
               }
               v48 = v48->next;
            }
         }
         else {
            v47 = NULL;
         }
         /*  v47 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v58 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 24) {
            /* ----------------------------- start of ----------------------------- */
            /* ----------- v51 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            if ((j-i-6) >= 22) {
               v51 = NULL;
               for (k11=i+14; k11<=j-14; k11++) {
                  if (abs(tbl_closed_Pr(i, j) - (((((380 + (tbl_block_Pr(i+3, k11) + tbl_comps_Pr(k11, j-3))) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                     v50=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v50->next = NULL;
                     v50->last = v50;
                     v50->item.alg_energy = tbl_block_Pr(i+3, k11) + tbl_comps_Pr(k11, j-3);
                     v50->item.alg_enum = new_Combine_ff(back_block_Pr, i+3, k11, back_comps_Pr, k11, j-3);
                  }
                  else {
                     v50 = NULL;
                  }
                  /* ---------------------- v51 = v50 ++ v51 ---------------------- */
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
            }
            else {
               v51 = NULL;
            }
            /* ----------- v51 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v53 = combine <<< p block ~~~ p comps_Pr ------------- */
            v53 = NULL;
            for (k12=i+10; k12<=j-14; k12++) {
               if (abs(tbl_closed_Pr(i, j) - (((((380 + (tbl_block(i+3, k12) + tbl_comps_Pr(k12, j-3))) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v52=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v52->next = NULL;
                  v52->last = v52;
                  v52->item.alg_energy = tbl_block(i+3, k12) + tbl_comps_Pr(k12, j-3);
                  v52->item.alg_enum = new_Combine_ff(back_block, i+3, k12, back_comps_Pr, k12, j-3);
               }
               else {
                  v52 = NULL;
               }
               /* ------------------------ v53 = v52 ++ v53 ----------------------- */
               if (v52 == NULL) {
               } else 
               if (v53 == NULL) {
                  v53 = v52;
               }
               else {
                  v52->last->next = v53;
                  v52->last = v53->last;
                  v53 = v52;
               }
            }
            /* ------------- v53 = combine <<< p block ~~~ p comps_Pr ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v55 = combine <<< p block_Pr ~~~ p comps ------------- */
            v55 = NULL;
            for (k13=i+14; k13<=j-10; k13++) {
               if (abs(tbl_closed_Pr(i, j) - (((((380 + (tbl_block_Pr(i+3, k13) + tbl_comps(k13, j-3))) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v54=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v54->next = NULL;
                  v54->last = v54;
                  v54->item.alg_energy = tbl_block_Pr(i+3, k13) + tbl_comps(k13, j-3);
                  v54->item.alg_enum = new_Combine_ff(back_block_Pr, i+3, k13, back_comps, k13, j-3);
               }
               else {
                  v54 = NULL;
               }
               /* ------------------------ v55 = v54 ++ v55 ----------------------- */
               if (v54 == NULL) {
               } else 
               if (v55 == NULL) {
                  v55 = v54;
               }
               else {
                  v54->last->next = v55;
                  v54->last = v55->last;
                  v55 = v54;
               }
            }
            /* ------------- v55 = combine <<< p block_Pr ~~~ p comps ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ------------------------- v56 = v53 ++ v55 ------------------------- */
            if (v53 == NULL) {
               v56 = v55;
            } else 
            if (v55 == NULL) {
               v56 = v53;
            }
            else {
               v53->last->next = v55;
               v53->last = v55->last;
               v56 = v53;
            }
            /* ------------------------- v57 = v51 ++ v56 ------------------------- */
            if (v51 == NULL) {
               v57 = v56;
            } else 
            if (v56 == NULL) {
               v57 = v51;
            }
            else {
               v51->last->next = v56;
               v51->last = v56->last;
               v57 = v51;
            }
            v58 = NULL;
            /* +--------------------------------------------------------------------------------------------------------------------------------- */
            /* v49 stores the result of a single application of algebra function                                                                  */
            /* v57 holds the results of expression                                                                                                */
            /*      combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps           */
            /*                                                                                                                                    */
            /* we use v59 to iterate over v57 and                                                                                                 */
            /* v58 to collect the results                                                                                                         */
            /* +--------------------------------------------------------------------------------------------------------------------------------- */
            v59 = v57;
            while (v59 != NULL) {
               if (abs(tbl_closed_Pr(i, j) - (((((380 + v59->item.alg_energy) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v49=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v49->next = NULL;
                  v49->last = v49;
                  v49->item.alg_energy = ((((380 + v59->item.alg_energy) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v49->item.alg_enum = new_Mldlr_s(i+1, i+2, i+3, v59->item.alg_enum, j-2, j-1, j);
               }
               else {
                  v49 = NULL;
               }
               /* ------------------------ v58 = v49 ++ v58 ----------------------- */
               if (v49 == NULL) {
               } else 
               if (v58 == NULL) {
                  v58 = v49;
               }
               else {
                  v49->last->next = v58;
                  v49->last = v58->last;
                  v58 = v49;
               }
               v59 = v59->next;
            }
         }
         else {
            v58 = NULL;
         }
         /*  v58 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v69 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 22) {
            /* ----------------------------- start of ----------------------------- */
            /* ----------- v62 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            if ((j-i-4) >= 22) {
               v62 = NULL;
               for (k14=i+13; k14<=j-13; k14++) {
                  if (abs(tbl_closed_Pr(i, j) - (((380 + (tbl_block_Pr(i+2, k14) + tbl_comps_Pr(k14, j-2))) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                     v61=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v61->next = NULL;
                     v61->last = v61;
                     v61->item.alg_energy = tbl_block_Pr(i+2, k14) + tbl_comps_Pr(k14, j-2);
                     v61->item.alg_enum = new_Combine_ff(back_block_Pr, i+2, k14, back_comps_Pr, k14, j-2);
                  }
                  else {
                     v61 = NULL;
                  }
                  /* ---------------------- v62 = v61 ++ v62 ---------------------- */
                  if (v61 == NULL) {
                  } else 
                  if (v62 == NULL) {
                     v62 = v61;
                  }
                  else {
                     v61->last->next = v62;
                     v61->last = v62->last;
                     v62 = v61;
                  }
               }
            }
            else {
               v62 = NULL;
            }
            /* ----------- v62 = combine <<< p block_Pr ~~~ p comps_Pr ------------ */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v64 = combine <<< p block ~~~ p comps_Pr ------------- */
            v64 = NULL;
            for (k15=i+9; k15<=j-13; k15++) {
               if (abs(tbl_closed_Pr(i, j) - (((380 + (tbl_block(i+2, k15) + tbl_comps_Pr(k15, j-2))) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v63=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v63->next = NULL;
                  v63->last = v63;
                  v63->item.alg_energy = tbl_block(i+2, k15) + tbl_comps_Pr(k15, j-2);
                  v63->item.alg_enum = new_Combine_ff(back_block, i+2, k15, back_comps_Pr, k15, j-2);
               }
               else {
                  v63 = NULL;
               }
               /* ------------------------ v64 = v63 ++ v64 ----------------------- */
               if (v63 == NULL) {
               } else 
               if (v64 == NULL) {
                  v64 = v63;
               }
               else {
                  v63->last->next = v64;
                  v63->last = v64->last;
                  v64 = v63;
               }
            }
            /* ------------- v64 = combine <<< p block ~~~ p comps_Pr ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ----------------------------- start of ----------------------------- */
            /* ------------- v66 = combine <<< p block_Pr ~~~ p comps ------------- */
            v66 = NULL;
            for (k16=i+13; k16<=j-9; k16++) {
               if (abs(tbl_closed_Pr(i, j) - (((380 + (tbl_block_Pr(i+2, k16) + tbl_comps(k16, j-2))) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v65=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v65->next = NULL;
                  v65->last = v65;
                  v65->item.alg_energy = tbl_block_Pr(i+2, k16) + tbl_comps(k16, j-2);
                  v65->item.alg_enum = new_Combine_ff(back_block_Pr, i+2, k16, back_comps, k16, j-2);
               }
               else {
                  v65 = NULL;
               }
               /* ------------------------ v66 = v65 ++ v66 ----------------------- */
               if (v65 == NULL) {
               } else 
               if (v66 == NULL) {
                  v66 = v65;
               }
               else {
                  v65->last->next = v66;
                  v65->last = v66->last;
                  v66 = v65;
               }
            }
            /* ------------- v66 = combine <<< p block_Pr ~~~ p comps ------------- */
            /* ----------------------------- finished ----------------------------- */

            /* ------------------------- v67 = v64 ++ v66 ------------------------- */
            if (v64 == NULL) {
               v67 = v66;
            } else 
            if (v66 == NULL) {
               v67 = v64;
            }
            else {
               v64->last->next = v66;
               v64->last = v66->last;
               v67 = v64;
            }
            /* ------------------------- v68 = v62 ++ v67 ------------------------- */
            if (v62 == NULL) {
               v68 = v67;
            } else 
            if (v67 == NULL) {
               v68 = v62;
            }
            else {
               v62->last->next = v67;
               v62->last = v67->last;
               v68 = v62;
            }
            v69 = NULL;
            /* +--------------------------------------------------------------------------------------------------------------------------------- */
            /* v60 stores the result of a single application of algebra function                                                                  */
            /* v68 holds the results of expression                                                                                                */
            /*      combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps           */
            /*                                                                                                                                    */
            /* we use v70 to iterate over v68 and                                                                                                 */
            /* v69 to collect the results                                                                                                         */
            /* +--------------------------------------------------------------------------------------------------------------------------------- */
            v70 = v68;
            while (v70 != NULL) {
               if (abs(tbl_closed_Pr(i, j) - (((380 + v70->item.alg_energy) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v60=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v60->next = NULL;
                  v60->last = v60;
                  v60->item.alg_energy = ((380 + v70->item.alg_energy) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
                  v60->item.alg_enum = new_Ml_s(i+1, i+2, v70->item.alg_enum, j-1, j);
               }
               else {
                  v60 = NULL;
               }
               /* ------------------------ v69 = v60 ++ v69 ----------------------- */
               if (v60 == NULL) {
               } else 
               if (v69 == NULL) {
                  v69 = v60;
               }
               else {
                  v60->last->next = v69;
                  v60->last = v69->last;
                  v69 = v60;
               }
               v70 = v70->next;
            }
         }
         else {
            v69 = NULL;
         }
         /*  v69 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block_Pr ~~~ p comps_Pr ||| combine <<< p block ~~~ p comps_Pr ||| combine <<< p block_Pr ~~~ p comps) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* --------------------------- v71 = v58 ++ v69 -------------------------- */
         if (v58 == NULL) {
            v71 = v69;
         } else 
         if (v69 == NULL) {
            v71 = v58;
         }
         else {
            v58->last->next = v69;
            v58->last = v69->last;
            v71 = v58;
         }
         /* --------------------------- v72 = v47 ++ v71 -------------------------- */
         if (v47 == NULL) {
            v72 = v71;
         } else 
         if (v71 == NULL) {
            v72 = v47;
         }
         else {
            v47->last->next = v71;
            v47->last = v71->last;
            v72 = v47;
         }
         /* --------------------------- v73 = v36 ++ v72 -------------------------- */
         if (v36 == NULL) {
            v73 = v72;
         } else 
         if (v72 == NULL) {
            v73 = v36;
         }
         else {
            v36->last->next = v72;
            v36->last = v72->last;
            v73 = v36;
         }
         v74 = v73;
      }
      else {
         v74 = NULL;
      }
      /* --------------------------- v76 = minimum(v74) --------------------------- */
      v76 = 1.0e7;
      v75 = v74;
      while (v75 != NULL) {
         v76 = v76 < v75->item.alg_energy ? v76 : v75->item.alg_energy;
         v75 = v75->next;
      }
      v75 = v74;
      v78 = NULL;
      while (v75 != NULL) {
         if (abs(v76 - v75->item.alg_energy) <= diff) {
            update_str_Signature(v75->item.alg_enum->item, diff - abs(v76 - v75->item.alg_energy));
            v77=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v77->item = v75->item;
            v77->next = NULL;
            v77->last = v77;
            /* ------------------------- v78 = v77 ++ v78 ------------------------- */
            if (v77 == NULL) {
            } else 
            if (v78 == NULL) {
               v78 = v77;
            }
            else {
               v77->last->next = v78;
               v77->last = v78->last;
               v78 = v77;
            }
         }
         v75 = v75->next;
      }
      /* ---------------------------- v79 = v26 ++ v78 ---------------------------- */
      if (v26 == NULL) {
         v79 = v78;
      } else 
      if (v78 == NULL) {
         v79 = v26;
      }
      else {
         v26->last->next = v78;
         v26->last = v78->last;
         v79 = v26;
      }
      /* ---------------------------- v80 = v20 ++ v79 ---------------------------- */
      if (v20 == NULL) {
         v80 = v79;
      } else 
      if (v79 == NULL) {
         v80 = v20;
      }
      else {
         v20->last->next = v79;
         v20->last = v79->last;
         v80 = v20;
      }
      /* ---------------------------- v81 = v11 ++ v80 ---------------------------- */
      if (v11 == NULL) {
         v81 = v80;
      } else 
      if (v80 == NULL) {
         v81 = v11;
      }
      else {
         v11->last->next = v80;
         v11->last = v80->last;
         v81 = v11;
      }
      v82 = v81;
   }
   else {
      v82 = NULL;
   }
   /* ------------------------------ v83 = v2 ++ v82 ------------------------------ */
   if (v2 == NULL) {
      v83 = v82;
   } else 
   if (v82 == NULL) {
      v83 = v2;
   }
   else {
      v2->last->next = v82;
      v2->last = v82->last;
      v83 = v2;
   }
   /* ----------------------------- v85 = minimum(v83) ---------------------------- */
   v85 = 1.0e7;
   v84 = v83;
   while (v84 != NULL) {
      v85 = v85 < v84->item.alg_energy ? v85 : v84->item.alg_energy;
      v84 = v84->next;
   }
   v84 = v83;
   v87 = NULL;
   while (v84 != NULL) {
      if (abs(v85 - v84->item.alg_energy) <= diff) {
         update_str_Signature(v84->item.alg_enum->item, diff - abs(v85 - v84->item.alg_energy));
         v86=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v86->item = v84->item;
         v86->next = NULL;
         v86->last = v86;
         /* --------------------------- v87 = v86 ++ v87 -------------------------- */
         if (v86 == NULL) {
         } else 
         if (v87 == NULL) {
            v87 = v86;
         }
         else {
            v86->last->next = v87;
            v86->last = v87->last;
            v87 = v86;
         }
      }
      v84 = v84->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v88 = v87;
   v89 = NULL;
   while (v88 != NULL) {
      /* -------------------- v89 = v88->item.alg_enum ++ v89 --------------------- */
      if (v88->item.alg_enum == NULL) {
      } else 
      if (v89 == NULL) {
         v89 = v88->item.alg_enum;
      }
      else {
         v88->item.alg_enum->last->next = v89;
         v88->item.alg_enum->last = v89->last;
         v89 = v88->item.alg_enum;
      }
      v88 = v88->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v89)));
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
   struct str3 *v60;
   int v22, v48, v56;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10, *v11;
   struct str5 *v12, *v13, *v14, *v15, *v16, *v17, *v18, *v19, *v20, *v21, *v23;
   struct str5 *v24, *v25, *v26, *v27, *v28, *v29, *v30, *v31, *v32, *v33, *v34;
   struct str5 *v35, *v36, *v37, *v38, *v39, *v40, *v41, *v42, *v43, *v44, *v45;
   struct str5 *v46, *v47, *v49, *v50, *v51, *v52;
   struct str5 *v53, *v54, *v55, *v57, *v58, *v59;
   int k;

   /* ---------------------------------- start of --------------------------------- */
   /*  v25 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h  */
   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ---- v4 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ----- */
      if ((j-i) >= 8) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------------- v3 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         if (abs(tbl_block(i, j) - (40 + ((tbl_closed(i+1, j) + termaupenalty((i+1) + 1, j)) + dl_energy((i+1) + 1, j)))) <= diff) {
            v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v3->next = NULL;
            v3->last = v3;
            v3->item.alg_energy = tbl_closed(i+1, j) + termaupenalty((i+1) + 1, j);
            v3->item.alg_enum = new_Is_f(i+1, back_closed, i+1, j, j);
         }
         else {
            v3 = NULL;
         }
         /* ----------------- v3 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

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
            if (abs(tbl_block(i, j) - (40 + (v5->item.alg_energy + dl_energy((i+1) + 1, j)))) <= diff) {
               v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v2->next = NULL;
               v2->last = v2;
               v2->item.alg_energy = v5->item.alg_energy + dl_energy((i+1) + 1, j);
               v2->item.alg_enum = new_Dl_s(i+1, v5->item.alg_enum, j);
            }
            else {
               v2 = NULL;
            }
            /* -------------------------- v4 = v2 ++ v4 --------------------------- */
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
      /* ---- v4 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ----- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ---- v8 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ----- */
      if ((j-i) >= 8) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------------- v7 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         if (abs(tbl_block(i, j) - (40 + ((tbl_closed(i, j-1) + termaupenalty((i) + 1, j-1)) + dr_energy((i) + 1, (j) - 1)))) <= diff) {
            v7=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v7->next = NULL;
            v7->last = v7;
            v7->item.alg_energy = tbl_closed(i, j-1) + termaupenalty((i) + 1, j-1);
            v7->item.alg_enum = new_Is_f(i, back_closed, i, j-1, j-1);
         }
         else {
            v7 = NULL;
         }
         /* ----------------- v7 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v8 = NULL;
         /* +------------------------------------------------------------------------- */
         /* v6 stores the result of a single application of algebra function           */
         /* v7 holds the results of expression                                         */
         /*      is <<< loc ~~~ p closed ~~~ loc                                       */
         /*                                                                            */
         /* we use v9 to iterate over v7 and                                           */
         /* v8 to collect the results                                                  */
         /* +------------------------------------------------------------------------- */
         v9 = v7;
         while (v9 != NULL) {
            if (abs(tbl_block(i, j) - (40 + (v9->item.alg_energy + dr_energy((i) + 1, (j) - 1)))) <= diff) {
               v6=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v6->next = NULL;
               v6->last = v6;
               v6->item.alg_energy = v9->item.alg_energy + dr_energy((i) + 1, (j) - 1);
               v6->item.alg_enum = new_Dr_s(i, v9->item.alg_enum, j);
            }
            else {
               v6 = NULL;
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
            v9 = v9->next;
         }
      }
      else {
         v8 = NULL;
      }
      /* ---- v8 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ----- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* -- v12 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase --- */
      if ((j-i) >= 9) {
         /* ------------------------------- start of ------------------------------ */
         /* ---------------- v11 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         if (abs(tbl_block(i, j) - (40 + (((tbl_closed(i+1, j-1) + termaupenalty((i+1) + 1, j-1)) + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)))) <= diff) {
            v11=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v11->next = NULL;
            v11->last = v11;
            v11->item.alg_energy = tbl_closed(i+1, j-1) + termaupenalty((i+1) + 1, j-1);
            v11->item.alg_enum = new_Is_f(i+1, back_closed, i+1, j-1, j-1);
         }
         else {
            v11 = NULL;
         }
         /* ---------------- v11 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v12 = NULL;
         /* +-------------------------------------------------------------------------- */
         /* v10 stores the result of a single application of algebra function           */
         /* v11 holds the results of expression                                         */
         /*      is <<< loc ~~~ p closed ~~~ loc                                        */
         /*                                                                             */
         /* we use v13 to iterate over v11 and                                          */
         /* v12 to collect the results                                                  */
         /* +-------------------------------------------------------------------------- */
         v13 = v11;
         while (v13 != NULL) {
            if (abs(tbl_block(i, j) - (40 + ((v13->item.alg_energy + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)))) <= diff) {
               v10=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v10->next = NULL;
               v10->last = v10;
               v10->item.alg_energy = (v13->item.alg_energy + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1);
               v10->item.alg_enum = new_Dlr_s(i+1, v13->item.alg_enum, j);
            }
            else {
               v10 = NULL;
            }
            /* ------------------------- v12 = v10 ++ v12 ------------------------- */
            if (v10 == NULL) {
            } else 
            if (v12 == NULL) {
               v12 = v10;
            }
            else {
               v10->last->next = v12;
               v10->last = v12->last;
               v12 = v10;
            }
            v13 = v13->next;
         }
      }
      else {
         v12 = NULL;
      }
      /* -- v12 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase --- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------- v16 = drem <<< is <<< loc ~~~ p closed ~~~ loc ------------- */
      /* -------------------------------- start of -------------------------------- */
      /* ----------------- v15 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      if (abs(tbl_block(i, j) - (40 + (tbl_closed(i, j) + termaupenalty((i) + 1, j)))) <= diff) {
         v15=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v15->next = NULL;
         v15->last = v15;
         v15->item.alg_energy = tbl_closed(i, j) + termaupenalty((i) + 1, j);
         v15->item.alg_enum = new_Is_f(i, back_closed, i, j, j);
      }
      else {
         v15 = NULL;
      }
      /* ----------------- v15 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v16 = NULL;
      /* +-------------------------------------------------------------------------- */
      /* v14 stores the result of a single application of algebra function           */
      /* v15 holds the results of expression                                         */
      /*      is <<< loc ~~~ p closed ~~~ loc                                        */
      /*                                                                             */
      /* we use v17 to iterate over v15 and                                          */
      /* v16 to collect the results                                                  */
      /* +-------------------------------------------------------------------------- */
      v17 = v15;
      while (v17 != NULL) {
         if (abs(tbl_block(i, j) - (40 + v17->item.alg_energy)) <= diff) {
            v14=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v14->next = NULL;
            v14->last = v14;
            v14->item.alg_energy = v17->item.alg_energy;
            v14->item.alg_enum = new_Drem_s(v17->item.alg_enum);
         }
         else {
            v14 = NULL;
         }
         /* --------------------------- v16 = v14 ++ v16 -------------------------- */
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
         v17 = v17->next;
      }
      /* ------------- v16 = drem <<< is <<< loc ~~~ p closed ~~~ loc ------------- */
      /* -------------------------------- finished -------------------------------- */

      /* ---------------------------- v18 = v12 ++ v16 ---------------------------- */
      if (v12 == NULL) {
         v18 = v16;
      } else 
      if (v16 == NULL) {
         v18 = v12;
      }
      else {
         v12->last->next = v16;
         v12->last = v16->last;
         v18 = v12;
      }
      /* ---------------------------- v19 = v8 ++ v18 ----------------------------- */
      if (v8 == NULL) {
         v19 = v18;
      } else 
      if (v18 == NULL) {
         v19 = v8;
      }
      else {
         v8->last->next = v18;
         v8->last = v18->last;
         v19 = v8;
      }
      /* ---------------------------- v20 = v4 ++ v19 ----------------------------- */
      if (v4 == NULL) {
         v20 = v19;
      } else 
      if (v19 == NULL) {
         v20 = v4;
      }
      else {
         v4->last->next = v19;
         v4->last = v19->last;
         v20 = v4;
      }
      /* --------------------------- v22 = minimum(v20) --------------------------- */
      v22 = 1.0e7;
      v21 = v20;
      while (v21 != NULL) {
         v22 = v22 < v21->item.alg_energy ? v22 : v21->item.alg_energy;
         v21 = v21->next;
      }
      v21 = v20;
      v24 = NULL;
      while (v21 != NULL) {
         if (abs(v22 - v21->item.alg_energy) <= diff) {
            update_str_Signature(v21->item.alg_enum->item, diff - abs(v22 - v21->item.alg_energy));
            v23=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v23->item = v21->item;
            v23->next = NULL;
            v23->last = v23;
            /* ------------------------- v24 = v23 ++ v24 ------------------------- */
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
      /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
      /* v1 stores the result of a single application of algebra function                                                                                                                                                                                              */
      /* v24 holds the results of expression                                                                                                                                                                                                                           */
      /*      dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h           */
      /*                                                                                                                                                                                                                                                               */
      /* we use v26 to iterate over v24 and                                                                                                                                                                                                                            */
      /* v25 to collect the results                                                                                                                                                                                                                                    */
      /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
      v26 = v24;
      while (v26 != NULL) {
         if (abs(tbl_block(i, j) - (40 + v26->item.alg_energy)) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = 40 + v26->item.alg_energy;
            v1->item.alg_enum = new_Ul_s(v26->item.alg_enum);
         }
         else {
            v1 = NULL;
         }
         /* --------------------------- v25 = v1 ++ v25 --------------------------- */
         if (v1 == NULL) {
         } else 
         if (v25 == NULL) {
            v25 = v1;
         }
         else {
            v1->last->next = v25;
            v1->last = v25->last;
            v25 = v1;
         }
         v26 = v26->next;
      }
   }
   else {
      v25 = NULL;
   }
   /*  v25 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h  */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /*  v53 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h)  */
   if ((j-i) >= 8) {
      v53 = NULL;
      for (k=i+1; k<=j-7; k++) {
         /* ------------------------------- start of ------------------------------ */
         /* --- v30 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc -- */
         if ((j-k) >= 8) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v29 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            if (abs(tbl_block(i, j) - ((40 + ((tbl_closed(k+1, j) + termaupenalty((k+1) + 1, j)) + dl_energy((k+1) + 1, j))) + ss_energy(i, k))) <= diff) {
               v29=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v29->next = NULL;
               v29->last = v29;
               v29->item.alg_energy = tbl_closed(k+1, j) + termaupenalty((k+1) + 1, j);
               v29->item.alg_enum = new_Is_f(k+1, back_closed, k+1, j, j);
            }
            else {
               v29 = NULL;
            }
            /* -------------- v29 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v30 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v28 stores the result of a single application of algebra function           */
            /* v29 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed ~~~ loc                                        */
            /*                                                                             */
            /* we use v31 to iterate over v29 and                                          */
            /* v30 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v31 = v29;
            while (v31 != NULL) {
               if (abs(tbl_block(i, j) - ((40 + (v31->item.alg_energy + dl_energy((k+1) + 1, j))) + ss_energy(i, k))) <= diff) {
                  v28=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v28->next = NULL;
                  v28->last = v28;
                  v28->item.alg_energy = v31->item.alg_energy + dl_energy((k+1) + 1, j);
                  v28->item.alg_enum = new_Dl_s(k+1, v31->item.alg_enum, j);
               }
               else {
                  v28 = NULL;
               }
               /* ------------------------ v30 = v28 ++ v30 ----------------------- */
               if (v28 == NULL) {
               } else 
               if (v30 == NULL) {
                  v30 = v28;
               }
               else {
                  v28->last->next = v30;
                  v28->last = v30->last;
                  v30 = v28;
               }
               v31 = v31->next;
            }
         }
         else {
            v30 = NULL;
         }
         /* --- v30 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc -- */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* --- v34 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase -- */
         if ((j-k) >= 8) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v33 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            if (abs(tbl_block(i, j) - ((40 + ((tbl_closed(k, j-1) + termaupenalty((k) + 1, j-1)) + dr_energy((k) + 1, (j) - 1))) + ss_energy(i, k))) <= diff) {
               v33=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v33->next = NULL;
               v33->last = v33;
               v33->item.alg_energy = tbl_closed(k, j-1) + termaupenalty((k) + 1, j-1);
               v33->item.alg_enum = new_Is_f(k, back_closed, k, j-1, j-1);
            }
            else {
               v33 = NULL;
            }
            /* -------------- v33 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v34 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v32 stores the result of a single application of algebra function           */
            /* v33 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed ~~~ loc                                        */
            /*                                                                             */
            /* we use v35 to iterate over v33 and                                          */
            /* v34 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v35 = v33;
            while (v35 != NULL) {
               if (abs(tbl_block(i, j) - ((40 + (v35->item.alg_energy + dr_energy((k) + 1, (j) - 1))) + ss_energy(i, k))) <= diff) {
                  v32=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v32->next = NULL;
                  v32->last = v32;
                  v32->item.alg_energy = v35->item.alg_energy + dr_energy((k) + 1, (j) - 1);
                  v32->item.alg_enum = new_Dr_s(k, v35->item.alg_enum, j);
               }
               else {
                  v32 = NULL;
               }
               /* ------------------------ v34 = v32 ++ v34 ----------------------- */
               if (v32 == NULL) {
               } else 
               if (v34 == NULL) {
                  v34 = v32;
               }
               else {
                  v32->last->next = v34;
                  v32->last = v34->last;
                  v34 = v32;
               }
               v35 = v35->next;
            }
         }
         else {
            v34 = NULL;
         }
         /* --- v34 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase -- */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* - v38 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase - */
         if ((j-k) >= 9) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v37 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            if (abs(tbl_block(i, j) - ((40 + (((tbl_closed(k+1, j-1) + termaupenalty((k+1) + 1, j-1)) + dl_energy((k+1) + 1, (j) - 1)) + dr_energy((k+1) + 1, (j) - 1))) + ss_energy(i, k))) <= diff) {
               v37=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v37->next = NULL;
               v37->last = v37;
               v37->item.alg_energy = tbl_closed(k+1, j-1) + termaupenalty((k+1) + 1, j-1);
               v37->item.alg_enum = new_Is_f(k+1, back_closed, k+1, j-1, j-1);
            }
            else {
               v37 = NULL;
            }
            /* -------------- v37 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v38 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v36 stores the result of a single application of algebra function           */
            /* v37 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed ~~~ loc                                        */
            /*                                                                             */
            /* we use v39 to iterate over v37 and                                          */
            /* v38 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v39 = v37;
            while (v39 != NULL) {
               if (abs(tbl_block(i, j) - ((40 + ((v39->item.alg_energy + dl_energy((k+1) + 1, (j) - 1)) + dr_energy((k+1) + 1, (j) - 1))) + ss_energy(i, k))) <= diff) {
                  v36=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v36->next = NULL;
                  v36->last = v36;
                  v36->item.alg_energy = (v39->item.alg_energy + dl_energy((k+1) + 1, (j) - 1)) + dr_energy((k+1) + 1, (j) - 1);
                  v36->item.alg_enum = new_Dlr_s(k+1, v39->item.alg_enum, j);
               }
               else {
                  v36 = NULL;
               }
               /* ------------------------ v38 = v36 ++ v38 ----------------------- */
               if (v36 == NULL) {
               } else 
               if (v38 == NULL) {
                  v38 = v36;
               }
               else {
                  v36->last->next = v38;
                  v36->last = v38->last;
                  v38 = v36;
               }
               v39 = v39->next;
            }
         }
         else {
            v38 = NULL;
         }
         /* - v38 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase - */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* ------------ v42 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
         /* ------------------------------- start of ------------------------------ */
         /* ---------------- v41 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         if (abs(tbl_block(i, j) - ((40 + (tbl_closed(k, j) + termaupenalty((k) + 1, j))) + ss_energy(i, k))) <= diff) {
            v41=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v41->next = NULL;
            v41->last = v41;
            v41->item.alg_energy = tbl_closed(k, j) + termaupenalty((k) + 1, j);
            v41->item.alg_enum = new_Is_f(k, back_closed, k, j, j);
         }
         else {
            v41 = NULL;
         }
         /* ---------------- v41 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v42 = NULL;
         /* +-------------------------------------------------------------------------- */
         /* v40 stores the result of a single application of algebra function           */
         /* v41 holds the results of expression                                         */
         /*      is <<< loc ~~~ p closed ~~~ loc                                        */
         /*                                                                             */
         /* we use v43 to iterate over v41 and                                          */
         /* v42 to collect the results                                                  */
         /* +-------------------------------------------------------------------------- */
         v43 = v41;
         while (v43 != NULL) {
            if (abs(tbl_block(i, j) - ((40 + v43->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v40=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v40->next = NULL;
               v40->last = v40;
               v40->item.alg_energy = v43->item.alg_energy;
               v40->item.alg_enum = new_Drem_s(v43->item.alg_enum);
            }
            else {
               v40 = NULL;
            }
            /* ------------------------- v42 = v40 ++ v42 ------------------------- */
            if (v40 == NULL) {
            } else 
            if (v42 == NULL) {
               v42 = v40;
            }
            else {
               v40->last->next = v42;
               v40->last = v42->last;
               v42 = v40;
            }
            v43 = v43->next;
         }
         /* ------------ v42 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
         /* ------------------------------- finished ------------------------------ */

         /* --------------------------- v44 = v38 ++ v42 -------------------------- */
         if (v38 == NULL) {
            v44 = v42;
         } else 
         if (v42 == NULL) {
            v44 = v38;
         }
         else {
            v38->last->next = v42;
            v38->last = v42->last;
            v44 = v38;
         }
         /* --------------------------- v45 = v34 ++ v44 -------------------------- */
         if (v34 == NULL) {
            v45 = v44;
         } else 
         if (v44 == NULL) {
            v45 = v34;
         }
         else {
            v34->last->next = v44;
            v34->last = v44->last;
            v45 = v34;
         }
         /* --------------------------- v46 = v30 ++ v45 -------------------------- */
         if (v30 == NULL) {
            v46 = v45;
         } else 
         if (v45 == NULL) {
            v46 = v30;
         }
         else {
            v30->last->next = v45;
            v30->last = v45->last;
            v46 = v30;
         }
         /* -------------------------- v48 = minimum(v46) ------------------------- */
         v48 = 1.0e7;
         v47 = v46;
         while (v47 != NULL) {
            v48 = v48 < v47->item.alg_energy ? v48 : v47->item.alg_energy;
            v47 = v47->next;
         }
         v47 = v46;
         v50 = NULL;
         while (v47 != NULL) {
            if (abs(v48 - v47->item.alg_energy) <= diff) {
               update_str_Signature(v47->item.alg_enum->item, diff - abs(v48 - v47->item.alg_energy));
               v49=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v49->item = v47->item;
               v49->next = NULL;
               v49->last = v49;
               /* ------------------------ v50 = v49 ++ v50 ----------------------- */
               if (v49 == NULL) {
               } else 
               if (v50 == NULL) {
                  v50 = v49;
               }
               else {
                  v49->last->next = v50;
                  v49->last = v50->last;
                  v50 = v49;
               }
            }
            v47 = v47->next;
         }
         v51 = NULL;
         /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
         /* v27 stores the result of a single application of algebra function                                                                                                                                                                                             */
         /* v50 holds the results of expression                                                                                                                                                                                                                           */
         /*      dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h           */
         /*                                                                                                                                                                                                                                                               */
         /* we use v52 to iterate over v50 and                                                                                                                                                                                                                            */
         /* v51 to collect the results                                                                                                                                                                                                                                    */
         /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
         v52 = v50;
         while (v52 != NULL) {
            if (abs(tbl_block(i, j) - ((40 + v52->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v27=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v27->next = NULL;
               v27->last = v27;
               v27->item.alg_energy = (40 + v52->item.alg_energy) + ss_energy(i, k);
               v27->item.alg_enum = new_Ssadd_s(i, k, v52->item.alg_enum);
            }
            else {
               v27 = NULL;
            }
            /* ------------------------- v51 = v27 ++ v51 ------------------------- */
            if (v27 == NULL) {
            } else 
            if (v51 == NULL) {
               v51 = v27;
            }
            else {
               v27->last->next = v51;
               v27->last = v51->last;
               v51 = v27;
            }
            v52 = v52->next;
         }
         /* --------------------------- v53 = v51 ++ v53 -------------------------- */
         if (v51 == NULL) {
         } else 
         if (v53 == NULL) {
            v53 = v51;
         }
         else {
            v51->last->next = v53;
            v51->last = v53->last;
            v53 = v51;
         }
      }
   }
   else {
      v53 = NULL;
   }
   /*  v53 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h)  */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------ v54 = v25 ++ v53 ----------------------------- */
   if (v25 == NULL) {
      v54 = v53;
   } else 
   if (v53 == NULL) {
      v54 = v25;
   }
   else {
      v25->last->next = v53;
      v25->last = v53->last;
      v54 = v25;
   }
   /* ----------------------------- v56 = minimum(v54) ---------------------------- */
   v56 = 1.0e7;
   v55 = v54;
   while (v55 != NULL) {
      v56 = v56 < v55->item.alg_energy ? v56 : v55->item.alg_energy;
      v55 = v55->next;
   }
   v55 = v54;
   v58 = NULL;
   while (v55 != NULL) {
      if (abs(v56 - v55->item.alg_energy) <= diff) {
         update_str_Signature(v55->item.alg_enum->item, diff - abs(v56 - v55->item.alg_energy));
         v57=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v57->item = v55->item;
         v57->next = NULL;
         v57->last = v57;
         /* --------------------------- v58 = v57 ++ v58 -------------------------- */
         if (v57 == NULL) {
         } else 
         if (v58 == NULL) {
            v58 = v57;
         }
         else {
            v57->last->next = v58;
            v57->last = v58->last;
            v58 = v57;
         }
      }
      v55 = v55->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v59 = v58;
   v60 = NULL;
   while (v59 != NULL) {
      /* -------------------- v60 = v59->item.alg_enum ++ v60 --------------------- */
      if (v59->item.alg_enum == NULL) {
      } else 
      if (v60 == NULL) {
         v60 = v59->item.alg_enum;
      }
      else {
         v59->item.alg_enum->last->next = v60;
         v59->item.alg_enum->last = v60->last;
         v60 = v59->item.alg_enum;
      }
      v59 = v59->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v60)));
}

/* backtracing code for production block_Pr                                         */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_block_Pr(int i, int j, int diff)
{
   struct str3 *v68;
   int v22, v48, v64;
   struct str5 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10, *v11, *v12;
   struct str5 *v13, *v14, *v15, *v16, *v17, *v18;
   struct str5 *v19, *v20, *v21, *v23, *v24, *v25, *v26;
   struct str5 *v27, *v28, *v29, *v30, *v31, *v32;
   struct str5 *v33, *v34, *v35, *v36, *v37, *v38, *v39;
   struct str5 *v40, *v41, *v42, *v43, *v44, *v45;
   struct str5 *v46, *v47, *v49, *v50, *v51, *v52, *v53;
   struct str5 *v54, *v55, *v56, *v57, *v58, *v59;
   struct str5 *v60, *v61, *v62, *v63, *v65, *v66, *v67;
   int k;

   /* ---------------------------------- start of --------------------------------- */
   /*  v25 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h  */
   if ((j-i) >= 22) {
      /* -------------------------------- start of -------------------------------- */
      /* --- v4 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc --- */
      if ((j-i) >= 23) {
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v3 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         if (abs(tbl_block_Pr(i, j) - (40 + ((tbl_closed_Pr(i+1, j) + termaupenalty((i+1) + 1, j)) + dl_energy((i+1) + 1, j)))) <= diff) {
            v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v3->next = NULL;
            v3->last = v3;
            v3->item.alg_energy = tbl_closed_Pr(i+1, j) + termaupenalty((i+1) + 1, j);
            v3->item.alg_enum = new_Is_f(i+1, back_closed_Pr, i+1, j, j);
         }
         else {
            v3 = NULL;
         }
         /* --------------- v3 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         /* ------------------------------- finished ------------------------------ */

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
            if (abs(tbl_block_Pr(i, j) - (40 + (v5->item.alg_energy + dl_energy((i+1) + 1, j)))) <= diff) {
               v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v2->next = NULL;
               v2->last = v2;
               v2->item.alg_energy = v5->item.alg_energy + dl_energy((i+1) + 1, j);
               v2->item.alg_enum = new_Dl_s(i+1, v5->item.alg_enum, j);
            }
            else {
               v2 = NULL;
            }
            /* -------------------------- v4 = v2 ++ v4 --------------------------- */
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
      /* --- v4 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc --- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --- v8 = dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase --- */
      if ((j-i) >= 23) {
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v7 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         if (abs(tbl_block_Pr(i, j) - (40 + ((tbl_closed_Pr(i, j-1) + termaupenalty((i) + 1, j-1)) + dr_energy((i) + 1, (j) - 1)))) <= diff) {
            v7=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v7->next = NULL;
            v7->last = v7;
            v7->item.alg_energy = tbl_closed_Pr(i, j-1) + termaupenalty((i) + 1, j-1);
            v7->item.alg_enum = new_Is_f(i, back_closed_Pr, i, j-1, j-1);
         }
         else {
            v7 = NULL;
         }
         /* --------------- v7 = is <<< loc ~~~ p closed_Pr ~~~ loc --------------- */
         /* ------------------------------- finished ------------------------------ */

         v8 = NULL;
         /* +------------------------------------------------------------------------- */
         /* v6 stores the result of a single application of algebra function           */
         /* v7 holds the results of expression                                         */
         /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                    */
         /*                                                                            */
         /* we use v9 to iterate over v7 and                                           */
         /* v8 to collect the results                                                  */
         /* +------------------------------------------------------------------------- */
         v9 = v7;
         while (v9 != NULL) {
            if (abs(tbl_block_Pr(i, j) - (40 + (v9->item.alg_energy + dr_energy((i) + 1, (j) - 1)))) <= diff) {
               v6=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v6->next = NULL;
               v6->last = v6;
               v6->item.alg_energy = v9->item.alg_energy + dr_energy((i) + 1, (j) - 1);
               v6->item.alg_enum = new_Dr_s(i, v9->item.alg_enum, j);
            }
            else {
               v6 = NULL;
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
            v9 = v9->next;
         }
      }
      else {
         v8 = NULL;
      }
      /* --- v8 = dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase --- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* - v12 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase - */
      if ((j-i) >= 24) {
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v11 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
         if (abs(tbl_block_Pr(i, j) - (40 + (((tbl_closed_Pr(i+1, j-1) + termaupenalty((i+1) + 1, j-1)) + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)))) <= diff) {
            v11=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v11->next = NULL;
            v11->last = v11;
            v11->item.alg_energy = tbl_closed_Pr(i+1, j-1) + termaupenalty((i+1) + 1, j-1);
            v11->item.alg_enum = new_Is_f(i+1, back_closed_Pr, i+1, j-1, j-1);
         }
         else {
            v11 = NULL;
         }
         /* --------------- v11 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
         /* ------------------------------- finished ------------------------------ */

         v12 = NULL;
         /* +-------------------------------------------------------------------------- */
         /* v10 stores the result of a single application of algebra function           */
         /* v11 holds the results of expression                                         */
         /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                     */
         /*                                                                             */
         /* we use v13 to iterate over v11 and                                          */
         /* v12 to collect the results                                                  */
         /* +-------------------------------------------------------------------------- */
         v13 = v11;
         while (v13 != NULL) {
            if (abs(tbl_block_Pr(i, j) - (40 + ((v13->item.alg_energy + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)))) <= diff) {
               v10=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v10->next = NULL;
               v10->last = v10;
               v10->item.alg_energy = (v13->item.alg_energy + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1);
               v10->item.alg_enum = new_Dlr_s(i+1, v13->item.alg_enum, j);
            }
            else {
               v10 = NULL;
            }
            /* ------------------------- v12 = v10 ++ v12 ------------------------- */
            if (v10 == NULL) {
            } else 
            if (v12 == NULL) {
               v12 = v10;
            }
            else {
               v10->last->next = v12;
               v10->last = v12->last;
               v12 = v10;
            }
            v13 = v13->next;
         }
      }
      else {
         v12 = NULL;
      }
      /* - v12 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase - */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ----------- v16 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v15 = is <<< loc ~~~ p closed_Pr ~~~ loc ---------------- */
      if (abs(tbl_block_Pr(i, j) - (40 + (tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j)))) <= diff) {
         v15=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v15->next = NULL;
         v15->last = v15;
         v15->item.alg_energy = tbl_closed_Pr(i, j) + termaupenalty((i) + 1, j);
         v15->item.alg_enum = new_Is_f(i, back_closed_Pr, i, j, j);
      }
      else {
         v15 = NULL;
      }
      /* ---------------- v15 = is <<< loc ~~~ p closed_Pr ~~~ loc ---------------- */
      /* -------------------------------- finished -------------------------------- */

      v16 = NULL;
      /* +-------------------------------------------------------------------------- */
      /* v14 stores the result of a single application of algebra function           */
      /* v15 holds the results of expression                                         */
      /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                     */
      /*                                                                             */
      /* we use v17 to iterate over v15 and                                          */
      /* v16 to collect the results                                                  */
      /* +-------------------------------------------------------------------------- */
      v17 = v15;
      while (v17 != NULL) {
         if (abs(tbl_block_Pr(i, j) - (40 + v17->item.alg_energy)) <= diff) {
            v14=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v14->next = NULL;
            v14->last = v14;
            v14->item.alg_energy = v17->item.alg_energy;
            v14->item.alg_enum = new_Drem_s(v17->item.alg_enum);
         }
         else {
            v14 = NULL;
         }
         /* --------------------------- v16 = v14 ++ v16 -------------------------- */
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
         v17 = v17->next;
      }
      /* ----------- v16 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ------------ */
      /* -------------------------------- finished -------------------------------- */

      /* ---------------------------- v18 = v12 ++ v16 ---------------------------- */
      if (v12 == NULL) {
         v18 = v16;
      } else 
      if (v16 == NULL) {
         v18 = v12;
      }
      else {
         v12->last->next = v16;
         v12->last = v16->last;
         v18 = v12;
      }
      /* ---------------------------- v19 = v8 ++ v18 ----------------------------- */
      if (v8 == NULL) {
         v19 = v18;
      } else 
      if (v18 == NULL) {
         v19 = v8;
      }
      else {
         v8->last->next = v18;
         v8->last = v18->last;
         v19 = v8;
      }
      /* ---------------------------- v20 = v4 ++ v19 ----------------------------- */
      if (v4 == NULL) {
         v20 = v19;
      } else 
      if (v19 == NULL) {
         v20 = v4;
      }
      else {
         v4->last->next = v19;
         v4->last = v19->last;
         v20 = v4;
      }
      /* --------------------------- v22 = minimum(v20) --------------------------- */
      v22 = 1.0e7;
      v21 = v20;
      while (v21 != NULL) {
         v22 = v22 < v21->item.alg_energy ? v22 : v21->item.alg_energy;
         v21 = v21->next;
      }
      v21 = v20;
      v24 = NULL;
      while (v21 != NULL) {
         if (abs(v22 - v21->item.alg_energy) <= diff) {
            update_str_Signature(v21->item.alg_enum->item, diff - abs(v22 - v21->item.alg_energy));
            v23=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v23->item = v21->item;
            v23->next = NULL;
            v23->last = v23;
            /* ------------------------- v24 = v23 ++ v24 ------------------------- */
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
      /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
      /* v1 stores the result of a single application of algebra function                                                                                                                                                                                                          */
      /* v24 holds the results of expression                                                                                                                                                                                                                                       */
      /*      dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h           */
      /*                                                                                                                                                                                                                                                                           */
      /* we use v26 to iterate over v24 and                                                                                                                                                                                                                                        */
      /* v25 to collect the results                                                                                                                                                                                                                                                */
      /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
      v26 = v24;
      while (v26 != NULL) {
         if (abs(tbl_block_Pr(i, j) - (40 + v26->item.alg_energy)) <= diff) {
            v1=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v1->next = NULL;
            v1->last = v1;
            v1->item.alg_energy = 40 + v26->item.alg_energy;
            v1->item.alg_enum = new_Ul_s(v26->item.alg_enum);
         }
         else {
            v1 = NULL;
         }
         /* --------------------------- v25 = v1 ++ v25 --------------------------- */
         if (v1 == NULL) {
         } else 
         if (v25 == NULL) {
            v25 = v1;
         }
         else {
            v1->last->next = v25;
            v1->last = v25->last;
            v25 = v1;
         }
         v26 = v26->next;
      }
   }
   else {
      v25 = NULL;
   }
   /*  v25 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h  */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /*  v53 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h)  */
   if ((j-i) >= 23) {
      v53 = NULL;
      for (k=i+1; k<=j-22; k++) {
         /* ------------------------------- start of ------------------------------ */
         /* - v30 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc - */
         if ((j-k) >= 23) {
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v29 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            if (abs(tbl_block_Pr(i, j) - ((40 + ((tbl_closed_Pr(k+1, j) + termaupenalty((k+1) + 1, j)) + dl_energy((k+1) + 1, j))) + ss_energy(i, k))) <= diff) {
               v29=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v29->next = NULL;
               v29->last = v29;
               v29->item.alg_energy = tbl_closed_Pr(k+1, j) + termaupenalty((k+1) + 1, j);
               v29->item.alg_enum = new_Is_f(k+1, back_closed_Pr, k+1, j, j);
            }
            else {
               v29 = NULL;
            }
            /* ------------- v29 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            /* ----------------------------- finished ----------------------------- */

            v30 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v28 stores the result of a single application of algebra function           */
            /* v29 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                     */
            /*                                                                             */
            /* we use v31 to iterate over v29 and                                          */
            /* v30 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v31 = v29;
            while (v31 != NULL) {
               if (abs(tbl_block_Pr(i, j) - ((40 + (v31->item.alg_energy + dl_energy((k+1) + 1, j))) + ss_energy(i, k))) <= diff) {
                  v28=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v28->next = NULL;
                  v28->last = v28;
                  v28->item.alg_energy = v31->item.alg_energy + dl_energy((k+1) + 1, j);
                  v28->item.alg_enum = new_Dl_s(k+1, v31->item.alg_enum, j);
               }
               else {
                  v28 = NULL;
               }
               /* ------------------------ v30 = v28 ++ v30 ----------------------- */
               if (v28 == NULL) {
               } else 
               if (v30 == NULL) {
                  v30 = v28;
               }
               else {
                  v28->last->next = v30;
                  v28->last = v30->last;
                  v30 = v28;
               }
               v31 = v31->next;
            }
         }
         else {
            v30 = NULL;
         }
         /* - v30 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc - */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* - v34 = dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase - */
         if ((j-k) >= 23) {
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v33 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            if (abs(tbl_block_Pr(i, j) - ((40 + ((tbl_closed_Pr(k, j-1) + termaupenalty((k) + 1, j-1)) + dr_energy((k) + 1, (j) - 1))) + ss_energy(i, k))) <= diff) {
               v33=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v33->next = NULL;
               v33->last = v33;
               v33->item.alg_energy = tbl_closed_Pr(k, j-1) + termaupenalty((k) + 1, j-1);
               v33->item.alg_enum = new_Is_f(k, back_closed_Pr, k, j-1, j-1);
            }
            else {
               v33 = NULL;
            }
            /* ------------- v33 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            /* ----------------------------- finished ----------------------------- */

            v34 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v32 stores the result of a single application of algebra function           */
            /* v33 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                     */
            /*                                                                             */
            /* we use v35 to iterate over v33 and                                          */
            /* v34 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v35 = v33;
            while (v35 != NULL) {
               if (abs(tbl_block_Pr(i, j) - ((40 + (v35->item.alg_energy + dr_energy((k) + 1, (j) - 1))) + ss_energy(i, k))) <= diff) {
                  v32=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v32->next = NULL;
                  v32->last = v32;
                  v32->item.alg_energy = v35->item.alg_energy + dr_energy((k) + 1, (j) - 1);
                  v32->item.alg_enum = new_Dr_s(k, v35->item.alg_enum, j);
               }
               else {
                  v32 = NULL;
               }
               /* ------------------------ v34 = v32 ++ v34 ----------------------- */
               if (v32 == NULL) {
               } else 
               if (v34 == NULL) {
                  v34 = v32;
               }
               else {
                  v32->last->next = v34;
                  v32->last = v34->last;
                  v34 = v32;
               }
               v35 = v35->next;
            }
         }
         else {
            v34 = NULL;
         }
         /* - v34 = dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase - */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v38 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase */
         if ((j-k) >= 24) {
            /* ----------------------------- start of ----------------------------- */
            /* ------------- v37 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            if (abs(tbl_block_Pr(i, j) - ((40 + (((tbl_closed_Pr(k+1, j-1) + termaupenalty((k+1) + 1, j-1)) + dl_energy((k+1) + 1, (j) - 1)) + dr_energy((k+1) + 1, (j) - 1))) + ss_energy(i, k))) <= diff) {
               v37=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v37->next = NULL;
               v37->last = v37;
               v37->item.alg_energy = tbl_closed_Pr(k+1, j-1) + termaupenalty((k+1) + 1, j-1);
               v37->item.alg_enum = new_Is_f(k+1, back_closed_Pr, k+1, j-1, j-1);
            }
            else {
               v37 = NULL;
            }
            /* ------------- v37 = is <<< loc ~~~ p closed_Pr ~~~ loc ------------- */
            /* ----------------------------- finished ----------------------------- */

            v38 = NULL;
            /* +-------------------------------------------------------------------------- */
            /* v36 stores the result of a single application of algebra function           */
            /* v37 holds the results of expression                                         */
            /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                     */
            /*                                                                             */
            /* we use v39 to iterate over v37 and                                          */
            /* v38 to collect the results                                                  */
            /* +-------------------------------------------------------------------------- */
            v39 = v37;
            while (v39 != NULL) {
               if (abs(tbl_block_Pr(i, j) - ((40 + ((v39->item.alg_energy + dl_energy((k+1) + 1, (j) - 1)) + dr_energy((k+1) + 1, (j) - 1))) + ss_energy(i, k))) <= diff) {
                  v36=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                  v36->next = NULL;
                  v36->last = v36;
                  v36->item.alg_energy = (v39->item.alg_energy + dl_energy((k+1) + 1, (j) - 1)) + dr_energy((k+1) + 1, (j) - 1);
                  v36->item.alg_enum = new_Dlr_s(k+1, v39->item.alg_enum, j);
               }
               else {
                  v36 = NULL;
               }
               /* ------------------------ v38 = v36 ++ v38 ----------------------- */
               if (v36 == NULL) {
               } else 
               if (v38 == NULL) {
                  v38 = v36;
               }
               else {
                  v36->last->next = v38;
                  v36->last = v38->last;
                  v38 = v36;
               }
               v39 = v39->next;
            }
         }
         else {
            v38 = NULL;
         }
         /*  v38 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* ---------- v42 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
         /* ------------------------------- start of ------------------------------ */
         /* --------------- v41 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
         if (abs(tbl_block_Pr(i, j) - ((40 + (tbl_closed_Pr(k, j) + termaupenalty((k) + 1, j))) + ss_energy(i, k))) <= diff) {
            v41=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
            v41->next = NULL;
            v41->last = v41;
            v41->item.alg_energy = tbl_closed_Pr(k, j) + termaupenalty((k) + 1, j);
            v41->item.alg_enum = new_Is_f(k, back_closed_Pr, k, j, j);
         }
         else {
            v41 = NULL;
         }
         /* --------------- v41 = is <<< loc ~~~ p closed_Pr ~~~ loc -------------- */
         /* ------------------------------- finished ------------------------------ */

         v42 = NULL;
         /* +-------------------------------------------------------------------------- */
         /* v40 stores the result of a single application of algebra function           */
         /* v41 holds the results of expression                                         */
         /*      is <<< loc ~~~ p closed_Pr ~~~ loc                                     */
         /*                                                                             */
         /* we use v43 to iterate over v41 and                                          */
         /* v42 to collect the results                                                  */
         /* +-------------------------------------------------------------------------- */
         v43 = v41;
         while (v43 != NULL) {
            if (abs(tbl_block_Pr(i, j) - ((40 + v43->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v40=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v40->next = NULL;
               v40->last = v40;
               v40->item.alg_energy = v43->item.alg_energy;
               v40->item.alg_enum = new_Drem_s(v43->item.alg_enum);
            }
            else {
               v40 = NULL;
            }
            /* ------------------------- v42 = v40 ++ v42 ------------------------- */
            if (v40 == NULL) {
            } else 
            if (v42 == NULL) {
               v42 = v40;
            }
            else {
               v40->last->next = v42;
               v40->last = v42->last;
               v42 = v40;
            }
            v43 = v43->next;
         }
         /* ---------- v42 = drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ---------- */
         /* ------------------------------- finished ------------------------------ */

         /* --------------------------- v44 = v38 ++ v42 -------------------------- */
         if (v38 == NULL) {
            v44 = v42;
         } else 
         if (v42 == NULL) {
            v44 = v38;
         }
         else {
            v38->last->next = v42;
            v38->last = v42->last;
            v44 = v38;
         }
         /* --------------------------- v45 = v34 ++ v44 -------------------------- */
         if (v34 == NULL) {
            v45 = v44;
         } else 
         if (v44 == NULL) {
            v45 = v34;
         }
         else {
            v34->last->next = v44;
            v34->last = v44->last;
            v45 = v34;
         }
         /* --------------------------- v46 = v30 ++ v45 -------------------------- */
         if (v30 == NULL) {
            v46 = v45;
         } else 
         if (v45 == NULL) {
            v46 = v30;
         }
         else {
            v30->last->next = v45;
            v30->last = v45->last;
            v46 = v30;
         }
         /* -------------------------- v48 = minimum(v46) ------------------------- */
         v48 = 1.0e7;
         v47 = v46;
         while (v47 != NULL) {
            v48 = v48 < v47->item.alg_energy ? v48 : v47->item.alg_energy;
            v47 = v47->next;
         }
         v47 = v46;
         v50 = NULL;
         while (v47 != NULL) {
            if (abs(v48 - v47->item.alg_energy) <= diff) {
               update_str_Signature(v47->item.alg_enum->item, diff - abs(v48 - v47->item.alg_energy));
               v49=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v49->item = v47->item;
               v49->next = NULL;
               v49->last = v49;
               /* ------------------------ v50 = v49 ++ v50 ----------------------- */
               if (v49 == NULL) {
               } else 
               if (v50 == NULL) {
                  v50 = v49;
               }
               else {
                  v49->last->next = v50;
                  v49->last = v50->last;
                  v50 = v49;
               }
            }
            v47 = v47->next;
         }
         v51 = NULL;
         /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
         /* v27 stores the result of a single application of algebra function                                                                                                                                                                                                         */
         /* v50 holds the results of expression                                                                                                                                                                                                                                       */
         /*      dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h           */
         /*                                                                                                                                                                                                                                                                           */
         /* we use v52 to iterate over v50 and                                                                                                                                                                                                                                        */
         /* v51 to collect the results                                                                                                                                                                                                                                                */
         /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
         v52 = v50;
         while (v52 != NULL) {
            if (abs(tbl_block_Pr(i, j) - ((40 + v52->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v27=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
               v27->next = NULL;
               v27->last = v27;
               v27->item.alg_energy = (40 + v52->item.alg_energy) + ss_energy(i, k);
               v27->item.alg_enum = new_Ssadd_s(i, k, v52->item.alg_enum);
            }
            else {
               v27 = NULL;
            }
            /* ------------------------- v51 = v27 ++ v51 ------------------------- */
            if (v27 == NULL) {
            } else 
            if (v51 == NULL) {
               v51 = v27;
            }
            else {
               v27->last->next = v51;
               v27->last = v51->last;
               v51 = v27;
            }
            v52 = v52->next;
         }
         /* --------------------------- v53 = v51 ++ v53 -------------------------- */
         if (v51 == NULL) {
         } else 
         if (v53 == NULL) {
            v53 = v51;
         }
         else {
            v51->last->next = v53;
            v51->last = v53->last;
            v53 = v51;
         }
      }
   }
   else {
      v53 = NULL;
   }
   /*  v53 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed_Pr ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed_Pr ~~~ loc ... h)  */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v54 = pkmldl <<< lbase ~~~ p knot --------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      if (abs(tbl_block_Pr(i, j) - ((tbl_knot(i+1, j).tup1 + 600) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3)))) <= diff) {
         v54=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v54->next = NULL;
         v54->last = v54;
         v54->item.alg_energy = (tbl_knot(i+1, j).tup1 + 600) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3));
         v54->item.alg_enum = new_Pkmldl_f(i+1, back_knot, i+1, j, tbl_knot(i+1, j).tup2, tbl_knot(i+1, j).tup3);
      }
      else {
         v54 = NULL;
      }
   }
   else {
      v54 = NULL;
   }
   /* --------------------- v54 = pkmldl <<< lbase ~~~ p knot --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v55 = pkmldr <<< p knot ~~~ lbase --------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      if (abs(tbl_block_Pr(i, j) - ((tbl_knot(i, j-1).tup1 + 600) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1)))) <= diff) {
         v55=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v55->next = NULL;
         v55->last = v55;
         v55->item.alg_energy = (tbl_knot(i, j-1).tup1 + 600) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1));
         v55->item.alg_enum = new_Pkmldr_f(back_knot, i, j-1, tbl_knot(i, j-1).tup2, tbl_knot(i, j-1).tup3, j);
      }
      else {
         v55 = NULL;
      }
   }
   else {
      v55 = NULL;
   }
   /* --------------------- v55 = pkmldr <<< p knot ~~~ lbase --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ---------------- v56 = pkmldlr <<< lbase ~~~ p knot ~~~ lbase --------------- */
   if (((j-i) >= 13) && ((j-i) <= (max_pknot_length+2))) {
      if (abs(tbl_block_Pr(i, j) - ((tbl_knot(i+1, j-1).tup1 + 600) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1))))) <= diff) {
         v56=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v56->next = NULL;
         v56->last = v56;
         v56->item.alg_energy = (tbl_knot(i+1, j-1).tup1 + 600) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1)));
         v56->item.alg_enum = new_Pkmldlr_f(i+1, back_knot, i+1, j-1, tbl_knot(i+1, j-1).tup2, tbl_knot(i+1, j-1).tup3, j);
      }
      else {
         v56 = NULL;
      }
   }
   else {
      v56 = NULL;
   }
   /* ---------------- v56 = pkmldlr <<< lbase ~~~ p knot ~~~ lbase --------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------------- v57 = pkml <<< p knot --------------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      if (abs(tbl_block_Pr(i, j) - (tbl_knot(i, j).tup1 + 600)) <= diff) {
         v57=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v57->next = NULL;
         v57->last = v57;
         v57->item.alg_energy = tbl_knot(i, j).tup1 + 600;
         v57->item.alg_enum = new_Pkml_f(back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3);
      }
      else {
         v57 = NULL;
      }
   }
   else {
      v57 = NULL;
   }
   /* --------------------------- v57 = pkml <<< p knot --------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------------ v58 = v56 ++ v57 ----------------------------- */
   if (v56 == NULL) {
      v58 = v57;
   } else 
   if (v57 == NULL) {
      v58 = v56;
   }
   else {
      v56->last->next = v57;
      v56->last = v57->last;
      v58 = v56;
   }
   /* ------------------------------ v59 = v55 ++ v58 ----------------------------- */
   if (v55 == NULL) {
      v59 = v58;
   } else 
   if (v58 == NULL) {
      v59 = v55;
   }
   else {
      v55->last->next = v58;
      v55->last = v58->last;
      v59 = v55;
   }
   /* ------------------------------ v60 = v54 ++ v59 ----------------------------- */
   if (v54 == NULL) {
      v60 = v59;
   } else 
   if (v59 == NULL) {
      v60 = v54;
   }
   else {
      v54->last->next = v59;
      v54->last = v59->last;
      v60 = v54;
   }
   /* ------------------------------ v61 = v53 ++ v60 ----------------------------- */
   if (v53 == NULL) {
      v61 = v60;
   } else 
   if (v60 == NULL) {
      v61 = v53;
   }
   else {
      v53->last->next = v60;
      v53->last = v60->last;
      v61 = v53;
   }
   /* ------------------------------ v62 = v25 ++ v61 ----------------------------- */
   if (v25 == NULL) {
      v62 = v61;
   } else 
   if (v61 == NULL) {
      v62 = v25;
   }
   else {
      v25->last->next = v61;
      v25->last = v61->last;
      v62 = v25;
   }
   /* ----------------------------- v64 = minimum(v62) ---------------------------- */
   v64 = 1.0e7;
   v63 = v62;
   while (v63 != NULL) {
      v64 = v64 < v63->item.alg_energy ? v64 : v63->item.alg_energy;
      v63 = v63->next;
   }
   v63 = v62;
   v66 = NULL;
   while (v63 != NULL) {
      if (abs(v64 - v63->item.alg_energy) <= diff) {
         update_str_Signature(v63->item.alg_enum->item, diff - abs(v64 - v63->item.alg_energy));
         v65=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
         v65->item = v63->item;
         v65->next = NULL;
         v65->last = v65;
         /* --------------------------- v66 = v65 ++ v66 -------------------------- */
         if (v65 == NULL) {
         } else 
         if (v66 == NULL) {
            v66 = v65;
         }
         else {
            v65->last->next = v66;
            v65->last = v66->last;
            v66 = v65;
         }
      }
      v63 = v63->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v67 = v66;
   v68 = NULL;
   while (v67 != NULL) {
      /* -------------------- v68 = v67->item.alg_enum ++ v68 --------------------- */
      if (v67->item.alg_enum == NULL) {
      } else 
      if (v68 == NULL) {
         v68 = v67->item.alg_enum;
      }
      else {
         v67->item.alg_enum->last->next = v68;
         v67->item.alg_enum->last = v68->last;
         v68 = v67->item.alg_enum;
      }
      v67 = v67->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v68)));
}

/* backtracing code for production knot                                             */
/* -------------------------------------------------------------------------------- */
static struct str3 *back_knot(int i, int j, int diff)
{
   struct str3 *v155;
   struct str1 v151;
   int v12, v27, v34, v50, v65, v80, v95, v107, v120, v135, v142;
   struct str5 *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10, *v11, *v13, *v14;
   struct str5 *v15, *v16, *v17, *v18, *v19, *v20;
   struct str5 *v21, *v22, *v23, *v24, *v25, *v26;
   struct str5 *v28, *v29, *v30, *v31, *v32, *v33;
   struct str5 *v35, *v36, *v37, *v38, *v39, *v40;
   struct str5 *v41, *v42, *v43, *v44, *v45, *v46;
   struct str5 *v47, *v48, *v49, *v51, *v52, *v53;
   struct str5 *v54, *v55, *v56, *v57, *v58, *v59;
   struct str5 *v60, *v61, *v62, *v63, *v64, *v66;
   struct str5 *v67, *v68, *v69, *v70, *v71, *v72;
   struct str5 *v73, *v74, *v75, *v76, *v77, *v78;
   struct str5 *v79, *v81, *v82, *v83, *v84, *v85;
   struct str5 *v86, *v87, *v88, *v89, *v90, *v91;
   struct str5 *v92, *v93, *v94, *v96, *v97, *v98;
   struct str5 *v99, *v100, *v101, *v102, *v103, *v104;
   struct str5 *v105, *v106, *v108, *v109, *v110, *v111;
   struct str5 *v112, *v113, *v114, *v115, *v116, *v117, *v118;
   struct str5 *v119, *v121, *v122, *v123, *v124, *v125;
   struct str5 *v126, *v127, *v128, *v129, *v130, *v131, *v132;
   struct str5 *v133, *v134, *v136, *v137, *v138, *v139;
   struct str5 *v140, *v141, *v143, *v144, *v146, *v147, *v148;
   struct str7 *v1, *v145, *v149, *v150, *v152, *v153, *v154;
   int lc_alphanrg, lc_betalen, lc_betanrg, lc_correctionterm, lc_energy;
   int lc_h, lc_h_Pr, lc_k, lc_l, lc_middle_k, lc_middle_l;

   /* ---------------------------------- start of --------------------------------- */
   /* ------- v149 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
   if ((j-i) >= 0) {
      v149 = NULL;
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
                  /* = co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr .. */
                  if ((lc_l-(i+lc_h)-1) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v5 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v4 = pss <<< uregion ------------------ */
                     v4=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v4->next = NULL;
                     v4->last = v4;
                     v4->item.alg_energy = sspenalty((lc_l) - (i+lc_h+1));
                     v4->item.alg_enum = new_Pss_(i+lc_h+1, lc_l);
                     /* ------------------- v4 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v5 = NULL;
                     /* +------------------------------------------------------------------------- */
                     /* v3 stores the result of a single application of algebra function           */
                     /* v4 holds the results of expression                                         */
                     /*      pss <<< uregion                                                       */
                     /*                                                                            */
                     /* we use v6 to iterate over v4 and                                           */
                     /* v5 to collect the results                                                  */
                     /* +------------------------------------------------------------------------- */
                     v6 = v4;
                     while (v6 != NULL) {
                        v3=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v3->next = NULL;
                        v3->last = v3;
                        v3->item.alg_energy = v6->item.alg_energy;
                        v3->item.alg_enum = new_Pul_s(v6->item.alg_enum);
                        /* -------------------- v5 = v3 ++ v5 --------------------- */
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
                     /* --------------- v5 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ----------------------- v7 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_l-(i+lc_h)-1) >= 7) {
                        v7=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v7->item.alg_energy = tbl_comps(i+lc_h+1, lc_l);
                        v7->item.alg_enum = new__NTID(back_comps, i+lc_h+1, lc_l);
                        v7->next = NULL;
                        v7->last = v7;
                     }
                     else {
                        v7 = NULL;
                     }
                     /* --------------------- v8 = p comps_Pr --------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps_Pr is implemented as a tabulated                            */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps_Pr into a single list element.            */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_l-(i+lc_h)-1) >= 11) {
                        v8=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v8->item.alg_energy = tbl_comps_Pr(i+lc_h+1, lc_l);
                        v8->item.alg_enum = new__NTID(back_comps_Pr, i+lc_h+1, lc_l);
                        v8->next = NULL;
                        v8->last = v8;
                     }
                     else {
                        v8 = NULL;
                     }
                     /* ---------------------- v9 = v7 ++ v8 ---------------------- */
                     if (v7 == NULL) {
                        v9 = v8;
                     } else 
                     if (v8 == NULL) {
                        v9 = v7;
                     }
                     else {
                        v7->last->next = v8;
                        v7->last = v8->last;
                        v9 = v7;
                     }
                     /* ---------------------- v10 = v5 ++ v9 --------------------- */
                     if (v5 == NULL) {
                        v10 = v9;
                     } else 
                     if (v9 == NULL) {
                        v10 = v5;
                     }
                     else {
                        v5->last->next = v9;
                        v5->last = v9->last;
                        v10 = v5;
                     }
                     /* -------------------- v12 = minimum(v10) ------------------- */
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
                           /* ------------------ v14 = v13 ++ v14 ----------------- */
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
                     v15 = NULL;
                     /* +------------------------------------------------------------------------- */
                     /* v2 stores the result of a single application of algebra function           */
                     /* v14 holds the results of expression                                        */
                     /*      pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h              */
                     /*                                                                            */
                     /* we use v16 to iterate over v14 and                                         */
                     /* v15 to collect the results                                                 */
                     /* +------------------------------------------------------------------------- */
                     v16 = v14;
                     while (v16 != NULL) {
                        v2=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v2->next = NULL;
                        v2->last = v2;
                        v2->item.alg_energy = v16->item.alg_energy;
                        v2->item.alg_enum = new_Co_s(v16->item.alg_enum);
                        /* ------------------- v15 = v2 ++ v15 -------------------- */
                        if (v2 == NULL) {
                        } else 
                        if (v15 == NULL) {
                           v15 = v2;
                        }
                        else {
                           v2->last->next = v15;
                           v2->last = v15->last;
                           v15 = v2;
                        }
                        v16 = v16->next;
                     }
                  }
                  else {
                     v15 = NULL;
                  }
                  /* = co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr .. */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v30 = frd j <<< (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  if ((lc_l-(i+lc_h)-1) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v20 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v19 = pss <<< uregion ------------------ */
                     v19=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v19->next = NULL;
                     v19->last = v19;
                     v19->item.alg_energy = sspenalty((lc_l-1) - (i+lc_h+1));
                     v19->item.alg_enum = new_Pss_(i+lc_h+1, lc_l-1);
                     /* ------------------ v19 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v20 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v18 stores the result of a single application of algebra function           */
                     /* v19 holds the results of expression                                         */
                     /*      pss <<< uregion                                                        */
                     /*                                                                             */
                     /* we use v21 to iterate over v19 and                                          */
                     /* v20 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v21 = v19;
                     while (v21 != NULL) {
                        v18=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v18->next = NULL;
                        v18->last = v18;
                        v18->item.alg_energy = v21->item.alg_energy;
                        v18->item.alg_enum = new_Pul_s(v21->item.alg_enum);
                        /* ------------------- v20 = v18 ++ v20 ------------------- */
                        if (v18 == NULL) {
                        } else 
                        if (v20 == NULL) {
                           v20 = v18;
                        }
                        else {
                           v18->last->next = v20;
                           v18->last = v20->last;
                           v20 = v18;
                        }
                        v21 = v21->next;
                     }
                     /* -------------- v20 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v22 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_l-(i+lc_h)-2) >= 7) {
                        v22=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v22->item.alg_energy = tbl_comps(i+lc_h+1, lc_l-1);
                        v22->item.alg_enum = new__NTID(back_comps, i+lc_h+1, lc_l-1);
                        v22->next = NULL;
                        v22->last = v22;
                     }
                     else {
                        v22 = NULL;
                     }
                     /* --------------------- v23 = p comps_Pr -------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps_Pr is implemented as a tabulated                            */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps_Pr into a single list element.            */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_l-(i+lc_h)-2) >= 11) {
                        v23=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v23->item.alg_energy = tbl_comps_Pr(i+lc_h+1, lc_l-1);
                        v23->item.alg_enum = new__NTID(back_comps_Pr, i+lc_h+1, lc_l-1);
                        v23->next = NULL;
                        v23->last = v23;
                     }
                     else {
                        v23 = NULL;
                     }
                     /* --------------------- v24 = v22 ++ v23 -------------------- */
                     if (v22 == NULL) {
                        v24 = v23;
                     } else 
                     if (v23 == NULL) {
                        v24 = v22;
                     }
                     else {
                        v22->last->next = v23;
                        v22->last = v23->last;
                        v24 = v22;
                     }
                     /* --------------------- v25 = v20 ++ v24 -------------------- */
                     if (v20 == NULL) {
                        v25 = v24;
                     } else 
                     if (v24 == NULL) {
                        v25 = v20;
                     }
                     else {
                        v20->last->next = v24;
                        v20->last = v24->last;
                        v25 = v20;
                     }
                     /* -------------------- v27 = minimum(v25) ------------------- */
                     v27 = 1.0e7;
                     v26 = v25;
                     while (v26 != NULL) {
                        v27 = v27 < v26->item.alg_energy ? v27 : v26->item.alg_energy;
                        v26 = v26->next;
                     }
                     v26 = v25;
                     v29 = NULL;
                     while (v26 != NULL) {
                        if (abs(v27 - v26->item.alg_energy) <= diff) {
                           update_str_Signature(v26->item.alg_enum->item, diff - abs(v27 - v26->item.alg_energy));
                           v28=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                           v28->item = v26->item;
                           v28->next = NULL;
                           v28->last = v28;
                           /* ------------------ v29 = v28 ++ v29 ----------------- */
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
                        v26 = v26->next;
                     }
                     v30 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v17 stores the result of a single application of algebra function           */
                     /* v29 holds the results of expression                                         */
                     /*      pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h               */
                     /*                                                                             */
                     /* we use v31 to iterate over v29 and                                          */
                     /* v30 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v31 = v29;
                     while (v31 != NULL) {
                        v17=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v17->next = NULL;
                        v17->last = v17;
                        v17->item.alg_energy = (v31->item.alg_energy + (wkn * dl_energy((lc_l) + 1, j))) + npp;
                        v17->item.alg_enum = new_Frd_s(j, v31->item.alg_enum, lc_l);
                        /* ------------------- v30 = v17 ++ v30 ------------------- */
                        if (v17 == NULL) {
                        } else 
                        if (v30 == NULL) {
                           v30 = v17;
                        }
                        else {
                           v17->last->next = v30;
                           v17->last = v30->last;
                           v30 = v17;
                        }
                        v31 = v31->next;
                     }
                  }
                  else {
                     v30 = NULL;
                  }
                  /*  v30 = frd j <<< (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* ---------------------- v32 = v15 ++ v30 ---------------------- */
                  if (v15 == NULL) {
                     v32 = v30;
                  } else 
                  if (v30 == NULL) {
                     v32 = v15;
                  }
                  else {
                     v15->last->next = v30;
                     v15->last = v30->last;
                     v32 = v15;
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
                  /* ------ v37 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 0) {
                     v37=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v37->next = NULL;
                     v37->last = v37;
                     v37->item.alg_energy = wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, lc_l+lc_h_Pr, (lc_l+lc_h_Pr) + 1);
                     v37->item.alg_enum = new_Emptymid_(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr);
                  }
                  else {
                     v37 = NULL;
                  }
                  /* ------ v37 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* ------ v38 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 1) {
                     v38=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v38->next = NULL;
                     v38->last = v38;
                     v38->item.alg_energy = (wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, (lc_k-lc_h) - 1, (lc_k-lc_h) + 1)) + npp;
                     v38->item.alg_enum = new_Midbase_(lc_middle_k, lc_middle_l, lc_k-lc_h);
                  }
                  else {
                     v38 = NULL;
                  }
                  /* ------ v38 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* - v39 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 2) {
                     v39=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v39->next = NULL;
                     v39->last = v39;
                     v39->item.alg_energy = (2 * npp) + (wkn * (dri_energy(lc_middle_l, (lc_l+lc_h_Pr+1) + 2) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                     v39->item.alg_enum = new_Middlro_(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr+1, lc_k-lc_h);
                  }
                  else {
                     v39 = NULL;
                  }
                  /* - v39 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v53 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h)  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v43 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v42 = pss <<< region ------------------ */
                     v42=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v42->next = NULL;
                     v42->last = v42;
                     v42->item.alg_energy = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr+1));
                     v42->item.alg_enum = new_Pss_(lc_l+lc_h_Pr+1, lc_k-lc_h);
                     /* ------------------- v42 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v43 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v41 stores the result of a single application of algebra function           */
                     /* v42 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v44 to iterate over v42 and                                          */
                     /* v43 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v44 = v42;
                     while (v44 != NULL) {
                        v41=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v41->next = NULL;
                        v41->last = v41;
                        v41->item.alg_energy = v44->item.alg_energy;
                        v41->item.alg_enum = new_Pul_s(v44->item.alg_enum);
                        /* ------------------- v43 = v41 ++ v43 ------------------- */
                        if (v41 == NULL) {
                        } else 
                        if (v43 == NULL) {
                           v43 = v41;
                        }
                        else {
                           v41->last->next = v43;
                           v41->last = v43->last;
                           v43 = v41;
                        }
                        v44 = v44->next;
                     }
                     /* --------------- v43 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v45 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v45=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v45->item.alg_energy = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h);
                        v45->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr+1, lc_k-lc_h);
                        v45->next = NULL;
                        v45->last = v45;
                     }
                     else {
                        v45 = NULL;
                     }
                     /* --------------------- v46 = p comps_Pr -------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps_Pr is implemented as a tabulated                            */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps_Pr into a single list element.            */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 11) {
                        v46=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v46->item.alg_energy = tbl_comps_Pr(lc_l+lc_h_Pr+1, lc_k-lc_h);
                        v46->item.alg_enum = new__NTID(back_comps_Pr, lc_l+lc_h_Pr+1, lc_k-lc_h);
                        v46->next = NULL;
                        v46->last = v46;
                     }
                     else {
                        v46 = NULL;
                     }
                     /* --------------------- v47 = v45 ++ v46 -------------------- */
                     if (v45 == NULL) {
                        v47 = v46;
                     } else 
                     if (v46 == NULL) {
                        v47 = v45;
                     }
                     else {
                        v45->last->next = v46;
                        v45->last = v46->last;
                        v47 = v45;
                     }
                     /* --------------------- v48 = v43 ++ v47 -------------------- */
                     if (v43 == NULL) {
                        v48 = v47;
                     } else 
                     if (v47 == NULL) {
                        v48 = v43;
                     }
                     else {
                        v43->last->next = v47;
                        v43->last = v47->last;
                        v48 = v43;
                     }
                     /* -------------------- v50 = minimum(v48) ------------------- */
                     v50 = 1.0e7;
                     v49 = v48;
                     while (v49 != NULL) {
                        v50 = v50 < v49->item.alg_energy ? v50 : v49->item.alg_energy;
                        v49 = v49->next;
                     }
                     v49 = v48;
                     v52 = NULL;
                     while (v49 != NULL) {
                        if (abs(v50 - v49->item.alg_energy) <= diff) {
                           update_str_Signature(v49->item.alg_enum->item, diff - abs(v50 - v49->item.alg_energy));
                           v51=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                           v51->item = v49->item;
                           v51->next = NULL;
                           v51->last = v51;
                           /* ------------------ v52 = v51 ++ v52 ----------------- */
                           if (v51 == NULL) {
                           } else 
                           if (v52 == NULL) {
                              v52 = v51;
                           }
                           else {
                              v51->last->next = v52;
                              v51->last = v52->last;
                              v52 = v51;
                           }
                        }
                        v49 = v49->next;
                     }
                     v53 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v40 stores the result of a single application of algebra function           */
                     /* v52 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h                */
                     /*                                                                             */
                     /* we use v54 to iterate over v52 and                                          */
                     /* v53 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v54 = v52;
                     while (v54 != NULL) {
                        v40=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v40->next = NULL;
                        v40->last = v40;
                        v40->item.alg_energy = (v54->item.alg_energy + npp) + (wkn * dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1));
                        v40->item.alg_enum = new_Middl_s(lc_middle_k, lc_l+lc_h_Pr+1, v54->item.alg_enum);
                        /* ------------------- v53 = v40 ++ v53 ------------------- */
                        if (v40 == NULL) {
                        } else 
                        if (v53 == NULL) {
                           v53 = v40;
                        }
                        else {
                           v40->last->next = v53;
                           v40->last = v53->last;
                           v53 = v40;
                        }
                        v54 = v54->next;
                     }
                  }
                  else {
                     v53 = NULL;
                  }
                  /*  v53 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h)  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v68 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v58 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v57 = pss <<< region ------------------ */
                     v57=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v57->next = NULL;
                     v57->last = v57;
                     v57->item.alg_energy = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr));
                     v57->item.alg_enum = new_Pss_(lc_l+lc_h_Pr, lc_k-lc_h-1);
                     /* ------------------- v57 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v58 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v56 stores the result of a single application of algebra function           */
                     /* v57 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v59 to iterate over v57 and                                          */
                     /* v58 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v59 = v57;
                     while (v59 != NULL) {
                        v56=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v56->next = NULL;
                        v56->last = v56;
                        v56->item.alg_energy = v59->item.alg_energy;
                        v56->item.alg_enum = new_Pul_s(v59->item.alg_enum);
                        /* ------------------- v58 = v56 ++ v58 ------------------- */
                        if (v56 == NULL) {
                        } else 
                        if (v58 == NULL) {
                           v58 = v56;
                        }
                        else {
                           v56->last->next = v58;
                           v56->last = v58->last;
                           v58 = v56;
                        }
                        v59 = v59->next;
                     }
                     /* --------------- v58 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v60 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v60=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v60->item.alg_energy = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h-1);
                        v60->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr, lc_k-lc_h-1);
                        v60->next = NULL;
                        v60->last = v60;
                     }
                     else {
                        v60 = NULL;
                     }
                     /* --------------------- v61 = p comps_Pr -------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps_Pr is implemented as a tabulated                            */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps_Pr into a single list element.            */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 11) {
                        v61=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v61->item.alg_energy = tbl_comps_Pr(lc_l+lc_h_Pr, lc_k-lc_h-1);
                        v61->item.alg_enum = new__NTID(back_comps_Pr, lc_l+lc_h_Pr, lc_k-lc_h-1);
                        v61->next = NULL;
                        v61->last = v61;
                     }
                     else {
                        v61 = NULL;
                     }
                     /* --------------------- v62 = v60 ++ v61 -------------------- */
                     if (v60 == NULL) {
                        v62 = v61;
                     } else 
                     if (v61 == NULL) {
                        v62 = v60;
                     }
                     else {
                        v60->last->next = v61;
                        v60->last = v61->last;
                        v62 = v60;
                     }
                     /* --------------------- v63 = v58 ++ v62 -------------------- */
                     if (v58 == NULL) {
                        v63 = v62;
                     } else 
                     if (v62 == NULL) {
                        v63 = v58;
                     }
                     else {
                        v58->last->next = v62;
                        v58->last = v62->last;
                        v63 = v58;
                     }
                     /* -------------------- v65 = minimum(v63) ------------------- */
                     v65 = 1.0e7;
                     v64 = v63;
                     while (v64 != NULL) {
                        v65 = v65 < v64->item.alg_energy ? v65 : v64->item.alg_energy;
                        v64 = v64->next;
                     }
                     v64 = v63;
                     v67 = NULL;
                     while (v64 != NULL) {
                        if (abs(v65 - v64->item.alg_energy) <= diff) {
                           update_str_Signature(v64->item.alg_enum->item, diff - abs(v65 - v64->item.alg_energy));
                           v66=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                           v66->item = v64->item;
                           v66->next = NULL;
                           v66->last = v66;
                           /* ------------------ v67 = v66 ++ v67 ----------------- */
                           if (v66 == NULL) {
                           } else 
                           if (v67 == NULL) {
                              v67 = v66;
                           }
                           else {
                              v66->last->next = v67;
                              v66->last = v67->last;
                              v67 = v66;
                           }
                        }
                        v64 = v64->next;
                     }
                     v68 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v55 stores the result of a single application of algebra function           */
                     /* v67 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h                */
                     /*                                                                             */
                     /* we use v69 to iterate over v67 and                                          */
                     /* v68 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v69 = v67;
                     while (v69 != NULL) {
                        v55=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v55->next = NULL;
                        v55->last = v55;
                        v55->item.alg_energy = (v69->item.alg_energy + npp) + (wkn * dri_energy(lc_middle_l, (lc_k-lc_h) + 1));
                        v55->item.alg_enum = new_Middr_s(lc_middle_l, v69->item.alg_enum, lc_k-lc_h);
                        /* ------------------- v68 = v55 ++ v68 ------------------- */
                        if (v55 == NULL) {
                        } else 
                        if (v68 == NULL) {
                           v68 = v55;
                        }
                        else {
                           v55->last->next = v68;
                           v55->last = v68->last;
                           v68 = v55;
                        }
                        v69 = v69->next;
                     }
                  }
                  else {
                     v68 = NULL;
                  }
                  /*  v68 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v83 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 3) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v73 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v72 = pss <<< region ------------------ */
                     v72=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v72->next = NULL;
                     v72->last = v72;
                     v72->item.alg_energy = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr+1));
                     v72->item.alg_enum = new_Pss_(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                     /* ------------------- v72 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v73 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v71 stores the result of a single application of algebra function           */
                     /* v72 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v74 to iterate over v72 and                                          */
                     /* v73 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v74 = v72;
                     while (v74 != NULL) {
                        v71=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v71->next = NULL;
                        v71->last = v71;
                        v71->item.alg_energy = v74->item.alg_energy;
                        v71->item.alg_enum = new_Pul_s(v74->item.alg_enum);
                        /* ------------------- v73 = v71 ++ v73 ------------------- */
                        if (v71 == NULL) {
                        } else 
                        if (v73 == NULL) {
                           v73 = v71;
                        }
                        else {
                           v71->last->next = v73;
                           v71->last = v73->last;
                           v73 = v71;
                        }
                        v74 = v74->next;
                     }
                     /* --------------- v73 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v75 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-2) >= 7) {
                        v75=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v75->item.alg_energy = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                        v75->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                        v75->next = NULL;
                        v75->last = v75;
                     }
                     else {
                        v75 = NULL;
                     }
                     /* --------------------- v76 = p comps_Pr -------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps_Pr is implemented as a tabulated                            */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps_Pr into a single list element.            */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-2) >= 11) {
                        v76=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v76->item.alg_energy = tbl_comps_Pr(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                        v76->item.alg_enum = new__NTID(back_comps_Pr, lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                        v76->next = NULL;
                        v76->last = v76;
                     }
                     else {
                        v76 = NULL;
                     }
                     /* --------------------- v77 = v75 ++ v76 -------------------- */
                     if (v75 == NULL) {
                        v77 = v76;
                     } else 
                     if (v76 == NULL) {
                        v77 = v75;
                     }
                     else {
                        v75->last->next = v76;
                        v75->last = v76->last;
                        v77 = v75;
                     }
                     /* --------------------- v78 = v73 ++ v77 -------------------- */
                     if (v73 == NULL) {
                        v78 = v77;
                     } else 
                     if (v77 == NULL) {
                        v78 = v73;
                     }
                     else {
                        v73->last->next = v77;
                        v73->last = v77->last;
                        v78 = v73;
                     }
                     /* -------------------- v80 = minimum(v78) ------------------- */
                     v80 = 1.0e7;
                     v79 = v78;
                     while (v79 != NULL) {
                        v80 = v80 < v79->item.alg_energy ? v80 : v79->item.alg_energy;
                        v79 = v79->next;
                     }
                     v79 = v78;
                     v82 = NULL;
                     while (v79 != NULL) {
                        if (abs(v80 - v79->item.alg_energy) <= diff) {
                           update_str_Signature(v79->item.alg_enum->item, diff - abs(v80 - v79->item.alg_energy));
                           v81=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                           v81->item = v79->item;
                           v81->next = NULL;
                           v81->last = v81;
                           /* ------------------ v82 = v81 ++ v82 ----------------- */
                           if (v81 == NULL) {
                           } else 
                           if (v82 == NULL) {
                              v82 = v81;
                           }
                           else {
                              v81->last->next = v82;
                              v81->last = v82->last;
                              v82 = v81;
                           }
                        }
                        v79 = v79->next;
                     }
                     v83 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v70 stores the result of a single application of algebra function           */
                     /* v82 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h                */
                     /*                                                                             */
                     /* we use v84 to iterate over v82 and                                          */
                     /* v83 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v84 = v82;
                     while (v84 != NULL) {
                        v70=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v70->next = NULL;
                        v70->last = v70;
                        v70->item.alg_energy = (v84->item.alg_energy + (2 * npp)) + (wkn * (dri_energy(lc_middle_l, (lc_k-lc_h) + 1) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                        v70->item.alg_enum = new_Middlr_s(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr+1, v84->item.alg_enum, lc_k-lc_h);
                        /* ------------------- v83 = v70 ++ v83 ------------------- */
                        if (v70 == NULL) {
                        } else 
                        if (v83 == NULL) {
                           v83 = v70;
                        }
                        else {
                           v70->last->next = v83;
                           v70->last = v83->last;
                           v83 = v70;
                        }
                        v84 = v84->next;
                     }
                  }
                  else {
                     v83 = NULL;
                  }
                  /*  v83 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* idregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v88 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v87 = pss <<< region ------------------ */
                     v87=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v87->next = NULL;
                     v87->last = v87;
                     v87->item.alg_energy = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr));
                     v87->item.alg_enum = new_Pss_(lc_l+lc_h_Pr, lc_k-lc_h);
                     /* ------------------- v87 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v88 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v86 stores the result of a single application of algebra function           */
                     /* v87 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v89 to iterate over v87 and                                          */
                     /* v88 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v89 = v87;
                     while (v89 != NULL) {
                        v86=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v86->next = NULL;
                        v86->last = v86;
                        v86->item.alg_energy = v89->item.alg_energy;
                        v86->item.alg_enum = new_Pul_s(v89->item.alg_enum);
                        /* ------------------- v88 = v86 ++ v88 ------------------- */
                        if (v86 == NULL) {
                        } else 
                        if (v88 == NULL) {
                           v88 = v86;
                        }
                        else {
                           v86->last->next = v88;
                           v86->last = v88->last;
                           v88 = v86;
                        }
                        v89 = v89->next;
                     }
                     /* --------------- v88 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v90 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 7) {
                        v90=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v90->item.alg_energy = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h);
                        v90->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr, lc_k-lc_h);
                        v90->next = NULL;
                        v90->last = v90;
                     }
                     else {
                        v90 = NULL;
                     }
                     /* --------------------- v91 = p comps_Pr -------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps_Pr is implemented as a tabulated                            */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps_Pr into a single list element.            */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 11) {
                        v91=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v91->item.alg_energy = tbl_comps_Pr(lc_l+lc_h_Pr, lc_k-lc_h);
                        v91->item.alg_enum = new__NTID(back_comps_Pr, lc_l+lc_h_Pr, lc_k-lc_h);
                        v91->next = NULL;
                        v91->last = v91;
                     }
                     else {
                        v91 = NULL;
                     }
                     /* --------------------- v92 = v90 ++ v91 -------------------- */
                     if (v90 == NULL) {
                        v92 = v91;
                     } else 
                     if (v91 == NULL) {
                        v92 = v90;
                     }
                     else {
                        v90->last->next = v91;
                        v90->last = v91->last;
                        v92 = v90;
                     }
                     /* --------------------- v93 = v88 ++ v92 -------------------- */
                     if (v88 == NULL) {
                        v93 = v92;
                     } else 
                     if (v92 == NULL) {
                        v93 = v88;
                     }
                     else {
                        v88->last->next = v92;
                        v88->last = v92->last;
                        v93 = v88;
                     }
                     /* -------------------- v95 = minimum(v93) ------------------- */
                     v95 = 1.0e7;
                     v94 = v93;
                     while (v94 != NULL) {
                        v95 = v95 < v94->item.alg_energy ? v95 : v94->item.alg_energy;
                        v94 = v94->next;
                     }
                     v94 = v93;
                     v97 = NULL;
                     while (v94 != NULL) {
                        if (abs(v95 - v94->item.alg_energy) <= diff) {
                           update_str_Signature(v94->item.alg_enum->item, diff - abs(v95 - v94->item.alg_energy));
                           v96=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                           v96->item = v94->item;
                           v96->next = NULL;
                           v96->last = v96;
                           /* ------------------ v97 = v96 ++ v97 ----------------- */
                           if (v96 == NULL) {
                           } else 
                           if (v97 == NULL) {
                              v97 = v96;
                           }
                           else {
                              v96->last->next = v97;
                              v96->last = v97->last;
                              v97 = v96;
                           }
                        }
                        v94 = v94->next;
                     }
                     v98 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v85 stores the result of a single application of algebra function           */
                     /* v97 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h                */
                     /*                                                                             */
                     /* we use v99 to iterate over v97 and                                          */
                     /* v98 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v99 = v97;
                     while (v99 != NULL) {
                        v85=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v85->next = NULL;
                        v85->last = v85;
                        v85->item.alg_energy = v99->item.alg_energy;
                        v85->item.alg_enum = new_Midregion_s(v99->item.alg_enum);
                        /* ------------------- v98 = v85 ++ v98 ------------------- */
                        if (v85 == NULL) {
                        } else 
                        if (v98 == NULL) {
                           v98 = v85;
                        }
                        else {
                           v85->last->next = v98;
                           v85->last = v98->last;
                           v98 = v85;
                        }
                        v99 = v99->next;
                     }
                  }
                  else {
                     v98 = NULL;
                  }
                  /* idregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr */
                  /* -------------------------- finished -------------------------- */

                  /* --------------------- v100 = v83 ++ v98 ---------------------- */
                  if (v83 == NULL) {
                     v100 = v98;
                  } else 
                  if (v98 == NULL) {
                     v100 = v83;
                  }
                  else {
                     v83->last->next = v98;
                     v83->last = v98->last;
                     v100 = v83;
                  }
                  /* --------------------- v101 = v68 ++ v100 --------------------- */
                  if (v68 == NULL) {
                     v101 = v100;
                  } else 
                  if (v100 == NULL) {
                     v101 = v68;
                  }
                  else {
                     v68->last->next = v100;
                     v68->last = v100->last;
                     v101 = v68;
                  }
                  /* --------------------- v102 = v53 ++ v101 --------------------- */
                  if (v53 == NULL) {
                     v102 = v101;
                  } else 
                  if (v101 == NULL) {
                     v102 = v53;
                  }
                  else {
                     v53->last->next = v101;
                     v53->last = v101->last;
                     v102 = v53;
                  }
                  /* --------------------- v103 = v39 ++ v102 --------------------- */
                  if (v39 == NULL) {
                     v103 = v102;
                  } else 
                  if (v102 == NULL) {
                     v103 = v39;
                  }
                  else {
                     v39->last->next = v102;
                     v39->last = v102->last;
                     v103 = v39;
                  }
                  /* --------------------- v104 = v38 ++ v103 --------------------- */
                  if (v38 == NULL) {
                     v104 = v103;
                  } else 
                  if (v103 == NULL) {
                     v104 = v38;
                  }
                  else {
                     v38->last->next = v103;
                     v38->last = v103->last;
                     v104 = v38;
                  }
                  /* --------------------- v105 = v37 ++ v104 --------------------- */
                  if (v37 == NULL) {
                     v105 = v104;
                  } else 
                  if (v104 == NULL) {
                     v105 = v37;
                  }
                  else {
                     v37->last->next = v104;
                     v37->last = v104->last;
                     v105 = v37;
                  }
                  /* -------------------- v107 = minimum(v105) -------------------- */
                  v107 = 1.0e7;
                  v106 = v105;
                  while (v106 != NULL) {
                     v107 = v107 < v106->item.alg_energy ? v107 : v106->item.alg_energy;
                     v106 = v106->next;
                  }
                  v106 = v105;
                  v109 = NULL;
                  while (v106 != NULL) {
                     if (abs(v107 - v106->item.alg_energy) <= diff) {
                        update_str_Signature(v106->item.alg_enum->item, diff - abs(v107 - v106->item.alg_energy));
                        v108=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v108->item = v106->item;
                        v108->next = NULL;
                        v108->last = v108;
                        /* ----------------- v109 = v108 ++ v109 ------------------ */
                        if (v108 == NULL) {
                        } else 
                        if (v109 == NULL) {
                           v109 = v108;
                        }
                        else {
                           v108->last->next = v109;
                           v108->last = v109->last;
                           v109 = v108;
                        }
                     }
                     v106 = v106->next;
                  }
                  /* -------------------------- start of -------------------------- */
                  /*  = co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr . */
                  if ((j-lc_h_Pr-lc_k-2) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v113 = pul <<< pss <<< uregion ------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v112 = pss <<< uregion ----------------- */
                     v112=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v112->next = NULL;
                     v112->last = v112;
                     v112->item.alg_energy = sspenalty((j-lc_h_Pr-2) - (lc_k));
                     v112->item.alg_enum = new_Pss_(lc_k, j-lc_h_Pr-2);
                     /* ------------------ v112 = pss <<< uregion ----------------- */
                     /* ------------------------- finished ------------------------ */

                     v113 = NULL;
                     /* +--------------------------------------------------------------------------- */
                     /* v111 stores the result of a single application of algebra function           */
                     /* v112 holds the results of expression                                         */
                     /*      pss <<< uregion                                                         */
                     /*                                                                              */
                     /* we use v114 to iterate over v112 and                                         */
                     /* v113 to collect the results                                                  */
                     /* +--------------------------------------------------------------------------- */
                     v114 = v112;
                     while (v114 != NULL) {
                        v111=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v111->next = NULL;
                        v111->last = v111;
                        v111->item.alg_energy = v114->item.alg_energy;
                        v111->item.alg_enum = new_Pul_s(v114->item.alg_enum);
                        /* ----------------- v113 = v111 ++ v113 ------------------ */
                        if (v111 == NULL) {
                        } else 
                        if (v113 == NULL) {
                           v113 = v111;
                        }
                        else {
                           v111->last->next = v113;
                           v111->last = v113->last;
                           v113 = v111;
                        }
                        v114 = v114->next;
                     }
                     /* -------------- v113 = pul <<< pss <<< uregion ------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v115 = p comps --------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((j-lc_h_Pr-lc_k-2) >= 7) {
                        v115=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v115->item.alg_energy = tbl_comps(lc_k, j-lc_h_Pr-2);
                        v115->item.alg_enum = new__NTID(back_comps, lc_k, j-lc_h_Pr-2);
                        v115->next = NULL;
                        v115->last = v115;
                     }
                     else {
                        v115 = NULL;
                     }
                     /* -------------------- v116 = p comps_Pr -------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps_Pr is implemented as a tabulated                            */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps_Pr into a single list element.            */
                     /* +---------------------------------------------------------------------------- */
                     if ((j-lc_h_Pr-lc_k-2) >= 11) {
                        v116=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v116->item.alg_energy = tbl_comps_Pr(lc_k, j-lc_h_Pr-2);
                        v116->item.alg_enum = new__NTID(back_comps_Pr, lc_k, j-lc_h_Pr-2);
                        v116->next = NULL;
                        v116->last = v116;
                     }
                     else {
                        v116 = NULL;
                     }
                     /* ------------------- v117 = v115 ++ v116 ------------------- */
                     if (v115 == NULL) {
                        v117 = v116;
                     } else 
                     if (v116 == NULL) {
                        v117 = v115;
                     }
                     else {
                        v115->last->next = v116;
                        v115->last = v116->last;
                        v117 = v115;
                     }
                     /* ------------------- v118 = v113 ++ v117 ------------------- */
                     if (v113 == NULL) {
                        v118 = v117;
                     } else 
                     if (v117 == NULL) {
                        v118 = v113;
                     }
                     else {
                        v113->last->next = v117;
                        v113->last = v117->last;
                        v118 = v113;
                     }
                     /* ------------------- v120 = minimum(v118) ------------------ */
                     v120 = 1.0e7;
                     v119 = v118;
                     while (v119 != NULL) {
                        v120 = v120 < v119->item.alg_energy ? v120 : v119->item.alg_energy;
                        v119 = v119->next;
                     }
                     v119 = v118;
                     v122 = NULL;
                     while (v119 != NULL) {
                        if (abs(v120 - v119->item.alg_energy) <= diff) {
                           update_str_Signature(v119->item.alg_enum->item, diff - abs(v120 - v119->item.alg_energy));
                           v121=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                           v121->item = v119->item;
                           v121->next = NULL;
                           v121->last = v121;
                           /* ---------------- v122 = v121 ++ v122 ---------------- */
                           if (v121 == NULL) {
                           } else 
                           if (v122 == NULL) {
                              v122 = v121;
                           }
                           else {
                              v121->last->next = v122;
                              v121->last = v122->last;
                              v122 = v121;
                           }
                        }
                        v119 = v119->next;
                     }
                     v123 = NULL;
                     /* +--------------------------------------------------------------------------- */
                     /* v110 stores the result of a single application of algebra function           */
                     /* v122 holds the results of expression                                         */
                     /*      pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h                */
                     /*                                                                              */
                     /* we use v124 to iterate over v122 and                                         */
                     /* v123 to collect the results                                                  */
                     /* +--------------------------------------------------------------------------- */
                     v124 = v122;
                     while (v124 != NULL) {
                        v110=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v110->next = NULL;
                        v110->last = v110;
                        v110->item.alg_energy = v124->item.alg_energy;
                        v110->item.alg_enum = new_Co_s(v124->item.alg_enum);
                        /* ----------------- v123 = v110 ++ v123 ------------------ */
                        if (v110 == NULL) {
                        } else 
                        if (v123 == NULL) {
                           v123 = v110;
                        }
                        else {
                           v110->last->next = v123;
                           v110->last = v123->last;
                           v123 = v110;
                        }
                        v124 = v124->next;
                     }
                  }
                  else {
                     v123 = NULL;
                  }
                  /*  = co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr . */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v138 = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h)  */
                  if ((j-lc_h_Pr-lc_k-2) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v128 = pul <<< pss <<< uregion ------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v127 = pss <<< uregion ----------------- */
                     v127=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                     v127->next = NULL;
                     v127->last = v127;
                     v127->item.alg_energy = sspenalty((j-lc_h_Pr-2) - (lc_k+1));
                     v127->item.alg_enum = new_Pss_(lc_k+1, j-lc_h_Pr-2);
                     /* ------------------ v127 = pss <<< uregion ----------------- */
                     /* ------------------------- finished ------------------------ */

                     v128 = NULL;
                     /* +--------------------------------------------------------------------------- */
                     /* v126 stores the result of a single application of algebra function           */
                     /* v127 holds the results of expression                                         */
                     /*      pss <<< uregion                                                         */
                     /*                                                                              */
                     /* we use v129 to iterate over v127 and                                         */
                     /* v128 to collect the results                                                  */
                     /* +--------------------------------------------------------------------------- */
                     v129 = v127;
                     while (v129 != NULL) {
                        v126=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v126->next = NULL;
                        v126->last = v126;
                        v126->item.alg_energy = v129->item.alg_energy;
                        v126->item.alg_enum = new_Pul_s(v129->item.alg_enum);
                        /* ----------------- v128 = v126 ++ v128 ------------------ */
                        if (v126 == NULL) {
                        } else 
                        if (v128 == NULL) {
                           v128 = v126;
                        }
                        else {
                           v126->last->next = v128;
                           v126->last = v128->last;
                           v128 = v126;
                        }
                        v129 = v129->next;
                     }
                     /* -------------- v128 = pul <<< pss <<< uregion ------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v130 = p comps --------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((j-lc_h_Pr-lc_k-3) >= 7) {
                        v130=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v130->item.alg_energy = tbl_comps(lc_k+1, j-lc_h_Pr-2);
                        v130->item.alg_enum = new__NTID(back_comps, lc_k+1, j-lc_h_Pr-2);
                        v130->next = NULL;
                        v130->last = v130;
                     }
                     else {
                        v130 = NULL;
                     }
                     /* -------------------- v131 = p comps_Pr -------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps_Pr is implemented as a tabulated                            */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps_Pr into a single list element.            */
                     /* +---------------------------------------------------------------------------- */
                     if ((j-lc_h_Pr-lc_k-3) >= 11) {
                        v131=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v131->item.alg_energy = tbl_comps_Pr(lc_k+1, j-lc_h_Pr-2);
                        v131->item.alg_enum = new__NTID(back_comps_Pr, lc_k+1, j-lc_h_Pr-2);
                        v131->next = NULL;
                        v131->last = v131;
                     }
                     else {
                        v131 = NULL;
                     }
                     /* ------------------- v132 = v130 ++ v131 ------------------- */
                     if (v130 == NULL) {
                        v132 = v131;
                     } else 
                     if (v131 == NULL) {
                        v132 = v130;
                     }
                     else {
                        v130->last->next = v131;
                        v130->last = v131->last;
                        v132 = v130;
                     }
                     /* ------------------- v133 = v128 ++ v132 ------------------- */
                     if (v128 == NULL) {
                        v133 = v132;
                     } else 
                     if (v132 == NULL) {
                        v133 = v128;
                     }
                     else {
                        v128->last->next = v132;
                        v128->last = v132->last;
                        v133 = v128;
                     }
                     /* ------------------- v135 = minimum(v133) ------------------ */
                     v135 = 1.0e7;
                     v134 = v133;
                     while (v134 != NULL) {
                        v135 = v135 < v134->item.alg_energy ? v135 : v134->item.alg_energy;
                        v134 = v134->next;
                     }
                     v134 = v133;
                     v137 = NULL;
                     while (v134 != NULL) {
                        if (abs(v135 - v134->item.alg_energy) <= diff) {
                           update_str_Signature(v134->item.alg_enum->item, diff - abs(v135 - v134->item.alg_energy));
                           v136=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                           v136->item = v134->item;
                           v136->next = NULL;
                           v136->last = v136;
                           /* ---------------- v137 = v136 ++ v137 ---------------- */
                           if (v136 == NULL) {
                           } else 
                           if (v137 == NULL) {
                              v137 = v136;
                           }
                           else {
                              v136->last->next = v137;
                              v136->last = v137->last;
                              v137 = v136;
                           }
                        }
                        v134 = v134->next;
                     }
                     v138 = NULL;
                     /* +--------------------------------------------------------------------------- */
                     /* v125 stores the result of a single application of algebra function           */
                     /* v137 holds the results of expression                                         */
                     /*      pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h                */
                     /*                                                                              */
                     /* we use v139 to iterate over v137 and                                         */
                     /* v138 to collect the results                                                  */
                     /* +--------------------------------------------------------------------------- */
                     v139 = v137;
                     while (v139 != NULL) {
                        v125=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v125->next = NULL;
                        v125->last = v125;
                        v125->item.alg_energy = (v139->item.alg_energy + (wkn * dr_energy(i + 1, (lc_k+1) - 1))) + npp;
                        v125->item.alg_enum = new_Bkd_s(i, lc_k+1, v139->item.alg_enum);
                        /* ----------------- v138 = v125 ++ v138 ------------------ */
                        if (v125 == NULL) {
                        } else 
                        if (v138 == NULL) {
                           v138 = v125;
                        }
                        else {
                           v125->last->next = v138;
                           v125->last = v138->last;
                           v138 = v125;
                        }
                        v139 = v139->next;
                     }
                  }
                  else {
                     v138 = NULL;
                  }
                  /*  v138 = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h)  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------- v140 = v123 ++ v138 --------------------- */
                  if (v123 == NULL) {
                     v140 = v138;
                  } else 
                  if (v138 == NULL) {
                     v140 = v123;
                  }
                  else {
                     v123->last->next = v138;
                     v123->last = v138->last;
                     v140 = v123;
                  }
                  /* -------------------- v142 = minimum(v140) -------------------- */
                  v142 = 1.0e7;
                  v141 = v140;
                  while (v141 != NULL) {
                     v142 = v142 < v141->item.alg_energy ? v142 : v141->item.alg_energy;
                     v141 = v141->next;
                  }
                  v141 = v140;
                  v144 = NULL;
                  while (v141 != NULL) {
                     if (abs(v142 - v141->item.alg_energy) <= diff) {
                        update_str_Signature(v141->item.alg_enum->item, diff - abs(v142 - v141->item.alg_energy));
                        v143=(struct str5 *) myalloc(adp_dynmem, sizeof(struct str5 ));
                        v143->item = v141->item;
                        v143->next = NULL;
                        v143->last = v143;
                        /* ----------------- v144 = v143 ++ v144 ------------------ */
                        if (v143 == NULL) {
                        } else 
                        if (v144 == NULL) {
                           v144 = v143;
                        }
                        else {
                           v143->last->next = v144;
                           v143->last = v144->last;
                           v144 = v143;
                        }
                     }
                     v141 = v141->next;
                  }
                  v145 = NULL;
                  /* +---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                  /* v1 stores the result of a single application of algebra function                                                                                                        */
                  /* v36 holds the results of expression                                                                                                                                     */
                  /*      co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h ||| frd j <<< (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h) ~~~ lbase ... h           */
                  /*                                                                                                                                                                         */
                  /* we use v148 to iterate over v36 and                                                                                                                                     */
                  /* v145 to collect the results                                                                                                                                             */
                  /* +---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                  v148 = v36;
                  while (v148 != NULL) {
                     /* +--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                     /* v1 stores the result of a single application of algebra function                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 */
                     /* v109 holds the results of expression                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             */
                     /*      emptymid lc_middle_k lc_middle_l <<< empty ||| midbase lc_middle_k lc_middle_l <<< lbase ||| middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase ||| middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ||| middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase ||| middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h) ~~~ lbase ||| midregion <<< pul <<< pss <<< region ||| p comps ||| p comps_Pr ... h ... h           */
                     /*                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  */
                     /* we use v147 to iterate over v109 and                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             */
                     /* v145 to collect the results                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      */
                     /* +--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                     v147 = v109;
                     while (v147 != NULL) {
                        /* +---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                        /* v1 stores the result of a single application of algebra function                                                                                                        */
                        /* v144 holds the results of expression                                                                                                                                    */
                        /*      co <<< pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h ||| bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ||| p comps_Pr ... h) ... h           */
                        /*                                                                                                                                                                         */
                        /* we use v146 to iterate over v144 and                                                                                                                                    */
                        /* v145 to collect the results                                                                                                                                             */
                        /* +---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                        v146 = v144;
                        while (v146 != NULL) {
                           if (abs(tbl_knot(i, j).tup1 - ((((((pkinit + lc_energy) + (3 * npp)) + v148->item.alg_energy) + v147->item.alg_energy) + v146->item.alg_energy) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j))) <= diff) {
                              v1=(struct str7 *) myalloc(adp_dynmem, sizeof(struct str7 ));
                              v1->next = NULL;
                              v1->last = v1;
                              v1->item.alg_energy.tup1 = (((((pkinit + lc_energy) + (3 * npp)) + v148->item.alg_energy) + v147->item.alg_energy) + v146->item.alg_energy) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j);
                              v1->item.alg_energy.tup2 = lc_l;
                              v1->item.alg_energy.tup3 = lc_k;
                              v1->item.alg_enum = new_Pk_Pr_sss(lc_energy, i, i+lc_h, v148->item.alg_enum, lc_l, lc_l+lc_h_Pr, v147->item.alg_enum, lc_k-lc_h, lc_k, v146->item.alg_enum, j-lc_h_Pr, j);
                           }
                           else {
                              v1 = NULL;
                           }
                           /* ----------------- v145 = v1 ++ v145 ----------------- */
                           if (v1 == NULL) {
                           } else 
                           if (v145 == NULL) {
                              v145 = v1;
                           }
                           else {
                              v1->last->next = v145;
                              v1->last = v145->last;
                              v145 = v1;
                           }
                           v146 = v146->next;
                        }
                        v147 = v147->next;
                     }
                     v148 = v148->next;
                  }
               }
               else {
                  v145 = NULL;
               }
            }
            else {
               v145 = NULL;
            }
            /* ----------------------- v149 = v145 ++ v149 ------------------------ */
            if (v145 == NULL) {
            } else 
            if (v149 == NULL) {
               v149 = v145;
            }
            else {
               v145->last->next = v149;
               v145->last = v149->last;
               v149 = v145;
            }
         }
      }
   }
   else {
      v149 = NULL;
   }
   /* ------- v149 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------- v151 = minimum(v149) --------------------------- */
   v151.tup1 = 1.0e7;
   v151.tup2 = 0;
   v151.tup3 = 0;
   v150 = v149;
   while (v150 != NULL) {
      /* -------------- v151 = minimum(v151, v150->item.alg_energy) --------------- */
      v151 = v151.tup1 < v150->item.alg_energy.tup1 ? v151 : v150->item.alg_energy;
      v150 = v150->next;
   }
   v150 = v149;
   v153 = NULL;
   while (v150 != NULL) {
      if (abs(v151.tup1 - v150->item.alg_energy.tup1) <= diff) {
         update_str_Signature(v150->item.alg_enum->item, diff - abs(v151.tup1 - v150->item.alg_energy.tup1));
         v152=(struct str7 *) myalloc(adp_dynmem, sizeof(struct str7 ));
         v152->item = v150->item;
         v152->next = NULL;
         v152->last = v152;
         /* ------------------------- v153 = v152 ++ v153 ------------------------- */
         if (v152 == NULL) {
         } else 
         if (v153 == NULL) {
            v153 = v152;
         }
         else {
            v152->last->next = v153;
            v152->last = v153->last;
            v153 = v152;
         }
      }
      v150 = v150->next;
   }
   /* ------------------------- build candidate structures ------------------------ */
   v154 = v153;
   v155 = NULL;
   while (v154 != NULL) {
      /* ------------------- v155 = v154->item.alg_enum ++ v155 ------------------- */
      if (v154->item.alg_enum == NULL) {
      } else 
      if (v155 == NULL) {
         v155 = v154->item.alg_enum;
      }
      else {
         v154->item.alg_enum->last->next = v155;
         v154->item.alg_enum->last = v155->last;
         v155 = v154->item.alg_enum;
      }
      v154 = v154->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v155)));
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

int main_pk_enf_so(toptions *_opts, tsequence *_seq)
{
   opts = _opts;
   seq  = _seq;
   z    = _seq->seq - 1;
   n    = _seq->length;

   if (opts->debug) printf("pk-enf-so.c\n");

   adplib_init(opts,seq,&z,&n);
   result_prettyprint = (char *) myalloc(adp_statmem, 30*n*sizeof(char));
   traceback_diff = opts->traceback_diff * 100;
   rnalib_init(opts,seq);
   if (opts->window_mode) rna_output_descr(opts,seq);
   mainloop();
   freeall();
}


