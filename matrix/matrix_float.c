#include "matrix_float.h"

matrix_float alloc_matrix_float(size_t nrows, size_t ncols)
{
  int i;
  matrix_float matrix;
  matrix.nrows = nrows;
  matrix.ncols = ncols;
  matrix.data = malloc(nrows * sizeof(float *));
  for (i = 0; i < nrows; i++) {
    matrix.data[i] = malloc(ncols * sizeof(float));
  }
  return matrix;
}

/* print_matrix_float:
 * take a pointer to a matrix and a format string used to print each
 * element, and print it!
 */
void print_matrix_float(matrix_float matrix)
{
  int i, j;
  for (i = 0; i < matrix.nrows; i++) {
    for (j = 0; j < matrix.ncols; j++) {
      printf("%10f ", matrix.data[i][j]);
    }
    printf("\n");
  }
}
