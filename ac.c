#include <stdio.h>

#include "ac.h"
#include "config.h"

int isAcOnline() {
  printf("isAcOnline() called.\n");
  FILE* fp = fopen(AC_PRESENT_FILE, "r");

  if (fp != NULL) {
    int value;
    fscanf(fp, "%d", &value);
    printf("isAcOnline(): %d.\n", value);
    fclose(fp);

    return value;
  } else {
    printf("Could not open file.\n");
    return -1;
  }
}
