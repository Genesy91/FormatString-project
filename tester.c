#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void) {
  // int *a;
  // int b=2;
  // a = &b;
  // printf("ggwpn %d\n", 2);

  FILE *fp;

   fp = fopen ("file.txt", "a");
   fprintf(fp, "ggwp%d", 2);
   fclose(fp);
  //printf("ggwp %%nfff");
  return 0;
}
