#ifndef __MATRIX_DOUBLE_H__
#define __MATRIX_DOUBLE_H__

#include <stdlib.h>

/* matrix_double type */
typedef struct {
  size_t ncols;
  size_t nrows;
  double **data;
} matrix_double;

/* create, copy and destroy matrices */
matrix_double alloc_matrix_double(size_t nrows, size_t ncols);
matrix_double alloc_matrix_double_set(size_t nrows, size_t ncols, double value);
matrix_double copy_matrix_double(matrix_double matrix);
void free_matrix_double(matrix_double matrix);

/* print matrices */
void print_matrix_double(matrix_double matrix);

/* modify sections of a matrix */
void multiply_section_matrix_double(matrix_double matrix,
                                  struct pair_coordinates section,
                                  double k);
void add_to_section_matrix_double(matrix_double matrix,
                                  struct pair_coordinates section,
                                  double k);
void reorder_matrix_rows_double(matrix_double matrix, int *orders);

matrix_double extract_section_matrix_double(matrix_double matrix,
                                            struct pair_coordinates section);
/*** multiplication ***/

/* single row */
void multiply_row_matrix_double(matrix_double matrix, int row, double k);
/* scalar */
void multiply_matrix_double(matrix_double matrix, double k);
/* dot product */
matrix_double matrix_product(matrix_double matrix1, matrix_double matrix2);

/* addition */
int add_matrix_to_matrix_double(matrix_double toadd,
                                matrix_double tomodify);
/* substraction */
int substract_matrix_from_matrix_double(matrix_double tosubstract,
                                        matrix_double tomodify);

/*** work with individual columns / rows ***/
void interchange_rows_matrix_double(matrix_double matrix, int rowA, int rowB);
void interchange_cols_matrix_double(matrix_double matrix, int colA, int colB);
void set_col_matrix_double(matrix_double matrix, double *column, int col_index);
void shuffle_columns_matrix_double(matrix_double matrix);
void copy_row_matrix_double(matrix_double A, double *v, int row);
void copy_col_matrix_double(matrix_double A, double *v, int col);
void add_to_row_matrix_double(matrix_double matrix, int row,
                              double vector[matrix.ncols]);

matrix_double transpose_matrix_double(matrix_double matrix);
#endif /* __MATRIX_DOUBLE_H_ */
