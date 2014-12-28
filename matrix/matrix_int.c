#include <stdio.h>
#include "matrix_int.h"

/* allocate enough space for a nrows by ncols matrix and return it */
matrix_int alloc_matrix_int(size_t nrows, size_t ncols)
{
  int i;
  matrix_int matrix;
  matrix.nrows = nrows;
  matrix.ncols = ncols;
  matrix.data = malloc(nrows * sizeof(int *));
  for (i = 0; i < nrows; i++) {
    matrix.data[i] = malloc(ncols * sizeof(int));
  }
  return matrix;
}

/* free the space used by the matrix */
void free_matrix_int(matrix_int *matrix)
{
  int i;
  /* free each row */
  for (i = 0; i < matrix->nrows; i++) {
    free(matrix->data[i]);
  }
  /* free data */
  free(matrix->data);
}

/* print_matrix_int:
 * take a pointer to a matrix and a format string used to print each
 * element, and print it!
 */
void print_matrix_int(matrix_int matrix)
{
  int i, j;
  for (i = 0; i < matrix.nrows; i++) {
    for (j = 0; j < matrix.ncols; j++) {
      printf("%10d ", matrix.data[i][j]);
    }
    printf("\n");
  }
}

/* Given a matrix and two coordinates "start" and "end", multiply by k all the
 * elements in the matrix within the square delimited by "start" and "end"
 */
void multiply_section_matrix_int(matrix_int *matrix,
                                  struct pair_coordinates section,
                                  int k)
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
void add_to_section_matrix_int(matrix_int *matrix,
                                  struct pair_coordinates section,
                                  int k)
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

void interchange_array_elements_int(int *array, int i, int j)
{
  int tmp;
  tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

void reorder_matrix_rows_int(matrix_int *matrix, int *orders)
{
  int i;
  for (i = 0; i < matrix->nrows; i++) {
    while (orders[i] != i) {
      interchange_rows_matrix_int(matrix, i, orders[i]);
      interchange_array_elements_int(orders, i, orders[i]);
    }
  }
}

/* multiply a row (row) by a int (k) */
void multiply_row_matrix_int(matrix_int *matrix, int row, int k)
{
  int i;
  for (i = 0; i < matrix->ncols; i++) {
    matrix->data[row][i] *= k;
  }
}

/* multiply_matrix_int:
 * take a matrix "matrix" and divide all its elements by "k"
 */
void multiply_matrix_int(matrix_int *matrix, int k)
{
  int i, j;
  for (i = 0; i < matrix->nrows; i++) {
    for (j = 0; j < matrix->ncols; j++) {
      matrix->data[i][j] *= k;
    }
  }
}

/* copy_row_matrix_int:
 * given a matrix "A", a vector "v" and an integer "row",
 * copy the row A[row] into v
 */
void copy_row_matrix_int(matrix_int *A, int *v, int row)
{
  int i;
  for (i = 0; i < A->ncols; i++) {
    v[i] = A->data[row][i];
  }
}

/* add "vector" to row matrix[row] */
void add_to_row_matrix_int(matrix_int *matrix, int row,
                                      int vector[matrix->ncols])
{
  int i;
  for (i = 0; i < matrix->ncols; i++) {
    matrix->data[row][i] += vector[i];
  }
}

/* interchange_rows_matrix_int:
 * take a matrix and interchange rowA and rowB
 */
void interchange_rows_matrix_int(matrix_int *matrix,
                                        int rowA, int rowB)
{
  int i;
  int tmp;
  for (i = 0; i < matrix->ncols; i++) {
    tmp = matrix->data[rowA][i];
    matrix->data[rowA][i] = matrix->data[rowB][i];
    matrix->data[rowB][i] = tmp;
  }
}

/* interchange_cols_matrix_int:
 * take a matrix and interchange colA and colB
 */
void interchange_cols_matrix_int(matrix_int *matrix,
                                        int colA, int colB)
{
  int i;
  int tmp;
  for (i = 0; i < matrix->ncols; i++) {
    tmp = matrix->data[i][colA];
    matrix->data[i][colA] = matrix->data[i][colB];
    matrix->data[i][colB] = tmp;
  }
}

void copy_vector_int(int len, int *source, int *dest)
{
  int i;
  for (i = 0; i < len; i++) {
    dest[i] = source[i];
  }
}

void multiply_vector_int(int len, int *vector, int k)
{
  int i;
  for (i = 0; i < len; i++) {
    vector[i] *= k;
  }
}
