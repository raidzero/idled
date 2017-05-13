#include <X11/extensions/scrnsaver.h>

// shortcut to a type for byte
typedef unsigned char byte;

// used for the set/read brightness functions to know which file to work with
typedef enum { LCD, KBD } BRIGHTNESS_TYPE;

// returns current brightness of either keyboard backlight or lcd backlight
int readBrightness(BRIGHTNESS_TYPE);

// sets brightness of either keyboard backlight of lcd backlight
int setBrightness(BRIGHTNESS_TYPE, int);

// listens for inacitivty and returns a status, active or any of 3 idle levels
byte listen(Display*, XScreenSaverInfo*);

