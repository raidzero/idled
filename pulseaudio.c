#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "pulseaudio.h"

#define PULSE_CMD "/usr/bin/pactl list | grep RUNNING"

// check to see if there is a window that is playing google music
byte isPulsePlaying() {
  printf("isPulsePlaying() called.\n");
  int result = WEXITSTATUS(system(PULSE_CMD));
  return (result == 0) ? 1 : 0;
}
