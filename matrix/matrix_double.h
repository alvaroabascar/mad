#ifndef __MATRIX_DOUBLE_H__
#define __MATRIX_DOUBLE_H__

#include <stdlib.h>

typedef struct {
  size_t ncols;
  size_t nrows;
  double **data;
} matrix_double;

matrix_double alloc_matrix_double(size_t nrows, size_t ncols);
matrix_double copy_matrix_double(matrix_double matrix);
void free_matrix_double(matrix_double matrix);
void print_matrix_double(matrix_double matrix);
void multiply_section_matrix_double(matrix_double matrix,
                                  struct pair_coordinates section,
                                  double k);
void add_to_section_matrix_double(matrix_double matrix,
                                  struct pair_coordinates section,
                                  double k);
void reorder_matrix_rows_double(matrix_double matrix, int *orders);

/* multiplication */
void multiply_row_matrix_double(matrix_double matrix, int row, double k);
void multiply_matrix_double(matrix_double matrix, double k);
matrix_double matrix_product_matrix_double(matrix_double matrix1, matrix_double matrix2);

void copy_row_matrix_double(matrix_double A, double *v, int row);
void add_to_row_matrix_double(matrix_double matrix, int row,
                              double vector[matrix.ncols]);
void interchange_rows_matrix_double(matrix_double matrix, int rowA, int rowB);
void interchange_cols_matrix_double(matrix_double matrix, int colA, int colB);

matrix_double transpose_matrix_double(matrix_double matrix);
#endif /* __MATRIX_DOUBLE_H_ */
