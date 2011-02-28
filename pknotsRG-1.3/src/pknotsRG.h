/* ---------------------------------------------------------------------------
pknotsRG 1.3
Copyright (C) 2004-2006 Jens Reeder, Robert Giegerich, Peter Steffen
--------------------------------------------------------------------------- */
#ifndef pknotsRG_h
#define pknotsRG_h

int main_pk_mfe(toptions *_opts, tsequence *_seq);
int main_pk_enf(toptions *_opts, tsequence *_seq);
int main_pk_loc(toptions *_opts, tsequence *_seq);
int main_pk_mfe_so(toptions *_opts, tsequence *_seq);
int main_pk_enf_so(toptions *_opts, tsequence *_seq);
int main_pk_loc_so(toptions *_opts, tsequence *_seq);
int main_pk_mfe_so_nd(toptions *_opts, tsequence *_seq);
int main_pk_enf_so_nd(toptions *_opts, tsequence *_seq);
int main_pk_loc_so_nd(toptions *_opts, tsequence *_seq);

#endif

