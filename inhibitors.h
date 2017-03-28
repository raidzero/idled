// make a quick way to use function pointer as a type
// cdecl: declare funcPtr as pointer to function returning int
typedef int (*funcPtr)();

// return 1 to inhibit
int shouldInhibitAction(int);

// runs all functions in funcPtr array and returns 1 if one does the same
int runInhibitors(funcPtr*, int); 

