#include <stdio.h>

#include "config.h"
#include "idled.h"

int readBrightness(BRIGHTNESS_TYPE type) {
  FILE* fp = NULL;

  if (type == LCD) {
    fp = fopen(BRIGHTNESS_FILE, "r");
  } else if (type == KBD) {
    fp = fopen(KBD_BRIGHTNESS_FILE, "r");
  }

  if (fp != NULL) {
    int buffer[5] = { 0 };
    int i;

    for (i = 0; i < 5; i++) {
      fscanf(fp, "%d", &buffer[i]);
    }

    fclose(fp);

    return *buffer;
  } else {
    return -1;
  }
}

int setBrightness(BRIGHTNESS_TYPE type, int brightness) {
  FILE* fp = NULL;
  if (type == LCD) {
    fp = fopen(BRIGHTNESS_FILE, "w");
  } else if (type == KBD) {
    fp = fopen(KBD_BRIGHTNESS_FILE, "w");
  }
  
  if (fp != NULL) {
    fprintf(fp, "%d", brightness);
    fclose(fp);
    return 0;
  } else {
    return -1;
  }
}
