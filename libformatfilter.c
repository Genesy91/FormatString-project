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

const char *i;
va_list argument_list;
void *handler;

int find_n(const char *format){
  for (i=format; *i; i++){
    if (*i == '%'){
      i++;
      if(*i != '%'){
        while (*i != 'd' && *i != 'i' && *i != 'o' && *i != 'u' && *i != 'x'
        && *i != 'X' && *i != 'e' && *i != 'E' && *i != 'f' && *i != 'F' && *i != 'g'
        && *i != 'G' && *i != 'a' && *i != 'A' && *i != 'c' && *i != 's' && *i != 'C' && *i != 'S'
        && *i != 'p' && *i != 'm'){
          if (*i == 'n' || *i == '$'){
            openlog(NULL, LOG_PID, LOG_USER);
            return 1;
          }
          i++;
        }
      }
    }
  }
  return 0;
}

void *get_function (char *name) {
  void *real_function;
  const char *error;
  handler = dlopen("libc.so.6", RTLD_LAZY);
  if (!handler) {
    fputs(dlerror(), stderr);
    exit(1);
  }
  dlerror();
  real_function = dlsym(handler, name);
  if ((error = dlerror())) {
    fputs(error, stderr);
    exit(1);
  }
  return real_function;
}

void n_found () {
  char x;
  puts("WARNING: dangerous use of a format strig detected! Press [x] to continue or any other key to exit");
  real_scanf = get_function("scanf");
  int j = real_scanf("%c", &x);
  if (x != 'x') exit(1);
}

int printf (const char *format, ...) {
  int numofchar;
  if (find_n(format)){
    syslog(LOG_WARNING, "WARNING: %%n found in printf\n");
    n_found();
  }
  real_printf = get_function("vprintf");
  va_start(argument_list, format);
  numofchar = real_printf(format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}




int fprintf(FILE *stream, const char *format, ...){
  int numofchar;
  if (find_n(format)) syslog(LOG_WARNING, "WARNING: %%n found in fprintf\n");
  real_fprintf = get_function("vfprintf");
  va_start(argument_list, format);
  numofchar = real_fprintf(stream, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}




int sprintf(char *str, const char *format, ...){
  int numofchar;
  if (find_n(format)) syslog(LOG_WARNING, "WARNING: %%n found in sprintf\n");
  real_sprintf = get_function("vsprintf");
  va_start(argument_list, format);
  numofchar = real_sprintf(str, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}




int snprintf(char *str, size_t size, const char *format, ...){
  int numofchar;
  if (find_n(format)) syslog(LOG_WARNING, "WARNING: %%n found in snprintf\n");
  real_snprintf = get_function("vsnprintf");
  va_start(argument_list, format);
  numofchar = real_snprintf(str, size, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}



int scanf(const char *format, ...){
  int numofinputs;
  if (find_n(format)) syslog(LOG_WARNING, "WARNING: %%n found in scanf\n");
  real_scanf = get_function("vscanf");
  va_start(argument_list, format);
  numofinputs = real_scanf(format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofinputs;
}



int fscanf(FILE *stream, const char *format, ...){
  int numofinputs;
  if (find_n(format)) syslog(LOG_WARNING, "WARNING: %%n found in fscanf\n");
  real_fscanf = get_function("vfscanf");
  va_start(argument_list, format);
  numofinputs = real_fscanf(stream, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofinputs;
}



int sscanf(const char *str, const char *format, ...){
  int numofinputs;
  if (find_n(format)) syslog(LOG_WARNING, "WARNING: %%n found in sscanf\n");
  real_sscanf = get_function("vsscanf");
  va_start(argument_list, format);
  numofinputs = real_sscanf(str, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofinputs;
}
