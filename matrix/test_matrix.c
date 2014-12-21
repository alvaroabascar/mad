#include <stdio.h>
#include "matrix.h"

#define NROWS 2
#define NCOLS 2

int main(int argc, char *argv[])
{
  int i, j;
  matrix_double mymatrix = alloc_matrix_double(NROWS, NCOLS);
  for (i = 0; i < NROWS; i++) {
    for (j = 0; j < NCOLS; j++) {
      mymatrix.data[i][j] = i + j;
    }
  }
  print_matrix_double(mymatrix);
  printf("*********+\n");
  switch_cols_matrix_double(&mymatrix, 0, 1);
  print_matrix_double(mymatrix);
  printf("everything ok\n");
  return 0;
}
