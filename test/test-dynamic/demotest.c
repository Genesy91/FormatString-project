#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*dynamic_function)(void);

int main(void) {
  const char *error;
  void *handler;
  dynamic_function script_testfunction;

  // carico libreria
  handler = dlopen("libtest.so", RTLD_LAZY);
  if (!handler) {
    fprintf(stderr, "impossibile cricare libreria! ERRORE: %s\n", dlerror());
    exit(1);
  }

  // associo la funzione dello script con quella dellalibreria (ricavo simbolo)
  dlerror();
  script_testfunction = dlsym(handler, "testfunction");
  if ((error = dlerror())) {
    fprintf(stderr, "impossibile ricavare il simbolo! ERRORE: %s\n", error);
    exit(1);
  }

  // uso la funzione
  (*script_testfunction)();
  dlclose(handler);
  return 0;
}
