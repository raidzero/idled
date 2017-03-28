#include <stdio.h>

#include "ac.h"
#include "config.h"
#include "inhibitors.h"


// arrays of inhibitor functions to call
funcPtr idle_1_inhibitors[] = { isAcOnline };
funcPtr idle_2_inhibitors[] = { }; // nothing inhibits locking the screen
funcPtr idle_3_inhibitors[] = { isAcOnline };

int shouldInhibitAction(int idleAction) {
  int numFuncs = 0;
  
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

int runInhibitors(funcPtr *inhibitors, int len) {
  for (int i=0; i<len; i++) {
    int result = (*inhibitors[i])();
    if (result == 1) {
      return 1;
    }
  }

  return 0;
} 
