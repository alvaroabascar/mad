#include <stdio.h>
#include <matrix.h>
#include <inverse.h>

int main(int argc, char *argv[])
{
  matrix_double A, I;
  A = alloc_matrix_double(2, 2);
  A.data[0][0] = 1;
  A.data[0][1] = 2;
  A.data[1][0] = 3;
  A.data[1][1] = 4;

  printf("********************************************\n");
  printf("Trying a random system with solution 1, 2, 3\n");
  printf("********************************************\n");
  I = inverse(A);

  printf("A:\n");
  print_matrix_double(A);
  printf("I:\n");
  print_matrix_double(I);

  free_matrix_double(A);
  free_matrix_double(I);
  A = alloc_matrix_double(3, 3);
  A.data[0][0] = 1;
  A.data[0][1] = 2;
  A.data[0][2] = 3;
  A.data[1][0] = 4;
  A.data[1][1] = 5;
  A.data[1][2] = 6;
  A.data[2][0] = 7;
  A.data[2][1] = 8;
  A.data[2][2] = 9;

  printf("\n*****************************\n");
  printf("Trying with a singular matrix\n");
  printf("*****************************\n");
  I = inverse(A);
  printf("A:\n");
  print_matrix_double(A);
  printf("I:\n");
  print_matrix_double(I);

  free_matrix_double(A);
  free_matrix_double(I);

  return 0;
}
