/* gcc -o idled idled.c -lXss -lX11 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/extensions/scrnsaver.h>

#include "config.h"
#include "idled.h"

int main(void) {
  Display *dpy = XOpenDisplay(NULL);
  
  if (!dpy) {
    printf("Could not open display.\n");
    return(-1);
  }

  printf("Starting idled as user: %d/%d\n", getuid(), getgid());
  
  // brightness values before we messed with them
  int preSetBrightness = readBrightness(LCD);
  int preSetKbdBrightness = readBrightness(KBD);

  XScreenSaverInfo *info = XScreenSaverAllocInfo();
  
  int listening = 1;
  int event = listen(dpy, info);
  
  int actionTaken1 = 0;
  int actionTaken2 = 0;
  int actionTaken3 = 0;

  while (listening) {
    printf("%d\n", event);

    if (event == ACTIVE) {
      int currentLcdBrightness = readBrightness(LCD);
      int currentKbdBrightness = readBrightness(KBD);

      if (currentLcdBrightness != IDLE_BRIGHTNESS) {
        preSetBrightness = readBrightness(LCD);
      }

      if (currentKbdBrightness != 0) {
        preSetKbdBrightness = readBrightness(KBD);
      }

      setBrightness(LCD, preSetBrightness);
      setBrightness(KBD, preSetKbdBrightness);

      printf("Resetting action flags.\n");
      actionTaken1 = 0;
      actionTaken2 = 0;
      actionTaken3 = 0;
    } else {
      switch (event) {
        case IDLE_1:
          if (!actionTaken1) {
            printf("Dimming as user %d/%d\n", getuid(), getgid());
            setBrightness(LCD, IDLE_BRIGHTNESS);
            setBrightness(KBD, 0);
            actionTaken1 = 1;
          }
          break;
        case IDLE_2:
          if (!actionTaken2) {
            system(ACTION_2);
            actionTaken2 = 1;// runs a system command as a given user, used for lock screen
void runAs(int, int, char*);
          }
          break;
        case IDLE_3:
          if (!actionTaken3) {
            system(ACTION_3);
            actionTaken3 = 1;
          }
          break;
      }
    }

    event = listen(dpy, info);
  }

  return(0);
}


int listen(Display* dpy, XScreenSaverInfo* info) {
  unsigned long int idleTime = 0;
  int running = 1;
  do {
    sleep(1);
    XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), info);
    idleTime = info->idle;

    if (idleTime > TIMEOUT_1) {
      if (idleTime < TIMEOUT_2) {
        return IDLE_1;
      } else if (idleTime > TIMEOUT_2 && idleTime < TIMEOUT_3) {
        return IDLE_2;
      } else {
        return IDLE_3;
      }
    } else if (idleTime <= 1000) {
      return ACTIVE;
    }
  } while(running);

  return -1;
}


