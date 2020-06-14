#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
  int* cycle;
  int clen = 0;
  int step = 1;
  int illustrate = 0;
  int i, tmp, checksum, mult;

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
    if (illustrate) {
      printf("%05d ", step); //TBD: figure out padding
    }
    for (i = 0; i < clen; i++) {
      checksum += ((step % cycle[i]));
      if (illustrate) {
	printf("%s", (((step % cycle[i]) == 1 || cycle[i] == 1) ? ". " : "  "));
      }
    }
    if (illustrate) {
      printf("\n");
    }

    // If it adds to 0, the cycles are back in phase, and we have a result 
    if (checksum == 0) {      
      if (illustrate) {
	// extra step for illustration purposes, showing align
	printf("%05d ", step+1); //TBD: figure out padding
	for (i = 0; i < clen; i++) {
	  printf("%s", ". ");
	}
	printf("\n");
      }
      break;
    }
    step++;
  }

  // print summary
  printf("\n");
  printf("[");
  for (i = 0; i < clen; i++) {
    printf("%d", cycle[i]);
    if ((i+1) < clen) 
      printf(",");
  }
  printf("] : %d steps until all phases re-align\n", step);

  // print multiplication of cycle lengths
  mult = cycle[0];
  printf("%d ", cycle[0]);
  if ((clen - 1) != 0)
      printf("x ");
  for (i = 1; i < clen; i++) {
    mult *= cycle[i];
    printf("%d ", cycle[i]);
    if ((clen - 1) != i)
      printf("x ");
  }
  printf("== %d\n\n", mult);

  free(cycle);
  return 0;
}
