#include <stdio.h>
#include <matrix.h>
#include <gaussjbs.h>

void print_a_b(matrix_double, matrix_double);

int main(int argc, char *argv[])
{
  matrix_double A, B;
  A = alloc_matrix_double(3, 3);
  B = alloc_matrix_double(3, 2);
  A.data[0][0] = 1;
  A.data[0][1] = 2;
  A.data[0][2] = 3;
  A.data[1][0] = 4;
  A.data[1][1] = 5;
  A.data[1][2] = 6;
  A.data[2][0] = 7;
  A.data[2][1] = 0;
  A.data[2][2] = 9;

  B.data[0][0] = 14;
  B.data[1][0] = 32;
  B.data[2][0] = 34;
  B.data[0][1] = 28;
  B.data[1][1] = 64;
  B.data[2][1] = 68;

  printf("before gaussj:\n");
  print_a_b(A, B);
  gaussjbs(&A, &B);
  printf("after gaussj:\n");
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
