#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "music.h"

#define MUSIC_CMD "/usr/bin/python2 /home/raidzero/.config/polybar/gmusic.py"
// check to see if there is a window that is playing google music
byte isMusicPlaying() {
  printf("isMusicPlaying() called.\n");
  int result = WEXITSTATUS(system(MUSIC_CMD));
  return (result == 0) ? 1 : 0;
}
