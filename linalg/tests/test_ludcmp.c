#include <stdio.h>
#include <matrix.h>
#include <ludcmp.h>
#include <stdlib.h>

void print_a_b(matrix_double, matrix_double);

int main(int argc, char *argv[])
{
  int i, j;
  matrix_double A, B;
  A = alloc_matrix_double(3, 3);
  B = alloc_matrix_double(3, 1);
  srand(100);
  for (i = 0; i < A.nrows; i++) {
    for (j = 0; j < A.ncols; j++) {
      A.data[i][j] = (double) rand();
    }
  }

  for (i = 0; i < A.nrows; i++) {
    for (j = 0; j < A.ncols; j++) {
      B.data[i][0] += A.data[i][j] * (j + 1);
    }
  }
  int changes[A.nrows];
  int d;
  printf("before ludcmp:\n");
  print_a_b(A, B);
  ludcmp(&A, changes, &d);
  lusolve(&A, &B, changes, &d);
  printf("after ludcmp:\n");
  print_a_b(A, B);
  return 0;
}

void print_a_b(matrix_double A, matrix_double B)
{
  printf("A:\n");
  print_matrix_double(A);
  printf("B:\n");
  print_matrix_double(B);
}
