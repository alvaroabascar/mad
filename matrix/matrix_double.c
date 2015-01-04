#include <stdio.h>
#include "matrix_double.h"
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
void free_matrix_double(matrix_double *matrix)
{
  int i;
  /* free each row */
  for (i = 0; i < matrix->nrows; i++) {
    free(matrix->data[i]);
  }
  /* free data */
  free(matrix->data);
  matrix->nrows = 0;
  matrix->ncols = 0;
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

void print_array_double(int len, double *array)
{
  int i;
  printf("{");
  for (i = 0; i < len; i++) {
    printf("%10.4f%s", array[i], (i < len - 1) ? ", " : "}\n");
  }
}


/* Given a matrix and two coordinates "start" and "end", multiply by k all the
 * elements in the matrix within the square delimited by "start" and "end"
 */
void multiply_section_matrix_double(matrix_double *matrix,
                                  struct pair_coordinates section,
                                  double k)
{
  int i, j;
  struct coordinate start, end;
  start = section.a;
  end = section.b;
  for (i = start.row; i <= end.row; i++) {
    for (j = start.col; j <= end.col; j++) {
      matrix->data[i][j] *= k;
    }
  }
}

/* Given a matrix and two coordinates "start" and "end", add k to all the
 * elements in the matrix within the square delimited by "start" and "end"
 */
void add_to_section_matrix_double(matrix_double *matrix,
                                  struct pair_coordinates section,
                                  double k)
{
  int i, j;
  struct coordinate start, end;
  start = section.a;
  end = section.b;
  for (i = start.row; i <= end.row; i++) {
    for (j = start.col; j <= end.col; j++) {
      matrix->data[i][j] += k;
    }
  }
}

void interchange_array_elements_double(double *array, int i, int j)
{
  double tmp;
  tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

void reorder_matrix_rows_double(matrix_double *matrix, int *orders_arg)
{
  int i;
  int orders[matrix->nrows];
  /* make copy of orders_arg to avoid destroying the original */
  for (i = 0; i < matrix->nrows; i++) {
    orders[i] = orders_arg[i];
  }
  for (i = 0; i < matrix->nrows; i++) {
    while (orders[i] != i) {
      interchange_rows_matrix_double(matrix, i, orders[i]);
      interchange_array_elements_int(orders, i, orders[i]);
    }
  }
}

void reorder_array_double(int len, double *array, int *orders_arg)
{
  int i;
  int orders[len];
  /* copy orders array to avoid destroying it */
  for (i = 0; i < len; i++) {
    orders[i] = orders_arg[i];
  }
  for (i = 0; i < len; i++) {
    while (orders[i] != i) {
      interchange_array_elements_double(array, i, orders[i]);
      interchange_array_elements_int(orders, i, orders[i]);
    }
  }
}

/* multiply a row (row) by a double (k) */
void multiply_row_matrix_double(matrix_double *matrix, int row, double k)
{
  int i;
  for (i = 0; i < matrix->ncols; i++) {
    matrix->data[row][i] *= k;
  }
}

/* multiply_matrix_double:
 * take a matrix "matrix" and divide all its elements by "k"
 */
void multiply_matrix_double(matrix_double *matrix, double k)
{
  int i, j;
  for (i = 0; i < matrix->nrows; i++) {
    for (j = 0; j < matrix->ncols; j++) {
      matrix->data[i][j] *= k;
    }
  }
}

/* copy_row_matrix_double:
 * given a matrix "A", a vector "v" and an integer "row",
 * copy the row A[row] into v
 */
void copy_row_matrix_double(matrix_double *A, double *v, int row)
{
  int i;
  for (i = 0; i < A->ncols; i++) {
    v[i] = A->data[row][i];
  }
}

/* add "vector" to row matrix[row] */
void add_to_row_matrix_double(matrix_double *matrix, int row,
                                      double vector[matrix->ncols])
{
  int i;
  for (i = 0; i < matrix->ncols; i++) {
    matrix->data[row][i] += vector[i];
  }
}

/* interchange_rows_matrix_double:
 * take a matrix and interchange rowA and rowB
 */
void interchange_rows_matrix_double(matrix_double *matrix,
                                        int rowA, int rowB)
{
  double *tmp;
  tmp = matrix->data[rowA];
  matrix->data[rowA] = matrix->data[rowB];
  matrix->data[rowB] = tmp;
}

/* interchange_cols_matrix_double:
 * take a matrix and interchange colA and colB
 */
void interchange_cols_matrix_double(matrix_double *matrix,
                                        int colA, int colB)
{
  int i;
  double tmp;
  for (i = 0; i < matrix->ncols; i++) {
    tmp = matrix->data[i][colA];
    matrix->data[i][colA] = matrix->data[i][colB];
    matrix->data[i][colB] = tmp;
  }
}

void copy_vector_double(int len, double *source, double *dest)
{
  int i;
  for (i = 0; i < len; i++) {
    dest[i] = source[i];
  }
}

void multiply_vector_double(int len, double *vector, double k)
{
  int i;
  for (i = 0; i < len; i++) {
    vector[i] *= k;
  }
}

double absmax_vector_double(int len, double *vector)
{
  double max = 0;
  while (len-- > 0) {
    if (abs(vector[len]) > max) {
      max = vector[len];
    }
  }
  return max;
}
