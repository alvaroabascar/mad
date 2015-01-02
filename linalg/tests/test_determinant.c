#include <stdio.h>
#include <matrix.h>
#include <ludcmp.h>

int main(int argc, char *argv[])
{
  matrix_double A = alloc_matrix_double(3, 3);
  A.data[0][0] = 1;
  A.data[0][1] = 2;
  A.data[0][2] = 3;
  A.data[1][0] = 4;
  A.data[1][1] = 5;
  A.data[1][2] = 6;
  A.data[2][0] = 7;
  A.data[2][1] = 0;
  A.data[2][2] = 9;

  printf("%2.f\n", determinant(A));
  return 0;
}

