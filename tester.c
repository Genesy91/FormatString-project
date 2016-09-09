#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void) {
  FILE *fp;
  char *str_s;
  char *str_sn;
  size_t sn_len = 8;

  fp = fopen ("file.txt", "a");
  printf("A robot may not injure a human bein%c\n", 'g');
  fprintf(fp, "A robot may not injure a human bein%c\n", 'g');
  /*sprintf(str_s, "A robot may not injure a human bein%c\n", 'g');
  puts(str_s);
  snprintf(str_sn, sn_len, "A robot may not injure a human bein%c\n", 'g');
  puts(str_sn);*/
  fclose(fp);

  return 0;
}
