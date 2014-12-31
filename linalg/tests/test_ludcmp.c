#include <stdio.h>
#include <matrix.h>
#include <ludcmp.h>
#include <stdlib.h>

void print_a_b(matrix_double, matrix_double);

int main(int argc, char *argv[])
{
  matrix_double A, B, B_copy;
  int i, j;
  int d = 0;
  A = alloc_matrix_double(3, 3);
  B = alloc_matrix_double(3, 1);
  int changes[A.nrows];
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
  B_copy = copy_matrix_double(B);
  printf("before ludcmp:\n");
  print_a_b(A, B);
  ludcmp(&A, changes, &d);
  lusolve(&A, &B, changes, &d);
  printf("after ludcmp:\n");
  print_a_b(A, B);
  free_matrix_double(&B);
  printf("before ludcmp:\n");
  print_a_b(A, B_copy);
  lusolve(&A, &B_copy, changes, &d);
  printf("after ludcmp:\n");
  print_a_b(A, B_copy);
  return 0;
}

void print_a_b(matrix_double A, matrix_double B)
{
  printf("A:\n");
  print_matrix_double(A);
  printf("B:\n");
  print_matrix_double(B);
}
