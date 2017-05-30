#include <stdio.h>

#include "ac.h"
#include "music.h"
#include "config.h"
#include "inhibitors.h"
#include "idled.h"

// arrays of inhibitor functions to call, as long as there are under 255 functions per action ;)
funcPtr idle_1_inhibitors[] = { isAcOnline };
funcPtr idle_2_inhibitors[] = { }; // nothing inhibits locking the screen
funcPtr idle_3_inhibitors[] = { isAcOnline, isMusicPlaying };

byte shouldInhibitAction(byte idleAction) {
  byte numFuncs = 0;

  // declare a pointer to the array of inhibitor functions
  funcPtr *inhibitors;

  // need to count the number of functions before the inhibitors pointer is created
  // because the size of the pointer cannot be known
  switch(idleAction) {
    case IDLE_1:
      numFuncs = sizeof(idle_1_inhibitors) / sizeof(funcPtr);
      inhibitors = idle_1_inhibitors;
      break;

    case IDLE_2:
      numFuncs = sizeof(idle_2_inhibitors) / sizeof(funcPtr);
      inhibitors = idle_2_inhibitors;
      break;

    case IDLE_3:
      numFuncs = sizeof(idle_3_inhibitors) / sizeof(funcPtr);
      inhibitors = idle_3_inhibitors;
      break;
  }


  // iterate over function pointers
  // if any one returns 1 then return 1
  return runInhibitors(inhibitors, numFuncs);
}

byte runInhibitors(funcPtr *inhibitors, byte len) {
  for (byte i=0; i<len; i++) {
    byte result = (*inhibitors[i])();
    if (result == 1) {
      printf("Inhibiting action.\n");
      return 1;
    }
  }

  return 0;
}
