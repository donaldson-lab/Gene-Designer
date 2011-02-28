/* ---------------------------------------------------------------------------
pknotsRG 1.3
Copyright (C) 2004-2006 Jens Reeder, Robert Giegerich, Peter Steffen
--------------------------------------------------------------------------- */
/* compiled by the ADP compiler, version 0.8 (rev 690)    Tue Sep 12 13:32:13 MEST 2006 */
/* source file: pknotsRG-mfe.lhs                                                    */
/* command:                                                                         */
/* adpcompile -c pknotsRG-mfe.lhs -al energy enum -cs energy -alpp pp -O -lcf -ta bto -bt s -gc cc -iuc -W */
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
   int alg_energy;
   struct str_Signature *alg_enum;
};
struct str4 {
   struct str1 alg_energy;
   struct str_Signature *alg_enum;
};
struct str5 {
   struct str2 alg_energy;
   struct str_Signature *alg_enum;
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
};

static struct str_Signature *new_Signature(int u, void *entry)
{
   struct str_Signature *t;

   t=(struct str_Signature *) myalloc(adp_dynmem, sizeof(struct str_Signature ));
   t->utype = u;
   t->entry = entry;
   return(t);
}

/* signature operators                                                              */
/* -------------------------------------------------------------------------------- */
/* operator _NTID                                                                   */
/* -------------------------------------------------------------------------------- */

struct str__NTID {
   int isStructure1;
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
};

static struct str_Signature *new__NTID(struct str_Signature *(*f1)(int , int ), int i1, int j1)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
};

static struct str_Signature *new_Sadd_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
   int isStructure2;
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
};

static struct str_Signature *new_Cadd_ff(struct str_Signature *(*f1)(int , int ), int i1, int j1, struct str_Signature *(*f2)(int , int ), int i2, int j2)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};

static struct str_Signature *new_Is_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};

static struct str_Signature *new_Sr_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3)
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
};

static struct str_Signature *new_Hl_(int a1, int a2, int a3, int a4, int a5, int a6)
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
   struct str_Signature *structure5;
   struct str_Signature *a5;
   struct str_Signature *(*f5)(int , int );
   int i5, j5;
   int a6;
   int a7;
};


static struct str_Signature *new_Bl_s(int a1, int a2, int a3, int a4, struct str_Signature *structure5, int a6, int a7)
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
   struct str_Signature *structure3;
   struct str_Signature *a3;
   struct str_Signature *(*f3)(int , int );
   int i3, j3;
   int a4;
   int a5;
   int a6;
   int a7;
};


static struct str_Signature *new_Br_s(int a1, int a2, struct str_Signature *structure3, int a4, int a5, int a6, int a7)
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
   struct str_Signature *structure5;
   struct str_Signature *a5;
   struct str_Signature *(*f5)(int , int );
   int i5, j5;
   int a6;
   int a7;
   int a8;
   int a9;
};

static struct str_Signature *new_Il_f(int a1, int a2, int a3, int a4, struct str_Signature *(*f5)(int , int ), int i5, int j5, int a6, int a7, int a8, int a9)
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
   struct str_Signature *structure3;
   struct str_Signature *a3;
   struct str_Signature *(*f3)(int , int );
   int i3, j3;
   int a4;
   int a5;
};


static struct str_Signature *new_Ml_s(int a1, int a2, struct str_Signature *structure3, int a4, int a5)
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
   struct str_Signature *structure4;
   struct str_Signature *a4;
   struct str_Signature *(*f4)(int , int );
   int i4, j4;
   int a5;
   int a6;
};


static struct str_Signature *new_Mldl_s(int a1, int a2, int a3, struct str_Signature *structure4, int a5, int a6)
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
   struct str_Signature *structure3;
   struct str_Signature *a3;
   struct str_Signature *(*f3)(int , int );
   int i3, j3;
   int a4;
   int a5;
   int a6;
};


static struct str_Signature *new_Mldr_s(int a1, int a2, struct str_Signature *structure3, int a4, int a5, int a6)
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
   struct str_Signature *structure4;
   struct str_Signature *a4;
   struct str_Signature *(*f4)(int , int );
   int i4, j4;
   int a5;
   int a6;
   int a7;
};


static struct str_Signature *new_Mldlr_s(int a1, int a2, int a3, struct str_Signature *structure4, int a5, int a6, int a7)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};


static struct str_Signature *new_Dl_s(int a1, struct str_Signature *structure2, int a3)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};


static struct str_Signature *new_Dr_s(int a1, struct str_Signature *structure2, int a3)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};


static struct str_Signature *new_Dlr_s(int a1, struct str_Signature *structure2, int a3)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};

static struct str_Signature *new_Edl_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};

static struct str_Signature *new_Edr_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};

static struct str_Signature *new_Edlr_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
};


static struct str_Signature *new_Drem_s(struct str_Signature *structure1)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
   int isStructure2;
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
};

static struct str_Signature *new_Cons_ff(struct str_Signature *(*f1)(int , int ), int i1, int j1, struct str_Signature *(*f2)(int , int ), int i2, int j2)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
};


static struct str_Signature *new_Ul_s(struct str_Signature *structure1)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
};


static struct str_Signature *new_Pul_s(struct str_Signature *structure1)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
   int a2;
   int a3;
};

static struct str_Signature *new_Addss_f(struct str_Signature *(*f1)(int , int ), int i1, int j1, int a2, int a3)
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
   struct str_Signature *structure3;
   struct str_Signature *a3;
   struct str_Signature *(*f3)(int , int );
   int i3, j3;
};


static struct str_Signature *new_Ssadd_s(int a1, int a2, struct str_Signature *structure3)
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
};

static struct str_Signature *new_Nil_(int a1)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
   int isStructure2;
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
};

static struct str_Signature *new_Combine_ff(struct str_Signature *(*f1)(int , int ), int i1, int j1, struct str_Signature *(*f2)(int , int ), int i2, int j2)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
   int a4;
};

static struct str_Signature *new_Sum_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3, int a4)
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
};

static struct str_Signature *new_Sumend_(int a1, int a2, int a3, int a4)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
};


static struct str_Signature *new_Co_s(struct str_Signature *structure1)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
   int a2;
   int a3;
};

static struct str_Signature *new_Pk_f(struct str_Signature *(*f1)(int , int ), int i1, int j1, int a2, int a3)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
   int a4;
};

static struct str_Signature *new_Pkmldl_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3, int a4)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
   int a2;
   int a3;
   int a4;
};

static struct str_Signature *new_Pkmldr_f(struct str_Signature *(*f1)(int , int ), int i1, int j1, int a2, int a3, int a4)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
   int a4;
   int a5;
};

static struct str_Signature *new_Pkmldlr_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3, int a4, int a5)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
   int a2;
   int a3;
};

static struct str_Signature *new_Pkml_f(struct str_Signature *(*f1)(int , int ), int i1, int j1, int a2, int a3)
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
   struct str_Signature *structure4;
   struct str_Signature *a4;
   struct str_Signature *(*f4)(int , int );
   int i4, j4;
   int a5;
   int a6;
   int isStructure7;
   struct str_Signature *structure7;
   struct str_Signature *a7;
   struct str_Signature *(*f7)(int , int );
   int i7, j7;
   int a8;
   int a9;
   int isStructure10;
   struct str_Signature *structure10;
   struct str_Signature *a10;
   struct str_Signature *(*f10)(int , int );
   int i10, j10;
   int a11;
   int a12;
};








static struct str_Signature *new_Pk_Pr_sss(int a1, int a2, int a3, struct str_Signature *structure4, int a5, int a6, struct str_Signature *structure7, int a8, int a9, struct str_Signature *structure10, int a11, int a12)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
   int a4;
};

static struct str_Signature *new_Kndl_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3, int a4)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
   int a2;
   int a3;
   int a4;
};

static struct str_Signature *new_Kndr_f(struct str_Signature *(*f1)(int , int ), int i1, int j1, int a2, int a3, int a4)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
   int a4;
   int a5;
};

static struct str_Signature *new_Kndlr_f(int a1, struct str_Signature *(*f2)(int , int ), int i2, int j2, int a3, int a4, int a5)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};


static struct str_Signature *new_Frd_s(int a1, struct str_Signature *structure2, int a3)
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
   struct str_Signature *structure3;
   struct str_Signature *a3;
   struct str_Signature *(*f3)(int , int );
   int i3, j3;
};


static struct str_Signature *new_Bkd_s(int a1, int a2, struct str_Signature *structure3)
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
};

static struct str_Signature *new_Emptymid_(int a1, int a2, int a3)
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
};

static struct str_Signature *new_Midbase_(int a1, int a2, int a3)
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
};

static struct str_Signature *new_Middlro_(int a1, int a2, int a3, int a4)
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
   struct str_Signature *structure3;
   struct str_Signature *a3;
   struct str_Signature *(*f3)(int , int );
   int i3, j3;
};


static struct str_Signature *new_Middl_s(int a1, int a2, struct str_Signature *structure3)
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
   struct str_Signature *structure2;
   struct str_Signature *a2;
   struct str_Signature *(*f2)(int , int );
   int i2, j2;
   int a3;
};


static struct str_Signature *new_Middr_s(int a1, struct str_Signature *structure2, int a3)
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
   struct str_Signature *structure4;
   struct str_Signature *a4;
   struct str_Signature *(*f4)(int , int );
   int i4, j4;
   int a5;
};


static struct str_Signature *new_Middlr_s(int a1, int a2, int a3, struct str_Signature *structure4, int a5)
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
   struct str_Signature *structure1;
   struct str_Signature *a1;
   struct str_Signature *(*f1)(int , int );
   int i1, j1;
};


static struct str_Signature *new_Midregion_s(struct str_Signature *structure1)
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
};

static struct str_Signature *new_Pss_(int a1, int a2)
{
   struct str_Pss *t;

   t=(struct str_Pss *) myalloc(adp_dynmem, sizeof(struct str_Pss ));
   t->a1 = a1;
   t->a2 = a2;
   return(new_Signature(SIGID_Pss, t));
}

/* signature pretty printer                                                         */
/* -------------------------------------------------------------------------------- */
static void pp_str_Signature(struct str_Signature *l)
{
   struct str_Signature *c;

   if (l != NULL) {
      c = l;
      if (c->utype == SIGID__NTID) {
         pp_str_Signature(((struct str__NTID *)(c->entry))->a1);
      } else 
      if (c->utype == SIGID_Sadd) {
         printf(".");
         pp_str_Signature(((struct str_Sadd *)(c->entry))->a2);
      } else 
      if (c->utype == SIGID_Cadd) {
         pp_str_Signature(((struct str_Cadd *)(c->entry))->a1);
         pp_str_Signature(((struct str_Cadd *)(c->entry))->a2);
      } else 
      if (c->utype == SIGID_Is) {
         pp_str_Signature(((struct str_Is *)(c->entry))->a2);
      } else 
      if (c->utype == SIGID_Sr) {
         printf("(");
         pp_str_Signature(((struct str_Sr *)(c->entry))->a2);
         printf(")");
      } else 
      if (c->utype == SIGID_Hl) {
         printf("((");
         printf("%s", dots(((struct str_Hl *)(c->entry))->a3, ((struct str_Hl *)(c->entry))->a4));
         printf("))");
      } else 
      if (c->utype == SIGID_Bl) {
         printf("((");
         printf("%s", dots(((struct str_Bl *)(c->entry))->a3, ((struct str_Bl *)(c->entry))->a4));
         pp_str_Signature(((struct str_Bl *)(c->entry))->a5);
         printf("))");
      } else 
      if (c->utype == SIGID_Br) {
         printf("((");
         pp_str_Signature(((struct str_Br *)(c->entry))->a3);
         printf("%s", dots(((struct str_Br *)(c->entry))->a4, ((struct str_Br *)(c->entry))->a5));
         printf("))");
      } else 
      if (c->utype == SIGID_Il) {
         printf("((");
         printf("%s", dots(((struct str_Il *)(c->entry))->a3, ((struct str_Il *)(c->entry))->a4));
         pp_str_Signature(((struct str_Il *)(c->entry))->a5);
         printf("%s", dots(((struct str_Il *)(c->entry))->a6, ((struct str_Il *)(c->entry))->a7));
         printf("))");
      } else 
      if (c->utype == SIGID_Ml) {
         printf("((");
         pp_str_Signature(((struct str_Ml *)(c->entry))->a3);
         printf("))");
      } else 
      if (c->utype == SIGID_Mldl) {
         printf("((.");
         pp_str_Signature(((struct str_Mldl *)(c->entry))->a4);
         printf("))");
      } else 
      if (c->utype == SIGID_Mldr) {
         printf("((");
         pp_str_Signature(((struct str_Mldr *)(c->entry))->a3);
         printf(".))");
      } else 
      if (c->utype == SIGID_Mldlr) {
         printf("((.");
         pp_str_Signature(((struct str_Mldlr *)(c->entry))->a4);
         printf(".))");
      } else 
      if (c->utype == SIGID_Dl) {
         printf(".");
         pp_str_Signature(((struct str_Dl *)(c->entry))->a2);
      } else 
      if (c->utype == SIGID_Dr) {
         pp_str_Signature(((struct str_Dr *)(c->entry))->a2);
         printf(".");
      } else 
      if (c->utype == SIGID_Dlr) {
         printf(".");
         pp_str_Signature(((struct str_Dlr *)(c->entry))->a2);
         printf(".");
      } else 
      if (c->utype == SIGID_Edl) {
         printf(".");
         pp_str_Signature(((struct str_Edl *)(c->entry))->a2);
      } else 
      if (c->utype == SIGID_Edr) {
         pp_str_Signature(((struct str_Edr *)(c->entry))->a2);
         printf(".");
      } else 
      if (c->utype == SIGID_Edlr) {
         printf(".");
         pp_str_Signature(((struct str_Edlr *)(c->entry))->a2);
         printf(".");
      } else 
      if (c->utype == SIGID_Drem) {
         pp_str_Signature(((struct str_Drem *)(c->entry))->a1);
      } else 
      if (c->utype == SIGID_Cons) {
         pp_str_Signature(((struct str_Cons *)(c->entry))->a1);
         pp_str_Signature(((struct str_Cons *)(c->entry))->a2);
      } else 
      if (c->utype == SIGID_Ul) {
         pp_str_Signature(((struct str_Ul *)(c->entry))->a1);
      } else 
      if (c->utype == SIGID_Pul) {
         pp_str_Signature(((struct str_Pul *)(c->entry))->a1);
      } else 
      if (c->utype == SIGID_Addss) {
         pp_str_Signature(((struct str_Addss *)(c->entry))->a1);
         printf("%s", dots(((struct str_Addss *)(c->entry))->a2, ((struct str_Addss *)(c->entry))->a3));
      } else 
      if (c->utype == SIGID_Ssadd) {
         printf("%s", dots(((struct str_Ssadd *)(c->entry))->a1, ((struct str_Ssadd *)(c->entry))->a2));
         pp_str_Signature(((struct str_Ssadd *)(c->entry))->a3);
      } else 
      if (c->utype == SIGID_Nil) {
         printf("");
      } else 
      if (c->utype == SIGID_Combine) {
         pp_str_Signature(((struct str_Combine *)(c->entry))->a1);
         pp_str_Signature(((struct str_Combine *)(c->entry))->a2);
      } else 
      if (c->utype == SIGID_Sum) {
         printf("");
      } else 
      if (c->utype == SIGID_Sumend) {
         printf("");
      } else 
      if (c->utype == SIGID_Co) {
         pp_str_Signature(((struct str_Co *)(c->entry))->a1);
      } else 
      if (c->utype == SIGID_Pk) {
         pp_str_Signature(((struct str_Pk *)(c->entry))->a1);
      } else 
      if (c->utype == SIGID_Pkmldl) {
         printf(".");
         pp_str_Signature(((struct str_Pkmldl *)(c->entry))->a2);
      } else 
      if (c->utype == SIGID_Pkmldr) {
         pp_str_Signature(((struct str_Pkmldr *)(c->entry))->a1);
         printf(".");
      } else 
      if (c->utype == SIGID_Pkmldlr) {
         printf(".");
         pp_str_Signature(((struct str_Pkmldlr *)(c->entry))->a2);
         printf(".");
      } else 
      if (c->utype == SIGID_Pkml) {
         pp_str_Signature(((struct str_Pkml *)(c->entry))->a1);
      } else 
      if (c->utype == SIGID_Pk_Pr) {
         printf("%s", open1(((struct str_Pk_Pr *)(c->entry))->a2, ((struct str_Pk_Pr *)(c->entry))->a3));
         printf(".");
         pp_str_Signature(((struct str_Pk_Pr *)(c->entry))->a4);
         printf("%s", open2(((struct str_Pk_Pr *)(c->entry))->a5, ((struct str_Pk_Pr *)(c->entry))->a6));
         pp_str_Signature(((struct str_Pk_Pr *)(c->entry))->a7);
         printf("%s", close1(((struct str_Pk_Pr *)(c->entry))->a8, ((struct str_Pk_Pr *)(c->entry))->a9));
         pp_str_Signature(((struct str_Pk_Pr *)(c->entry))->a10);
         printf("..");
         printf("%s", close2(((struct str_Pk_Pr *)(c->entry))->a11, ((struct str_Pk_Pr *)(c->entry))->a12));
      } else 
      if (c->utype == SIGID_Kndl) {
         printf(".");
         pp_str_Signature(((struct str_Kndl *)(c->entry))->a2);
      } else 
      if (c->utype == SIGID_Kndr) {
         pp_str_Signature(((struct str_Kndr *)(c->entry))->a1);
         printf(".");
      } else 
      if (c->utype == SIGID_Kndlr) {
         printf(".");
         pp_str_Signature(((struct str_Kndlr *)(c->entry))->a2);
         printf(".");
      } else 
      if (c->utype == SIGID_Frd) {
         pp_str_Signature(((struct str_Frd *)(c->entry))->a2);
         printf(".");
      } else 
      if (c->utype == SIGID_Bkd) {
         printf(".");
         pp_str_Signature(((struct str_Bkd *)(c->entry))->a3);
      } else 
      if (c->utype == SIGID_Emptymid) {
         printf("");
      } else 
      if (c->utype == SIGID_Midbase) {
         printf(".");
      } else 
      if (c->utype == SIGID_Middlro) {
         printf("..");
      } else 
      if (c->utype == SIGID_Middl) {
         printf(".");
         pp_str_Signature(((struct str_Middl *)(c->entry))->a3);
      } else 
      if (c->utype == SIGID_Middr) {
         pp_str_Signature(((struct str_Middr *)(c->entry))->a2);
         printf(".");
      } else 
      if (c->utype == SIGID_Middlr) {
         printf(".");
         pp_str_Signature(((struct str_Middlr *)(c->entry))->a4);
         printf(".");
      } else 
      if (c->utype == SIGID_Midregion) {
         pp_str_Signature(((struct str_Midregion *)(c->entry))->a1);
      } else 
      if (c->utype == SIGID_Pss) {
         printf("%s", dots(((struct str_Pss *)(c->entry))->a1, ((struct str_Pss *)(c->entry))->a2));
      };
   }
}

/* structure builder                                                                */
/* -------------------------------------------------------------------------------- */
static struct str_Signature *build_str_Signature(struct str_Signature *l)
{
   struct str_Signature *c;
   struct str_Signature *cl;

   c = l;
   if (c != NULL) {
      if (c->utype == SIGID__NTID) {
         if (((struct str__NTID *)(c->entry))->isStructure1) {
            ((struct str__NTID *)(c->entry))->a1 = build_str_Signature(((struct str__NTID *)(c->entry))->structure1);
         }
         else {
            ((struct str__NTID *)(c->entry))->a1 = (*((struct str__NTID *)(c->entry))->f1)(((struct str__NTID *)(c->entry))->i1, ((struct str__NTID *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Sadd) {
         if (((struct str_Sadd *)(c->entry))->isStructure2) {
            ((struct str_Sadd *)(c->entry))->a2 = build_str_Signature(((struct str_Sadd *)(c->entry))->structure2);
         }
         else {
            ((struct str_Sadd *)(c->entry))->a2 = (*((struct str_Sadd *)(c->entry))->f2)(((struct str_Sadd *)(c->entry))->i2, ((struct str_Sadd *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Cadd) {
         if (((struct str_Cadd *)(c->entry))->isStructure1) {
            ((struct str_Cadd *)(c->entry))->a1 = build_str_Signature(((struct str_Cadd *)(c->entry))->structure1);
         }
         else {
            ((struct str_Cadd *)(c->entry))->a1 = (*((struct str_Cadd *)(c->entry))->f1)(((struct str_Cadd *)(c->entry))->i1, ((struct str_Cadd *)(c->entry))->j1);
         }
         if (((struct str_Cadd *)(c->entry))->isStructure2) {
            ((struct str_Cadd *)(c->entry))->a2 = build_str_Signature(((struct str_Cadd *)(c->entry))->structure2);
         }
         else {
            ((struct str_Cadd *)(c->entry))->a2 = (*((struct str_Cadd *)(c->entry))->f2)(((struct str_Cadd *)(c->entry))->i2, ((struct str_Cadd *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Is) {
         if (((struct str_Is *)(c->entry))->isStructure2) {
            ((struct str_Is *)(c->entry))->a2 = build_str_Signature(((struct str_Is *)(c->entry))->structure2);
         }
         else {
            ((struct str_Is *)(c->entry))->a2 = (*((struct str_Is *)(c->entry))->f2)(((struct str_Is *)(c->entry))->i2, ((struct str_Is *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Sr) {
         if (((struct str_Sr *)(c->entry))->isStructure2) {
            ((struct str_Sr *)(c->entry))->a2 = build_str_Signature(((struct str_Sr *)(c->entry))->structure2);
         }
         else {
            ((struct str_Sr *)(c->entry))->a2 = (*((struct str_Sr *)(c->entry))->f2)(((struct str_Sr *)(c->entry))->i2, ((struct str_Sr *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Hl) {
      } else 
      if (c->utype == SIGID_Bl) {
         if (((struct str_Bl *)(c->entry))->isStructure5) {
            ((struct str_Bl *)(c->entry))->a5 = build_str_Signature(((struct str_Bl *)(c->entry))->structure5);
         }
         else {
            ((struct str_Bl *)(c->entry))->a5 = (*((struct str_Bl *)(c->entry))->f5)(((struct str_Bl *)(c->entry))->i5, ((struct str_Bl *)(c->entry))->j5);
         }
      } else 
      if (c->utype == SIGID_Br) {
         if (((struct str_Br *)(c->entry))->isStructure3) {
            ((struct str_Br *)(c->entry))->a3 = build_str_Signature(((struct str_Br *)(c->entry))->structure3);
         }
         else {
            ((struct str_Br *)(c->entry))->a3 = (*((struct str_Br *)(c->entry))->f3)(((struct str_Br *)(c->entry))->i3, ((struct str_Br *)(c->entry))->j3);
         }
      } else 
      if (c->utype == SIGID_Il) {
         if (((struct str_Il *)(c->entry))->isStructure5) {
            ((struct str_Il *)(c->entry))->a5 = build_str_Signature(((struct str_Il *)(c->entry))->structure5);
         }
         else {
            ((struct str_Il *)(c->entry))->a5 = (*((struct str_Il *)(c->entry))->f5)(((struct str_Il *)(c->entry))->i5, ((struct str_Il *)(c->entry))->j5);
         }
      } else 
      if (c->utype == SIGID_Ml) {
         if (((struct str_Ml *)(c->entry))->isStructure3) {
            ((struct str_Ml *)(c->entry))->a3 = build_str_Signature(((struct str_Ml *)(c->entry))->structure3);
         }
         else {
            ((struct str_Ml *)(c->entry))->a3 = (*((struct str_Ml *)(c->entry))->f3)(((struct str_Ml *)(c->entry))->i3, ((struct str_Ml *)(c->entry))->j3);
         }
      } else 
      if (c->utype == SIGID_Mldl) {
         if (((struct str_Mldl *)(c->entry))->isStructure4) {
            ((struct str_Mldl *)(c->entry))->a4 = build_str_Signature(((struct str_Mldl *)(c->entry))->structure4);
         }
         else {
            ((struct str_Mldl *)(c->entry))->a4 = (*((struct str_Mldl *)(c->entry))->f4)(((struct str_Mldl *)(c->entry))->i4, ((struct str_Mldl *)(c->entry))->j4);
         }
      } else 
      if (c->utype == SIGID_Mldr) {
         if (((struct str_Mldr *)(c->entry))->isStructure3) {
            ((struct str_Mldr *)(c->entry))->a3 = build_str_Signature(((struct str_Mldr *)(c->entry))->structure3);
         }
         else {
            ((struct str_Mldr *)(c->entry))->a3 = (*((struct str_Mldr *)(c->entry))->f3)(((struct str_Mldr *)(c->entry))->i3, ((struct str_Mldr *)(c->entry))->j3);
         }
      } else 
      if (c->utype == SIGID_Mldlr) {
         if (((struct str_Mldlr *)(c->entry))->isStructure4) {
            ((struct str_Mldlr *)(c->entry))->a4 = build_str_Signature(((struct str_Mldlr *)(c->entry))->structure4);
         }
         else {
            ((struct str_Mldlr *)(c->entry))->a4 = (*((struct str_Mldlr *)(c->entry))->f4)(((struct str_Mldlr *)(c->entry))->i4, ((struct str_Mldlr *)(c->entry))->j4);
         }
      } else 
      if (c->utype == SIGID_Dl) {
         if (((struct str_Dl *)(c->entry))->isStructure2) {
            ((struct str_Dl *)(c->entry))->a2 = build_str_Signature(((struct str_Dl *)(c->entry))->structure2);
         }
         else {
            ((struct str_Dl *)(c->entry))->a2 = (*((struct str_Dl *)(c->entry))->f2)(((struct str_Dl *)(c->entry))->i2, ((struct str_Dl *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Dr) {
         if (((struct str_Dr *)(c->entry))->isStructure2) {
            ((struct str_Dr *)(c->entry))->a2 = build_str_Signature(((struct str_Dr *)(c->entry))->structure2);
         }
         else {
            ((struct str_Dr *)(c->entry))->a2 = (*((struct str_Dr *)(c->entry))->f2)(((struct str_Dr *)(c->entry))->i2, ((struct str_Dr *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Dlr) {
         if (((struct str_Dlr *)(c->entry))->isStructure2) {
            ((struct str_Dlr *)(c->entry))->a2 = build_str_Signature(((struct str_Dlr *)(c->entry))->structure2);
         }
         else {
            ((struct str_Dlr *)(c->entry))->a2 = (*((struct str_Dlr *)(c->entry))->f2)(((struct str_Dlr *)(c->entry))->i2, ((struct str_Dlr *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Edl) {
         if (((struct str_Edl *)(c->entry))->isStructure2) {
            ((struct str_Edl *)(c->entry))->a2 = build_str_Signature(((struct str_Edl *)(c->entry))->structure2);
         }
         else {
            ((struct str_Edl *)(c->entry))->a2 = (*((struct str_Edl *)(c->entry))->f2)(((struct str_Edl *)(c->entry))->i2, ((struct str_Edl *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Edr) {
         if (((struct str_Edr *)(c->entry))->isStructure2) {
            ((struct str_Edr *)(c->entry))->a2 = build_str_Signature(((struct str_Edr *)(c->entry))->structure2);
         }
         else {
            ((struct str_Edr *)(c->entry))->a2 = (*((struct str_Edr *)(c->entry))->f2)(((struct str_Edr *)(c->entry))->i2, ((struct str_Edr *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Edlr) {
         if (((struct str_Edlr *)(c->entry))->isStructure2) {
            ((struct str_Edlr *)(c->entry))->a2 = build_str_Signature(((struct str_Edlr *)(c->entry))->structure2);
         }
         else {
            ((struct str_Edlr *)(c->entry))->a2 = (*((struct str_Edlr *)(c->entry))->f2)(((struct str_Edlr *)(c->entry))->i2, ((struct str_Edlr *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Drem) {
         if (((struct str_Drem *)(c->entry))->isStructure1) {
            ((struct str_Drem *)(c->entry))->a1 = build_str_Signature(((struct str_Drem *)(c->entry))->structure1);
         }
         else {
            ((struct str_Drem *)(c->entry))->a1 = (*((struct str_Drem *)(c->entry))->f1)(((struct str_Drem *)(c->entry))->i1, ((struct str_Drem *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Cons) {
         if (((struct str_Cons *)(c->entry))->isStructure1) {
            ((struct str_Cons *)(c->entry))->a1 = build_str_Signature(((struct str_Cons *)(c->entry))->structure1);
         }
         else {
            ((struct str_Cons *)(c->entry))->a1 = (*((struct str_Cons *)(c->entry))->f1)(((struct str_Cons *)(c->entry))->i1, ((struct str_Cons *)(c->entry))->j1);
         }
         if (((struct str_Cons *)(c->entry))->isStructure2) {
            ((struct str_Cons *)(c->entry))->a2 = build_str_Signature(((struct str_Cons *)(c->entry))->structure2);
         }
         else {
            ((struct str_Cons *)(c->entry))->a2 = (*((struct str_Cons *)(c->entry))->f2)(((struct str_Cons *)(c->entry))->i2, ((struct str_Cons *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Ul) {
         if (((struct str_Ul *)(c->entry))->isStructure1) {
            ((struct str_Ul *)(c->entry))->a1 = build_str_Signature(((struct str_Ul *)(c->entry))->structure1);
         }
         else {
            ((struct str_Ul *)(c->entry))->a1 = (*((struct str_Ul *)(c->entry))->f1)(((struct str_Ul *)(c->entry))->i1, ((struct str_Ul *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Pul) {
         if (((struct str_Pul *)(c->entry))->isStructure1) {
            ((struct str_Pul *)(c->entry))->a1 = build_str_Signature(((struct str_Pul *)(c->entry))->structure1);
         }
         else {
            ((struct str_Pul *)(c->entry))->a1 = (*((struct str_Pul *)(c->entry))->f1)(((struct str_Pul *)(c->entry))->i1, ((struct str_Pul *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Addss) {
         if (((struct str_Addss *)(c->entry))->isStructure1) {
            ((struct str_Addss *)(c->entry))->a1 = build_str_Signature(((struct str_Addss *)(c->entry))->structure1);
         }
         else {
            ((struct str_Addss *)(c->entry))->a1 = (*((struct str_Addss *)(c->entry))->f1)(((struct str_Addss *)(c->entry))->i1, ((struct str_Addss *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Ssadd) {
         if (((struct str_Ssadd *)(c->entry))->isStructure3) {
            ((struct str_Ssadd *)(c->entry))->a3 = build_str_Signature(((struct str_Ssadd *)(c->entry))->structure3);
         }
         else {
            ((struct str_Ssadd *)(c->entry))->a3 = (*((struct str_Ssadd *)(c->entry))->f3)(((struct str_Ssadd *)(c->entry))->i3, ((struct str_Ssadd *)(c->entry))->j3);
         }
      } else 
      if (c->utype == SIGID_Nil) {
      } else 
      if (c->utype == SIGID_Combine) {
         if (((struct str_Combine *)(c->entry))->isStructure1) {
            ((struct str_Combine *)(c->entry))->a1 = build_str_Signature(((struct str_Combine *)(c->entry))->structure1);
         }
         else {
            ((struct str_Combine *)(c->entry))->a1 = (*((struct str_Combine *)(c->entry))->f1)(((struct str_Combine *)(c->entry))->i1, ((struct str_Combine *)(c->entry))->j1);
         }
         if (((struct str_Combine *)(c->entry))->isStructure2) {
            ((struct str_Combine *)(c->entry))->a2 = build_str_Signature(((struct str_Combine *)(c->entry))->structure2);
         }
         else {
            ((struct str_Combine *)(c->entry))->a2 = (*((struct str_Combine *)(c->entry))->f2)(((struct str_Combine *)(c->entry))->i2, ((struct str_Combine *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Sum) {
         if (((struct str_Sum *)(c->entry))->isStructure2) {
            ((struct str_Sum *)(c->entry))->a2 = build_str_Signature(((struct str_Sum *)(c->entry))->structure2);
         }
         else {
            ((struct str_Sum *)(c->entry))->a2 = (*((struct str_Sum *)(c->entry))->f2)(((struct str_Sum *)(c->entry))->i2, ((struct str_Sum *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Sumend) {
      } else 
      if (c->utype == SIGID_Co) {
         if (((struct str_Co *)(c->entry))->isStructure1) {
            ((struct str_Co *)(c->entry))->a1 = build_str_Signature(((struct str_Co *)(c->entry))->structure1);
         }
         else {
            ((struct str_Co *)(c->entry))->a1 = (*((struct str_Co *)(c->entry))->f1)(((struct str_Co *)(c->entry))->i1, ((struct str_Co *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Pk) {
         if (((struct str_Pk *)(c->entry))->isStructure1) {
            ((struct str_Pk *)(c->entry))->a1 = build_str_Signature(((struct str_Pk *)(c->entry))->structure1);
         }
         else {
            ((struct str_Pk *)(c->entry))->a1 = (*((struct str_Pk *)(c->entry))->f1)(((struct str_Pk *)(c->entry))->i1, ((struct str_Pk *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Pkmldl) {
         if (((struct str_Pkmldl *)(c->entry))->isStructure2) {
            ((struct str_Pkmldl *)(c->entry))->a2 = build_str_Signature(((struct str_Pkmldl *)(c->entry))->structure2);
         }
         else {
            ((struct str_Pkmldl *)(c->entry))->a2 = (*((struct str_Pkmldl *)(c->entry))->f2)(((struct str_Pkmldl *)(c->entry))->i2, ((struct str_Pkmldl *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Pkmldr) {
         if (((struct str_Pkmldr *)(c->entry))->isStructure1) {
            ((struct str_Pkmldr *)(c->entry))->a1 = build_str_Signature(((struct str_Pkmldr *)(c->entry))->structure1);
         }
         else {
            ((struct str_Pkmldr *)(c->entry))->a1 = (*((struct str_Pkmldr *)(c->entry))->f1)(((struct str_Pkmldr *)(c->entry))->i1, ((struct str_Pkmldr *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Pkmldlr) {
         if (((struct str_Pkmldlr *)(c->entry))->isStructure2) {
            ((struct str_Pkmldlr *)(c->entry))->a2 = build_str_Signature(((struct str_Pkmldlr *)(c->entry))->structure2);
         }
         else {
            ((struct str_Pkmldlr *)(c->entry))->a2 = (*((struct str_Pkmldlr *)(c->entry))->f2)(((struct str_Pkmldlr *)(c->entry))->i2, ((struct str_Pkmldlr *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Pkml) {
         if (((struct str_Pkml *)(c->entry))->isStructure1) {
            ((struct str_Pkml *)(c->entry))->a1 = build_str_Signature(((struct str_Pkml *)(c->entry))->structure1);
         }
         else {
            ((struct str_Pkml *)(c->entry))->a1 = (*((struct str_Pkml *)(c->entry))->f1)(((struct str_Pkml *)(c->entry))->i1, ((struct str_Pkml *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Pk_Pr) {
         if (((struct str_Pk_Pr *)(c->entry))->isStructure4) {
            ((struct str_Pk_Pr *)(c->entry))->a4 = build_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure4);
         }
         else {
            ((struct str_Pk_Pr *)(c->entry))->a4 = (*((struct str_Pk_Pr *)(c->entry))->f4)(((struct str_Pk_Pr *)(c->entry))->i4, ((struct str_Pk_Pr *)(c->entry))->j4);
         }
         if (((struct str_Pk_Pr *)(c->entry))->isStructure7) {
            ((struct str_Pk_Pr *)(c->entry))->a7 = build_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure7);
         }
         else {
            ((struct str_Pk_Pr *)(c->entry))->a7 = (*((struct str_Pk_Pr *)(c->entry))->f7)(((struct str_Pk_Pr *)(c->entry))->i7, ((struct str_Pk_Pr *)(c->entry))->j7);
         }
         if (((struct str_Pk_Pr *)(c->entry))->isStructure10) {
            ((struct str_Pk_Pr *)(c->entry))->a10 = build_str_Signature(((struct str_Pk_Pr *)(c->entry))->structure10);
         }
         else {
            ((struct str_Pk_Pr *)(c->entry))->a10 = (*((struct str_Pk_Pr *)(c->entry))->f10)(((struct str_Pk_Pr *)(c->entry))->i10, ((struct str_Pk_Pr *)(c->entry))->j10);
         }
      } else 
      if (c->utype == SIGID_Kndl) {
         if (((struct str_Kndl *)(c->entry))->isStructure2) {
            ((struct str_Kndl *)(c->entry))->a2 = build_str_Signature(((struct str_Kndl *)(c->entry))->structure2);
         }
         else {
            ((struct str_Kndl *)(c->entry))->a2 = (*((struct str_Kndl *)(c->entry))->f2)(((struct str_Kndl *)(c->entry))->i2, ((struct str_Kndl *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Kndr) {
         if (((struct str_Kndr *)(c->entry))->isStructure1) {
            ((struct str_Kndr *)(c->entry))->a1 = build_str_Signature(((struct str_Kndr *)(c->entry))->structure1);
         }
         else {
            ((struct str_Kndr *)(c->entry))->a1 = (*((struct str_Kndr *)(c->entry))->f1)(((struct str_Kndr *)(c->entry))->i1, ((struct str_Kndr *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Kndlr) {
         if (((struct str_Kndlr *)(c->entry))->isStructure2) {
            ((struct str_Kndlr *)(c->entry))->a2 = build_str_Signature(((struct str_Kndlr *)(c->entry))->structure2);
         }
         else {
            ((struct str_Kndlr *)(c->entry))->a2 = (*((struct str_Kndlr *)(c->entry))->f2)(((struct str_Kndlr *)(c->entry))->i2, ((struct str_Kndlr *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Frd) {
         if (((struct str_Frd *)(c->entry))->isStructure2) {
            ((struct str_Frd *)(c->entry))->a2 = build_str_Signature(((struct str_Frd *)(c->entry))->structure2);
         }
         else {
            ((struct str_Frd *)(c->entry))->a2 = (*((struct str_Frd *)(c->entry))->f2)(((struct str_Frd *)(c->entry))->i2, ((struct str_Frd *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Bkd) {
         if (((struct str_Bkd *)(c->entry))->isStructure3) {
            ((struct str_Bkd *)(c->entry))->a3 = build_str_Signature(((struct str_Bkd *)(c->entry))->structure3);
         }
         else {
            ((struct str_Bkd *)(c->entry))->a3 = (*((struct str_Bkd *)(c->entry))->f3)(((struct str_Bkd *)(c->entry))->i3, ((struct str_Bkd *)(c->entry))->j3);
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
         }
         else {
            ((struct str_Middl *)(c->entry))->a3 = (*((struct str_Middl *)(c->entry))->f3)(((struct str_Middl *)(c->entry))->i3, ((struct str_Middl *)(c->entry))->j3);
         }
      } else 
      if (c->utype == SIGID_Middr) {
         if (((struct str_Middr *)(c->entry))->isStructure2) {
            ((struct str_Middr *)(c->entry))->a2 = build_str_Signature(((struct str_Middr *)(c->entry))->structure2);
         }
         else {
            ((struct str_Middr *)(c->entry))->a2 = (*((struct str_Middr *)(c->entry))->f2)(((struct str_Middr *)(c->entry))->i2, ((struct str_Middr *)(c->entry))->j2);
         }
      } else 
      if (c->utype == SIGID_Middlr) {
         if (((struct str_Middlr *)(c->entry))->isStructure4) {
            ((struct str_Middlr *)(c->entry))->a4 = build_str_Signature(((struct str_Middlr *)(c->entry))->structure4);
         }
         else {
            ((struct str_Middlr *)(c->entry))->a4 = (*((struct str_Middlr *)(c->entry))->f4)(((struct str_Middlr *)(c->entry))->i4, ((struct str_Middlr *)(c->entry))->j4);
         }
      } else 
      if (c->utype == SIGID_Midregion) {
         if (((struct str_Midregion *)(c->entry))->isStructure1) {
            ((struct str_Midregion *)(c->entry))->a1 = build_str_Signature(((struct str_Midregion *)(c->entry))->structure1);
         }
         else {
            ((struct str_Midregion *)(c->entry))->a1 = (*((struct str_Midregion *)(c->entry))->f1)(((struct str_Midregion *)(c->entry))->i1, ((struct str_Midregion *)(c->entry))->j1);
         }
      } else 
      if (c->utype == SIGID_Pss) {
      };
   }
   return(l);
}

/* table access                                                                     */
/* -------------------------------------------------------------------------------- */

static int *offset;

#define tbl_struct(I, J) arr_struct[(I)]
#define tbl_edangle(I, J) arr_edangle[offset[(J)]+(I)]
#define tbl_closed(I, J) arr_closed[offset[(J)]+(I)]
#define tbl_comps(I, J) arr_comps[offset[(J)]+(I)]
#define tbl_block(I, J) arr_block[offset[(J)]+(I)]
#define tbl_knot(I, J) arr_knot[offset[(J)]+(I)]
#define tbl_stacklen(I, J) arr_stacklen[offset[(J)]+(I)]

/* table declarations                                                               */
/* -------------------------------------------------------------------------------- */

static int *arr_struct;
static int *arr_edangle;
static int *arr_closed;
static int *arr_comps;
static int *arr_block;
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

/* table calculation for production closed                                          */
/* -------------------------------------------------------------------------------- */
static void calc_closed(int i, int j)
{
   int v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16;
   int v17, v18, v19, v20, v21, v22, v23, v24;
   int v25, v26, v27, v28, v29, v30, v31, v32;
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

         /* ------------------------------- start of ------------------------------ */
         /*  v12 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 19) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v14 = combine <<< p block ~~~ p comps --------------- */
            v14 = 1.0e7;
            for (k5=i+10; k5<=j-9; k5++) {
               v13 = tbl_block(i+3, k5) + tbl_comps(k5, j-2);
               v14 = v13 < v14 ? v13 : v14;
            }
            /* -------------- v14 = combine <<< p block ~~~ p comps --------------- */
            /* ----------------------------- finished ----------------------------- */

            v12 = (((380 + v14) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
         }
         else {
            v12 = 1.0e7;
         }
         /*  v12 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v15 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 19) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v17 = combine <<< p block ~~~ p comps --------------- */
            v17 = 1.0e7;
            for (k6=i+9; k6<=j-10; k6++) {
               v16 = tbl_block(i+2, k6) + tbl_comps(k6, j-3);
               v17 = v16 < v17 ? v16 : v17;
            }
            /* -------------- v17 = combine <<< p block ~~~ p comps --------------- */
            /* ----------------------------- finished ----------------------------- */

            v15 = (((380 + v17) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
         }
         else {
            v15 = 1.0e7;
         }
         /*  v15 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v18 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 20) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v20 = combine <<< p block ~~~ p comps --------------- */
            v20 = 1.0e7;
            for (k7=i+10; k7<=j-10; k7++) {
               v19 = tbl_block(i+3, k7) + tbl_comps(k7, j-3);
               v20 = v19 < v20 ? v19 : v20;
            }
            /* -------------- v20 = combine <<< p block ~~~ p comps --------------- */
            /* ----------------------------- finished ----------------------------- */

            v18 = ((((380 + v20) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
         }
         else {
            v18 = 1.0e7;
         }
         /*  v18 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /*  v21 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         if ((j-i) >= 18) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v23 = combine <<< p block ~~~ p comps --------------- */
            v23 = 1.0e7;
            for (k8=i+9; k8<=j-9; k8++) {
               v22 = tbl_block(i+2, k8) + tbl_comps(k8, j-2);
               v23 = v22 < v23 ? v22 : v23;
            }
            /* -------------- v23 = combine <<< p block ~~~ p comps --------------- */
            /* ----------------------------- finished ----------------------------- */

            v21 = ((380 + v23) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
         }
         else {
            v21 = 1.0e7;
         }
         /*  v21 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
         /* ------------------------------- finished ------------------------------ */

         v24 = v18 < v21 ? v18 : v21;
         v25 = v15 < v24 ? v15 : v24;
         v26 = v12 < v25 ? v12 : v25;
         v27 = v11 < v26 ? v11 : v26;
         v28 = v9 < v27 ? v9 : v27;
         v29 = v6 < v28 ? v6 : v28;
         v30 = v3 < v29 ? v3 : v29;
         v31 = v30;
      }
      else {
         v31 = 1.0e7;
      }
      v32 = v2 < v31 ? v2 : v31;
      /* ----------------------- assign table entry result ------------------------ */
      tbl_closed(i, j) = v32;
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
   struct str1 v1, v53;
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
                  /* --- v2 = co <<< pul <<< pss <<< uregion ||| p comps ... h ---- */
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
                  /* --- v2 = co <<< pul <<< pss <<< uregion ||| p comps ... h ---- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* = frd j <<< (pul <<< pss <<< uregion ||| p comps ... h) ~~~ lb */
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
                  /* = frd j <<< (pul <<< pss <<< uregion ||| p comps ... h) ~~~ lb */
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
                  /*  v16 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h)  */
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
                  /*  v16 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h)  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v21 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ... h) ~~~ lbase  */
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
                  /*  v21 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v26 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h) ~~~ lbase  */
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
                  /*  v26 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v31 = midregion <<< pul <<< pss <<< region ||| p comps ... h  */
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
                  /*  v31 = midregion <<< pul <<< pss <<< region ||| p comps ... h  */
                  /* -------------------------- finished -------------------------- */

                  v36 = v26 < v31 ? v26 : v31;
                  v37 = v21 < v36 ? v21 : v36;
                  v38 = v16 < v37 ? v16 : v37;
                  v39 = v15 < v38 ? v15 : v38;
                  v40 = v14 < v39 ? v14 : v39;
                  v41 = v13 < v40 ? v13 : v40;
                  /* -------------------------- start of -------------------------- */
                  /* --- v42 = co <<< pul <<< pss <<< uregion ||| p comps ... h --- */
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
                  /* --- v42 = co <<< pul <<< pss <<< uregion ||| p comps ... h --- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ... */
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
                  /* = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ... */
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

static struct str_Signature *back_closed(int i, int j);

static struct str_Signature *back_knot(int i, int j);

static struct str_Signature *back_stacklen(int i, int j);

static struct str_Signature *back_edangle(int i, int j);

static struct str_Signature *back_block(int i, int j);

static struct str_Signature *back_struct(int i, int j);

static struct str_Signature *back_comps(int i, int j);

/* backtracing code                                                                 */
/* -------------------------------------------------------------------------------- */

/* backtracing code for production struct                                           */
/* -------------------------------------------------------------------------------- */
static struct str_Signature *back_struct(int i, int j)
{
   struct str3 v1, v2, v3, v4, v5, v6;
   int k;

   /* ---------------------------------- start of --------------------------------- */
   /* ---------------------- v1 = sadd <<< lbase ~~~ p struct --------------------- */
   if ((j-i) >= 1) {
      v1.alg_energy = tbl_struct(i+1, j);
      v1.alg_enum = new_Sadd_f(i+1, back_struct, i+1, j);
   }
   else {
      v1.alg_energy = 1.0e7;
      v1.alg_enum = NULL;
   }
   /* ---------------------- v1 = sadd <<< lbase ~~~ p struct --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* -------------------- v3 = cadd <<< p edangle ~~~ p struct ------------------- */
   if ((j-i) >= 7) {
      v3.alg_energy = 1.0e7;
      v3.alg_enum = NULL;
      for (k=i+7; k<=j; k++) {
         v2.alg_energy = tbl_edangle(i, k) + tbl_struct(k, j);
         v2.alg_enum = new_Cadd_ff(back_edangle, i, k, back_struct, k, j);
         /* ------------------------- v3 = minimum(v2, v3) ------------------------ */
         v3 = v2.alg_energy < v3.alg_energy ? v2 : v3;
      }
   }
   else {
      v3.alg_energy = 1.0e7;
      v3.alg_enum = NULL;
   }
   /* -------------------- v3 = cadd <<< p edangle ~~~ p struct ------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------------- v4 = nil <<< empty ---------------------------- */
   if ((j-i) == 0) {
      v4.alg_energy = 0;
      v4.alg_enum = new_Nil_(i);
   }
   else {
      v4.alg_energy = 1.0e7;
      v4.alg_enum = NULL;
   }
   /* ----------------------------- v4 = nil <<< empty ---------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------- v5 = minimum(v3, v4) --------------------------- */
   v5 = v3.alg_energy < v4.alg_energy ? v3 : v4;
   /* ---------------------------- v6 = minimum(v1, v5) --------------------------- */
   v6 = v1.alg_energy < v5.alg_energy ? v1 : v5;
   /* ------------------------- build candidate structures ------------------------ */
   return(build_str_Signature(v6.alg_enum));
}

/* backtracing code for production edangle                                          */
/* -------------------------------------------------------------------------------- */
static struct str_Signature *back_edangle(int i, int j)
{
   struct str3 v1, v2, v3, v4, v5, v6, v7, v8;
   struct str3 v9, v10, v11, v12, v13, v14, v15, v16;

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------ v1 = edl <<< lbase ~~~ p closed ~~~ loc ------------------ */
   if ((j-i) >= 8) {
      v1.alg_energy = (tbl_closed(i+1, j) + dl_energy((i+1) + 1, j)) + termaupenalty((i+1) + 1, j);
      v1.alg_enum = new_Edl_f(i+1, back_closed, i+1, j, j);
   }
   else {
      v1.alg_energy = 1.0e7;
      v1.alg_enum = NULL;
   }
   /* ------------------ v1 = edl <<< lbase ~~~ p closed ~~~ loc ------------------ */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ------------------ v2 = edr <<< loc ~~~ p closed ~~~ lbase ------------------ */
   if ((j-i) >= 8) {
      v2.alg_energy = (tbl_closed(i, j-1) + dr_energy((i) + 1, (j) - 1)) + termaupenalty((i) + 1, (j) - 1);
      v2.alg_enum = new_Edr_f(i, back_closed, i, j-1, j);
   }
   else {
      v2.alg_energy = 1.0e7;
      v2.alg_enum = NULL;
   }
   /* ------------------ v2 = edr <<< loc ~~~ p closed ~~~ lbase ------------------ */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------- v3 = edlr <<< lbase ~~~ p closed ~~~ lbase ---------------- */
   if ((j-i) >= 9) {
      v3.alg_energy = ((tbl_closed(i+1, j-1) + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1)) + termaupenalty((i+1) + 1, (j) - 1);
      v3.alg_enum = new_Edlr_f(i+1, back_closed, i+1, j-1, j);
   }
   else {
      v3.alg_energy = 1.0e7;
      v3.alg_enum = NULL;
   }
   /* ----------------- v3 = edlr <<< lbase ~~~ p closed ~~~ lbase ---------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------- v4 = drem <<< is <<< loc ~~~ p closed ~~~ loc --------------- */
   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v5 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      v5.alg_energy = tbl_closed(i, j) + termaupenalty((i) + 1, j);
      v5.alg_enum = new_Is_f(i, back_closed, i, j, j);
      /* ------------------ v5 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v4.alg_energy = v5.alg_energy;
      v4.alg_enum = new_Drem_s(v5.alg_enum);
   }
   else {
      v4.alg_energy = 1.0e7;
      v4.alg_enum = NULL;
   }
   /* --------------- v4 = drem <<< is <<< loc ~~~ p closed ~~~ loc --------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------- v6 = kndr <<< p knot ~~~ lbase ---------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      v6.alg_energy = (tbl_knot(i, j-1).tup1 + npp) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1));
      v6.alg_enum = new_Kndr_f(back_knot, i, j-1, tbl_knot(i, j-1).tup2, tbl_knot(i, j-1).tup3, j);
   }
   else {
      v6.alg_energy = 1.0e7;
      v6.alg_enum = NULL;
   }
   /* ----------------------- v6 = kndr <<< p knot ~~~ lbase ---------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------- v7 = kndl <<< lbase ~~~ p knot ---------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      v7.alg_energy = (tbl_knot(i+1, j).tup1 + npp) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3));
      v7.alg_enum = new_Kndl_f(i+1, back_knot, i+1, j, tbl_knot(i+1, j).tup2, tbl_knot(i+1, j).tup3);
   }
   else {
      v7.alg_energy = 1.0e7;
      v7.alg_enum = NULL;
   }
   /* ----------------------- v7 = kndl <<< lbase ~~~ p knot ---------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------- v8 = kndlr <<< lbase ~~~ p knot ~~~ lbase ----------------- */
   if (((j-i) >= 13) && ((j-i) <= (max_pknot_length+2))) {
      v8.alg_energy = (tbl_knot(i+1, j-1).tup1 + (2 * npp)) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1)));
      v8.alg_enum = new_Kndlr_f(i+1, back_knot, i+1, j-1, tbl_knot(i+1, j-1).tup2, tbl_knot(i+1, j-1).tup3, j);
   }
   else {
      v8.alg_energy = 1.0e7;
      v8.alg_enum = NULL;
   }
   /* ----------------- v8 = kndlr <<< lbase ~~~ p knot ~~~ lbase ----------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ----------------------------- v9 = pk <<< p knot ---------------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      v9.alg_energy = tbl_knot(i, j).tup1;
      v9.alg_enum = new_Pk_f(back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3);
   }
   else {
      v9.alg_energy = 1.0e7;
      v9.alg_enum = NULL;
   }
   /* ----------------------------- v9 = pk <<< p knot ---------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* --------------------------- v10 = minimum(v8, v9) --------------------------- */
   v10 = v8.alg_energy < v9.alg_energy ? v8 : v9;
   /* --------------------------- v11 = minimum(v7, v10) -------------------------- */
   v11 = v7.alg_energy < v10.alg_energy ? v7 : v10;
   /* --------------------------- v12 = minimum(v6, v11) -------------------------- */
   v12 = v6.alg_energy < v11.alg_energy ? v6 : v11;
   /* --------------------------- v13 = minimum(v4, v12) -------------------------- */
   v13 = v4.alg_energy < v12.alg_energy ? v4 : v12;
   /* --------------------------- v14 = minimum(v3, v13) -------------------------- */
   v14 = v3.alg_energy < v13.alg_energy ? v3 : v13;
   /* --------------------------- v15 = minimum(v2, v14) -------------------------- */
   v15 = v2.alg_energy < v14.alg_energy ? v2 : v14;
   /* --------------------------- v16 = minimum(v1, v15) -------------------------- */
   v16 = v1.alg_energy < v15.alg_energy ? v1 : v15;
   /* ------------------------- build candidate structures ------------------------ */
   return(build_str_Signature(v16.alg_enum));
}

/* backtracing code for production closed                                           */
/* -------------------------------------------------------------------------------- */
static struct str_Signature *back_closed(int i, int j)
{
   struct str3 v1, v2, v3, v4, v5, v6, v7, v8, v9, v10;
   struct str3 v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21;
   struct str3 v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32;
   int k, k2, k3, k4, k5, k6, k7, k8;

   if (basepairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /* ---------------- v1 = sr <<< lbase ~~~ p closed ~~~ lbase ---------------- */
      if ((j-i) >= 9) {
         v1.alg_energy = tbl_closed(i+1, j-1) + sr_energy(i+1, j);
         v1.alg_enum = new_Sr_f(i+1, back_closed, i+1, j-1, j);
      }
      else {
         v1.alg_energy = 1.0e7;
         v1.alg_enum = NULL;
      }
      /* ---------------- v1 = sr <<< lbase ~~~ p closed ~~~ lbase ---------------- */
      /* -------------------------------- finished -------------------------------- */

      v2 = v1;
   }
   else {
      v2.alg_energy = 1.0e7;
      v2.alg_enum = NULL;
   }
   if (stackpairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /*  v3 = hl <<< lbase ~~~ lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 7) {
         v3.alg_energy = hl_energy(i+2, j-1) + sr_energy(i+1, j);
         v3.alg_enum = new_Hl_(i+1, i+2, i+2, j-2, j-1, j);
      }
      else {
         v3.alg_energy = 1.0e7;
         v3.alg_enum = NULL;
      }
      /*  v3 = hl <<< lbase ~~~ lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v6 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 12) {
         v6.alg_energy = 1.0e7;
         v6.alg_enum = NULL;
         for (k=i+3; k<=j-9; k++) {
            /* ----------------------------- start of ----------------------------- */
            /* --------------- v5 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            v5.alg_energy = tbl_closed(k, j-2) + termaupenalty((k) + 1, j-2);
            v5.alg_enum = new_Is_f(k, back_closed, k, j-2, j-2);
            /* --------------- v5 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v4.alg_energy = (v5.alg_energy + bl_energy(i+2, i+2, k, j-1)) + sr_energy(i+1, j);
            v4.alg_enum = new_Bl_s(i+1, i+2, i+2, k, v5.alg_enum, j-1, j);
            /* ----------------------- v6 = minimum(v4, v6) ----------------------- */
            v6 = v4.alg_energy < v6.alg_energy ? v4 : v6;
         }
      }
      else {
         v6.alg_energy = 1.0e7;
         v6.alg_enum = NULL;
      }
      /*  v6 = bl <<< lbase ~~~ lbase ~~~ region ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v9 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 12) {
         v9.alg_energy = 1.0e7;
         v9.alg_enum = NULL;
         for (k2=i+9; k2<=j-3; k2++) {
            /* ----------------------------- start of ----------------------------- */
            /* --------------- v8 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            v8.alg_energy = tbl_closed(i+2, k2) + termaupenalty((i+2) + 1, k2);
            v8.alg_enum = new_Is_f(i+2, back_closed, i+2, k2, k2);
            /* --------------- v8 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v7.alg_energy = (v8.alg_energy + br_energy(i+2, k2, j-2, j-1)) + sr_energy(i+1, j);
            v7.alg_enum = new_Br_s(i+1, i+2, v8.alg_enum, k2, j-2, j-1, j);
            /* ----------------------- v9 = minimum(v7, v9) ----------------------- */
            v9 = v7.alg_energy < v9.alg_energy ? v7 : v9;
         }
      }
      else {
         v9.alg_energy = 1.0e7;
         v9.alg_enum = NULL;
      }
      /*  v9 = br <<< lbase ~~~ lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ region ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v11 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 13) {
         v11.alg_energy = 1.0e7;
         v11.alg_enum = NULL;
         for (k4=max(i+10, j-32); k4<=j-3; k4++) {
            for (k3=i+3; k3<=min(i+34, k4-7); k3++) {
               v10.alg_energy = (tbl_closed(k3, k4) + sr_energy(i+1, j)) + il_energy(i+2, k3, k4, j-2);
               v10.alg_enum = new_Il_f(i+1, i+2, i+2, k3, back_closed, k3, k4, k4, j-2, j-1, j);
               /* -------------------- v11 = minimum(v10, v11) -------------------- */
               v11 = v10.alg_energy < v11.alg_energy ? v10 : v11;
            }
         }
      }
      else {
         v11.alg_energy = 1.0e7;
         v11.alg_enum = NULL;
      }
      /*  v11 = il <<< lbase ~~~ lbase ~~~ (region `with` (maxsize 32.0)) ~~~ p closed ~~~ (region `with` (maxsize 30.0)) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v12 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 19) {
         /* ------------------------------- start of ------------------------------ */
         /* ---------------- v14 = combine <<< p block ~~~ p comps ---------------- */
         v14.alg_energy = 1.0e7;
         v14.alg_enum = NULL;
         for (k5=i+10; k5<=j-9; k5++) {
            v13.alg_energy = tbl_block(i+3, k5) + tbl_comps(k5, j-2);
            v13.alg_enum = new_Combine_ff(back_block, i+3, k5, back_comps, k5, j-2);
            /* --------------------- v14 = minimum(v13, v14) ---------------------- */
            v14 = v13.alg_energy < v14.alg_energy ? v13 : v14;
         }
         /* ---------------- v14 = combine <<< p block ~~~ p comps ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v12.alg_energy = (((380 + v14.alg_energy) + dli_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
         v12.alg_enum = new_Mldl_s(i+1, i+2, i+3, v14.alg_enum, j-1, j);
      }
      else {
         v12.alg_energy = 1.0e7;
         v12.alg_enum = NULL;
      }
      /*  v12 = mldl <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v15 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 19) {
         /* ------------------------------- start of ------------------------------ */
         /* ---------------- v17 = combine <<< p block ~~~ p comps ---------------- */
         v17.alg_energy = 1.0e7;
         v17.alg_enum = NULL;
         for (k6=i+9; k6<=j-10; k6++) {
            v16.alg_energy = tbl_block(i+2, k6) + tbl_comps(k6, j-3);
            v16.alg_enum = new_Combine_ff(back_block, i+2, k6, back_comps, k6, j-3);
            /* --------------------- v17 = minimum(v16, v17) ---------------------- */
            v17 = v16.alg_energy < v17.alg_energy ? v16 : v17;
         }
         /* ---------------- v17 = combine <<< p block ~~~ p comps ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v15.alg_energy = (((380 + v17.alg_energy) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
         v15.alg_enum = new_Mldr_s(i+1, i+2, v17.alg_enum, j-2, j-1, j);
      }
      else {
         v15.alg_energy = 1.0e7;
         v15.alg_enum = NULL;
      }
      /*  v15 = mldr <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v18 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 20) {
         /* ------------------------------- start of ------------------------------ */
         /* ---------------- v20 = combine <<< p block ~~~ p comps ---------------- */
         v20.alg_energy = 1.0e7;
         v20.alg_enum = NULL;
         for (k7=i+10; k7<=j-10; k7++) {
            v19.alg_energy = tbl_block(i+3, k7) + tbl_comps(k7, j-3);
            v19.alg_enum = new_Combine_ff(back_block, i+3, k7, back_comps, k7, j-3);
            /* --------------------- v20 = minimum(v19, v20) ---------------------- */
            v20 = v19.alg_energy < v20.alg_energy ? v19 : v20;
         }
         /* ---------------- v20 = combine <<< p block ~~~ p comps ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v18.alg_energy = ((((380 + v20.alg_energy) + dli_energy(i+2, j-1)) + dri_energy(i+2, j-1)) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
         v18.alg_enum = new_Mldlr_s(i+1, i+2, i+3, v20.alg_enum, j-2, j-1, j);
      }
      else {
         v18.alg_energy = 1.0e7;
         v18.alg_enum = NULL;
      }
      /*  v18 = mldlr <<< lbase ~~~ lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /*  v21 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
      if ((j-i) >= 18) {
         /* ------------------------------- start of ------------------------------ */
         /* ---------------- v23 = combine <<< p block ~~~ p comps ---------------- */
         v23.alg_energy = 1.0e7;
         v23.alg_enum = NULL;
         for (k8=i+9; k8<=j-9; k8++) {
            v22.alg_energy = tbl_block(i+2, k8) + tbl_comps(k8, j-2);
            v22.alg_enum = new_Combine_ff(back_block, i+2, k8, back_comps, k8, j-2);
            /* --------------------- v23 = minimum(v22, v23) ---------------------- */
            v23 = v22.alg_energy < v23.alg_energy ? v22 : v23;
         }
         /* ---------------- v23 = combine <<< p block ~~~ p comps ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v21.alg_energy = ((380 + v23.alg_energy) + sr_energy(i+1, j)) + termaupenalty(i+2, j-1);
         v21.alg_enum = new_Ml_s(i+1, i+2, v23.alg_enum, j-1, j);
      }
      else {
         v21.alg_energy = 1.0e7;
         v21.alg_enum = NULL;
      }
      /*  v21 = ml <<< lbase ~~~ lbase ~~~ (combine <<< p block ~~~ p comps) ~~~ lbase ~~~ lbase  */
      /* -------------------------------- finished -------------------------------- */

      /* ------------------------ v24 = minimum(v18, v21) ------------------------- */
      v24 = v18.alg_energy < v21.alg_energy ? v18 : v21;
      /* ------------------------ v25 = minimum(v15, v24) ------------------------- */
      v25 = v15.alg_energy < v24.alg_energy ? v15 : v24;
      /* ------------------------ v26 = minimum(v12, v25) ------------------------- */
      v26 = v12.alg_energy < v25.alg_energy ? v12 : v25;
      /* ------------------------ v27 = minimum(v11, v26) ------------------------- */
      v27 = v11.alg_energy < v26.alg_energy ? v11 : v26;
      /* ------------------------- v28 = minimum(v9, v27) ------------------------- */
      v28 = v9.alg_energy < v27.alg_energy ? v9 : v27;
      /* ------------------------- v29 = minimum(v6, v28) ------------------------- */
      v29 = v6.alg_energy < v28.alg_energy ? v6 : v28;
      /* ------------------------- v30 = minimum(v3, v29) ------------------------- */
      v30 = v3.alg_energy < v29.alg_energy ? v3 : v29;
      v31 = v30;
   }
   else {
      v31.alg_energy = 1.0e7;
      v31.alg_enum = NULL;
   }
   /* --------------------------- v32 = minimum(v2, v31) -------------------------- */
   v32 = v2.alg_energy < v31.alg_energy ? v2 : v31;
   /* ------------------------- build candidate structures ------------------------ */
   return(build_str_Signature(v32.alg_enum));
}

/* backtracing code for production comps                                            */
/* -------------------------------------------------------------------------------- */
static struct str_Signature *back_comps(int i, int j)
{
   struct str3 v1, v2, v3, v4, v5, v6, v7;
   int k, k2;

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v2 = cons <<< p block ~~~ p comps --------------------- */
   if ((j-i) >= 14) {
      v2.alg_energy = 1.0e7;
      v2.alg_enum = NULL;
      for (k=i+7; k<=j-7; k++) {
         v1.alg_energy = tbl_block(i, k) + tbl_comps(k, j);
         v1.alg_enum = new_Cons_ff(back_block, i, k, back_comps, k, j);
         /* ------------------------- v2 = minimum(v1, v2) ------------------------ */
         v2 = v1.alg_energy < v2.alg_energy ? v1 : v2;
      }
   }
   else {
      v2.alg_energy = 1.0e7;
      v2.alg_enum = NULL;
   }
   /* --------------------- v2 = cons <<< p block ~~~ p comps --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* -------------------------------- v3 = p block ------------------------------- */
   if ((j-i) >= 7) {
      v3.alg_energy = tbl_block(i, j);
      v3.alg_enum = new__NTID(back_block, i, j);
   }
   else {
      v3.alg_energy = 1.0e7;
      v3.alg_enum = NULL;
   }
   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v5 = addss <<< p block ~~~ region --------------------- */
   if ((j-i) >= 8) {
      v5.alg_energy = 1.0e7;
      v5.alg_enum = NULL;
      for (k2=i+7; k2<=j-1; k2++) {
         v4.alg_energy = tbl_block(i, k2) + ss_energy(k2, j);
         v4.alg_enum = new_Addss_f(back_block, i, k2, k2, j);
         /* ------------------------- v5 = minimum(v4, v5) ------------------------ */
         v5 = v4.alg_energy < v5.alg_energy ? v4 : v5;
      }
   }
   else {
      v5.alg_energy = 1.0e7;
      v5.alg_enum = NULL;
   }
   /* --------------------- v5 = addss <<< p block ~~~ region --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------- v6 = minimum(v3, v5) --------------------------- */
   v6 = v3.alg_energy < v5.alg_energy ? v3 : v5;
   /* ---------------------------- v7 = minimum(v2, v6) --------------------------- */
   v7 = v2.alg_energy < v6.alg_energy ? v2 : v6;
   /* ------------------------- build candidate structures ------------------------ */
   return(build_str_Signature(v7.alg_enum));
}

/* backtracing code for production block                                            */
/* -------------------------------------------------------------------------------- */
static struct str_Signature *back_block(int i, int j)
{
   struct str3 v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;
   struct str3 v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22;
   struct str3 v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34;
   int k;

   /* ---------------------------------- start of --------------------------------- */
   /*  v1 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h  */
   if ((j-i) >= 7) {
      /* -------------------------------- start of -------------------------------- */
      /* ---- v2 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ----- */
      if ((j-i) >= 8) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------------- v3 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         v3.alg_energy = tbl_closed(i+1, j) + termaupenalty((i+1) + 1, j);
         v3.alg_enum = new_Is_f(i+1, back_closed, i+1, j, j);
         /* ----------------- v3 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v2.alg_energy = v3.alg_energy + dl_energy((i+1) + 1, j);
         v2.alg_enum = new_Dl_s(i+1, v3.alg_enum, j);
      }
      else {
         v2.alg_energy = 1.0e7;
         v2.alg_enum = NULL;
      }
      /* ---- v2 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ----- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ---- v4 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ----- */
      if ((j-i) >= 8) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------------- v5 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         v5.alg_energy = tbl_closed(i, j-1) + termaupenalty((i) + 1, j-1);
         v5.alg_enum = new_Is_f(i, back_closed, i, j-1, j-1);
         /* ----------------- v5 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v4.alg_energy = v5.alg_energy + dr_energy((i) + 1, (j) - 1);
         v4.alg_enum = new_Dr_s(i, v5.alg_enum, j);
      }
      else {
         v4.alg_energy = 1.0e7;
         v4.alg_enum = NULL;
      }
      /* ---- v4 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ----- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* --- v6 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase --- */
      if ((j-i) >= 9) {
         /* ------------------------------- start of ------------------------------ */
         /* ----------------- v7 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         v7.alg_energy = tbl_closed(i+1, j-1) + termaupenalty((i+1) + 1, j-1);
         v7.alg_enum = new_Is_f(i+1, back_closed, i+1, j-1, j-1);
         /* ----------------- v7 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v6.alg_energy = (v7.alg_energy + dl_energy((i+1) + 1, (j) - 1)) + dr_energy((i+1) + 1, (j) - 1);
         v6.alg_enum = new_Dlr_s(i+1, v7.alg_enum, j);
      }
      else {
         v6.alg_energy = 1.0e7;
         v6.alg_enum = NULL;
      }
      /* --- v6 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase --- */
      /* -------------------------------- finished -------------------------------- */

      /* -------------------------------- start of -------------------------------- */
      /* ------------- v8 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- start of -------------------------------- */
      /* ------------------ v9 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      v9.alg_energy = tbl_closed(i, j) + termaupenalty((i) + 1, j);
      v9.alg_enum = new_Is_f(i, back_closed, i, j, j);
      /* ------------------ v9 = is <<< loc ~~~ p closed ~~~ loc ------------------ */
      /* -------------------------------- finished -------------------------------- */

      v8.alg_energy = v9.alg_energy;
      v8.alg_enum = new_Drem_s(v9.alg_enum);
      /* ------------- v8 = drem <<< is <<< loc ~~~ p closed ~~~ loc -------------- */
      /* -------------------------------- finished -------------------------------- */

      /* ------------------------- v10 = minimum(v6, v8) -------------------------- */
      v10 = v6.alg_energy < v8.alg_energy ? v6 : v8;
      /* ------------------------- v11 = minimum(v4, v10) ------------------------- */
      v11 = v4.alg_energy < v10.alg_energy ? v4 : v10;
      /* ------------------------- v12 = minimum(v2, v11) ------------------------- */
      v12 = v2.alg_energy < v11.alg_energy ? v2 : v11;
      v1.alg_energy = 40 + v12.alg_energy;
      v1.alg_enum = new_Ul_s(v12.alg_enum);
   }
   else {
      v1.alg_energy = 1.0e7;
      v1.alg_enum = NULL;
   }
   /*  v1 = ul <<< dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h  */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /*  v25 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h)  */
   if ((j-i) >= 8) {
      v25.alg_energy = 1.0e7;
      v25.alg_enum = NULL;
      for (k=i+1; k<=j-7; k++) {
         /* ------------------------------- start of ------------------------------ */
         /* --- v14 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc -- */
         if ((j-k) >= 8) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v15 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            v15.alg_energy = tbl_closed(k+1, j) + termaupenalty((k+1) + 1, j);
            v15.alg_enum = new_Is_f(k+1, back_closed, k+1, j, j);
            /* -------------- v15 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v14.alg_energy = v15.alg_energy + dl_energy((k+1) + 1, j);
            v14.alg_enum = new_Dl_s(k+1, v15.alg_enum, j);
         }
         else {
            v14.alg_energy = 1.0e7;
            v14.alg_enum = NULL;
         }
         /* --- v14 = dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc -- */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* --- v16 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase -- */
         if ((j-k) >= 8) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v17 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            v17.alg_energy = tbl_closed(k, j-1) + termaupenalty((k) + 1, j-1);
            v17.alg_enum = new_Is_f(k, back_closed, k, j-1, j-1);
            /* -------------- v17 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v16.alg_energy = v17.alg_energy + dr_energy((k) + 1, (j) - 1);
            v16.alg_enum = new_Dr_s(k, v17.alg_enum, j);
         }
         else {
            v16.alg_energy = 1.0e7;
            v16.alg_enum = NULL;
         }
         /* --- v16 = dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase -- */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* - v18 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase - */
         if ((j-k) >= 9) {
            /* ----------------------------- start of ----------------------------- */
            /* -------------- v19 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            v19.alg_energy = tbl_closed(k+1, j-1) + termaupenalty((k+1) + 1, j-1);
            v19.alg_enum = new_Is_f(k+1, back_closed, k+1, j-1, j-1);
            /* -------------- v19 = is <<< loc ~~~ p closed ~~~ loc --------------- */
            /* ----------------------------- finished ----------------------------- */

            v18.alg_energy = (v19.alg_energy + dl_energy((k+1) + 1, (j) - 1)) + dr_energy((k+1) + 1, (j) - 1);
            v18.alg_enum = new_Dlr_s(k+1, v19.alg_enum, j);
         }
         else {
            v18.alg_energy = 1.0e7;
            v18.alg_enum = NULL;
         }
         /* - v18 = dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase - */
         /* ------------------------------- finished ------------------------------ */

         /* ------------------------------- start of ------------------------------ */
         /* ------------ v20 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
         /* ------------------------------- start of ------------------------------ */
         /* ---------------- v21 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         v21.alg_energy = tbl_closed(k, j) + termaupenalty((k) + 1, j);
         v21.alg_enum = new_Is_f(k, back_closed, k, j, j);
         /* ---------------- v21 = is <<< loc ~~~ p closed ~~~ loc ---------------- */
         /* ------------------------------- finished ------------------------------ */

         v20.alg_energy = v21.alg_energy;
         v20.alg_enum = new_Drem_s(v21.alg_enum);
         /* ------------ v20 = drem <<< is <<< loc ~~~ p closed ~~~ loc ----------- */
         /* ------------------------------- finished ------------------------------ */

         /* ----------------------- v22 = minimum(v18, v20) ----------------------- */
         v22 = v18.alg_energy < v20.alg_energy ? v18 : v20;
         /* ----------------------- v23 = minimum(v16, v22) ----------------------- */
         v23 = v16.alg_energy < v22.alg_energy ? v16 : v22;
         /* ----------------------- v24 = minimum(v14, v23) ----------------------- */
         v24 = v14.alg_energy < v23.alg_energy ? v14 : v23;
         v13.alg_energy = (40 + v24.alg_energy) + ss_energy(i, k);
         v13.alg_enum = new_Ssadd_s(i, k, v24.alg_enum);
         /* ----------------------- v25 = minimum(v13, v25) ----------------------- */
         v25 = v13.alg_energy < v25.alg_energy ? v13 : v25;
      }
   }
   else {
      v25.alg_energy = 1.0e7;
      v25.alg_enum = NULL;
   }
   /*  v25 = ssadd <<< region ~~~ (dl <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ loc ||| dr <<< loc ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| dlr <<< lbase ~~~ (is <<< loc ~~~ p closed ~~~ loc) ~~~ lbase ||| drem <<< is <<< loc ~~~ p closed ~~~ loc ... h)  */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v26 = pkmldl <<< lbase ~~~ p knot --------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      v26.alg_energy = (tbl_knot(i+1, j).tup1 + 600) + (wkn * dl_energy((i+1) + 1, tbl_knot(i+1, j).tup3));
      v26.alg_enum = new_Pkmldl_f(i+1, back_knot, i+1, j, tbl_knot(i+1, j).tup2, tbl_knot(i+1, j).tup3);
   }
   else {
      v26.alg_energy = 1.0e7;
      v26.alg_enum = NULL;
   }
   /* --------------------- v26 = pkmldl <<< lbase ~~~ p knot --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------- v27 = pkmldr <<< p knot ~~~ lbase --------------------- */
   if (((j-i) >= 12) && ((j-i) <= (max_pknot_length+1))) {
      v27.alg_energy = (tbl_knot(i, j-1).tup1 + 600) + (wkn * dr_energy(tbl_knot(i, j-1).tup2 + 1, (j) - 1));
      v27.alg_enum = new_Pkmldr_f(back_knot, i, j-1, tbl_knot(i, j-1).tup2, tbl_knot(i, j-1).tup3, j);
   }
   else {
      v27.alg_energy = 1.0e7;
      v27.alg_enum = NULL;
   }
   /* --------------------- v27 = pkmldr <<< p knot ~~~ lbase --------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* ---------------- v28 = pkmldlr <<< lbase ~~~ p knot ~~~ lbase --------------- */
   if (((j-i) >= 13) && ((j-i) <= (max_pknot_length+2))) {
      v28.alg_energy = (tbl_knot(i+1, j-1).tup1 + 600) + (wkn * (dl_energy((i+1) + 1, tbl_knot(i+1, j-1).tup3) + dr_energy(tbl_knot(i+1, j-1).tup2 + 1, (j) - 1)));
      v28.alg_enum = new_Pkmldlr_f(i+1, back_knot, i+1, j-1, tbl_knot(i+1, j-1).tup2, tbl_knot(i+1, j-1).tup3, j);
   }
   else {
      v28.alg_energy = 1.0e7;
      v28.alg_enum = NULL;
   }
   /* ---------------- v28 = pkmldlr <<< lbase ~~~ p knot ~~~ lbase --------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ---------------------------------- start of --------------------------------- */
   /* --------------------------- v29 = pkml <<< p knot --------------------------- */
   if (((j-i) >= 11) && ((j-i) <= (max_pknot_length))) {
      v29.alg_energy = tbl_knot(i, j).tup1 + 600;
      v29.alg_enum = new_Pkml_f(back_knot, i, j, tbl_knot(i, j).tup2, tbl_knot(i, j).tup3);
   }
   else {
      v29.alg_energy = 1.0e7;
      v29.alg_enum = NULL;
   }
   /* --------------------------- v29 = pkml <<< p knot --------------------------- */
   /* ---------------------------------- finished --------------------------------- */

   /* -------------------------- v30 = minimum(v28, v29) -------------------------- */
   v30 = v28.alg_energy < v29.alg_energy ? v28 : v29;
   /* -------------------------- v31 = minimum(v27, v30) -------------------------- */
   v31 = v27.alg_energy < v30.alg_energy ? v27 : v30;
   /* -------------------------- v32 = minimum(v26, v31) -------------------------- */
   v32 = v26.alg_energy < v31.alg_energy ? v26 : v31;
   /* -------------------------- v33 = minimum(v25, v32) -------------------------- */
   v33 = v25.alg_energy < v32.alg_energy ? v25 : v32;
   /* --------------------------- v34 = minimum(v1, v33) -------------------------- */
   v34 = v1.alg_energy < v33.alg_energy ? v1 : v33;
   /* ------------------------- build candidate structures ------------------------ */
   return(build_str_Signature(v34.alg_enum));
}

/* backtracing code for production knot                                             */
/* -------------------------------------------------------------------------------- */
static struct str_Signature *back_knot(int i, int j)
{
   struct str3 v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13;
   struct str3 v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26;
   struct str3 v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39;
   struct str3 v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52;
   struct str4 v1, v53;
   int lc_alphanrg, lc_betalen, lc_betanrg, lc_correctionterm, lc_energy;
   int lc_h, lc_h_Pr, lc_k, lc_l, lc_middle_k, lc_middle_l;

   /* ---------------------------------- start of --------------------------------- */
   /* ------- v53 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------- */
   if ((j-i) >= 0) {
      v53.alg_energy.tup1 = 1.0e7;
      v53.alg_energy.tup2 = 0;
      v53.alg_energy.tup3 = 0;
      v53.alg_enum = NULL;
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
                  /* --- v2 = co <<< pul <<< pss <<< uregion ||| p comps ... h ---- */
                  if ((lc_l-(i+lc_h)-1) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v3 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v4 = pss <<< uregion ------------------ */
                     v4.alg_energy = sspenalty((lc_l) - (i+lc_h+1));
                     v4.alg_enum = new_Pss_(i+lc_h+1, lc_l);
                     /* ------------------- v4 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v3.alg_energy = v4.alg_energy;
                     v3.alg_enum = new_Pul_s(v4.alg_enum);
                     /* --------------- v3 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ----------------------- v5 = p comps ---------------------- */
                     if ((lc_l-(i+lc_h)-1) >= 7) {
                        v5.alg_energy = tbl_comps(i+lc_h+1, lc_l);
                        v5.alg_enum = new__NTID(back_comps, i+lc_h+1, lc_l);
                     }
                     else {
                        v5.alg_energy = 1.0e7;
                        v5.alg_enum = NULL;
                     }
                     /* ------------------- v6 = minimum(v3, v5) ------------------ */
                     v6 = v3.alg_energy < v5.alg_energy ? v3 : v5;
                     v2.alg_energy = v6.alg_energy;
                     v2.alg_enum = new_Co_s(v6.alg_enum);
                  }
                  else {
                     v2.alg_energy = 1.0e7;
                     v2.alg_enum = NULL;
                  }
                  /* --- v2 = co <<< pul <<< pss <<< uregion ||| p comps ... h ---- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* = frd j <<< (pul <<< pss <<< uregion ||| p comps ... h) ~~~ lb */
                  if ((lc_l-(i+lc_h)-1) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v8 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v9 = pss <<< uregion ------------------ */
                     v9.alg_energy = sspenalty((lc_l-1) - (i+lc_h+1));
                     v9.alg_enum = new_Pss_(i+lc_h+1, lc_l-1);
                     /* ------------------- v9 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v8.alg_energy = v9.alg_energy;
                     v8.alg_enum = new_Pul_s(v9.alg_enum);
                     /* --------------- v8 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v10 = p comps ---------------------- */
                     if ((lc_l-(i+lc_h)-2) >= 7) {
                        v10.alg_energy = tbl_comps(i+lc_h+1, lc_l-1);
                        v10.alg_enum = new__NTID(back_comps, i+lc_h+1, lc_l-1);
                     }
                     else {
                        v10.alg_energy = 1.0e7;
                        v10.alg_enum = NULL;
                     }
                     /* ------------------ v11 = minimum(v8, v10) ----------------- */
                     v11 = v8.alg_energy < v10.alg_energy ? v8 : v10;
                     v7.alg_energy = (v11.alg_energy + (wkn * dl_energy((lc_l) + 1, j))) + npp;
                     v7.alg_enum = new_Frd_s(j, v11.alg_enum, lc_l);
                  }
                  else {
                     v7.alg_energy = 1.0e7;
                     v7.alg_enum = NULL;
                  }
                  /* = frd j <<< (pul <<< pss <<< uregion ||| p comps ... h) ~~~ lb */
                  /* -------------------------- finished -------------------------- */

                  /* ------------------- v12 = minimum(v2, v7) -------------------- */
                  v12 = v2.alg_energy < v7.alg_energy ? v2 : v7;
                  /* -------------------------- start of -------------------------- */
                  /* ------ v13 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 0) {
                     v13.alg_energy = wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, lc_l+lc_h_Pr, (lc_l+lc_h_Pr) + 1);
                     v13.alg_enum = new_Emptymid_(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr);
                  }
                  else {
                     v13.alg_energy = 1.0e7;
                     v13.alg_enum = NULL;
                  }
                  /* ------ v13 = emptymid lc_middle_k lc_middle_l <<< empty ------ */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* ------ v14 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 1) {
                     v14.alg_energy = (wkn * stack_dg_ac(lc_middle_l, lc_middle_k + 1, (lc_k-lc_h) - 1, (lc_k-lc_h) + 1)) + npp;
                     v14.alg_enum = new_Midbase_(lc_middle_k, lc_middle_l, lc_k-lc_h);
                  }
                  else {
                     v14.alg_energy = 1.0e7;
                     v14.alg_enum = NULL;
                  }
                  /* ------ v14 = midbase lc_middle_k lc_middle_l <<< lbase ------- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* - v15 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) == 2) {
                     v15.alg_energy = (2 * npp) + (wkn * (dri_energy(lc_middle_l, (lc_l+lc_h_Pr+1) + 2) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                     v15.alg_enum = new_Middlro_(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr+1, lc_k-lc_h);
                  }
                  else {
                     v15.alg_energy = 1.0e7;
                     v15.alg_enum = NULL;
                  }
                  /* - v15 = middlro lc_middle_k lc_middle_l <<< lbase ~~~ lbase -- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v16 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h)  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v17 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v18 = pss <<< region ------------------ */
                     v18.alg_energy = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr+1));
                     v18.alg_enum = new_Pss_(lc_l+lc_h_Pr+1, lc_k-lc_h);
                     /* ------------------- v18 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v17.alg_energy = v18.alg_energy;
                     v17.alg_enum = new_Pul_s(v18.alg_enum);
                     /* --------------- v17 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v19 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v19.alg_energy = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h);
                        v19.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr+1, lc_k-lc_h);
                     }
                     else {
                        v19.alg_energy = 1.0e7;
                        v19.alg_enum = NULL;
                     }
                     /* ----------------- v20 = minimum(v17, v19) ----------------- */
                     v20 = v17.alg_energy < v19.alg_energy ? v17 : v19;
                     v16.alg_energy = (v20.alg_energy + npp) + (wkn * dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1));
                     v16.alg_enum = new_Middl_s(lc_middle_k, lc_l+lc_h_Pr+1, v20.alg_enum);
                  }
                  else {
                     v16.alg_energy = 1.0e7;
                     v16.alg_enum = NULL;
                  }
                  /*  v16 = middl lc_middle_k <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h)  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v21 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ... h) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 2) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v22 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v23 = pss <<< region ------------------ */
                     v23.alg_energy = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr));
                     v23.alg_enum = new_Pss_(lc_l+lc_h_Pr, lc_k-lc_h-1);
                     /* ------------------- v23 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v22.alg_energy = v23.alg_energy;
                     v22.alg_enum = new_Pul_s(v23.alg_enum);
                     /* --------------- v22 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v24 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-1) >= 7) {
                        v24.alg_energy = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h-1);
                        v24.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr, lc_k-lc_h-1);
                     }
                     else {
                        v24.alg_energy = 1.0e7;
                        v24.alg_enum = NULL;
                     }
                     /* ----------------- v25 = minimum(v22, v24) ----------------- */
                     v25 = v22.alg_energy < v24.alg_energy ? v22 : v24;
                     v21.alg_energy = (v25.alg_energy + npp) + (wkn * dri_energy(lc_middle_l, (lc_k-lc_h) + 1));
                     v21.alg_enum = new_Middr_s(lc_middle_l, v25.alg_enum, lc_k-lc_h);
                  }
                  else {
                     v21.alg_energy = 1.0e7;
                     v21.alg_enum = NULL;
                  }
                  /*  v21 = middr lc_middle_l <<< (pul <<< pss <<< region ||| p comps ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v26 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h) ~~~ lbase  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 3) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v27 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v28 = pss <<< region ------------------ */
                     v28.alg_energy = sspenalty((lc_k-lc_h-1) - (lc_l+lc_h_Pr+1));
                     v28.alg_enum = new_Pss_(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                     /* ------------------- v28 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v27.alg_energy = v28.alg_energy;
                     v27.alg_enum = new_Pul_s(v28.alg_enum);
                     /* --------------- v27 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v29 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)-2) >= 7) {
                        v29.alg_energy = tbl_comps(lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                        v29.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr+1, lc_k-lc_h-1);
                     }
                     else {
                        v29.alg_energy = 1.0e7;
                        v29.alg_enum = NULL;
                     }
                     /* ----------------- v30 = minimum(v27, v29) ----------------- */
                     v30 = v27.alg_energy < v29.alg_energy ? v27 : v29;
                     v26.alg_energy = (v30.alg_energy + (2 * npp)) + (wkn * (dri_energy(lc_middle_l, (lc_k-lc_h) + 1) + dli_energy((lc_l+lc_h_Pr+1) - 1, lc_middle_k + 1)));
                     v26.alg_enum = new_Middlr_s(lc_middle_k, lc_middle_l, lc_l+lc_h_Pr+1, v30.alg_enum, lc_k-lc_h);
                  }
                  else {
                     v26.alg_energy = 1.0e7;
                     v26.alg_enum = NULL;
                  }
                  /*  v26 = middlr lc_middle_k lc_middle_l <<< lbase ~~~ (pul <<< pss <<< region ||| p comps ... h) ~~~ lbase  */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /*  v31 = midregion <<< pul <<< pss <<< region ||| p comps ... h  */
                  if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* --------------- v32 = pul <<< pss <<< region -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------- v33 = pss <<< region ------------------ */
                     v33.alg_energy = sspenalty((lc_k-lc_h) - (lc_l+lc_h_Pr));
                     v33.alg_enum = new_Pss_(lc_l+lc_h_Pr, lc_k-lc_h);
                     /* ------------------- v33 = pss <<< region ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v32.alg_energy = v33.alg_energy;
                     v32.alg_enum = new_Pul_s(v33.alg_enum);
                     /* --------------- v32 = pul <<< pss <<< region -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v34 = p comps ---------------------- */
                     if ((lc_k-lc_h-(lc_l+lc_h_Pr)) >= 7) {
                        v34.alg_energy = tbl_comps(lc_l+lc_h_Pr, lc_k-lc_h);
                        v34.alg_enum = new__NTID(back_comps, lc_l+lc_h_Pr, lc_k-lc_h);
                     }
                     else {
                        v34.alg_energy = 1.0e7;
                        v34.alg_enum = NULL;
                     }
                     /* ----------------- v35 = minimum(v32, v34) ----------------- */
                     v35 = v32.alg_energy < v34.alg_energy ? v32 : v34;
                     v31.alg_energy = v35.alg_energy;
                     v31.alg_enum = new_Midregion_s(v35.alg_enum);
                  }
                  else {
                     v31.alg_energy = 1.0e7;
                     v31.alg_enum = NULL;
                  }
                  /*  v31 = midregion <<< pul <<< pss <<< region ||| p comps ... h  */
                  /* -------------------------- finished -------------------------- */

                  /* ------------------ v36 = minimum(v26, v31) ------------------- */
                  v36 = v26.alg_energy < v31.alg_energy ? v26 : v31;
                  /* ------------------ v37 = minimum(v21, v36) ------------------- */
                  v37 = v21.alg_energy < v36.alg_energy ? v21 : v36;
                  /* ------------------ v38 = minimum(v16, v37) ------------------- */
                  v38 = v16.alg_energy < v37.alg_energy ? v16 : v37;
                  /* ------------------ v39 = minimum(v15, v38) ------------------- */
                  v39 = v15.alg_energy < v38.alg_energy ? v15 : v38;
                  /* ------------------ v40 = minimum(v14, v39) ------------------- */
                  v40 = v14.alg_energy < v39.alg_energy ? v14 : v39;
                  /* ------------------ v41 = minimum(v13, v40) ------------------- */
                  v41 = v13.alg_energy < v40.alg_energy ? v13 : v40;
                  /* -------------------------- start of -------------------------- */
                  /* --- v42 = co <<< pul <<< pss <<< uregion ||| p comps ... h --- */
                  if ((j-lc_h_Pr-lc_k-2) >= 0) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v43 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v44 = pss <<< uregion ------------------ */
                     v44.alg_energy = sspenalty((j-lc_h_Pr-2) - (lc_k));
                     v44.alg_enum = new_Pss_(lc_k, j-lc_h_Pr-2);
                     /* ------------------ v44 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v43.alg_energy = v44.alg_energy;
                     v43.alg_enum = new_Pul_s(v44.alg_enum);
                     /* -------------- v43 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v45 = p comps ---------------------- */
                     if ((j-lc_h_Pr-lc_k-2) >= 7) {
                        v45.alg_energy = tbl_comps(lc_k, j-lc_h_Pr-2);
                        v45.alg_enum = new__NTID(back_comps, lc_k, j-lc_h_Pr-2);
                     }
                     else {
                        v45.alg_energy = 1.0e7;
                        v45.alg_enum = NULL;
                     }
                     /* ----------------- v46 = minimum(v43, v45) ----------------- */
                     v46 = v43.alg_energy < v45.alg_energy ? v43 : v45;
                     v42.alg_energy = v46.alg_energy;
                     v42.alg_enum = new_Co_s(v46.alg_enum);
                  }
                  else {
                     v42.alg_energy = 1.0e7;
                     v42.alg_enum = NULL;
                  }
                  /* --- v42 = co <<< pul <<< pss <<< uregion ||| p comps ... h --- */
                  /* -------------------------- finished -------------------------- */

                  /* -------------------------- start of -------------------------- */
                  /* = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ... */
                  if ((j-lc_h_Pr-lc_k-2) >= 1) {
                     /* ------------------------- start of ------------------------ */
                     /* -------------- v48 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- start of ------------------------ */
                     /* ------------------ v49 = pss <<< uregion ------------------ */
                     v49.alg_energy = sspenalty((j-lc_h_Pr-2) - (lc_k+1));
                     v49.alg_enum = new_Pss_(lc_k+1, j-lc_h_Pr-2);
                     /* ------------------ v49 = pss <<< uregion ------------------ */
                     /* ------------------------- finished ------------------------ */

                     v48.alg_energy = v49.alg_energy;
                     v48.alg_enum = new_Pul_s(v49.alg_enum);
                     /* -------------- v48 = pul <<< pss <<< uregion -------------- */
                     /* ------------------------- finished ------------------------ */

                     /* ---------------------- v50 = p comps ---------------------- */
                     if ((j-lc_h_Pr-lc_k-3) >= 7) {
                        v50.alg_energy = tbl_comps(lc_k+1, j-lc_h_Pr-2);
                        v50.alg_enum = new__NTID(back_comps, lc_k+1, j-lc_h_Pr-2);
                     }
                     else {
                        v50.alg_energy = 1.0e7;
                        v50.alg_enum = NULL;
                     }
                     /* ----------------- v51 = minimum(v48, v50) ----------------- */
                     v51 = v48.alg_energy < v50.alg_energy ? v48 : v50;
                     v47.alg_energy = (v51.alg_energy + (wkn * dr_energy(i + 1, (lc_k+1) - 1))) + npp;
                     v47.alg_enum = new_Bkd_s(i, lc_k+1, v51.alg_enum);
                  }
                  else {
                     v47.alg_energy = 1.0e7;
                     v47.alg_enum = NULL;
                  }
                  /* = bkd i <<< lbase ~~~ (pul <<< pss <<< uregion ||| p comps ... */
                  /* -------------------------- finished -------------------------- */

                  /* ------------------ v52 = minimum(v42, v47) ------------------- */
                  v52 = v42.alg_energy < v47.alg_energy ? v42 : v47;
                  v1.alg_energy.tup1 = (((((pkinit + lc_energy) + (3 * npp)) + v12.alg_energy) + v41.alg_energy) + v52.alg_energy) + dangles(i, i+lc_h, lc_l, lc_l+lc_h_Pr, lc_k-lc_h, lc_k, j-lc_h_Pr, j);
                  v1.alg_energy.tup2 = lc_l;
                  v1.alg_energy.tup3 = lc_k;
                  v1.alg_enum = new_Pk_Pr_sss(lc_energy, i, i+lc_h, v12.alg_enum, lc_l, lc_l+lc_h_Pr, v41.alg_enum, lc_k-lc_h, lc_k, v52.alg_enum, j-lc_h_Pr, j);
               }
               else {
                  v1.alg_energy.tup1 = 1.0e7;
                  v1.alg_energy.tup2 = 0;
                  v1.alg_energy.tup3 = 0;
                  v1.alg_enum = NULL;
               }
            }
            else {
               v1.alg_energy.tup1 = 1.0e7;
               v1.alg_energy.tup2 = 0;
               v1.alg_energy.tup3 = 0;
               v1.alg_enum = NULL;
            }
            /* ---------------------- v53 = minimum(v1, v53) ---------------------- */
            v53 = v1.alg_energy.tup1 < v53.alg_energy.tup1 ? v1 : v53;
         }
      }
   }
   else {
      v53.alg_energy.tup1 = 1.0e7;
      v53.alg_energy.tup2 = 0;
      v53.alg_energy.tup3 = 0;
      v53.alg_enum = NULL;
   }
   /* ------- v53 = [pk_Pr(lc_energy, lc_a, lc_u, lc_b, lc_v, lc_a_Pr, ...  ------- */
   /* ---------------------------------- finished --------------------------------- */

   /* ------------------------- build candidate structures ------------------------ */
   return(build_str_Signature(v53.alg_enum));
}

/* backtracing code for production stacklen                                         */
/* -------------------------------------------------------------------------------- */
static struct str_Signature *back_stacklen(int i, int j)
{
   struct str5 v1, v2, v3, v4, v5;

   if (basepairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /* -------------- v1 = sum <<< lbase ~~~ p stacklen ~~~ lbase --------------- */
      if ((j-i) >= 7) {
         v1.alg_energy.tup1 = tbl_stacklen(i+1, j-1).tup1 + sr_energy(i+1, j);
         v1.alg_energy.tup2 = tbl_stacklen(i+1, j-1).tup2 + 1;
         v1.alg_enum = new_Sum_f(i+1, back_stacklen, i+1, j-1, tbl_stacklen(i+1, j-1).tup2, j);
      }
      else {
         v1.alg_energy.tup1 = 1.0e7;
         v1.alg_energy.tup2 = 0;
         v1.alg_enum = NULL;
      }
      /* -------------- v1 = sum <<< lbase ~~~ p stacklen ~~~ lbase --------------- */
      /* -------------------------------- finished -------------------------------- */

      v2 = v1;
   }
   else {
      v2.alg_energy.tup1 = 1.0e7;
      v2.alg_energy.tup2 = 0;
      v2.alg_enum = NULL;
   }
   if (basepairing(i, j)) {
      /* -------------------------------- start of -------------------------------- */
      /* --- v3 = sumend <<< lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ---- */
      if ((j-i) >= 5) {
         v3.alg_energy.tup1 = 0;
         v3.alg_energy.tup2 = 1;
         v3.alg_enum = new_Sumend_(i+1, i+1, j-1, j);
      }
      else {
         v3.alg_energy.tup1 = 1.0e7;
         v3.alg_energy.tup2 = 0;
         v3.alg_enum = NULL;
      }
      /* --- v3 = sumend <<< lbase ~~~ (region `with` (minsize 3.0)) ~~~ lbase ---- */
      /* -------------------------------- finished -------------------------------- */

      v4 = v3;
   }
   else {
      v4.alg_energy.tup1 = 1.0e7;
      v4.alg_energy.tup2 = 0;
      v4.alg_enum = NULL;
   }
   /* ---------------------------- v5 = minimum(v2, v4) --------------------------- */
   v5 = v2.alg_energy.tup1 < v4.alg_energy.tup1 ? v2 : v4;
   /* ------------------------- build candidate structures ------------------------ */
   return(build_str_Signature(v5.alg_enum));
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
   arr_knot=(struct str1 *) malloc((offset[n]+n+1) * sizeof(struct str1 ));
   arr_stacklen=(struct str2 *) malloc((offset[n]+n+1) * sizeof(struct str2 ));
   arr_edangle=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_block=(int *) malloc((offset[n]+n+1) * sizeof(int ));
   arr_struct=(int *) malloc((n+1) * sizeof(int ));
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
   free(arr_edangle);
   free(arr_block);
   free(arr_struct);
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
            tbl_knot(i-p, j-p) = move_str1(tbl_knot(i, j));
         }
         if ((i >= p) && (j >= p)) {
            tbl_stacklen(i-p, j-p) = tbl_stacklen(i, j);
         }
         if ((i >= p) && (j >= p)) {
            tbl_edangle(i-p, j-p) = tbl_edangle(i, j);
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
   struct str_Signature *l;
   struct str_Signature *next;
   int score;
   int pos, startj;

   tableAlloc();
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
            calc_knot(i, j);
            calc_stacklen(i, j);
            calc_edangle(i, j);
            calc_block(i, j);
            if ((j) == (n)) {
               calc_struct(i, j);
            }
            calc_comps(i, j);
         }
      }
      /* --------------------------- show axiom: struct --------------------------- */
      l = back_struct(0, n);
      if(!opts->window_mode) printf("%s\n", seq->original_seq);
      else if (pos==0) print_sequence(opts, seq, opts->window_pos, opts->window_size);
      pp_str_Signature(l);
      printf("  (%.2f)\n", (float) tbl_struct(0, n) / 100);
   }
}

int main_pk_mfe(toptions *_opts, tsequence *_seq)
{
   opts = _opts;
   seq  = _seq;
   z    = _seq->seq - 1;
   n    = _seq->length;

   if (opts->debug) printf("pk-mfe.c\nmax_pknot_length = %d\n",max_pknot_length);

   adplib_init(opts,seq,&z,&n);
   rnalib_init(opts,seq);
   rna_output_descr(opts,seq);
   mainloop();
   freeall();
}


