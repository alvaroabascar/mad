#include "random.h"
#include "random.c"
#include <time.h>
#include <stdio.h>

#define NNUMS 10000
int main(int argc, char *argv[])
{
  int i;
  for (i = 0; i < NNUMS; i++) {
    printf("%d\n", rand_lim(10));
  }
  return 0;
}
