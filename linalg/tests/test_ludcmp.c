#include <stdio.h>
#include <matrix.h>
#include <ludcmp.h>
#include <stdlib.h>

void solve(matrix_double A, matrix_double B);
void fill_b(matrix_double *A, matrix_double *B);

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
  fill_b(&A, &B);

  printf("********************************************\n");
  printf("Trying a random system with solution 1, 2, 3\n");
  printf("********************************************\n");
  solve(A, B);

  A.data[0][0] = 1;
  A.data[0][1] = 2;
  A.data[0][2] = 3;
  A.data[1][0] = 4;
  A.data[1][1] = 5;
  A.data[1][2] = 6;
  A.data[2][0] = 7;
  A.data[2][1] = 8;
  A.data[2][2] = 9;

  fill_b(&A, &B);

  printf("\n*****************************\n");
  printf("Trying with a singular matrix\n");
  printf("*****************************\n");
  solve(A, B);

  return 0;
}

void solve(matrix_double A, matrix_double B)
{
  int d, changes[A.nrows];
  printf("before gaussj:\n");
  printf("A:\n");
  print_matrix_double(A);
  printf("B:\n");
  print_matrix_double(B);
  ludcmp(&A,changes, &d);
  lusolve(&A, &B, changes);
  printf("after gaussj:\n");
  printf("A:\n");
  print_matrix_double(A);
  printf("B:\n");
  print_matrix_double(B);
}

void fill_b(matrix_double *A, matrix_double *B)
{
  int i, j;
  for (i = 0; i < A->nrows; i++) {
    for (j = 0; j < A->ncols; j++) {
      B->data[i][0] += A->data[i][j] * (j + 1);
    }
  }
}
