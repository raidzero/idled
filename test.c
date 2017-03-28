#include <stdio.h>

// make a quick way to use function pointer as a type
// cdecl: declare funcPtr as pointer to function returning int
typedef int (*funcPtr)();

int printValue() {
  printf("printValue()\n");
}

int printStuff() {
  printf("printStuff()\n");
}

//int (*functions1[]) () = { printStuff, printValue, printStuff, printValue, printStuff, printValue };
funcPtr functions1[] = { printStuff, printValue, printStuff, printValue, printStuff, printValue };

// must pass length because there is no way to know the size of a pointer
int runFuncs(funcPtr *funcs, int len) {
  printf("runFuncs() will run %d functions.\n", len);
  
  for (int i=0; i<len; i++) {
    (*funcs[i])();
  }
}

int main(int argc, char** argv) {
  
  // determine length using absolute size functions1
  int length = sizeof(functions1) / sizeof(funcPtr);
  printf("length of array: %d\n", length);

  // make pointer to this array of function pointers
  funcPtr *functions = functions1;
  
  
  // call
  runFuncs(functions, length);
}
