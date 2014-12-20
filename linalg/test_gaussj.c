#include "gaussj.c"

void print_a_b(matrix_double, matrix_double);

int main(int argc, char *argv[])
{
  matrix_double A, B;
  A = alloc_matrix_double(2, 2);
  B = alloc_matrix_double(2, 1);
  A.data[0][0] = 1;
  A.data[0][1] = 2;
  A.data[1][0] = 3;
  A.data[1][1] = 4;

  B.data[0][0] = 5;
  B.data[1][0] = 11;

  printf("before gaussj:\n");
  print_a_b(A, B);
  gaussj(&A, &B);
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
