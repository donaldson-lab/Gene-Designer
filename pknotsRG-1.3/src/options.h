/* ---------------------------------------------------------------------------
pknotsRG 1.3
Copyright (C) 2004-2006 Jens Reeder, Robert Giegerich, Peter Steffen
--------------------------------------------------------------------------- */
#ifndef options_h
#define options_h

typedef struct {

  float	traceback_diff;    // Set energy range (kcal/mol) (-e)
  int  	traceback_percent; // Set energy range (%%) (-c)
  char 	window_mode;       // Set window size (-w)
  int  	window_size;       // Set window size (-w)
  int  	window_size_user;  // Set window size (-w)
  int  	window_step;       // Set window position increment (-W)
  char 	split_output_mode; // Specify output width for structures (-S)
  int  	split_output_size; // Specify output width for structures (-S)
  char 	*inputfile;        // Read input from file (-f)
  char 	colored_output;    // Colored output (-z)

  int window_pos;            // current window position
  
  int output_mode;           // output mode (-o)
  char *format_string;       // format string
  
  char interactive;          // interactive mode active
  char terminate;            // terminate program

  char debug;
  char pksOnly;

  char alg;
  char so;
  char nd;

} toptions;

#endif
