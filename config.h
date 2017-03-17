#define BRIGHTNESS_FILE "/sys/class/backlight/intel_backlight/brightness"
#define KBD_BRIGHTNESS_FILE "/sys/class/leds/chromeos::kbd_backlight/brightness"

#define IDLE_BRIGHTNESS 100 // max for me is 937 so this is roughly 10%

// timeouts for the various actions to take
#define TIMEOUT_1   30  * 1000 // dim after 30 secs
#define TIMEOUT_2   300 * 1000 // lock after 5 mins
#define TIMEOUT_3   600 * 1000 // hybrid-sleep after 10 min
#define ACTIVE 1

#define IDLE_1 1000 // dim screen/turn off keyboad backlight
#define IDLE_2 2000 // lock screen, trigger ACTION_2
#define IDLE_3 3000 // hybrid-sleep, trigger ACTION_3

#define ACTION_2 "/home/raidzero/.config/i3/lockscreen"

// requires sudo execution w/o passwd in sudoers
#define ACTION_3 "sudo systemctl hybrid-sleep" 
