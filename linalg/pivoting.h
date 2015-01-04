#ifndef __PIVOTING_H__
#define __PIVOTING_H__
int do_partial_pivoting(matrix_double *A, matrix_double *B, int i,
                        double *scaling,
                        int *row_changes);

void do_full_pivoting(matrix_double *A, matrix_double *B, int i,
                      int *col_changes);

#endif /* __PIVOTING_H__ */
