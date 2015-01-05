#include <stdio.h>
#include "matrix_double.h"
#include "array.c"
#define max(x) ((x > 0) ? x : -x)

/* allocate enough space for a nrows by ncols matrix and return it */
matrix_double alloc_matrix_double(size_t nrows, size_t ncols)
{
  int i, j;
  matrix_double matrix;
  matrix.nrows = nrows;
  matrix.ncols = ncols;
  matrix.data = malloc(nrows * sizeof(double *));
  for (i = 0; i < nrows; i++) {
    matrix.data[i] = malloc(ncols * sizeof(double));
    for (j = 0; j < ncols; j++) {
      matrix.data[i][j] = 0;
    }
  }
  return matrix;
}

/* free the space used by the matrix */
void free_matrix_double(matrix_double matrix)
{
  int i;
  /* free each row */
  for (i = 0; i < matrix.nrows; i++) {
    free(matrix.data[i]);
  }
  /* free data */
  free(matrix.data);
  matrix.nrows = 0;
  matrix.ncols = 0;
}

matrix_double copy_matrix_double(matrix_double matrix)
{
  int i, j;
  matrix_double new_matrix = alloc_matrix_double(matrix.nrows,
                                                 matrix.ncols);
  for (i = 0; i < matrix.nrows; i++) {
    for (j = 0; j < matrix.ncols; j++) {
      new_matrix.data[i][j] = matrix.data[i][j];
    }
  }
  return new_matrix;
}

/* print_matrix_double:
 * take a pointer to a matrix and a format string used to print each
 * element, and print it!
 */
void print_matrix_double(matrix_double matrix)
{
  int i, j;
  for (i = 0; i < matrix.nrows; i++) {
    for (j = 0; j < matrix.ncols; j++) {
      printf("%10f ", matrix.data[i][j]);
    }
    printf("\n");
  }
}

/* Given a matrix and two coordinates "start" and "end", multiply by k all the
 * elements in the matrix within the square delimited by "start" and "end"
 */
void multiply_section_matrix_double(matrix_double matrix,
                                  struct pair_coordinates section,
                                  double k)
{
  int i, j;
  struct coordinate start, end;
  start = section.a;
  end = section.b;
  for (i = start.row; i <= end.row; i++) {
    for (j = start.col; j <= end.col; j++) {
      matrix.data[i][j] *= k;
    }
  }
}

/* Given a matrix and two coordinates "start" and "end", add k to all the
 * elements in the matrix within the square delimited by "start" and "end"
 */
void add_to_section_matrix_double(matrix_double matrix,
                                  struct pair_coordinates section,
                                  double k)
{
  int i, j;
  struct coordinate start, end;
  start = section.a;
  end = section.b;
  for (i = start.row; i <= end.row; i++) {
    for (j = start.col; j <= end.col; j++) {
      matrix.data[i][j] += k;
    }
  }
}

void reorder_matrix_rows_double(matrix_double matrix, int *orders_arg)
{
  int i;
  int orders[matrix.nrows];
  /* make copy of orders_arg to avoid destroying the original */
  for (i = 0; i < matrix.nrows; i++) {
    orders[i] = orders_arg[i];
  }
  for (i = 0; i < matrix.nrows; i++) {
    while (orders[i] != i) {
      interchange_rows_matrix_double(matrix, i, orders[i]);
      interchange_array_elements_int(orders, i, orders[i]);
    }
  }
}

/* multiply a row (row) by a double (k) */
void multiply_row_matrix_double(matrix_double matrix, int row, double k)
{
  int i;
  for (i = 0; i < matrix.ncols; i++) {
    matrix.data[row][i] *= k;
  }
}

/* multiply_matrix_double:
 * take a matrix "matrix" and divide all its elements by "k"
 */
void multiply_matrix_double(matrix_double matrix, double k)
{
  int i, j;
  for (i = 0; i < matrix.nrows; i++) {
    for (j = 0; j < matrix.ncols; j++) {
      matrix.data[i][j] *= k;
    }
  }
}

/* copy_row_matrix_double:
 * given a matrix "A", a array "v" and an integer "row",
 * copy the row A[row] into v
 */
void copy_row_matrix_double(matrix_double A, double *v, int row)
{
  int i;
  for (i = 0; i < A.ncols; i++) {
    v[i] = A.data[row][i];
  }
}

/* add "array" to row matrix[row] */
void add_to_row_matrix_double(matrix_double matrix, int row,
                                      double array[matrix.ncols])
{
  int i;
  for (i = 0; i < matrix.ncols; i++) {
    matrix.data[row][i] += array[i];
  }
}

/* interchange_rows_matrix_double:
 * take a matrix and interchange rowA and rowB
 */
void interchange_rows_matrix_double(matrix_double matrix,
                                        int rowA, int rowB)
{
  double *tmp;
  tmp = matrix.data[rowA];
  matrix.data[rowA] = matrix.data[rowB];
  matrix.data[rowB] = tmp;
}

/* interchange_cols_matrix_double:
 * take a matrix and interchange colA and colB
 */
void interchange_cols_matrix_double(matrix_double matrix,
                                        int colA, int colB)
{
  int i;
  double tmp;
  for (i = 0; i < matrix.ncols; i++) {
    tmp = matrix.data[i][colA];
    matrix.data[i][colA] = matrix.data[i][colB];
    matrix.data[i][colB] = tmp;
  }
}
