#include <dlfcn.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int (*real_printf)(const char *format, ...);
int (*real_fprintf)(FILE *stream, const char *format, ...);
int (*real_sprintf)(char *str, const char *format, ...);
int (*real_snprintf)(char *str, size_t size, const char *format, ...);

const char *i, *error;
void *handler;
va_list argument_list;



int printf (const char *format, ...) {
  int numofchar;
  for (i=format; *i; i++){
    if (*i == '%'){
      i++;
      if(*i == 'n'){
        exit(1);
        /*trovato*/
      }
    }
  }
  handler = dlopen("libc.so.6", RTLD_LAZY);
  if (!handler) {
    fputs(dlerror(), stderr);
    exit(1);
  }
  dlerror();
  real_printf = dlsym(handler, "vprintf");
  if ((error = dlerror())) {
    fputs(error, stderr);
    exit(1);
  }
  va_start(argument_list, format);
  numofchar = real_printf(format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}




int fprintf(FILE *stream, const char *format, ...){
  int numofchar;
  for (i=format; *i; i++){
    if (*i == '%'){
      i++;
      if(*i == 'n'){
        exit(1);
        /*trovato*/
      }
    }
  }
  handler = dlopen("libc.so.6", RTLD_LAZY);
  if (!handler) {
    fputs(dlerror(), stderr);
    exit(1);
  }
  dlerror();
  real_fprintf = dlsym(handler, "vfprintf");
  if ((error = dlerror())) {
    fputs(error, stderr);
    exit(1);
  }
  va_start(argument_list, format);
  numofchar = real_fprintf(stream, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}

int sprintf(char *str, const char *format, ...){
  return 0;

}

int snprintf(char *str, size_t size, const char *format, ...){
  return 0;

}
