#include <stdio.h>
#include <stdlib.h>
#include <matrix.h>
#include <gaussjbs.h>

void print_a_b(matrix_double, matrix_double);

int main(int argc, char *argv[])
{
  int i, j;
  matrix_double A, B;
  A = alloc_matrix_double(1000, 1000);
  B = alloc_matrix_double(1000, 1);

  /* randomby fill A */
  srand(100);
  for (i = 0; i < A.ncols; i++) {
    for (j = 0; j < A.nrows; j++) {
      A.data[i][j] = (double) rand();
    }
  }

  /* fill B such that the solution is x1=1, x2=2, x3=3, etc. */
  for (j = 0; j < B.nrows; j++) {
    for (i = 0; i < A.ncols; i++) {
      B.data[j][0] += A.data[j][i] * (i + 1);
    }
  }

  /*
  printf("before gaussj:\n");
  print_a_b(A, B);
  */
  gaussjbs(&A, &B);
  free_matrix_double(&A);
  free_matrix_double(&B);
  /*
  printf("after gaussj:\n");
  print_a_b(A, B);
  */
  return 0;
}

void print_a_b(matrix_double A, matrix_double B)
{
  printf("A:\n");
  print_matrix_double(A);
  printf("B:\n");
  print_matrix_double(B);
}
