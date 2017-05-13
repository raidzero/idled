/* gcc -o idled idled.c -lXss -lX11 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/extensions/scrnsaver.h>

#include "config.h"
#include "idled.h"
#include "inhibitors.h"

byte ACTION_TAKEN_1 = 0x1;
byte ACTION_TAKEN_2 = 0x2;
byte ACTION_TAKEN_3 = 0x4;

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

  byte listening = 1;
  byte event = listen(dpy, info);

  // ibitwise operations will be done on this track of the different actions taken
  byte ACTIONS_TAKEN = 0;

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
      ACTIONS_TAKEN = 0;
    } else {
      int inhibit = shouldInhibitAction(event);

      // only do stuff if the action is not inhibited
      if (!inhibit) {
        switch (event) {
          case IDLE_1:
            if ((ACTIONS_TAKEN & ACTION_TAKEN_1) == 0) {
              printf("Dimming as user %d/%d\n", getuid(), getgid());
              setBrightness(LCD, IDLE_BRIGHTNESS);
              setBrightness(KBD, 0);
              ACTIONS_TAKEN |= ACTION_TAKEN_1;
            }
            break;
          case IDLE_2:
            if ((ACTIONS_TAKEN & ACTION_TAKEN_2) == 0) {
              system(ACTION_2);
              ACTIONS_TAKEN |= ACTION_TAKEN_2;
            }
            break;
          case IDLE_3:
            if ((ACTIONS_TAKEN & ACTION_TAKEN_3) == 0) {
              system(ACTION_3);
              ACTIONS_TAKEN |= ACTION_TAKEN_3;
            }
            break;
        }
      }
    }

    event = listen(dpy, info);
  }

  return(0);
}


byte listen(Display* dpy, XScreenSaverInfo* info) {
  unsigned long int idleTime = 0;
  byte running = 1;
  do {
    sleep(1);
    XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), info);
    idleTime = info->idle;

    printf("Idle time: %ld\n", idleTime);

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


