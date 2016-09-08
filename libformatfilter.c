#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

int (*real_printf)(const char *format, ...);
int (*real_fprintf)(FILE *stream, const char *format, ...);
int (*real_sprintf)(char *str, const char *format, ...);
int (*real_snprintf)(char *str, size_t size, const char *format, ...);

char *percn = "gg";
const char *i;

int printf (const char *format, ...) {
  void *handler;
  handler = dlopen("libc.so.6", RTLD_LAZY);
  real_printf = dlsym(handler, "printf");
  for (i=format; *i; i++){
    real_printf("i punta a: %s\n", i);
    if (*i == '%'){
      real_printf("trovato perc\n");
      i++;
      real_printf("i punta a: %s\n", i);
      if(*i == 'n'){
        real_printf("ffpls\n");
        //syslog
        break;
      }
    }
  }
}

int fprintf(FILE *stream, const char *format, ...){
  return 0;

}

int sprintf(char *str, const char *format, ...){
  return 0;

}

int snprintf(char *str, size_t size, const char *format, ...){
  return 0;

}
