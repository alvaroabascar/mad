#include <stdio.h>
#include <matrix.h>
#include <pivoting.h>

/* Given a matrix A, this routine replaces it by its LU decomposition.
 *
 * d is modified to store the parity of row interchanges.
 *     - If d is -1, the number of interchanges is odd.
 *     - If d is +1, the number of interchanges is even.
 *
 * This function uses the Crout's algorithm with implicit pivoting.
 *
 * The matrix L has diagonal elements equal to 1. These can be obviated, and
 * both L and U are stored in the original matrix A.
 *
 * The partial pivoting implies that the resulting LU is the decomposition
 * of a row-wise permutation of A. The permutations are stored in the
 * array "changes". E.g. if only rows 1 and 3 are interchanged, then
 * changes[1] = 3, changes[3] = 1, and changes[i] = i for every i != 1 and
 * i != 3.
 */
int ludcmp(matrix_double A, int *changes, int *d)
{
  int i, j, k;
  *d = 0;

  /* keep track of the scale of each row (for implicit pivoting) */
  double scaling[A.nrows];
  for (j = 0; j < A.ncols; j++) {
    changes[j] = j;
    scaling[j] = absmax_vector_double(A.nrows, A.data[j]);
  }

  for (j = 0; j < A.ncols; j++) {
    for (i = 0; i <= j; i++) {
      for (k = 0; k < i; k++) {
        /* calculate the elements of the upper matrix*/
        A.data[i][j] -= A.data[i][k] * A.data[k][j];
      }
    }
    for (i = j + 1; i < A.ncols; i++) {
      for (k = 0; k < j; k++) {
        /* calculate the elements of the lower matrix, but
         * postpone the division */
        A.data[i][j] -= A.data[i][k] * A.data[k][j];
      }
    }
    d += do_partial_pivoting(A, NULL, j, scaling, changes);
    if (A.data[j][j] == 0) {
      fprintf(stderr, "ludcmp: singular matrix\n");
      return -1;
    }
    for (i = j + 1; i < A.ncols; i++) {
      A.data[i][j] /= A.data[j][j];
    }
  }
  *d %= 2; /* 0 if even, 1 if odd */
  *d = 1 - (*d * 2); /* 1 if even, -1 if odd */
  return 0;
}

/* Given a LU decomposed matrix "LU", a right-hand side vector "B", an
 * array containing the row changes "changes" and an integer "d" specifying
 * whether the number of changes is even (0) or odd (1), transform "B" into
 * the vector of solutions
 *
 * Explanation:
 * Our system is of the form:
 * A x = b <=> (L U) x = b <=> L (U x) = b
 *
 * We can solve it by first solving for y such that:
 *  L y = b (solved by forward substitution)
 *
 * And then solving for x such that:
 *  U x = y (solved by backward substitution)
 */
void lusolve(matrix_double LU, double *B, int *changes)
{
  int i, j;

  /* step 1: forward substitution. solve y for L y = b */

  for (i = 0; i < LU.nrows; i++) {
    for (j = 0; j < i; j++) {
      B[i] -= B[j] * LU.data[i][j];
    }
  }

  /* now B contains y */
  /* step 2: backward substitution, solve x for U x = y */

  for (i = LU.nrows - 1; i >= 0; i--) {
    for (j = LU.ncols - 1; j > i; j--) {
      B[i] -= B[j] * LU.data[i][j];
    }
    B[i] /= LU.data[j][j];
  }
  reorder_array_double(LU.nrows, B, changes);
}

/* Return the determinant of a matrix, using its
 * LU decomposition
 */
double determinant(matrix_double A)
{
  int i, d;
  double det = 1;
  int changes[A.nrows];
  /* LU decomposition */
  if (ludcmp(A, changes, &d)) {
    fprintf(stderr, "determinant: singular matrix\n");
    return 0.0 / 0.0;
  }
  /* The determinant is the product of the diagonal elements */
  for (i = 0; i < A.nrows; i++) {
    det *= A.data[i][i];
  }
  /* If num of row interchanges was odd, the determinant is the
   * opposite (d = -1), else d = 1
   */
  return det * d;
}
