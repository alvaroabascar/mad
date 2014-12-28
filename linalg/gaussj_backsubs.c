#include <stdio.h>
#include "../matrix/matrix.h"

/* Gauss-Jordan elimination with full pivoting */

#define abs(x) ((x > 0 ? x : -x))

void do_partial_pivoting(matrix_double *A, matrix_double *B, int i, int *row_changes,
                                                            int *col_changes);
struct coordinate find_best_col_pivot(matrix_double *A, int i);

/* Given a matrix of coefficients (A), and a matrix of right-hand sides (B),
 * which compose a system of equations A*x = B, perform a gauss-jordan
 * elimination to produce the inverse of A and the matrix of solutions X.
 *
 * Note: B might be a n by 1 matrix (a vector) or a n x m matrix. This last
 * case is equivalent to solving m systems of equations.
 */
void gaussj_backsubs(matrix_double *A, matrix_double *B)
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

   int i, j, k;
   double pivot;
   double current_row_A[A->ncols];
   double current_row_B[B->ncols];
   double row_to_substract_A[A->ncols];
   double row_to_substract_B[B->ncols];
   /* keep track of row and column interchanges */
   int row_changes[A->nrows];
   int col_changes[A->ncols];
   int col_changes_copy[A->ncols];
   /* currently all rows & cols are in the original state:
    * row_changes[0] = 0, row_changes[1] = 1, etc.
    * If at some point row 0 and 1 are interchanged, this will
    * be stored in the array as:
    * row_changes[0] = 1, row_changes[1] = 0.
    * The same will occur with col_changes
    */
   for (i = 0; i < A->nrows; i++) {
     row_changes[i] = i;
   }
   for(i = 0; i < A->ncols; i++) {
     col_changes[i] = i;
   }

   /* I use this to delimitate a section of the matrix, so that I
    * can easily divide only the elements at the right at the pivot, and
    * not all the row */
   struct pair_coordinates matrix_section;

   /* for each element in the diagonal... */
   for (i = 0; i < A->nrows; i++) {
     /* 1. place in the diagonal the best (largest) element found in either
      * below in the same column or at the right in the same row, keeping
      * track of the column interchanges, if any. */
     do_partial_pivoting(A, B, i, row_changes, col_changes);
     pivot = A->data[i][i];
     /* 2. divide this row by the pivot */
     /* 2.1 do it in A (we skip elements at left of pivot, which are zero) */
     matrix_section.a = (struct coordinate) { .row = i,
                                              .col = i };
     matrix_section.b = (struct coordinate) { .row = i,
                                              .col = A->ncols - 1 };
     /* multiply_section_matrix_double(A, matrix_section, 1 / pivot); */
     multiply_row_matrix_double(A, i, 1 / pivot);
     /* 2.2 do it in B. In this case do it with the whole row */
     multiply_row_matrix_double(B, i, 1 / pivot);
     /* 3. for each row below, substract the right amount from the current row
      * to make all the elements below the pivot equal to zero
      * We do it in A and in B */
     /* obtain current row from the matrices */
     copy_row_matrix_double(A, current_row_A, i);
     copy_row_matrix_double(B, current_row_B, i);
     /* for each OTHER row, substract the right amount of current_row to
      * make the elements [j][i] zero */
     for (j = i + 1; j < A->nrows; j++) {
       /* copy it into another vector and multiply it by the element we
        * wish to make zero (-1 is to add instead of substract) */
       copy_vector_double(A->ncols, current_row_A, row_to_substract_A);
       copy_vector_double(B->ncols, current_row_B, row_to_substract_B);
       multiply_vector_double(A->ncols, row_to_substract_A, -1*A->data[j][i]);
       multiply_vector_double(B->ncols, row_to_substract_B, -1*A->data[j][i]);
       /* now substract (add, as it was multiplied by -1) it from row j */
       add_to_row_matrix_double(A, j, row_to_substract_A);
       add_to_row_matrix_double(B, j, row_to_substract_B);
     }
   }
   /* backsubstitution */
   /* this should be refactorized and hidden... */
   for (i = A->nrows - 1; i >= 0; i--) {
     for (j = A->ncols - 1; j > i; j--) {
       for (k = 0; k < B->ncols; k++) {
         B->data[i][k] -= A->data[i][j] * B->data[j][k];
       }
     }
     for (k = 0; k < B->ncols; k++) {
       B->data[i][k] /= A->data[j][j];
     }
   }
}

/* perform the pivoting process: look for the best pivot and then
 * interchange the rows or columns accordingly. Increase num_changes 
 * if two columns have been interchanged
 */
void do_partial_pivoting(matrix_double *A, matrix_double *B, int i, int *row_changes,
                                                            int *col_changes)
{
  struct coordinate pivot = find_best_col_pivot(A, i);
  /* we need to interchange rows */
  if (pivot.row > i) {
    /* interchange rows in A and B*/
    interchange_rows_matrix_double(A, i, pivot.row);
    interchange_rows_matrix_double(B, i, pivot.row);
    /* keep track of it */
    interchange_array_elements_double(row_changes, i, pivot.row);
  }
}

/* Given a matrix A, and the position (i, j) for which a pivot is needed,
 * this function finds the best (largest) pivot in the same column, which is
 * returned as a struct coordinate {row, col}
 */
struct coordinate find_best_col_pivot(matrix_double *A, int pos)
{
  int i;
  double max_pivot_val = abs(A->data[pos][pos]);
  struct coordinate best_pivot = { .row = pos, .col = pos };
  for (i = pos; i < A->nrows; i++) {
    if (abs(A->data[i][pos]) > max_pivot_val) {
      max_pivot_val = abs(A->data[i][pos]);
      best_pivot.row = i;
      best_pivot.col = pos;
    }
  }
  return best_pivot;
}
