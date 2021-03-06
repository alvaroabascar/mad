#include <stdio.h>
#include <matrix.h>
#include <gaussjbs.h>
#include <pivoting.h>

/* Gauss-Jordan elimination with partial implicit pivoting */

#define abs(x) ((x > 0 ? x : -x))

/* Given a matrix of coefficients (A), and a matrix of right-hand sides (B),
 * which compose a system of equations A*x = B, perform a gauss-jordan
 * elimination to produce the inverse of A and the matrix of solutions X.
 *
 * Note: B might be a n by 1 matrix (a array) or a n x m matrix. This last
 * case is equivalent to solving m systems of equations.
 */
int gaussjbs(matrix_double A, matrix_double B)
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
   double current_row_A[A.ncols];
   double current_row_B[B.ncols];
   double row_to_substract_A[A.ncols];
   double row_to_substract_B[B.ncols];
   double scaling[A.nrows];

   for (i = 0; i < A.nrows; i++) {
     scaling[i] = absmax_array_double(A.ncols, A.data[i]);
   }

   /* I use this to delimitate a section of the matrix, so that I
    * can easily divide only the elements at the right at the pivot, and
    * not all the row */
   struct pair_coordinates matrix_section;

   /* for each element in the diagonal... */
   for (i = 0; i < A.nrows; i++) {
     /* 1. place in the diagonal the best (largest) element found in either
      * below in the same column
      */
     do_partial_pivoting(A, &B, i, scaling, NULL);
     pivot = A.data[i][i];
     if (pivot == 0) {
       fprintf(stderr, "gaussjbs: singular matrix\n");
       return -1;
     }
     /* 2. divide this row by the pivot */
     /* 2.1 do it in A (we skip elements at left of pivot, which are zero) */
     A.data[i][i] = 1;
     if (i < A.ncols - 1) {
       matrix_section.a = (struct coordinate) { .row = i,
                                                .col = i + 1 };
       matrix_section.b = (struct coordinate) { .row = i,
                                                .col = A.ncols - 1 };
       multiply_section_matrix_double(A, matrix_section, 1 / pivot);
     }
     /* 2.2 do it in B. In this case do it with the whole row */
     multiply_row_matrix_double(B, i, 1 / pivot);
     /* 3. for each row below, substract the right amount from the current row
      * to make all the elements below the pivot equal to zero
      * We do it in A and in B */
     /* obtain current row from the matrices */
     copy_row_matrix_double(A, current_row_A, i);
     copy_row_matrix_double(B, current_row_B, i);
     /* for each OTHER row, substract the right amount of current_row to
      * make the elements [j][i] equal to zero */
     for (j = i + 1; j < A.nrows; j++) {
       /* copy it into another array and multiply it by the element we
        * wish to make zero (-1 is to add instead of substract) */
       copy_array_double(A.ncols, current_row_A, row_to_substract_A);
       copy_array_double(B.ncols, current_row_B, row_to_substract_B);
       multiply_array_double(A.ncols, row_to_substract_A, -1*A.data[j][i]);
       multiply_array_double(B.ncols, row_to_substract_B, -1*A.data[j][i]);
       /* now substract (add, as it was multiplied by -1) it from row j */
       add_to_row_matrix_double(A, j, row_to_substract_A);
       add_to_row_matrix_double(B, j, row_to_substract_B);
     }
   }
   /* backsubstitution */
   for (i = A.nrows - 1; i >= 0; i--) {
     multiply_array_double(B.ncols, current_row_B, 0); // set to zero
     for (j = A.ncols - 1; j > i; j--) {
       for (k = 0; k < B.ncols; k++) {
         current_row_B[k] -= B.data[j][k] * A.data[i][j];
       }
     }
     add_to_row_matrix_double(B, i, current_row_B);
     multiply_row_matrix_double(B, i, 1 / A.data[i][i]);
   }
   return 0;
}
