#include <matrix.h>
#include "pivoting.c"

/* Given a matrix A, this routine replaces it by its LU decomposition.
 * d is modified to store the number of row interchanges.
 *     - If d is 1, the number of interchanges is odd.
 *     - If d is 0, the number of interchanges is even.
 *
 * This function uses the Crout's algorithm, with implicit pivoting.
 *
 * The matrix L has diagonal elements equal to 1. These can be obviated, and
 * we store both L and U in the original matrix A.
 *
 * The implicit pivoting implies that the resulting LU is the decomposition
 * of a row-wise permutation of A. The permutations are stored in the
 * array "changes". E.g. if only rows 1 and 3 are interchanged, then
 * changes[1] = 3, changes[3] = 1, and changes[i] = i for every i != 1 and
 * != 3.
 */
void ludcmp(matrix_double *A, int *changes, int *d)
{
  int i, j, k;
  double scaling[A->nrows];

  for (j = 0; j < A->ncols; j++) {
    scaling[j] = absmax_vector_double(A->nrows, A->data[j]);
  }

  for (j = 0; j < A->ncols; j++) {
    for (i = 0; i <= j; i++) {
      for (k = 0; k < i; k++) {
        A->data[i][j] -= A->data[i][k] * A->data[k][j];
      }
    }
    for (i = j + 1; i < A->ncols; i++) {
      for (k = 0; k < j; k++) {
        A->data[i][j] -= A->data[i][k] * A->data[k][j];
      }
      do_partial_pivoting(A, NULL, i, scaling);
      A->data[i][j] /= A->data[j][j];
    }
  }
}

