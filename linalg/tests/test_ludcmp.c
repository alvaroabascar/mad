#include <matrix.h>
#include <ludcmp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  matrix_double A = alloc_matrix_double(3, 3);
  int d, changes[A.nrows];
  A.data[0][0] = 1;
  A.data[0][1] = 2;
  A.data[0][2] = 3;
  A.data[1][0] = 4;
  A.data[1][1] = 5;
  A.data[1][2] = 6;
  A.data[2][0] = 7;
  A.data[2][1] = 0;
  A.data[2][2] = 9;
  ludcmp(&A, changes, &d);
  print_matrix_double(A);
  return 0;
}
