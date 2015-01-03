#include <stdio.h>
#include <matrix.h>
#include <tridiag.h>

void print_vector(char *str, int len, double *d);

int main(int argc, char *argv[])
{
  /*
   * |1  2  0|   |1|   | 5|
   * |2  5  5| * |2| = |27|
   * |0  5  9|   |3|   |37|
   *
   * |1  2    0|   |1|   |  5|
   * |0  1    5| * |2| = | 17|
   * |0  0  -16|   |3|   |-48|
   *
   */
  double a[2] = {2, 5};
  double b[3] = {1, 5, 9};
  double c[2] = {2, 5};
  double d[3] = {5, 27, 37};

  tridiag(3, a, b, c, d);

  print_vector("a:", 2, a);
  print_vector("b:", 3, b);
  print_vector("c:", 2, c);
  print_vector("d:", 3, d);
  return 0;
}

void print_vector(char *str, int len, double *d)
{
  int i;
  printf("%s\n", str);
  printf("{");
  for (i = 0; i < len; i++) {
    printf("%.2f%s", d[i], (i < len - 1) ? " ," : "}\n");
  }
}
