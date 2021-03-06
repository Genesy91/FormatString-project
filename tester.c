/*This is a script that aims to show the behaviour of libformatfilter.so library
with different types of format string containing the %n specifier or the $ sign
or without them*/

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  FILE *fp;
  char str_s[100];
  char str_sn[100];
  size_t sn_len = 16;
  int return_value;
  int scan_intarg;
  char scan_chararg;
  char scan_word[20];
  int percn;
  long int lpercn;

  fp = fopen ("testfile-libformatfilter.txt", "w+");

  //printf test with a 3 characters conversion specification
  return_value = printf("PRINT: A robot may not injure a human bein%lc\n", 'g');
  printf("printf returned: %d\n", return_value);

  //fprintf test
  return_value = fprintf(fp, "FPRINT: A robot may not injure a human bein%c\n", 'g');
  printf("fprintf returned: %d\n", return_value);

  //sprintf test
  return_value = sprintf(str_s, "SPRINT: A robot may not injure a human bein%c\n", 'g');
  puts(str_s);
  printf("sprintf returned: %d\n", return_value);

  //snprintf test
  return_value = snprintf(str_sn, sn_len, "SNPRINT: A robot may not injure a human bein%c\n", 'g');
  puts(str_sn);
  printf("snprintf returned: %d\n", return_value);

  //scanf test with two conversion specification
  puts("Type an int and a char : ");
  return_value = scanf("%d %c", &scan_intarg, &scan_chararg);
  printf("You typed: %d, %c\nscanf returned: %d\n", scan_intarg, scan_chararg, return_value);

  //fscanf test
  rewind(fp);
  return_value = fscanf(fp,"%s", scan_word);
  printf("The first word in file.txt is: %s\nfscanf returned: %d\n", scan_word, return_value);

  //sscanf test
  return_value = sscanf(str_s, "%s", scan_word);
  printf("The first word in str_s string is: %s\nsscanf returned: %d\n", scan_word, return_value);


  //$ test
  printf("catch test %2$d %1$d\n", 1, 2);

  //%n test with a 2 characters conversion specification
  fprintf(fp, "catch test %ln", &lpercn);

  //%n tests
  sprintf(str_s, "catch test %n", &percn);
  snprintf(str_sn, sn_len, "catch test %n", &percn);
  scanf("%n", &percn);
  fscanf(fp, "%n", &percn);
  sscanf(str_s, "%n", &percn);

  fclose(fp);
  return 0;
}
