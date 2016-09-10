#include <dlfcn.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int (*real_printf)(const char *format, ...);
int (*real_fprintf)(FILE *stream, const char *format, ...);
int (*real_sprintf)(char *str, const char *format, ...);
int (*real_snprintf)(char *str, size_t size, const char *format, ...);
int (*real_scanf)(const char *format, ...);
int (*real_fscanf)(FILE *stream, const char *format, ...);
int (*real_sscanf)(const char *str, const char *format, ...);

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
        syslog(LOG_WARNING, "%m");
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
  real_sprintf = dlsym(handler, "vsprintf");
  if ((error = dlerror())) {
    fputs(error, stderr);
    exit(1);
  }
  va_start(argument_list, format);
  numofchar = real_sprintf(str, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}




int snprintf(char *str, size_t size, const char *format, ...){
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
  real_snprintf = dlsym(handler, "vsnprintf");
  if ((error = dlerror())) {
    fputs(error, stderr);
    exit(1);
  }
  va_start(argument_list, format);
  numofchar = real_snprintf(str, size, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}



int scanf(const char *format, ...){
  int numofinputs;
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
  real_scanf = dlsym(handler, "vscanf");
  if ((error = dlerror())) {
    fputs(error, stderr);
    exit(1);
  }
  va_start(argument_list, format);
  numofinputs = real_scanf(format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofinputs;
}



int fscanf(FILE *stream, const char *format, ...){
  int numofinputs;
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
  real_fscanf = dlsym(handler, "vfscanf");
  if ((error = dlerror())) {
    fputs(error, stderr);
    exit(1);
  }
  va_start(argument_list, format);
  numofinputs = real_fscanf(stream, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofinputs;
}



int sscanf(const char *str, const char *format, ...){
  int numofinputs;
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
  real_sscanf = dlsym(handler, "vsscanf");
  if ((error = dlerror())) {
    fputs(error, stderr);
    exit(1);
  }
  va_start(argument_list, format);
  numofinputs = real_sscanf(str, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofinputs;
}
