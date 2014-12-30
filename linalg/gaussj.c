#include <stdio.h>
#include <matrix.h>
#include "misc.c"

/* Gauss-Jordan elimination with full pivoting */

#define abs(x) ((x > 0 ? x : -x))

void do_pivoting(matrix_double *A, matrix_double *B, int i, int *col_changes);
struct coordinate find_best_pivot(matrix_double *A, int i);

/* Given a matrix of coefficients (A), and a matrix of right-hand sides (B),
 * which compose a system of equations A*x = B, perform a gauss-jordan
 * elimination to produce the inverse of A and the matrix of solutions X.
 *
 * Note: B might be a n by 1 matrix (a vector) or a n x m matrix. This last
 * case is equivalent to solving m systems of equations.
 */
void gaussj(matrix_double *A, matrix_double *B)
{
  /* Set i = 0
   * 1. Divide row i by pivot [i][i]
   *      1.1. Find best pivot
   *          1.1.1. Check same row
   *               best in same row? exchange cosl in A, exchange rows in
   *               B, keep track of the changes
   *          1.1.2. Check same column
   *               best in same column? exchange rows in A and B. No need to
   *               keep track of the change
   * 2. Substract from each row j > i the row[i]*row[j][0]
   * Increase i
   */

   int i, j;
   double pivot;
   double current_row_A[A->ncols];
   double current_row_B[B->ncols];
   double row_to_substract_A[A->ncols];
   double row_to_substract_B[B->ncols];
   /* keep track of column interchanges */
   int col_changes[A->ncols];
   int col_changes_copy[A->ncols];
   /* currently all cols are in the original state:
    * col_changes[0] = 0, col_changes[1] = 1, etc.
    * If at some point col 0 and 1 are interchanged, this will
    * be stored in the array as:
    * col_changes[0] = 1, col_changes[1] = 0.
    */
   for(i = 0; i < A->ncols; i++) {
     col_changes[i] = i;
   }

   /* for each element in the diagonal... */
   for (i = 0; i < A->nrows; i++) {
     /* 1. place in the diagonal the best (largest) element found in either
      * below in the same column or at the right in the same row, keeping
      * track of the column interchanges, if any. */
     do_pivoting(A, B, i, col_changes);
     pivot = A->data[i][i];
     /* 2. divide this row by the pivot */
     /* 2.1 do it in A (we skip elements at left of pivot, which are zero) */
     A->data[i][i] = 1;
     
     multiply_row_matrix_double(A, i, 1/pivot);
     /* 2.2 do it in B. In this case do it with the whole row */
     multiply_row_matrix_double(B, i, 1/pivot);
     /* 3. for each row below, substract the right amount from the current row
      * to make all the elements below the pivot equal to zero
      * We do it in A and in B */
     /* obtain current row from the matrices */
     copy_row_matrix_double(A, current_row_A, i);
     copy_row_matrix_double(B, current_row_B, i);
     /* for each OTHER row, substract the right amount of current_row to
      * make the elements [j][i] equal to zero */
     for (j = 0; j < A->nrows; j++) {
       if (j == i) {
         continue;
       }
       /* copy it into another vector and multiply it by the element we
        * wish to make zero (-1 is to add instead of substract) */
       copy_vector_double(A->ncols, current_row_A, row_to_substract_A);
       copy_vector_double(B->ncols, current_row_B, row_to_substract_B);
       multiply_vector_double(A->ncols, row_to_substract_A, -1*A->data[j][i]);
       multiply_vector_double(B->ncols, row_to_substract_B, -1*A->data[j][i]);
       A->data[j][i] = 0;
       /* now substract (add, as it was multiplied by -1) it from row j */
       add_to_row_matrix_double(A, j, row_to_substract_A);
       add_to_row_matrix_double(B, j, row_to_substract_B);
     }
   }
   /* unscramble solution using col_changes as the guide */
   copy_vector_int(A->ncols, col_changes, col_changes_copy);
   reorder_matrix_rows_double(B, col_changes);
   reorder_matrix_rows_double(A, col_changes_copy);
}

/* perform the pivoting process: look for the best pivot and then
 * interchange the rows or columns accordingly. Increase num_changes 
 * if two columns have been interchanged
 */
void do_pivoting(matrix_double *A, matrix_double *B, int i, int *col_changes)
{
  struct coordinate pivot = find_best_pivot(A, i);
  /* if we need to interchange columns */
  if (pivot.col > i) {
    /* interchange columns in A */
    interchange_cols_matrix_double(A, i, pivot.col);
    /* and keep track of it */
    interchange_array_elements_double(col_changes, i, pivot.col);
  }
  /* if we need to interchange rows */
  if (pivot.row > i && pivot.col == i) {
    /* interchange rows in A and B*/
    interchange_rows_matrix_double(A, i, pivot.row);
    interchange_rows_matrix_double(B, i, pivot.row);
  }
}

/* Given a matrix A, and the position (i, j) for which a pivot is needed,
 * this function finds the best (largest) pivot, which is returned in a
 * struct coordinate {row, col}
 */
struct coordinate find_best_pivot(matrix_double *A, int pos)
{
  int i, j;
  double max_pivot_val = abs(A->data[pos][pos]);
  struct coordinate best_pivot = { .row = pos, .col = pos };
  for (i = pos; i < A->nrows; i++) {
    for (j = pos; j == pos; j++) {
    //for (j = pos; j < A->ncols; j++) {
      if (abs(A->data[i][j]) > max_pivot_val) {
        max_pivot_val = abs(A->data[i][j]);
        best_pivot.row = i;
        best_pivot.col = j;
      }
    }
  }
  return best_pivot;
}
