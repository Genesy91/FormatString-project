// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@  This library wraps all the functions from the printf and scanf families.   @@@
// @@@  It must be loaded before th standard C library using LD_PRELOAD.           @@@
// @@@  Its purpose is to catch dangerous format strings containing the %n format  @@@
// @@@  specifier or the $ sign. When one of these is found, the user is asked     @@@
// @@@  to choose to terminate the program or call the original function.          @@@
// @@@  Original functions:                                                        @@@
// @@@  http://linux.die.net/man/3/printf                                          @@@
// @@@  http://linux.die.net/man/3/scanf                                           @@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Davide Macchi - 760461 @@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ POLIMI - Piattaforme software per la rete MOD2 @@@@

#include <dlfcn.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

//There is a pointer to a function for each function wrapped
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

//Read format string and find occurrences of '$' and %n in conversion specifications.
//It works when flags, width, precision and length fields are used.
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

//Load the needed function, refered by name argument, from the standard C library.
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

//When %n or $ is found, the user can terminate the program or go on
void n_found () {
  char x;
  puts("WARNING: dangerous use of a format strig detected! Press [x] to continue or any other key to exit");
  real_scanf = get_function("scanf");
  real_scanf(" %c", &x);
  if (x != 'x'){
    exit(1);
  }
}


//--------------------------------------------------------------------------------------------------------------


//There are 7 wrappers: printf, fprintf, sprintf, snprintf, scanf, fscanf, sscanf.
//They take a format strings and call find_n. On success a warnign message is sent to the syslog
//and n_found is called. If the user say so or find_n doesn't succeed, the original function is called.
//Actualy thw wrappers call the "v" version of the corresponding function that can take
//as an argument a list of arguments (http://linux.die.net/man/3/stdarg)

int printf (const char *format, ...) {
  int numofchar;
  if (find_n(format)){
    syslog(LOG_WARNING, "[printf]WARNING: this format string is dangerous\n     %s", format);
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
  if (find_n(format)){
    syslog(LOG_WARNING, "[fprintf]WARNING: this format string is dangerous\n     %s", format);
    n_found();
  }
  real_fprintf = get_function("vfprintf");
  va_start(argument_list, format);
  numofchar = real_fprintf(stream, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}




int sprintf(char *str, const char *format, ...){
  int numofchar;
  if (find_n(format)){
    syslog(LOG_WARNING, "[sprintf]WARNING: this format string is dangerous\n     %s", format);
    n_found();
  }
  real_sprintf = get_function("vsprintf");
  va_start(argument_list, format);
  numofchar = real_sprintf(str, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}




int snprintf(char *str, size_t size, const char *format, ...){
  int numofchar;
  if (find_n(format)){
    syslog(LOG_WARNING, "[snprintf]WARNING: this format string is dangerous\n     %s", format);
    n_found();
  }
  real_snprintf = get_function("vsnprintf");
  va_start(argument_list, format);
  numofchar = real_snprintf(str, size, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofchar;
}



int scanf(const char *format, ...){
  int numofinputs;
  if (find_n(format)){
    syslog(LOG_WARNING, "[scanf]WARNING: this format string is dangerous\n     %s", format);
    n_found();
  }
  real_scanf = get_function("vscanf");
  va_start(argument_list, format);
  numofinputs = real_scanf(format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofinputs;
}



int fscanf(FILE *stream, const char *format, ...){
  int numofinputs;
  if (find_n(format)){
    syslog(LOG_WARNING, "[fscanf]WARNING: this format string is dangerous\n     %s", format);
    n_found();
  }
  real_fscanf = get_function("vfscanf");
  va_start(argument_list, format);
  numofinputs = real_fscanf(stream, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofinputs;
}



int sscanf(const char *str, const char *format, ...){
  int numofinputs;
  if (find_n(format)){
    syslog(LOG_WARNING, "[sscanf]WARNING: this format string is dangerous\n     %s", format);
    n_found();
  }
  real_sscanf = get_function("vsscanf");
  va_start(argument_list, format);
  numofinputs = real_sscanf(str, format, argument_list);
  va_end(argument_list);
  dlclose(handler);
  return numofinputs;
}
