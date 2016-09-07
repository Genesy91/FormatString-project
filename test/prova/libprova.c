
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*real_function)(const char *format, ...);
//typedef  ssize_t (*real_function)(int fd, const void *buf, size_t count);

ssize_t write(int fd, const void *buf, size_t count) {
  void *handler;
  handler = dlopen("libc.so.6", RTLD_LAZY);
  real_function real_write;
   real_write = dlsym(handler, "printf");
   real_write("ffpls\n");
  // const char *error;
  // void *handler;
  // real_function real_printf;
  //
  // // carico libreria
  // handler = dlopen("libc.so", RTLD_LAZY);
  // if (!handler) {
  //   fprintf(stderr, "impossibile caricare libreria! ERRORE: %s\n", dlerror());
  //   exit(1);
  // }
  //
  // // associo la funzione dello script con quella dellalibreria (ricavo simbolo)
  // dlerror();
  // real_printf = dlsym(RTLD_NEXT, "printf");
  // if ((error = dlerror())) {
  //   fprintf(stderr, "impossibile ricavare il simbolo! ERRORE: %s\n", error);
  //   exit(1);
  // }
  //
  // // uso la funzione
  // (*real_printf)("ffpls");
  // dlclose(handler);
  return 0;
}
