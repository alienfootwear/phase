#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// some simple colors, more here:
// https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
// http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
#define C_YELLOW (printf("\033[0;33m"))
#define CB_BLUE  (printf("\033[1;34m"))
#define C_RESET  (printf("\033[0m"))


int main(int argc, char** argv) {
  int* cycle;
  int clen = 0;
  int illustrate = 0;
  int i, tmp, checksum;
  unsigned long step = 1;

  cycle = malloc(sizeof(int) * argc);
  
  for (i = 1; i < argc; i++) {
    tmp = atoi(argv[i]);
    if (tmp == 0) {
      if (strcmp(argv[i], "p") == 0)
	illustrate = 1;
      break;
    }
    else {
      cycle[i - 1] = tmp;
      clen++;
    }
  }

  if (clen == 0) {
    // about
    printf("\nUsage: phase <list of cycle lengths> [p]\n");
    printf("Example: phase 3 5 p\n");
    printf("  The result will show you how many steps it takes for \n");
    printf("  a cycle of 3 and a cycle of 5 to coincide (15).\n");
    printf("  Adding a 'p' outputs an additional illustration of the cycles.\n\n");
    return 0;
  }

  while (1) {
    checksum = 0;
    for (i = 0; i < clen; i++) {
      checksum += ((step % cycle[i]));
      if (illustrate) {
	if (i == 0) putchar(' ');
	CB_BLUE;
	printf("%s", (((step % cycle[i]) == 1 || cycle[i] == 1) ? "^ " : "  "));
	C_RESET;
      }
    }
    if (illustrate) {
      C_YELLOW;
      printf("  %lu\n", step);
      C_RESET;
    }

    // If it adds to 0, the cycles are back in phase, and we have a result 
    if (checksum == 0) {      
      if (illustrate) {
	// extra step for illustration purposes, showing align
	for (i = 0; i < clen; i++) {
	  if (i == 0) putchar(' ');
	  CB_BLUE;
	  printf("%s", "^ ");
	  C_RESET;
	}
	C_YELLOW;
	printf("  %lu\n", step+1);
	C_RESET;
      }
      break;
    }
    step++;
  }

  // print summary
  if (illustrate) printf("\n");
  printf("[");
  for (i = 0; i < clen; i++) {
    printf("%d", cycle[i]);
    if ((i+1) < clen) 
      printf(",");
  }
  printf("] : %lu steps until all phases re-align\n", step);

  free(cycle);
  return 0;
}
