//
//  myCLI.c
//
//  Created by Sebastian Ritter on 20.04.24.
//

#include "myCLI.h"


// Display the help text above.
void displayHelpOnCommandLine(enum Verbosity verbosity) {
  int n;
  
  if (verbosity == 0)
    return;
  for (n = 0; n < (int)(sizeof(helptext) / sizeof(char *)); n++) {
    fprintf(stderr, "%s\n", helptext[n]);
  }
  fflush(stderr);
  exit(0);
}


