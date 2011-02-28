if (manoptmode == '-')
switch (manopt) {
  case 'h':
    printf("-h Display this information\n\nOption -h displays a command option overview.\n");
    break;
  case 'H':
    printf("-H <option> Display detailed information on <option>\n\nThis displays the corresponding section of the pknotsRG manual for the\ngiven command line option.\n");
    break;
  case 'v':
    printf("-v Show version\n\nThis shows the version number of pknotsRG.\n");
    break;
  case 'm':
    printf("-m Use mfe strategy\n\nCompute the best structure (the structure with minimum free energy).\nThis is the default strategy.\n");
    break;
  case 'f':
    printf("-f Use enf strategy\n\nCompute the best structure that actually contains at least one\npseudoknot.\n");
    break;
  case 'l':
    printf("-l Use loc strategy\n\nCompute the best \"compact\" pseudoknot, defined as the structure with the\nlowest energy to length ratio.\n");
    break;
  case 's':
    printf("-s Show suboptimals\n\nShow suboptimals. If neither -e nor -c is specified, default is use with\n-c 10. This option can be combined with -m, -f and -l.\n");
    break;
  case 'u':
    printf("-u No dangling bases (implies -s)\n\nThis calculates all structures without dangling bases. Setting this\noption reduces the number of suboptimals drastically.\n");
    break;
  case 'o':
    printf("-o No suboptimals inside pknots (implies -s -l)\n\nUsed with loc-strategy, this option discards all suboptimal structures\ninside of pseudoknots.\n");
    break;
  case 'e':
    printf("-e <value> Set energy range (kcal/mol)\n\nThis sets the energy range for suboptimal results. value is the\ndifference to the minimum free energy for the sequence.\n");
    break;
  case 'c':
    printf("-c <value> Set energy range (%%%%)\n\nThis sets the energy range as percentage value of the minimum free\nenergy. For example, when -c 10 is specified, and the minimum free\nenergy is -10.0 kcal/mol, the energy range is set to -9.0 to -10.0\nkcal/mol.\n");
    break;
  case 'n':
    printf("-n <value> Set npp-value [0.3]\n\nThis option sets the energy penalty for unpaired bases inside of\npseudoknots.\n");
    break;
  case 'p':
    printf("-p <value> Set pkinit-value [9]\n\nThis options sets the energy penalty for creating a new pseudoknot.\n");
    break;
  case 'k':
    printf("-k <value> Set maximal pknot-length\n\nThis option sets the maximal pseudoknot-length allowed.\n");
    break;
  case 'w':
    printf("-w <value> Set window size\n\nBeginning with position 1 of the input sequence, the analysis is\nrepeatedly processed on subsequences of the specified size. After each\ncalculation, the results are printed out and the window is moved by the\nwindow position increment (-W), until the end of the input sequence is\nreached.\n");
    break;
  case 'W':
    printf("-W <value> Set window position increment\n\nThis option specifies the increment for the window analysis mode (-w).\n");
    break;
  case 'S':
    printf("-S <value> Specify output width for structures\n\nThis splits the structure strings into parts of the specified length.\nThis option is useful when displaying results for long sequences that\nwould otherwise not fit onto the screen.\n");
    break;
  case 'F':
    printf("-F <filename> Read input from file\n\nLet pknotsRG load its input data from file. file can contain a plain\nsingle sequence, or multiple sequences in fasta format. When given\nmultiple sequences, each sequence is processed separately in the order\nof input.\n\nValid characters in an input sequence are \"ACGU\" and \"acgu\". \"T\" and \"t\"\nwill be converted to \"U\". Other letters are mapped to \"N\" and will not\nbe paired. All other characters are ignored.\n");
    break;
  case 'z':
    printf("-z Colored output\n\nThis option enables colored output. In interactive mode, this is the\ndefault setting, so use -z to disable colors here.\n");
    break;
  default: fprintf(stderr, "unknown command line option -%c\n", manopt);
}
else
switch (manopt) {
  case 's':
    printf(":s Show current configuration\n\nThis command shows the current settings in an interactive pknotsRG\nsession.\n");
    break;
  case 'd':
    printf(":d Reset configuration\n\nThis command sets all settings to their default values.\n");
    break;
  case 'e':
    printf(":e <string> Execute system command\n\nCommand :e executes a system command.\n");
    break;
  case 'q':
    printf(":q Quit\n\nThis command quits an interactive pknotsRG session.\n");
    break;
  default: fprintf(stderr, "unknown command :%c\n", manopt);
}
