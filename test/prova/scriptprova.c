#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void) {
  write(0, "Hello, Kernel!\n", 15);
  return 0;
}
