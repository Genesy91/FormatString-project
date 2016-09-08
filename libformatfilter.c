#include <dlfcn.h>
#include <string.h>
#include <stdarg.h>
//#include <stdio.h>

int (*real_printf)(const char *format, ...);
int (*real_vprintf)(const char *format, va_list ap);
int (*real_fprintf)(void *stream, const char *format, ...);
int (*real_sprintf)(char *str, const char *format, ...);
int (*real_snprintf)(char *str, size_t size, const char *format, ...);

char *percn = "gg";
const char *i;

int printf (const char *format, ...) {
  void *handler;
  va_list argument_list;

  handler = dlopen("libc.so.6", RTLD_LAZY);
  real_printf = dlsym(handler, "printf");
  real_vprintf = dlsym(handler, "printf");
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
  real_printf("passo finale:\n");
  va_start(argument_list, format);
  real_printf(format);
  va_end(argument_list);
}

int fprintf(void *stream, const char *format, ...){
  void *handler;
  handler = dlopen("libc.so.6", RTLD_LAZY);
  // real_printf = dlsym(handler, "printf");
  // real_printf("cazzone");
  real_fprintf = dlsym(handler, "fprintf");
  //real_fprintf = dlsym(handler, "FILE");
  real_fprintf(stream,"ffpls");

  return 0;

}

int sprintf(char *str, const char *format, ...){
  return 0;

}

int snprintf(char *str, size_t size, const char *format, ...){
  return 0;

}
