/* ---------------------------------------------------------------------------
pknotsRG 1.3
Copyright (C) 2004-2006 Jens Reeder, Robert Giegerich, Peter Steffen
--------------------------------------------------------------------------- */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "config.h"
#include "options.h"
#include "adplib.h"
#include "pknotsRG.h"

/* ====================================================================== 
   Reset mode 
   ====================================================================== */

static void reset_mode(toptions *opt) {
  opt->colored_output = 1; // Colored output (-z)
}


/* ====================================================================== 
   Init default values
   ====================================================================== */

static void init_defaults(toptions *opt) {
  opt->traceback_diff    = 0;    // Set energy range (kcal/mol) (-e)
  opt->traceback_percent = 10;   // Set energy range (%%) (-c)
  opt->window_mode       = 0;    // Set window size (-w)
  opt->window_size       = 0;    // Set window size (-w)
  opt->window_size_user  = 0;    // Set window size (-w)
  opt->window_step       = 1;    // Set window position increment (-W)
  opt->split_output_mode = 0;    // Specify output width for structures (-S)
  opt->split_output_size = 0;    // Specify output width for structures (-S)
  if (opt->inputfile) free(opt->inputfile);
  opt->inputfile         = NULL; // Read input from file (-f)
  opt->colored_output    = 0;    // Colored output (-z)
  opt->terminate            = 0;
  opt->interactive          = 0;
  /* output mode */
  opt->output_mode          = 0;
  opt->format_string        =NULL;

  opt->debug=0;

  opt->alg = 0;
  opt->so = 0;
  opt->nd = 0;
  opt->pksOnly = 0;

  wkn              = 1;    /* The weighting parameter for pseudoknots */
  npp              = 30;   /* Unpaired base in a pseudoknot */
  pbp              = 0;    /* Basepair in a pseudoknot */
  pkinit           = 900;  /* pseudoknot - init - penalty */
  max_pknot_length      = -1;   /* maximal pseudoknot-length (-1 -> maximal) */
  max_pknot_length_user = -1;   /* maximal pseudoknot-length (-1 -> maximal) */
}



/* ====================================================================== 
   Process arguments   
   ====================================================================== */

static void process_args(toptions *opt, char interactive, int argc, char **argv) {
  int   c;
  char  manopt, manoptmode;
  float temp;

  opterr = 0; optind = 1;

  pcolor(opt->colored_output,COLOR_BLUE);
  while ((c = getopt (argc, argv, "hH:ve:c:w:W:S:F:zmflsudon:p:k:")) != -1) {
    switch (c) {

      // Display this information (-h)
      case 'h':
        if (interactive) {
          printf("Interactive mode:\nEnter sequence directly or use the following commands to change settings:\n");
        }
        else {
        
        printf("Options:\n");
        }
        printf("  -h           	Display this information\n");
        printf("  -H <option>  	Display detailed information on <option>\n");
        printf("  -v           	Show version\n");
        printf("  -m            Use mfe strategy\n");
        printf("  -f            Use enf strategy\n");
        printf("  -l            Use loc strategy\n");
        printf("  -s            Show suboptimals\n");
        printf("  -u            no dangling bases (implies -s)\n");
        printf("  -o            no suboptimals inside pknots (implies -s -l)\n");
        printf("  -e <value>   	Set energy range (kcal/mol)\n");
        printf("  -c <value>   	Set energy range (%%)\n");
        printf("  -n <value>    Set npp-value [0.3]\n");
        printf("  -p <value>    Set pkinit-value [9]\n");
        printf("  -k <value>    Set maximal pknot-length\n");
        printf("  -w <value>   	Set window size\n");
        printf("  -W <value>   	Set window position increment\n");
        printf("  -S <value>   	Specify output width for structures\n");
        printf("  -F <filename>	Read input from file\n");
        printf("  -z           	Colored output\n");
        if (opt->interactive) {
        printf("Additional interactive mode commands:\n");
        printf("  :s           	Show current configuration\n");
        printf("  :d           	Reset configuration\n");
        printf("  :e <string>  	Execute system command\n");
        printf("  :q           	Quit\n");
        }
        opt->terminate = 1;
        break;
      // Display detailed information on <option> (-H)
      case 'H':
        if      (optarg[0]=='-') { manoptmode = '-'; manopt = optarg[1]; }
        else if (optarg[0]==':') { manoptmode = ':'; manopt = optarg[1]; }
        else                     { manoptmode = '-'; manopt = optarg[0]; }
        if (!interactive) printf("\n");
        #include "pknotsRG-man.c"
        if (!interactive) printf("\n");
        opt->terminate = 1;
        break;
      // Show version (-v)
      case 'v':
        printf("%s (%s)\n",PACKAGE_STRING,RELEASE_DATE);
        printf("Copyright (C) 2004-2006 Jens Reeder, Robert Giegerich, Peter Steffen\n");
        printf("Send comments/bug reports to: J.Reeder <jreeder@techfak.uni-bielefeld.de>.\n");
        printf("Updates: http://bibiserv.techfak.uni-bielefeld.de/pknotsrg/\n");
        printf("\n");
        printf("pknotsRG contains code from the following contributors:\n");
        printf("\n");
        printf("* Editline library (libedit):\n");
        printf("  Copyright (C) 1997-2003 The NetBSD Foundation, Inc.\n");
        printf("  All rights reserved.\n");
        opt->terminate = 1;
        break;
      // Use mfe strategy
      case 'm':
        opt->alg = 0;
        if (interactive) printf("Use mfe strategy.\n");
        break;
      // Use enf strategy
      case 'f':
        opt->alg = 1;
        if (interactive) printf("Use enf strategy.\n");
        break;
      // Use loc strategy
      case 'l':
        opt->alg = 2;
        if (interactive) printf("Use loc strategy.\n");
        break;
      // Show suboptimals
      case 's':
        if (interactive) {
	  printf("Show suboptimals");
	  opt->so = 1 - opt->so;
	  if (opt->so) printf(" = ON. Type -s again to switch off.\n");
	  else printf(" = OFF. Type -s again to switch on.\n");
	}
        else opt->so = 1;
        break;
      // No dangling bases
      case 'u':
        if (interactive) {
	  printf("No dangling bases");
	  opt->nd = 1 - opt->nd;
	  if (opt->nd) opt->so=1;
	  if (opt->nd) printf(" = ON. Type -u again to switch off.\n");
	  else printf(" = OFF. Type -u again to switch on.\n");
	}
	else {
          opt->nd=1;
          opt->so=1;
	}
        break;
      // No suboptimals inside pknots
      case 'o':
        if (interactive) {
	  printf("No suboptimals inside pknots");
	  opt->pksOnly = 1 - opt->pksOnly;
	  if (opt->pksOnly) {opt->so=1; opt->alg=2;}
	  if (opt->pksOnly) printf(" = ON. Type -o again to switch off.\n");
	  else printf(" = OFF. Type -o again to switch on.\n");
	}
	else {
          opt->pksOnly=1;
          opt->so=1;
          opt->alg=2;
	}
        break;
      // Debug mode
      case 'd':
        opt->debug=1;
	break;
      // Set energy range (kcal/mol) (-e)
      case 'e':
        sscanf(optarg,"%f",&(opt->traceback_diff));
        opt->traceback_diff = max(0, opt->traceback_diff);
        if (interactive) printf("Energy range set to %.2f kcal/mol.\n", opt->traceback_diff);
        
        opt->traceback_percent = 0;
        break;
      // Set energy range (%%) (-c)
      case 'c':
        sscanf(optarg,"%d",&(opt->traceback_percent));
        opt->traceback_percent = max(0, opt->traceback_percent);
        if (interactive) printf("Energy range set to %d%% of mfe.\n", opt->traceback_percent);
        
        opt->traceback_diff = 0;
        break;
      // Set npp value
      case 'n':
        sscanf(optarg,"%f",&temp);
	if (interactive) printf("npp-value set to %.2f.\n", temp);
        npp = (int) (temp * 100);
        break;
      // Set pkinit value
      case 'p':
        sscanf(optarg,"%f",&temp);
	if (interactive) printf("pkinit-value set to %.2f.\n", temp);
        pkinit = (int) (temp * 100);
        break;
      // Set maximal pknot-length
      case 'k':
        sscanf(optarg,"%d",&max_pknot_length_user);
	if (interactive) printf("Maximal pknot-length set to %d.\n", max_pknot_length_user);
        break;
      // Set window size (-w)
      case 'w':
        if ((interactive) && (optarg[0] == '-')) {
          printf("Window mode disabled.\n");
          opt->window_mode = 0;
        }
        if (optarg[0] != '-') {
          opt->window_mode = 1;
          sscanf(optarg,"%d",&(opt->window_size_user));
          opt->window_size_user = max(1, opt->window_size_user);
          if (interactive) printf("Set window size to %d. Type -w - to disable.\n", opt->window_size_user);
        }
        break;
      // Set window position increment (-W)
      case 'W':
        sscanf(optarg,"%d",&(opt->window_step));
        opt->window_step = max(1, opt->window_step);
        if (interactive) printf("Set window position increment to %d.\n", opt->window_step);
        break;
      // Specify output width for structures (-S)
      case 'S':
        if ((interactive) && (optarg[0] == '-')) {
          printf("Output splitting disabled.\n");
          opt->split_output_mode = 0;
        }
        if (optarg[0] != '-') {
          opt->split_output_mode = 1;
          sscanf(optarg,"%d",&(opt->split_output_size));
          opt->split_output_size = max(1, opt->split_output_size);
          if (interactive) printf("Set output size to %d. Type -S - to disable.\n", opt->split_output_size);
        }
        break;
      // Read input from file (-F)
      case 'F':
        if (opt->inputfile) free(opt->inputfile);
        opt->inputfile = mkstr(optarg);
        break;
      // Colored output (-z)
      case 'z':
        if (interactive) {
          printf("Colored output");
          opt->colored_output = 1 - opt->colored_output;
          if (opt->colored_output) printf (" = ON. Type -z again to switch off.\n");
          else printf (" = OFF. Type -z again to switch on.\n");
        }
        else opt->colored_output = 1;
        if (opt->interactive && !opt->colored_output) printf(COLOR_DEFAULT);
        break;
      case '?':
        if (interactive) printf("Unknown option '-%c'. Type -h for more information.\n", optopt);
        else {
          fprintf (stderr, "%s: unknown option `-%c'.\nTry '%s -h' for more information.\n", argv[0], optopt, argv[0]);
          exit(1);
        }
        break;
      default:
        abort ();
      }
  }
  pcolor(opt->colored_output,COLOR_DEFAULT);
}

/* ====================================================================== 
   Print settings
   ====================================================================== */

static void print_settings(toptions *opt) {
 
  printf("Current settings\n-----------------\n");
  printf("Current strategy              ");
  if (opt->alg==0) printf("mfe\n");
  else if (opt->alg==1) printf("enf\n");
  else if (opt->alg==2) printf("loc\n");
  printf("Show suboptimals              %s  (-s)\n", opt->so ? "ON" : "OFF");
  printf("No dangling bases             %s  (-u)\n", opt->nd ? "ON" : "OFF");
  printf("No suboptimals inside pknots  %s  (-o)\n", opt->pksOnly ? "ON" : "OFF");
  printf("Energy range                  %.2f kcal/mol  (-e)\n", opt->traceback_diff);
  printf("Energy range                  %d%% of mfe  (-c)\n", opt->traceback_percent);
  printf("npp-value                     %.2f  (-n)\n", (float) npp / 100);
  printf("pkinit-value                  %.2f  (-p)\n", (float) pkinit / 100);
  if (max_pknot_length_user == -1) 
  printf("Maximal pknot-length          <input length>  (-k)\n");
  else 
  printf("Maximal pknot-length          %d  (-k)\n", max_pknot_length_user);
  if (opt->window_mode)
  printf("Window size:                  %d  (-w)\n", opt->window_size_user);
  else
  printf("Window size:                  %s-  (-w)\n","");
  printf("Window position increment:    %d  (-W)\n", opt->window_step);
  if (opt->split_output_mode)
  printf("Output width for structures:  %d  (-S)\n", opt->split_output_size);
  else
  printf("Output width for structures:  %s-  (-S)\n","");
  printf("Colored output                %s  (-z)\n", opt->colored_output ? "ON" : "OFF" );
}


/* ====================================================================== 
   Main interface
   ====================================================================== */

int main (int argc, char **argv) {
  toptions   *opt;
  tsequence  *seq;
  treadseq   *rs        = NULL; 
  ttokenizer *tokenizer = NULL;
  char       *command;

  opt = (toptions *) calloc(1,sizeof(toptions));

  init_defaults(opt);
  process_args(opt, 0, argc, argv);

  if (!opt->terminate) {
    if (optind < argc)               rs = readseq_open(READSEQ_STRING, argv[optind]);
    else if (opt->inputfile)         rs = readseq_open(READSEQ_FILE,   opt->inputfile);
    else if (!isatty(fileno(stdin))) rs = readseq_open(READSEQ_STDIN,  NULL);
    else {
      printf("Interactive mode. Try `./pknotsRG -h` for more information.\n", argv[0]);
      rl_init();
      opt->interactive = 1;
      opt->colored_output = 1 - opt->colored_output;
      tokenizer = tokenizer_new();
      rs = readseq_open(READSEQ_STRING, "");
    } 

    while (1) {
      if (opt->interactive) {
        if (opt->colored_output) 
          printf("%s\nInput sequence (upper or lower case); :q to quit, -h for help.\n....,....1....,....2....,....3....,....4....,....5....,....6....,....7....,....8\n%s",COLOR_RED,COLOR_DEFAULT);
        else 
	  printf("\nInput sequence (upper or lower case); :q to quit, -h for help.\n....,....1....,....2....,....3....,....4....,....5....,....6....,....7....,....8\n");
        command = rl_gets();

        if (!command || (command[0] == '@') || ((command[0] == ':') && (command[1] == 'q'))) {
          pcolor(opt->colored_output,COLOR_BLUE);
          printf("Leaving pknotsRG.");
          pcolor(opt->colored_output,COLOR_DEFAULT);
          printf("\n");
          exit(0);
        }
        else if (command[0] == ':') {
          pcolor(opt->colored_output,COLOR_BLUE);
          if (command[1] == 's') print_settings(opt);
          if (command[1] == 'd') {
            init_defaults(opt);
            opt->colored_output = 1;
            opt->interactive = 1;
            printf("Activated default configuration.\n");
            pcolor(opt->colored_output,COLOR_DEFAULT);
          }
          if (command[1] == 'e') {
            system(command + 2);
          }
        }
        else if (command[0] == '-') {
          tokenizer_exec(tokenizer, argv[0], command);
          process_args(opt, 1, tokenizer->count, tokenizer->token);
          if (opt->inputfile) { 
            rs = readseq_free(rs);
            rs = readseq_open(READSEQ_FILE, opt->inputfile);
          }
          free(opt->inputfile);
          opt->inputfile = NULL;
        }
        else {
          rs = readseq_free(rs);
          rs = readseq_open(READSEQ_STRING, command);
        }
      }

      while (1) {
        seq = readseq_next_fasta(rs);
        if (!(seq->success)) break;
        if (max_pknot_length_user == (-1)) max_pknot_length=seq->length;
        else                               max_pknot_length=max_pknot_length_user;

        if (!opt->so) {
          if (opt->alg==0) main_pk_mfe(opt,seq);
          if (opt->alg==1) main_pk_enf(opt,seq);
          if (opt->alg==2) main_pk_loc(opt,seq);
        } else {
          if (!opt->nd) {
            if (opt->alg==0) main_pk_mfe_so(opt,seq);
            if (opt->alg==1) main_pk_enf_so(opt,seq);
            if (opt->alg==2) main_pk_loc_so(opt,seq);
          }
          else {
            if (opt->alg==0) main_pk_mfe_so_nd(opt,seq);
            if (opt->alg==1) main_pk_enf_so_nd(opt,seq);
            if (opt->alg==2) main_pk_loc_so_nd(opt,seq);
          }
        }
        sequence_free(seq);
      }

      if (!opt->interactive) break;
    }
  }
  exit(0);
}
