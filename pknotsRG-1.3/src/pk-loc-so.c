/* ---------------------------------------------------------------------------
pknotsRG 1.3
Copyright (C) 2004-2006 Jens Reeder, Robert Giegerich, Peter Steffen
--------------------------------------------------------------------------- */
/* compiled by the ADP compiler, version 0.8 (rev 690)    Tue Sep 12 13:30:08 MEST 2006 */
/* source file: pknotsRG-loc.lhs                                                    */
/* command:                                                                         */
/* adpcompile -c pknotsRG-loc.lhs -al energy enum -cs energy -alpp pp -O -lcf -ta bto -bt so -gc cc -iuc -W */
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
#define SIGID_Mldl 9
#define SIGID_Mldr 10
#define SIGID_Mldlr 11
#define SIGID_Dl 12
#define SIGID_Dr 13
#define SIGID_Dlr 14
#define SIGID_Drem 15
#define SIGID_Cons 16
#define SIGID_Ul 17
#define SIGID_Pul 18
#define SIGID_Addss 19
#define SIGID_Ssadd 20
#define SIGID_Combine 21
#define SIGID_Sum 22
#define SIGID_Sumend 23
#define SIGID_Co 24
#define SIGID_Pkmldl 25
#define SIGID_Pkmldr 26
#define SIGID_Pkmldlr 27
#define SIGID_Pkml 28
#define SIGID_Pk_Pr 29
#define SIGID_Frd 30
#define SIGID_Bkd 31
#define SIGID_Scale 32
#define SIGID_Unscale 33
#define SIGID_Emptymid 34
#define SIGID_Midbase 35
#define SIGID_Middlro 36
#define SIGID_Middl 37
#define SIGID_Middr 38
#define SIGID_Middlr 39
#define SIGID_Midregion 40
#define SIGID_Pss 41
#define SIGID_Skipleft 42
#define SIGID_Skipright 43

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

/* operator Mldl                                                                    */
/* -------------------------------------------------------------------------------- */

struct str_Mldl {
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
};


static struct str4 *new_Mldl_s(int a1, int a2, int a3, struct str4 *structure4, int a5, int a6)
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
   struct str4 *structure3;
   struct str4 *a3;
   struct str4 *pp_init_a3;
   struct str4 *(*f3)(int , int , int );
   int i3, j3;
   int diff3;
   int a4;
   int a5;
   int a6;
};


static struct str4 *new_Mldr_s(int a1, int a2, struct str4 *structure3, int a4, int a5, int a6)
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
   struct str4 *structure4;
   struct str4 *a4;
   struct str4 *pp_init_a4;
   struct str4 *(*f4)(int , int , int );
   int i4, j4;
   int diff4;
   int a5;
   int a6;
   int a7;
};


static struct str4 *new_Mldlr_s(int a1, int a2, int a3, struct str4 *structure4, int a5, int a6, int a7)
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
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
};


static struct str4 *new_Dl_s(int a1, struct str4 *structure2, int a3)
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
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
};


static struct str4 *new_Dr_s(int a1, struct str4 *structure2, int a3)
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
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
};


static struct str4 *new_Dlr_s(int a1, struct str4 *structure2, int a3)
{
   struct str_Dlr *t;

   t=(struct str_Dlr *) myalloc(adp_dynmem, sizeof(struct str_Dlr ));
   t->a1 = a1;
   t->isStructure2 = 1;
   t->structure2 = structure2;
   t->a3 = a3;
   return(new_Signature(SIGID_Dlr, t));
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

/* operator Co                                                                      */
/* -------------------------------------------------------------------------------- */

struct str_Co {
   int isStructure1;
   struct str4 *structure1;
   struct str4 *a1;
   struct str4 *pp_init_a1;
   struct str4 *(*f1)(int , int , int );
   int i1, j1;
   int diff1;
};


static struct str4 *new_Co_s(struct str4 *structure1)
{
   struct str_Co *t;

   t=(struct str_Co *) myalloc(adp_dynmem, sizeof(struct str_Co ));
   t->isStructure1 = 1;
   t->structure1 = structure1;
   return(new_Signature(SIGID_Co, t));
}

/* operator Pkmldl                                                                  */
/* -------------------------------------------------------------------------------- */

struct str_Pkmldl {
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

static struct str4 *new_Pkmldl_f(int a1, struct str4 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4)
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

static struct str4 *new_Pkmldr_f(struct str4 *(*f1)(int , int , int ), int i1, int j1, int a2, int a3, int a4)
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

static struct str4 *new_Pkmldlr_f(int a1, struct str4 *(*f2)(int , int , int ), int i2, int j2, int a3, int a4, int a5)
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

/* operator Frd                                                                     */
/* -------------------------------------------------------------------------------- */

struct str_Frd {
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


static struct str4 *new_Frd_s(int a1, struct str4 *structure2, int a3)
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
   struct str4 *structure3;
   struct str4 *a3;
   struct str4 *pp_init_a3;
   struct str4 *(*f3)(int , int , int );
   int i3, j3;
   int diff3;
};


static struct str4 *new_Bkd_s(int a1, int a2, struct str4 *structure3)
{
   struct str_Bkd *t;

   t=(struct str_Bkd *) myalloc(adp_dynmem, sizeof(struct str_Bkd ));
   t->a1 = a1;
   t->a2 = a2;
   t->isStructure3 = 1;
   t->structure3 = structure3;
   return(new_Signature(SIGID_Bkd, t));
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

/* operator Middlro                                                                 */
/* -------------------------------------------------------------------------------- */

struct str_Middlro {
   int a1;
   int a2;
   int a3;
   int a4;
   int diff;
};

static struct str4 *new_Middlro_(int a1, int a2, int a3, int a4)
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
   struct str4 *structure3;
   struct str4 *a3;
   struct str4 *pp_init_a3;
   struct str4 *(*f3)(int , int , int );
   int i3, j3;
   int diff3;
};


static struct str4 *new_Middl_s(int a1, int a2, struct str4 *structure3)
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
   struct str4 *structure2;
   struct str4 *a2;
   struct str4 *pp_init_a2;
   struct str4 *(*f2)(int , int , int );
   int i2, j2;
   int diff2;
   int a3;
};


static struct str4 *new_Middr_s(int a1, struct str4 *structure2, int a3)
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
   struct str4 *structure4;
   struct str4 *a4;
   struct str4 *pp_init_a4;
   struct str4 *(*f4)(int , int , int );
   int i4, j4;
   int diff4;
   int a5;
};


static struct str4 *new_Middlr_s(int a1, int a2, int a3, struct str4 *structure4, int a5)
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
      if (id == SIGID_Co) {
         nstr->item->entry=(struct str_Co *) malloc(sizeof(struct str_Co ));
         (*((struct str_Co *)(nstr->item->entry))) = (*((struct str_Co *)entr));
         if (((struct str_Co *)(nstr->item->entry))->isStructure1) {
            ((struct str_Co *)(nstr->item->entry))->structure1 = copy_str_Signature(((struct str_Co *)entr)->structure1);
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
      if (c->utype == SIGID_Co) {
         if (((struct str_Co *)(c->entry))->isStructure1) {
            update_str_Signature(((struct str_Co *)(c->entry))->structure1->item, diff);
         }
         else {
            ((struct str_Co *)(c->entry))->diff1 = diff;
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
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;
   int v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22;
   int v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34;
   int k;

   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /*  v1 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s  */
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
      /*  v1 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v25 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s)  */
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
      /*  v25 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s)  */
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
      tbl_block(i, j) = v34;
   }
}

/* table calculation for production knot                                            */
/* -------------------------------------------------------------------------------- */
static void calc_knot(int i, int j)
{
   int v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13;
   int v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26;
   int v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39;
   int v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52;
   struct str2 v1, v53;
   int lc_alphanrg, lc_betalen, lc_betanrg, lc_correctionterm, lc_energy;
   int lc_h, lc_h_Pr, lc_k, lc_l, lc_middle_k, lc_middle_l;

   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      /* -------------------------------- start of -------------------------------- */
      /* ----- v53 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
      v53.tup1 = 1.0e7;
      v53.tup2 = 0;
      v53.tup3 = 0;
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
                  /* -- v2 = co <<< pul <<< pss <<< uregion ||| p comps ... h_l --- */
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
                     v6 = v3 < v5 ? v3 : v5;
                     v2 = v6;
                  }
                  else {
                     v2 = 1.0e7;
                  }
                  /* -- v2 = co <<< pul <<< pss <<< uregion ||| p comps ... h_l --- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  frd j <<< (pul <<< pss <<< uregion ||| p comps ... h_l) ~~~ l */
                  if ((lc_l-(i+lc_h)-1) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v8 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v9 = pss <<< uregion ------------------ */
                     v9 = sspenalty((lc_l-1) - (i+lc_h+1));
                     /* ------------------- v9 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v8 = v9;
                     /* --------------- v8 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v10 = p comps ---------------------- */
                     if ((lc_l-(i+lc_h)-2) >= 7) {
                        v10 = tbl_comps(i+lc_h+1, lc_l-1);
                     }
                     else {
                        v10 = 1.0e7;
                     }
                     v11 = v8 < v10 ? v8 : v10;
                     v7 = (v11 + (wkn * dl_energy((lc_l) + 1, j))) + npp;
                  }
                  else {
                     v7 = 1.0e7;
                  }
                  /*  frd j <<< (pul <<< pss <<< uregion ||| p comps ... h_l) ~~~ l */
                  /* -------------------------- finished -------------------------- */

                  v12 = v2 < v7 ? v2 : v7;
                  /* -------------------------- start of -------------------------- */
                  /* ------ v13 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 0) {
                     v13 = wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, lc_l+lc_h_Pr, (lc_l+lc_h_Pr) + 1);
                  }
                  else {
                     v13 = 1.0e7;
                  }
                  /* ------ v13 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* ------ v14 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 1) {
                     v14 = (wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, (lc_k-lc_h) - 1, (lc_k-lc_h) + 1)) + npp;
                  }
                  else {
                     v14 = 1.0e7;
                  }
                  /* ------ v14 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* - v15 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 2) {
                     v15 = (2 * npp) + (wkn * (dri_energy(lc_middle_l, (lc_l+lc_h_Pr+1) + 2) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                  }
                  else {
                     v15 = 1.0e7;
                  }
                  /* - v15 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v16 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l)  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v17 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v18 = pss <<< region ------------------ */
                     v18 = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr+1));
                     /* ------------------- v18 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v17 = v18;
                     /* --------------- v17 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v19 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v19 = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h);
                     }
                     else {
                        v19 = 1.0e7;
                     }
                     v20 = v17 < v19 ? v17 : v19;
                     v16 = (v20 + npp) + (wkn * dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1));
                  }
                  else {
                     v16 = 1.0e7;
                  }
                  /*  v16 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l)  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v21 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v22 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v23 = pss <<< region ------------------ */
                     v23 = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr));
                     /* ------------------- v23 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v22 = v23;
                     /* --------------- v22 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v24 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v24 = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h-1);
                     }
                     else {
                        v24 = 1.0e7;
                     }
                     v25 = v22 < v24 ? v22 : v24;
                     v21 = (v25 + npp) + (wkn * dri_energy(lc_middle_l, (lc_k-lc_h) + 1));
                  }
                  else {
                     v21 = 1.0e7;
                  }
                  /*  v21 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v26 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 3) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v27 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v28 = pss <<< region ------------------ */
                     v28 = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr+1));
                     /* ------------------- v28 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v27 = v28;
                     /* --------------- v27 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v29 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-2) >= 7) {
                        v29 = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                     }
                     else {
                        v29 = 1.0e7;
                     }
                     v30 = v27 < v29 ? v27 : v29;
                     v26 = (v30 + (2 * npp)) + (wkn * (dri_energy(lc_middle_l, (lc_k-lc_h) + 1) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                  }
                  else {
                     v26 = 1.0e7;
                  }
                  /*  v26 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* v31 = midregion <<< pul <<< pss <<< region ||| p comps ... h_l */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v32 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v33 = pss <<< region ------------------ */
                     v33 = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr));
                     /* ------------------- v33 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v32 = v33;
                     /* --------------- v32 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v34 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 7) {
                        v34 = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h);
                     }
                     else {
                        v34 = 1.0e7;
                     }
                     v35 = v32 < v34 ? v32 : v34;
                     v31 = v35;
                  }
                  else {
                     v31 = 1.0e7;
                  }
                  /* v31 = midregion <<< pul <<< pss <<< region ||| p comps ... h_l */
                  /* -------------------------- finished -------------------------- */

                  v36 = v26 < v31 ? v26 : v31;
                  v37 = v21 < v36 ? v21 : v36;
                  v38 = v16 < v37 ? v16 : v37;
                  v39 = v15 < v38 ? v15 : v38;
                  v40 = v14 < v39 ? v14 : v39;
                  v41 = v13 < v40 ? v13 : v40;
                  /* -------------------------- start of -------------------------- */
                  /* -- v42 = co <<< pul <<< pss <<< uregion ||| p comps ... h_l -- */
                  if ((j-lc_h_Pr-lc_k-2) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v43 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v44 = pss <<< uregion ------------------ */
                     v44 = sspenalty((j-lc_h_Pr-2) - (lc_k));
                     /* ------------------ v44 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v43 = v44;
                     /* -------------- v43 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v45 = p comps ---------------------- */
                     if ((j-lc_h_Pr-lc_k-2) >= 7) {
                        v45 = tbl_comps(lc_k, j-lc_h_Pr-2);
                     }
                     else {
                        v45 = 1.0e7;
                     }
                     v46 = v43 < v45 ? v43 : v45;
                     v42 = v46;
                  }
                  else {
                     v42 = 1.0e7;
                  }
                  /* -- v42 = co <<< pul <<< pss <<< uregion ||| p comps ... h_l -- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ...  */
                  if ((j-lc_h_Pr-lc_k-2) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v48 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v49 = pss <<< uregion ------------------ */
                     v49 = sspenalty((j-lc_h_Pr-2) - (lc_k+1));
                     /* ------------------ v49 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v48 = v49;
                     /* -------------- v48 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v50 = p comps ---------------------- */
                     if ((j-lc_h_Pr-lc_k-3) >= 7) {
                        v50 = tbl_comps(lc_k+1, j-lc_h_Pr-2);
                     }
                     else {
                        v50 = 1.0e7;
                     }
                     v51 = v48 < v50 ? v48 : v50;
                     v47 = (v51 + (wkn * dr_energy(i + 1, (lc_k+1) - 1))) + npp;
                  }
                  else {
                     v47 = 1.0e7;
                  }
                  /*  bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ...  */
                  /* -------------------------- finished -------------------------- */

                  v52 = v42 < v47 ? v42 : v47;
                  v1.tup1 = (((((pkinit + lc_energy) + (3 * npp)) + v12) + v41) + v52) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j);
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
            /* ---------------------- v53 = minimum(v1, v53) ---------------------- */
            v53 = v1.tup1 < v53.tup1 ? v1 : v53;
         }
      }
      /* ----- v53 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
      /* -------------------------------- finished -------------------------------- */

      /* ----------------------- assign table entry result ------------------------ */
      tbl_knot(i, j) = v53;
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
   struct str4 *v67;
   int v10, v19, v25, v53, v63;
   struct str6 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v11, *v12, *v13;
   struct str6 *v14, *v15, *v16, *v17, *v18, *v20;
   struct str6 *v21, *v22, *v23, *v24, *v26, *v27;
   struct str6 *v28, *v29, *v30, *v31, *v32, *v33;
   struct str6 *v34, *v35, *v36, *v37, *v38, *v39;
   struct str6 *v40, *v41, *v42, *v43, *v44, *v45;
   struct str6 *v46, *v47, *v48, *v49, *v50, *v51;
   struct str6 *v52, *v54, *v55, *v56, *v57, *v58;
   struct str6 *v59, *v60, *v61, *v62, *v64, *v65, *v66;
   int k, k2, k3, k4, k5, k6, k7, k8;

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
         /*  v31 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 19) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v30 = combine <<< p block ~~~ p comps --------------- */
            v30 = NULL;
            for (k5=i+10; k5<=j-9; k5++) {
               if (abs(tbl_closed(i, j) - ((((380 + (tbl_block(i+3, k5) + tbl_comps(k5, j-2))) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1))) <= diff) {
                  v29=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v28=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v34=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v33=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v39=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v38=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v44=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v43=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v54=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
         v64=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
   struct str4 *v68;
   int v22, v48, v64;
   struct str6 *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10, *v11, *v12;
   struct str6 *v13, *v14, *v15, *v16, *v17, *v18;
   struct str6 *v19, *v20, *v21, *v23, *v24, *v25, *v26;
   struct str6 *v27, *v28, *v29, *v30, *v31, *v32;
   struct str6 *v33, *v34, *v35, *v36, *v37, *v38, *v39;
   struct str6 *v40, *v41, *v42, *v43, *v44, *v45;
   struct str6 *v46, *v47, *v49, *v50, *v51, *v52, *v53;
   struct str6 *v54, *v55, *v56, *v57, *v58, *v59;
   struct str6 *v60, *v61, *v62, *v63, *v65, *v66, *v67;
   int k;

   /* ---------------------------------- start of --------------------------------- */
   /*  v25 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s  */
   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ---- v4 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ----- */
      if ((j-i) >= 8) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------------- v3 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         if (abs(tbl_block(i, j) - (40 + ((tbl_closed(i+1, j) + termaupenalty((i+1) + 1, j)) + dl_energy((i+1) + 1, j)))) <= diff) {
            v3=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
               v2=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v7=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
               v6=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v11=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
               v10=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
         v15=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v14=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v23=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
      /* +-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
      /* v1 stores the result of a single application of algebra function                                                                                                                                                                                                */
      /* v24 holds the results of expression                                                                                                                                                                                                                             */
      /*      dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s           */
      /*                                                                                                                                                                                                                                                                 */
      /* we use v26 to iterate over v24 and                                                                                                                                                                                                                              */
      /* v25 to collect the results                                                                                                                                                                                                                                      */
      /* +-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
      v26 = v24;
      while (v26 != NULL) {
         if (abs(tbl_block(i, j) - (40 + v26->item.alg_energy)) <= diff) {
            v1=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
   /*  v25 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s  */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /*  v53 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s)  */
   if ((j-i) >= 8) {
      v53 = NULL;
      for (k=i+1; k<=j-7; k++) {
         /* ------------------------------- start of ------------------------------ */
         /* --- v30 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc -- */
         if ((j-k) >= 8) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v29 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            if (abs(tbl_block(i, j) - ((40 + ((tbl_closed(k+1, j) + termaupenalty((k+1) + 1, j)) + dl_energy((k+1) + 1, j))) + ss_energy(i, k))) <= diff) {
               v29=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v28=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
               v33=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v32=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
               v37=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                  v36=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
            v41=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
               v40=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
               v49=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
         /* +-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
         /* v27 stores the result of a single application of algebra function                                                                                                                                                                                               */
         /* v50 holds the results of expression                                                                                                                                                                                                                             */
         /*      dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s           */
         /*                                                                                                                                                                                                                                                                 */
         /* we use v52 to iterate over v50 and                                                                                                                                                                                                                              */
         /* v51 to collect the results                                                                                                                                                                                                                                      */
         /* +-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
         v52 = v50;
         while (v52 != NULL) {
            if (abs(tbl_block(i, j) - ((40 + v52->item.alg_energy) + ss_energy(i, k))) <= diff) {
               v27=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
   /*  v53 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h_s)  */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v54 = pkmldl <<< lbase ~~~ p knot --------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      if (abs(tbl_block(i, j) - ((tbl_knot(i+1, j).tup1 + 600) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3)))) <= diff) {
         v54=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
      if (abs(tbl_block(i, j) - ((tbl_knot(i, j-1).tup1 + 600) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1)))) <= diff) {
         v55=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
      if (abs(tbl_block(i, j) - ((tbl_knot(i+1, j-1).tup1 + 600) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1))))) <= diff) {
         v56=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
      if (abs(tbl_block(i, j) - (tbl_knot(i, j).tup1 + 600)) <= diff) {
         v57=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
         v65=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
static struct str4 *back_knot(int i, int j, int diff)
{
   struct str4 *v139;
   struct str2 v135;
   int v10, v23, v30, v44, v57, v70, v83, v95, v106, v119, v126;
   struct str6 *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v11, *v12, *v13;
   struct str6 *v14, *v15, *v16, *v17, *v18, *v19;
   struct str6 *v20, *v21, *v22, *v24, *v25, *v26;
   struct str6 *v27, *v28, *v29, *v31, *v32, *v33;
   struct str6 *v34, *v35, *v36, *v37, *v38, *v39;
   struct str6 *v40, *v41, *v42, *v43, *v45, *v46;
   struct str6 *v47, *v48, *v49, *v50, *v51, *v52;
   struct str6 *v53, *v54, *v55, *v56, *v58, *v59;
   struct str6 *v60, *v61, *v62, *v63, *v64, *v65;
   struct str6 *v66, *v67, *v68, *v69, *v71, *v72;
   struct str6 *v73, *v74, *v75, *v76, *v77, *v78;
   struct str6 *v79, *v80, *v81, *v82, *v84, *v85;
   struct str6 *v86, *v87, *v88, *v89, *v90, *v91;
   struct str6 *v92, *v93, *v94, *v96, *v97, *v98;
   struct str6 *v99, *v100, *v101, *v102, *v103, *v104;
   struct str6 *v105, *v107, *v108, *v109, *v110, *v111;
   struct str6 *v112, *v113, *v114, *v115, *v116, *v117;
   struct str6 *v118, *v120, *v121, *v122, *v123, *v124;
   struct str6 *v125, *v127, *v128, *v130, *v131, *v132;
   struct str10 *v1, *v129, *v133, *v134, *v136, *v137, *v138;
   int lc_alphanrg, lc_betalen, lc_betanrg, lc_correctionterm, lc_energy;
   int lc_h, lc_h_Pr, lc_k, lc_l, lc_middle_k, lc_middle_l;

   /* ---------------------------------- start of --------------------------------- */
   /* ------- v133 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
   if ((j-i) >= 0) {
      v133 = NULL;
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
                  /* -- v13 = co <<< pul <<< pss <<< uregion ||| p comps ... h_l -- */
                  if ((lc_l-(i+lc_h)-1) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v5 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v4 = pss <<< uregion ------------------ */
                     v4=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                        v3=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                        v7=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v7->item.alg_energy = tbl_comps(i+lc_h+1, lc_l);
                        v7->item.alg_enum = new__NTID(back_comps, i+lc_h+1, lc_l);
                        v7->next = NULL;
                        v7->last = v7;
                     }
                     else {
                        v7 = NULL;
                     }
                     /* ---------------------- v8 = v5 ++ v7 ---------------------- */
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
                     /* -------------------- v10 = minimum(v8) -------------------- */
                     v10 = 1.0e7;
                     v9 = v8;
                     while (v9 != NULL) {
                        v10 = v10 < v9->item.alg_energy ? v10 : v9->item.alg_energy;
                        v9 = v9->next;
                     }
                     v9 = v8;
                     v12 = NULL;
                     while (v9 != NULL) {
                        if (abs(v10 - v9->item.alg_energy) <= whichDiff(diff)) {
                           update_str_Signature(v9->item.alg_enum->item, diff - abs(v10 - v9->item.alg_energy));
                           v11=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                           v11->item = v9->item;
                           v11->next = NULL;
                           v11->last = v11;
                           /* ------------------ v12 = v11 ++ v12 ----------------- */
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
                     v13 = NULL;
                     /* +------------------------------------------------------------------------- */
                     /* v2 stores the result of a single application of algebra function           */
                     /* v12 holds the results of expression                                        */
                     /*      pul <<< pss <<< uregion ||| p comps ... h_l                           */
                     /*                                                                            */
                     /* we use v14 to iterate over v12 and                                         */
                     /* v13 to collect the results                                                 */
                     /* +------------------------------------------------------------------------- */
                     v14 = v12;
                     while (v14 != NULL) {
                        v2=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v2->next = NULL;
                        v2->last = v2;
                        v2->item.alg_energy = v14->item.alg_energy;
                        v2->item.alg_enum = new_Co_s(v14->item.alg_enum);
                        /* ------------------- v13 = v2 ++ v13 -------------------- */
                        if (v2 == NULL) {
                        } else 
                        if (v13 == NULL) {
                           v13 = v2;
                        }
                        else {
                           v2->last->next = v13;
                           v2->last = v13->last;
                           v13 = v2;
                        }
                        v14 = v14->next;
                     }
                  }
                  else {
                     v13 = NULL;
                  }
                  /* -- v13 = co <<< pul <<< pss <<< uregion ||| p comps ... h_l -- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  frd j <<< (pul <<< pss <<< uregion ||| p comps ... h_l) ~~~ l */
                  if ((lc_l-(i+lc_h)-1) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v18 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v17 = pss <<< uregion ------------------ */
                     v17=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v17->next = NULL;
                     v17->last = v17;
                     v17->item.alg_energy = sspenalty((lc_l-1) - (i+lc_h+1));
                     v17->item.alg_enum = new_Pss_(i+lc_h+1, lc_l-1);
                     /* ------------------ v17 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v18 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v16 stores the result of a single application of algebra function           */
                     /* v17 holds the results of expression                                         */
                     /*      pss <<< uregion                                                        */
                     /*                                                                             */
                     /* we use v19 to iterate over v17 and                                          */
                     /* v18 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v19 = v17;
                     while (v19 != NULL) {
                        v16=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v16->next = NULL;
                        v16->last = v16;
                        v16->item.alg_energy = v19->item.alg_energy;
                        v16->item.alg_enum = new_Pul_s(v19->item.alg_enum);
                        /* ------------------- v18 = v16 ++ v18 ------------------- */
                        if (v16 == NULL) {
                        } else 
                        if (v18 == NULL) {
                           v18 = v16;
                        }
                        else {
                           v16->last->next = v18;
                           v16->last = v18->last;
                           v18 = v16;
                        }
                        v19 = v19->next;
                     }
                     /* -------------- v18 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v20 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_l-(i+lc_h)-2) >= 7) {
                        v20=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v20->item.alg_energy = tbl_comps(i+lc_h+1, lc_l-1);
                        v20->item.alg_enum = new__NTID(back_comps, i+lc_h+1, lc_l-1);
                        v20->next = NULL;
                        v20->last = v20;
                     }
                     else {
                        v20 = NULL;
                     }
                     /* --------------------- v21 = v18 ++ v20 -------------------- */
                     if (v18 == NULL) {
                        v21 = v20;
                     } else 
                     if (v20 == NULL) {
                        v21 = v18;
                     }
                     else {
                        v18->last->next = v20;
                        v18->last = v20->last;
                        v21 = v18;
                     }
                     /* -------------------- v23 = minimum(v21) ------------------- */
                     v23 = 1.0e7;
                     v22 = v21;
                     while (v22 != NULL) {
                        v23 = v23 < v22->item.alg_energy ? v23 : v22->item.alg_energy;
                        v22 = v22->next;
                     }
                     v22 = v21;
                     v25 = NULL;
                     while (v22 != NULL) {
                        if (abs(v23 - v22->item.alg_energy) <= whichDiff(diff)) {
                           update_str_Signature(v22->item.alg_enum->item, diff - abs(v23 - v22->item.alg_energy));
                           v24=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                           v24->item = v22->item;
                           v24->next = NULL;
                           v24->last = v24;
                           /* ------------------ v25 = v24 ++ v25 ----------------- */
                           if (v24 == NULL) {
                           } else 
                           if (v25 == NULL) {
                              v25 = v24;
                           }
                           else {
                              v24->last->next = v25;
                              v24->last = v25->last;
                              v25 = v24;
                           }
                        }
                        v22 = v22->next;
                     }
                     v26 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v15 stores the result of a single application of algebra function           */
                     /* v25 holds the results of expression                                         */
                     /*      pul <<< pss <<< uregion ||| p comps ... h_l                            */
                     /*                                                                             */
                     /* we use v27 to iterate over v25 and                                          */
                     /* v26 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v27 = v25;
                     while (v27 != NULL) {
                        v15=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v15->next = NULL;
                        v15->last = v15;
                        v15->item.alg_energy = (v27->item.alg_energy + (wkn * dl_energy((lc_l) + 1, j))) + npp;
                        v15->item.alg_enum = new_Frd_s(j, v27->item.alg_enum, lc_l);
                        /* ------------------- v26 = v15 ++ v26 ------------------- */
                        if (v15 == NULL) {
                        } else 
                        if (v26 == NULL) {
                           v26 = v15;
                        }
                        else {
                           v15->last->next = v26;
                           v15->last = v26->last;
                           v26 = v15;
                        }
                        v27 = v27->next;
                     }
                  }
                  else {
                     v26 = NULL;
                  }
                  /*  frd j <<< (pul <<< pss <<< uregion ||| p comps ... h_l) ~~~ l */
                  /* -------------------------- finished -------------------------- */

                  /* ---------------------- v28 = v13 ++ v26 ---------------------- */
                  if (v13 == NULL) {
                     v28 = v26;
                  } else 
                  if (v26 == NULL) {
                     v28 = v13;
                  }
                  else {
                     v13->last->next = v26;
                     v13->last = v26->last;
                     v28 = v13;
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
                  /* ------ v33 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 0) {
                     v33=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v33->next = NULL;
                     v33->last = v33;
                     v33->item.alg_energy = wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, lc_l+lc_h_Pr, (lc_l+lc_h_Pr) + 1);
                     v33->item.alg_enum = new_Emptymid_(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr);
                  }
                  else {
                     v33 = NULL;
                  }
                  /* ------ v33 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* ------ v34 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 1) {
                     v34=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v34->next = NULL;
                     v34->last = v34;
                     v34->item.alg_energy = (wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, (lc_k-lc_h) - 1, (lc_k-lc_h) + 1)) + npp;
                     v34->item.alg_enum = new_Midbase_(lc_middle_k, lc_middle_l, lc_k-lc_h);
                  }
                  else {
                     v34 = NULL;
                  }
                  /* ------ v34 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* - v35 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 2) {
                     v35=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v35->next = NULL;
                     v35->last = v35;
                     v35->item.alg_energy = (2 * npp) + (wkn * (dri_energy(lc_middle_l, (lc_l+lc_h_Pr+1) + 2) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                     v35->item.alg_enum = new_Middlro_(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr+1, lc_k-lc_h);
                  }
                  else {
                     v35 = NULL;
                  }
                  /* - v35 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v47 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l)  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v39 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v38 = pss <<< region ------------------ */
                     v38=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v38->next = NULL;
                     v38->last = v38;
                     v38->item.alg_energy = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr+1));
                     v38->item.alg_enum = new_Pss_(lc_l+lc_h_Pr+1, lc_k-lc_h);
                     /* ------------------- v38 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v39 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v37 stores the result of a single application of algebra function           */
                     /* v38 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v40 to iterate over v38 and                                          */
                     /* v39 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v40 = v38;
                     while (v40 != NULL) {
                        v37=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
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
                     /* --------------- v39 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v41 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v41=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v41->item.alg_energy = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h);
                        v41->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr+1, lc_k-lc_h);
                        v41->next = NULL;
                        v41->last = v41;
                     }
                     else {
                        v41 = NULL;
                     }
                     /* --------------------- v42 = v39 ++ v41 -------------------- */
                     if (v39 == NULL) {
                        v42 = v41;
                     } else 
                     if (v41 == NULL) {
                        v42 = v39;
                     }
                     else {
                        v39->last->next = v41;
                        v39->last = v41->last;
                        v42 = v39;
                     }
                     /* -------------------- v44 = minimum(v42) ------------------- */
                     v44 = 1.0e7;
                     v43 = v42;
                     while (v43 != NULL) {
                        v44 = v44 < v43->item.alg_energy ? v44 : v43->item.alg_energy;
                        v43 = v43->next;
                     }
                     v43 = v42;
                     v46 = NULL;
                     while (v43 != NULL) {
                        if (abs(v44 - v43->item.alg_energy) <= whichDiff(diff)) {
                           update_str_Signature(v43->item.alg_enum->item, diff - abs(v44 - v43->item.alg_energy));
                           v45=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                           v45->item = v43->item;
                           v45->next = NULL;
                           v45->last = v45;
                           /* ------------------ v46 = v45 ++ v46 ----------------- */
                           if (v45 == NULL) {
                           } else 
                           if (v46 == NULL) {
                              v46 = v45;
                           }
                           else {
                              v45->last->next = v46;
                              v45->last = v46->last;
                              v46 = v45;
                           }
                        }
                        v43 = v43->next;
                     }
                     v47 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v36 stores the result of a single application of algebra function           */
                     /* v46 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ... h_l                             */
                     /*                                                                             */
                     /* we use v48 to iterate over v46 and                                          */
                     /* v47 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v48 = v46;
                     while (v48 != NULL) {
                        v36=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v36->next = NULL;
                        v36->last = v36;
                        v36->item.alg_energy = (v48->item.alg_energy + npp) + (wkn * dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1));
                        v36->item.alg_enum = new_Middl_s(lc_middle_k, lc_l+lc_h_Pr+1, v48->item.alg_enum);
                        /* ------------------- v47 = v36 ++ v47 ------------------- */
                        if (v36 == NULL) {
                        } else 
                        if (v47 == NULL) {
                           v47 = v36;
                        }
                        else {
                           v36->last->next = v47;
                           v36->last = v47->last;
                           v47 = v36;
                        }
                        v48 = v48->next;
                     }
                  }
                  else {
                     v47 = NULL;
                  }
                  /*  v47 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l)  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v60 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v52 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v51 = pss <<< region ------------------ */
                     v51=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v51->next = NULL;
                     v51->last = v51;
                     v51->item.alg_energy = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr));
                     v51->item.alg_enum = new_Pss_(lc_l+lc_h_Pr, lc_k-lc_h-1);
                     /* ------------------- v51 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v52 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v50 stores the result of a single application of algebra function           */
                     /* v51 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v53 to iterate over v51 and                                          */
                     /* v52 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v53 = v51;
                     while (v53 != NULL) {
                        v50=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v50->next = NULL;
                        v50->last = v50;
                        v50->item.alg_energy = v53->item.alg_energy;
                        v50->item.alg_enum = new_Pul_s(v53->item.alg_enum);
                        /* ------------------- v52 = v50 ++ v52 ------------------- */
                        if (v50 == NULL) {
                        } else 
                        if (v52 == NULL) {
                           v52 = v50;
                        }
                        else {
                           v50->last->next = v52;
                           v50->last = v52->last;
                           v52 = v50;
                        }
                        v53 = v53->next;
                     }
                     /* --------------- v52 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v54 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v54=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v54->item.alg_energy = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h-1);
                        v54->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr, lc_k-lc_h-1);
                        v54->next = NULL;
                        v54->last = v54;
                     }
                     else {
                        v54 = NULL;
                     }
                     /* --------------------- v55 = v52 ++ v54 -------------------- */
                     if (v52 == NULL) {
                        v55 = v54;
                     } else 
                     if (v54 == NULL) {
                        v55 = v52;
                     }
                     else {
                        v52->last->next = v54;
                        v52->last = v54->last;
                        v55 = v52;
                     }
                     /* -------------------- v57 = minimum(v55) ------------------- */
                     v57 = 1.0e7;
                     v56 = v55;
                     while (v56 != NULL) {
                        v57 = v57 < v56->item.alg_energy ? v57 : v56->item.alg_energy;
                        v56 = v56->next;
                     }
                     v56 = v55;
                     v59 = NULL;
                     while (v56 != NULL) {
                        if (abs(v57 - v56->item.alg_energy) <= whichDiff(diff)) {
                           update_str_Signature(v56->item.alg_enum->item, diff - abs(v57 - v56->item.alg_energy));
                           v58=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                           v58->item = v56->item;
                           v58->next = NULL;
                           v58->last = v58;
                           /* ------------------ v59 = v58 ++ v59 ----------------- */
                           if (v58 == NULL) {
                           } else 
                           if (v59 == NULL) {
                              v59 = v58;
                           }
                           else {
                              v58->last->next = v59;
                              v58->last = v59->last;
                              v59 = v58;
                           }
                        }
                        v56 = v56->next;
                     }
                     v60 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v49 stores the result of a single application of algebra function           */
                     /* v59 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ... h_l                             */
                     /*                                                                             */
                     /* we use v61 to iterate over v59 and                                          */
                     /* v60 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v61 = v59;
                     while (v61 != NULL) {
                        v49=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v49->next = NULL;
                        v49->last = v49;
                        v49->item.alg_energy = (v61->item.alg_energy + npp) + (wkn * dri_energy(lc_middle_l, (lc_k-lc_h) + 1));
                        v49->item.alg_enum = new_Middr_s(lc_middle_l, v61->item.alg_enum, lc_k-lc_h);
                        /* ------------------- v60 = v49 ++ v60 ------------------- */
                        if (v49 == NULL) {
                        } else 
                        if (v60 == NULL) {
                           v60 = v49;
                        }
                        else {
                           v49->last->next = v60;
                           v49->last = v60->last;
                           v60 = v49;
                        }
                        v61 = v61->next;
                     }
                  }
                  else {
                     v60 = NULL;
                  }
                  /*  v60 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v73 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 3) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v65 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v64 = pss <<< region ------------------ */
                     v64=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v64->next = NULL;
                     v64->last = v64;
                     v64->item.alg_energy = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr+1));
                     v64->item.alg_enum = new_Pss_(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                     /* ------------------- v64 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v65 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v63 stores the result of a single application of algebra function           */
                     /* v64 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v66 to iterate over v64 and                                          */
                     /* v65 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v66 = v64;
                     while (v66 != NULL) {
                        v63=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v63->next = NULL;
                        v63->last = v63;
                        v63->item.alg_energy = v66->item.alg_energy;
                        v63->item.alg_enum = new_Pul_s(v66->item.alg_enum);
                        /* ------------------- v65 = v63 ++ v65 ------------------- */
                        if (v63 == NULL) {
                        } else 
                        if (v65 == NULL) {
                           v65 = v63;
                        }
                        else {
                           v63->last->next = v65;
                           v63->last = v65->last;
                           v65 = v63;
                        }
                        v66 = v66->next;
                     }
                     /* --------------- v65 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v67 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-2) >= 7) {
                        v67=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v67->item.alg_energy = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                        v67->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                        v67->next = NULL;
                        v67->last = v67;
                     }
                     else {
                        v67 = NULL;
                     }
                     /* --------------------- v68 = v65 ++ v67 -------------------- */
                     if (v65 == NULL) {
                        v68 = v67;
                     } else 
                     if (v67 == NULL) {
                        v68 = v65;
                     }
                     else {
                        v65->last->next = v67;
                        v65->last = v67->last;
                        v68 = v65;
                     }
                     /* -------------------- v70 = minimum(v68) ------------------- */
                     v70 = 1.0e7;
                     v69 = v68;
                     while (v69 != NULL) {
                        v70 = v70 < v69->item.alg_energy ? v70 : v69->item.alg_energy;
                        v69 = v69->next;
                     }
                     v69 = v68;
                     v72 = NULL;
                     while (v69 != NULL) {
                        if (abs(v70 - v69->item.alg_energy) <= whichDiff(diff)) {
                           update_str_Signature(v69->item.alg_enum->item, diff - abs(v70 - v69->item.alg_energy));
                           v71=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                           v71->item = v69->item;
                           v71->next = NULL;
                           v71->last = v71;
                           /* ------------------ v72 = v71 ++ v72 ----------------- */
                           if (v71 == NULL) {
                           } else 
                           if (v72 == NULL) {
                              v72 = v71;
                           }
                           else {
                              v71->last->next = v72;
                              v71->last = v72->last;
                              v72 = v71;
                           }
                        }
                        v69 = v69->next;
                     }
                     v73 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v62 stores the result of a single application of algebra function           */
                     /* v72 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ... h_l                             */
                     /*                                                                             */
                     /* we use v74 to iterate over v72 and                                          */
                     /* v73 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v74 = v72;
                     while (v74 != NULL) {
                        v62=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v62->next = NULL;
                        v62->last = v62;
                        v62->item.alg_energy = (v74->item.alg_energy + (2 * npp)) + (wkn * (dri_energy(lc_middle_l, (lc_k-lc_h) + 1) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                        v62->item.alg_enum = new_Middlr_s(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr+1, v74->item.alg_enum, lc_k-lc_h);
                        /* ------------------- v73 = v62 ++ v73 ------------------- */
                        if (v62 == NULL) {
                        } else 
                        if (v73 == NULL) {
                           v73 = v62;
                        }
                        else {
                           v62->last->next = v73;
                           v62->last = v73->last;
                           v73 = v62;
                        }
                        v74 = v74->next;
                     }
                  }
                  else {
                     v73 = NULL;
                  }
                  /*  v73 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* v86 = midregion <<< pul <<< pss <<< region ||| p comps ... h_l */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v78 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v77 = pss <<< region ------------------ */
                     v77=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v77->next = NULL;
                     v77->last = v77;
                     v77->item.alg_energy = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr));
                     v77->item.alg_enum = new_Pss_(lc_l+lc_h_Pr, lc_k-lc_h);
                     /* ------------------- v77 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v78 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v76 stores the result of a single application of algebra function           */
                     /* v77 holds the results of expression                                         */
                     /*      pss <<< region                                                         */
                     /*                                                                             */
                     /* we use v79 to iterate over v77 and                                          */
                     /* v78 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v79 = v77;
                     while (v79 != NULL) {
                        v76=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v76->next = NULL;
                        v76->last = v76;
                        v76->item.alg_energy = v79->item.alg_energy;
                        v76->item.alg_enum = new_Pul_s(v79->item.alg_enum);
                        /* ------------------- v78 = v76 ++ v78 ------------------- */
                        if (v76 == NULL) {
                        } else 
                        if (v78 == NULL) {
                           v78 = v76;
                        }
                        else {
                           v76->last->next = v78;
                           v76->last = v78->last;
                           v78 = v76;
                        }
                        v79 = v79->next;
                     }
                     /* --------------- v78 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v80 = p comps ---------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 7) {
                        v80=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v80->item.alg_energy = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h);
                        v80->item.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr, lc_k-lc_h);
                        v80->next = NULL;
                        v80->last = v80;
                     }
                     else {
                        v80 = NULL;
                     }
                     /* --------------------- v81 = v78 ++ v80 -------------------- */
                     if (v78 == NULL) {
                        v81 = v80;
                     } else 
                     if (v80 == NULL) {
                        v81 = v78;
                     }
                     else {
                        v78->last->next = v80;
                        v78->last = v80->last;
                        v81 = v78;
                     }
                     /* -------------------- v83 = minimum(v81) ------------------- */
                     v83 = 1.0e7;
                     v82 = v81;
                     while (v82 != NULL) {
                        v83 = v83 < v82->item.alg_energy ? v83 : v82->item.alg_energy;
                        v82 = v82->next;
                     }
                     v82 = v81;
                     v85 = NULL;
                     while (v82 != NULL) {
                        if (abs(v83 - v82->item.alg_energy) <= whichDiff(diff)) {
                           update_str_Signature(v82->item.alg_enum->item, diff - abs(v83 - v82->item.alg_energy));
                           v84=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                           v84->item = v82->item;
                           v84->next = NULL;
                           v84->last = v84;
                           /* ------------------ v85 = v84 ++ v85 ----------------- */
                           if (v84 == NULL) {
                           } else 
                           if (v85 == NULL) {
                              v85 = v84;
                           }
                           else {
                              v84->last->next = v85;
                              v84->last = v85->last;
                              v85 = v84;
                           }
                        }
                        v82 = v82->next;
                     }
                     v86 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v75 stores the result of a single application of algebra function           */
                     /* v85 holds the results of expression                                         */
                     /*      pul <<< pss <<< region ||| p comps ... h_l                             */
                     /*                                                                             */
                     /* we use v87 to iterate over v85 and                                          */
                     /* v86 to collect the results                                                  */
                     /* +-------------------------------------------------------------------------- */
                     v87 = v85;
                     while (v87 != NULL) {
                        v75=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v75->next = NULL;
                        v75->last = v75;
                        v75->item.alg_energy = v87->item.alg_energy;
                        v75->item.alg_enum = new_Midregion_s(v87->item.alg_enum);
                        /* ------------------- v86 = v75 ++ v86 ------------------- */
                        if (v75 == NULL) {
                        } else 
                        if (v86 == NULL) {
                           v86 = v75;
                        }
                        else {
                           v75->last->next = v86;
                           v75->last = v86->last;
                           v86 = v75;
                        }
                        v87 = v87->next;
                     }
                  }
                  else {
                     v86 = NULL;
                  }
                  /* v86 = midregion <<< pul <<< pss <<< region ||| p comps ... h_l */
                  /* -------------------------- finished -------------------------- */

                  /* ---------------------- v88 = v73 ++ v86 ---------------------- */
                  if (v73 == NULL) {
                     v88 = v86;
                  } else 
                  if (v86 == NULL) {
                     v88 = v73;
                  }
                  else {
                     v73->last->next = v86;
                     v73->last = v86->last;
                     v88 = v73;
                  }
                  /* ---------------------- v89 = v60 ++ v88 ---------------------- */
                  if (v60 == NULL) {
                     v89 = v88;
                  } else 
                  if (v88 == NULL) {
                     v89 = v60;
                  }
                  else {
                     v60->last->next = v88;
                     v60->last = v88->last;
                     v89 = v60;
                  }
                  /* ---------------------- v90 = v47 ++ v89 ---------------------- */
                  if (v47 == NULL) {
                     v90 = v89;
                  } else 
                  if (v89 == NULL) {
                     v90 = v47;
                  }
                  else {
                     v47->last->next = v89;
                     v47->last = v89->last;
                     v90 = v47;
                  }
                  /* ---------------------- v91 = v35 ++ v90 ---------------------- */
                  if (v35 == NULL) {
                     v91 = v90;
                  } else 
                  if (v90 == NULL) {
                     v91 = v35;
                  }
                  else {
                     v35->last->next = v90;
                     v35->last = v90->last;
                     v91 = v35;
                  }
                  /* ---------------------- v92 = v34 ++ v91 ---------------------- */
                  if (v34 == NULL) {
                     v92 = v91;
                  } else 
                  if (v91 == NULL) {
                     v92 = v34;
                  }
                  else {
                     v34->last->next = v91;
                     v34->last = v91->last;
                     v92 = v34;
                  }
                  /* ---------------------- v93 = v33 ++ v92 ---------------------- */
                  if (v33 == NULL) {
                     v93 = v92;
                  } else 
                  if (v92 == NULL) {
                     v93 = v33;
                  }
                  else {
                     v33->last->next = v92;
                     v33->last = v92->last;
                     v93 = v33;
                  }
                  /* --------------------- v95 = minimum(v93) --------------------- */
                  v95 = 1.0e7;
                  v94 = v93;
                  while (v94 != NULL) {
                     v95 = v95 < v94->item.alg_energy ? v95 : v94->item.alg_energy;
                     v94 = v94->next;
                  }
                  v94 = v93;
                  v97 = NULL;
                  while (v94 != NULL) {
                     if (abs(v95 - v94->item.alg_energy) <= whichDiff(diff)) {
                        update_str_Signature(v94->item.alg_enum->item, diff - abs(v95 - v94->item.alg_energy));
                        v96=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v96->item = v94->item;
                        v96->next = NULL;
                        v96->last = v96;
                        /* ------------------- v97 = v96 ++ v97 ------------------- */
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
                  /* -------------------------- start of -------------------------- */
                  /* - v109 = co <<< pul <<< pss <<< uregion ||| p comps ... h_l -- */
                  if ((j-lc_h_Pr-lc_k-2) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v101 = pul <<< pss <<< uregion ------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v100 = pss <<< uregion ----------------- */
                     v100=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v100->next = NULL;
                     v100->last = v100;
                     v100->item.alg_energy = sspenalty((j-lc_h_Pr-2) - (lc_k));
                     v100->item.alg_enum = new_Pss_(lc_k, j-lc_h_Pr-2);
                     /* ------------------ v100 = pss <<< uregion ----------------- */
                     /* ------------------------- finished ------------------------ */

                     v101 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v99 stores the result of a single application of algebra function           */
                     /* v100 holds the results of expression                                        */
                     /*      pss <<< uregion                                                        */
                     /*                                                                             */
                     /* we use v102 to iterate over v100 and                                        */
                     /* v101 to collect the results                                                 */
                     /* +-------------------------------------------------------------------------- */
                     v102 = v100;
                     while (v102 != NULL) {
                        v99=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v99->next = NULL;
                        v99->last = v99;
                        v99->item.alg_energy = v102->item.alg_energy;
                        v99->item.alg_enum = new_Pul_s(v102->item.alg_enum);
                        /* ------------------ v101 = v99 ++ v101 ------------------ */
                        if (v99 == NULL) {
                        } else 
                        if (v101 == NULL) {
                           v101 = v99;
                        }
                        else {
                           v99->last->next = v101;
                           v99->last = v101->last;
                           v101 = v99;
                        }
                        v102 = v102->next;
                     }
                     /* -------------- v101 = pul <<< pss <<< uregion ------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v103 = p comps --------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((j-lc_h_Pr-lc_k-2) >= 7) {
                        v103=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v103->item.alg_energy = tbl_comps(lc_k, j-lc_h_Pr-2);
                        v103->item.alg_enum = new__NTID(back_comps, lc_k, j-lc_h_Pr-2);
                        v103->next = NULL;
                        v103->last = v103;
                     }
                     else {
                        v103 = NULL;
                     }
                     /* ------------------- v104 = v101 ++ v103 ------------------- */
                     if (v101 == NULL) {
                        v104 = v103;
                     } else 
                     if (v103 == NULL) {
                        v104 = v101;
                     }
                     else {
                        v101->last->next = v103;
                        v101->last = v103->last;
                        v104 = v101;
                     }
                     /* ------------------- v106 = minimum(v104) ------------------ */
                     v106 = 1.0e7;
                     v105 = v104;
                     while (v105 != NULL) {
                        v106 = v106 < v105->item.alg_energy ? v106 : v105->item.alg_energy;
                        v105 = v105->next;
                     }
                     v105 = v104;
                     v108 = NULL;
                     while (v105 != NULL) {
                        if (abs(v106 - v105->item.alg_energy) <= whichDiff(diff)) {
                           update_str_Signature(v105->item.alg_enum->item, diff - abs(v106 - v105->item.alg_energy));
                           v107=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                           v107->item = v105->item;
                           v107->next = NULL;
                           v107->last = v107;
                           /* ---------------- v108 = v107 ++ v108 ---------------- */
                           if (v107 == NULL) {
                           } else 
                           if (v108 == NULL) {
                              v108 = v107;
                           }
                           else {
                              v107->last->next = v108;
                              v107->last = v108->last;
                              v108 = v107;
                           }
                        }
                        v105 = v105->next;
                     }
                     v109 = NULL;
                     /* +-------------------------------------------------------------------------- */
                     /* v98 stores the result of a single application of algebra function           */
                     /* v108 holds the results of expression                                        */
                     /*      pul <<< pss <<< uregion ||| p comps ... h_l                            */
                     /*                                                                             */
                     /* we use v110 to iterate over v108 and                                        */
                     /* v109 to collect the results                                                 */
                     /* +-------------------------------------------------------------------------- */
                     v110 = v108;
                     while (v110 != NULL) {
                        v98=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v98->next = NULL;
                        v98->last = v98;
                        v98->item.alg_energy = v110->item.alg_energy;
                        v98->item.alg_enum = new_Co_s(v110->item.alg_enum);
                        /* ------------------ v109 = v98 ++ v109 ------------------ */
                        if (v98 == NULL) {
                        } else 
                        if (v109 == NULL) {
                           v109 = v98;
                        }
                        else {
                           v98->last->next = v109;
                           v98->last = v109->last;
                           v109 = v98;
                        }
                        v110 = v110->next;
                     }
                  }
                  else {
                     v109 = NULL;
                  }
                  /* - v109 = co <<< pul <<< pss <<< uregion ||| p comps ... h_l -- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ... */
                  if ((j-lc_h_Pr-lc_k-2) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v114 = pul <<< pss <<< uregion ------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v113 = pss <<< uregion ----------------- */
                     v113=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                     v113->next = NULL;
                     v113->last = v113;
                     v113->item.alg_energy = sspenalty((j-lc_h_Pr-2) - (lc_k+1));
                     v113->item.alg_enum = new_Pss_(lc_k+1, j-lc_h_Pr-2);
                     /* ------------------ v113 = pss <<< uregion ----------------- */
                     /* ------------------------- finished ------------------------ */

                     v114 = NULL;
                     /* +--------------------------------------------------------------------------- */
                     /* v112 stores the result of a single application of algebra function           */
                     /* v113 holds the results of expression                                         */
                     /*      pss <<< uregion                                                         */
                     /*                                                                              */
                     /* we use v115 to iterate over v113 and                                         */
                     /* v114 to collect the results                                                  */
                     /* +--------------------------------------------------------------------------- */
                     v115 = v113;
                     while (v115 != NULL) {
                        v112=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v112->next = NULL;
                        v112->last = v112;
                        v112->item.alg_energy = v115->item.alg_energy;
                        v112->item.alg_enum = new_Pul_s(v115->item.alg_enum);
                        /* ----------------- v114 = v112 ++ v114 ------------------ */
                        if (v112 == NULL) {
                        } else 
                        if (v114 == NULL) {
                           v114 = v112;
                        }
                        else {
                           v112->last->next = v114;
                           v112->last = v114->last;
                           v114 = v112;
                        }
                        v115 = v115->next;
                     }
                     /* -------------- v114 = pul <<< pss <<< uregion ------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v116 = p comps --------------------- */
                     /* +---------------------------------------------------------------------------- */
                     /* Nonterminal comps is implemented as a tabulated                               */
                     /* function which yields atomar results. Since we are in list context,           */
                     /* we need to wrap the result of comps into a single list element.               */
                     /* +---------------------------------------------------------------------------- */
                     if ((j-lc_h_Pr-lc_k-3) >= 7) {
                        v116=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v116->item.alg_energy = tbl_comps(lc_k+1, j-lc_h_Pr-2);
                        v116->item.alg_enum = new__NTID(back_comps, lc_k+1, j-lc_h_Pr-2);
                        v116->next = NULL;
                        v116->last = v116;
                     }
                     else {
                        v116 = NULL;
                     }
                     /* ------------------- v117 = v114 ++ v116 ------------------- */
                     if (v114 == NULL) {
                        v117 = v116;
                     } else 
                     if (v116 == NULL) {
                        v117 = v114;
                     }
                     else {
                        v114->last->next = v116;
                        v114->last = v116->last;
                        v117 = v114;
                     }
                     /* ------------------- v119 = minimum(v117) ------------------ */
                     v119 = 1.0e7;
                     v118 = v117;
                     while (v118 != NULL) {
                        v119 = v119 < v118->item.alg_energy ? v119 : v118->item.alg_energy;
                        v118 = v118->next;
                     }
                     v118 = v117;
                     v121 = NULL;
                     while (v118 != NULL) {
                        if (abs(v119 - v118->item.alg_energy) <= whichDiff(diff)) {
                           update_str_Signature(v118->item.alg_enum->item, diff - abs(v119 - v118->item.alg_energy));
                           v120=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                           v120->item = v118->item;
                           v120->next = NULL;
                           v120->last = v120;
                           /* ---------------- v121 = v120 ++ v121 ---------------- */
                           if (v120 == NULL) {
                           } else 
                           if (v121 == NULL) {
                              v121 = v120;
                           }
                           else {
                              v120->last->next = v121;
                              v120->last = v121->last;
                              v121 = v120;
                           }
                        }
                        v118 = v118->next;
                     }
                     v122 = NULL;
                     /* +--------------------------------------------------------------------------- */
                     /* v111 stores the result of a single application of algebra function           */
                     /* v121 holds the results of expression                                         */
                     /*      pul <<< pss <<< uregion ||| p comps ... h_l                             */
                     /*                                                                              */
                     /* we use v123 to iterate over v121 and                                         */
                     /* v122 to collect the results                                                  */
                     /* +--------------------------------------------------------------------------- */
                     v123 = v121;
                     while (v123 != NULL) {
                        v111=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v111->next = NULL;
                        v111->last = v111;
                        v111->item.alg_energy = (v123->item.alg_energy + (wkn * dr_energy(i + 1, (lc_k+1) - 1))) + npp;
                        v111->item.alg_enum = new_Bkd_s(i, lc_k+1, v123->item.alg_enum);
                        /* ----------------- v122 = v111 ++ v122 ------------------ */
                        if (v111 == NULL) {
                        } else 
                        if (v122 == NULL) {
                           v122 = v111;
                        }
                        else {
                           v111->last->next = v122;
                           v111->last = v122->last;
                           v122 = v111;
                        }
                        v123 = v123->next;
                     }
                  }
                  else {
                     v122 = NULL;
                  }
                  /* = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ... */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------- v124 = v109 ++ v122 --------------------- */
                  if (v109 == NULL) {
                     v124 = v122;
                  } else 
                  if (v122 == NULL) {
                     v124 = v109;
                  }
                  else {
                     v109->last->next = v122;
                     v109->last = v122->last;
                     v124 = v109;
                  }
                  /* -------------------- v126 = minimum(v124) -------------------- */
                  v126 = 1.0e7;
                  v125 = v124;
                  while (v125 != NULL) {
                     v126 = v126 < v125->item.alg_energy ? v126 : v125->item.alg_energy;
                     v125 = v125->next;
                  }
                  v125 = v124;
                  v128 = NULL;
                  while (v125 != NULL) {
                     if (abs(v126 - v125->item.alg_energy) <= whichDiff(diff)) {
                        update_str_Signature(v125->item.alg_enum->item, diff - abs(v126 - v125->item.alg_energy));
                        v127=(struct str6 *) myalloc(adp_dynmem, sizeof(struct str6 ));
                        v127->item = v125->item;
                        v127->next = NULL;
                        v127->last = v127;
                        /* ----------------- v128 = v127 ++ v128 ------------------ */
                        if (v127 == NULL) {
                        } else 
                        if (v128 == NULL) {
                           v128 = v127;
                        }
                        else {
                           v127->last->next = v128;
                           v127->last = v128->last;
                           v128 = v127;
                        }
                     }
                     v125 = v125->next;
                  }
                  v129 = NULL;
                  /* +---------------------------------------------------------------------------------------------------------------------------------------------- */
                  /* v1 stores the result of a single application of algebra function                                                                                */
                  /* v32 holds the results of expression                                                                                                             */
                  /*      co <<< pul <<< pss <<< uregion ||| p comps ... h_l ||| frd j <<< (pul <<< pss <<< uregion ||| p comps ... h_l) ~~~ lbase ... h_l           */
                  /*                                                                                                                                                 */
                  /* we use v132 to iterate over v32 and                                                                                                             */
                  /* v129 to collect the results                                                                                                                     */
                  /* +---------------------------------------------------------------------------------------------------------------------------------------------- */
                  v132 = v32;
                  while (v132 != NULL) {
                     /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                     /* v1 stores the result of a single application of algebra function                                                                                                                                                                                                                                                                                                                                                                                                                                               */
                     /* v97 holds the results of expression                                                                                                                                                                                                                                                                                                                                                                                                                                                                            */
                     /*      emptymid lc_middle_k lc_middle_l <<< empty ||| midbase lc_middle_k lc_middle_l <<< lbase ||| middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase ||| middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l) ||| middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase ||| middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h_l) ~~~ lbase ||| midregion <<< pul <<< pss <<< region ||| p comps ... h_l ... h_l           */
                     /*                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                */
                     /* we use v131 to iterate over v97 and                                                                                                                                                                                                                                                                                                                                                                                                                                                                            */
                     /* v129 to collect the results                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    */
                     /* +------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
                     v131 = v97;
                     while (v131 != NULL) {
                        /* +---------------------------------------------------------------------------------------------------------------------------------------------- */
                        /* v1 stores the result of a single application of algebra function                                                                                */
                        /* v128 holds the results of expression                                                                                                            */
                        /*      co <<< pul <<< pss <<< uregion ||| p comps ... h_l ||| bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ... h_l) ... h_l           */
                        /*                                                                                                                                                 */
                        /* we use v130 to iterate over v128 and                                                                                                            */
                        /* v129 to collect the results                                                                                                                     */
                        /* +---------------------------------------------------------------------------------------------------------------------------------------------- */
                        v130 = v128;
                        while (v130 != NULL) {
                           if (abs(tbl_knot(i, j).tup1 - ((((((pkinit + lc_energy) + (3 * npp)) + v132->item.alg_energy) + v131->item.alg_energy) + v130->item.alg_energy) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j))) <= diff) {
                              v1=(struct str10 *) myalloc(adp_dynmem, sizeof(struct str10 ));
                              v1->next = NULL;
                              v1->last = v1;
                              v1->item.alg_energy.tup1 = (((((pkinit + lc_energy) + (3 * npp)) + v132->item.alg_energy) + v131->item.alg_energy) + v130->item.alg_energy) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j);
                              v1->item.alg_energy.tup2 = lc_l;
                              v1->item.alg_energy.tup3 = lc_k;
                              v1->item.alg_enum = new_Pk_Pr_sss(lc_energy, i, i+lc_h, v132->item.alg_enum, lc_l, lc_l+lc_h_Pr, v131->item.alg_enum, lc_k-lc_h, lc_k, v130->item.alg_enum, j-lc_h_Pr, j);
                           }
                           else {
                              v1 = NULL;
                           }
                           /* ----------------- v129 = v1 ++ v129 ----------------- */
                           if (v1 == NULL) {
                           } else 
                           if (v129 == NULL) {
                              v129 = v1;
                           }
                           else {
                              v1->last->next = v129;
                              v1->last = v129->last;
                              v129 = v1;
                           }
                           v130 = v130->next;
                        }
                        v131 = v131->next;
                     }
                     v132 = v132->next;
                  }
               }
               else {
                  v129 = NULL;
               }
            }
            else {
               v129 = NULL;
            }
            /* ----------------------- v133 = v129 ++ v133 ------------------------ */
            if (v129 == NULL) {
            } else 
            if (v133 == NULL) {
               v133 = v129;
            }
            else {
               v129->last->next = v133;
               v129->last = v133->last;
               v133 = v129;
            }
         }
      }
   }
   else {
      v133 = NULL;
   }
   /* ------- v133 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------ */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------- v135 = minimum(v133) --------------------------- */
   v135.tup1 = 1.0e7;
   v135.tup2 = 0;
   v135.tup3 = 0;
   v134 = v133;
   while (v134 != NULL) {
      /* -------------- v135 = minimum(v135, v134->item.alg_energy) --------------- */
      v135 = v135.tup1 < v134->item.alg_energy.tup1 ? v135 : v134->item.alg_energy;
      v134 = v134->next;
   }
   v134 = v133;
   v137 = NULL;
   while (v134 != NULL) {
      if (abs(v135.tup1 - v134->item.alg_energy.tup1) <= diff) {
         update_str_Signature(v134->item.alg_enum->item, diff - abs(v135.tup1 - v134->item.alg_energy.tup1));
         v136=(struct str10 *) myalloc(adp_dynmem, sizeof(struct str10 ));
         v136->item = v134->item;
         v136->next = NULL;
         v136->last = v136;
         /* ------------------------- v137 = v136 ++ v137 ------------------------- */
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
   /* ------------------------- build candidate structures ------------------------ */
   v138 = v137;
   v139 = NULL;
   while (v138 != NULL) {
      /* ------------------- v139 = v138->item.alg_enum ++ v139 ------------------- */
      if (v138->item.alg_enum == NULL) {
      } else 
      if (v139 == NULL) {
         v139 = v138->item.alg_enum;
      }
      else {
         v138->item.alg_enum->last->next = v139;
         v138->item.alg_enum->last = v139->last;
         v139 = v138->item.alg_enum;
      }
      v138 = v138->next;
   }
   memory_clear(adp_dynmem);
   return(build_str_Signature(copy_str_Signature(v139)));
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

int main_pk_loc_so(toptions *_opts, tsequence *_seq)
{
   opts = _opts;
   seq  = _seq;
   z    = _seq->seq - 1;
   n    = _seq->length;

   if (opts->debug) printf("pk-loc-so.c\n");
   pksOnly = opts->pksOnly;

   adplib_init(opts,seq,&z,&n);
   result_prettyprint = (char *) myalloc(adp_statmem, 30*n*sizeof(char));
   traceback_diff = opts->traceback_diff * 100;
   rnalib_init(opts,seq);
   rna_output_descr(opts,seq);
   mainloop();
   freeall();
}


