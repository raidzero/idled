// make a quick way to use function pointer as a type
// cdecl: declare funcPtr as pointer to function returning byte
typedef byte (*funcPtr)();

// return 1 to inhibit
byte shouldInhibitAction(byte);

// runs all functions in funcPtr array and returns 1 if one does the same
byte runInhibitors(funcPtr*, byte); 

