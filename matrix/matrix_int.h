#ifndef __MATRIX_int_H__
#define __MATRIX_int_H__

#include <stdlib.h>

typedef struct {
  size_t ncols;
  size_t nrows;
  int **data;
} matrix_int;

matrix_int alloc_matrix_int(size_t nrows, size_t ncols);
matrix_int copy_matrix_int(matrix_int matrix);
void free_matrix_int(matrix_int matrix);
void print_matrix_int(matrix_int matrix);
void print_array_int(int len, int *array);
void multiply_section_matrix_int(matrix_int matrix,
                                  struct pair_coordinates section,
                                  int k);
void add_to_section_matrix_int(matrix_int matrix,
                                  struct pair_coordinates section,
                                  int k);
void interchange_array_elements_int(int *array, int i, int j);
void reorder_matrix_rows_int(matrix_int matrix, int *orders);
void reorder_array_int(int len, int *array, int *orders);
void multiply_row_matrix_int(matrix_int matrix, int row, int k);
void multiply_matrix_int(matrix_int matrix, int k);
void copy_row_matrix_int(matrix_int A, int *v, int row);
void add_to_row_matrix_int(matrix_int matrix, int row,
                              int vector[matrix.ncols]);
void interchange_rows_matrix_int(matrix_int matrix, int rowA, int rowB);
void interchange_cols_matrix_int(matrix_int matrix, int colA, int colB);
void copy_vector_int(int len, int *source, int *dest);
void multiply_vector_int(int len, int *vector, int k);
int absmax_vector_int(int len, int *vector);



#endif /* __MATRIX_int_H_ */
