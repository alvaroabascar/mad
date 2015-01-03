#include <stdio.h>
#include <matrix.h>
#include <tridiag.h>

void print_vector(int len, double *d);

int main(int argc, char *argv[])
{
  double a[2] = {3, 8};
  double b[3] = {1, 4, 9};
  double c[2] = {2, 5};
  double d[3] = {1, 2, 3};

  tridiag(3, a, b, c, d);

  print_vector(3, d);
  return 0;
}

void print_vector(int len, double *d)
{
  int i;
  printf("{");
  for (i = 0; i < len; i++) {
    printf("%.2f%s", d[i], (i < len - 1) ? " ," : "}\n");
  }
}
