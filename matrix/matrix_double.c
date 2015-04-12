#include <stdio.h>
#include "matrix_double.h"
#include "array.c"
#define max(x) ((x > 0) ? x : -x)

/* allocate enough space for a nrows by ncols matrix and return it, with all
 * elements set to "value"
 */ 
matrix_double alloc_matrix_double_set(size_t nrows, size_t ncols, double value)
{
  int i, j;
  matrix_double matrix;
  matrix.nrows = nrows;
  matrix.ncols = ncols;
  matrix.data = malloc(nrows * sizeof(double *));
  for (i = 0; i < nrows; i++) {
    matrix.data[i] = malloc(ncols * sizeof(double));
    for (j = 0; j < ncols; j++) {
      matrix.data[i][j] = value;
    }
  }
  return matrix;
}

/* allocate enough space for a nrows by ncols matrix and return it, with all
 * elements set to zero
 */
matrix_double alloc_matrix_double(size_t nrows, size_t ncols)
{
  return alloc_matrix_double_set(nrows, ncols, 0);
}

/* like alloc_matrix_double, but will contain all ones instead of zeros */
matrix_double alloc_matrix_double_ones(size_t nrows, size_t ncols)
{
  return alloc_matrix_double_set(nrows, ncols, 1);
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

/* Given a matrix, extract a section and return it as a new matrix */
matrix_double extract_section_matrix_double(matrix_double matrix,
                                            struct pair_coordinates section)
{
  int nrows, ncols, i, j;
  nrows = section.b.row - section.a.row;
  ncols = section.b.col - section.a.col;
  matrix_double new_matrix = alloc_matrix_double(nrows, ncols);
  for (i = section.a.row; i < section.b.row; i++) {
    for (j = section.a.col; j < section.b.col; j++) {
      new_matrix.data[i-section.a.row][j-section.a.col] = matrix.data[i][j];
    }
  }
  return new_matrix;
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
 * take a matrix "matrix" and multiply all its elements by "k"
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

/** matrix_product:
 * matrix multiplication. Take two matrices n x m and m x k and return
 * the matrix product (n x k).
 */
matrix_double matrix_product(matrix_double matrix1, matrix_double matrix2)
{
  if (matrix1.ncols != matrix2.nrows) {
    fprintf(stderr, "Error: attempt to multiply matrices with dimensions %d x %d and %d x %d.\n",
            (int)matrix1.nrows, (int)matrix1.ncols, (int)matrix2.nrows, (int)matrix2.ncols);
    /* return alloc_matrix_double(0, 0); */
  }
  matrix_double result = alloc_matrix_double(matrix1.nrows, matrix2.ncols);
  int i, j, k;
  for (i = 0; i < matrix1.nrows; i++) {
    for (j = 0; j < matrix2.ncols; j++) {
      result.data[i][j] = 0;
      for (k = 0; k < matrix1.ncols; k++) {
        result.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
      }
    }
  }
  return result;
}

/**
 * Perform the matrix product of two matrices, and return the result as a new
 * matrix. Both matrices must have the same dimensions.
 */
matrix_double matrix_dot_product(matrix_double m1, matrix_double m2)
{
  /* check dimensions */
  if ((m1.ncols != m2.ncols) || (m1.nrows != m2.nrows)) {
    fprintf(stderr, "Error: attempt to dot product matrices of different sizes: %dx%d and %dx%d.\n",
        (int)m1.nrows, (int)m1.ncols, (int)m2.nrows, (int)m2.ncols);
    return alloc_matrix_double(0, 0);
  }
  matrix_double result = alloc_matrix_double(m1.nrows, m2.ncols);
  int i, j;
  for (i = 0; i < m1.nrows; i++) {
    for (j = 0; j < m1.ncols; j++) {
      result.data[i][j] = m1.data[i][j] * m2.data[i][j];
    }
  }
  return result;
}

/* Add to the second matrix the elements of the first one. The first one
 * is modified, the second one remains untouched.
 * Both matrices must have the same dimensions.
 *
 * Returns: 0 if everything was OK, -1 if dimensions didn't match.
 */
int add_matrix_to_matrix_double(matrix_double toadd,
                                matrix_double tomodify)
{
  int i, j;
  /* check dimensions */
  if ((tomodify.ncols != toadd.ncols) || (tomodify.nrows != toadd.nrows)) {
    fprintf(stderr, "Error: attempt to add matrices of different sizes: %dx%d and %dx%d.\n",
        (int)tomodify.nrows, (int)tomodify.ncols, (int)toadd.nrows, (int)toadd.ncols);
    return -1;
  }
  for (i = 0; i < tomodify.nrows; i++)
    for (j = 0; j < tomodify.ncols; j++)
      tomodify.data[i][j] += toadd.data[i][j];
  return 0;
}

/**
 * Substract from the second matrix, the first one. The first matrix remains
 * untouched, but the second one is modified.
 */
int substract_matrix_from_matrix_double(matrix_double tosubstract,
                                        matrix_double tomodify)
{
  int i, j;
  /* check dimensions */
  if ((tomodify.ncols != tosubstract.ncols) || (tomodify.nrows != tosubstract.nrows)) {
    fprintf(stderr, "Error: attempt to substact matrices of different sizes: %dx%d and %dx%d.\n",
        (int)tomodify.nrows, (int)tomodify.ncols, (int)tosubstract.nrows, (int)tosubstract.ncols);
    return -1;
  }
  for (i = 0; i < tomodify.nrows; i++)
    for (j = 0; j < tomodify.ncols; j++)
      tomodify.data[i][j] -= tosubstract.data[i][j];
  return 0;
}

/* copy_row_matrix_double:
 * given a matrix "A", an array "v" and an integer "row",
 * copy the row A[row] into v
 */
void copy_row_matrix_double(matrix_double A, double *v, int row)
{
  int i;
  for (i = 0; i < A.ncols; i++) {
    v[i] = A.data[row][i];
  }
}

/* copy_col_matrix_double:
 * given a matrix "A", an array "v" and an integer "col",
 * copy the column "col" from A into v
 */
void copy_col_matrix_double(matrix_double A, double *v, int col)
{
  int i;
  for (i = 0; i < A.nrows; i++) {
    v[i] = A.data[i][col];
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
  for (i = 0; i < matrix.nrows; i++) {
    tmp = matrix.data[i][colA];
    matrix.data[i][colA] = matrix.data[i][colB];
    matrix.data[i][colB] = tmp;
  }
}

matrix_double transpose_matrix_double(matrix_double matrix)
{
  int i, j;
  matrix_double transposed = alloc_matrix_double(matrix.ncols, matrix.nrows);
  for (i = 0; i < matrix.nrows; i++)
    for (j = 0; j < matrix.ncols; j++)
      transposed.data[i][j] = matrix.data[j][i];
  return transposed;
}

void set_col_matrix_double(matrix_double matrix, double *column, int col_index)
{
  int i;
  for (i = 0; i < matrix.nrows; i++)
    matrix.data[i][col_index] = column[i];
}

/* Shuffle the columns using the Fisher Yates shuffle */
void shuffle_columns_matrix_double(matrix_double matrix)
{
  int i, j;
  for (i = matrix.ncols-1; i >= 1; i--) {
    j = rand_lim(i);
    interchange_cols_matrix_double(matrix, i, j);
  }
}

