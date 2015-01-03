#include <matrix.h>

/* Solve a tridiagonal system of equations.
 *
 * (Tridiagonal matrix algorithm or Thomas algorithm)
 *
 * The matrix is represented here as three
 * vectors: a is the lower diagonal, b is the diagonal and c the upper
 * diagonal. d is a the righ-hand side vector, modified to store the
 * solutions
 * dim is the dimension of the matrix (length of b)
 *
 * the three vectors are destroyed during the procedure
 */
void tridiag(int dim, double *a, double *b, double *c, double *d)
{
  int i;
  /* divide first row by b[0], to make it one */
  d[0] /= b[0];
  c[0] /= b[0];
  b[0] = 1;
  /* substract to each row the previous one multiplied by a, in order to
   * eliminate a. Then divide row by "b" to set the b to one.
   */
  for (i = 1; i < dim - 1; i++) {
    d[i] = (d[i] - d[i-1] * a[i-1]) / (b[i] - c[i-1] * a[i-1]);
    c[i] /= (b[i] - c[i-1] * a[i-1]); // upper element is zero, so no need to substract
    a[i-1] = 0; // a becomes zero (this is the pursue of this loop!)
    b[i] = 1;
  }
  /* now the last row */
  d[dim - 1] = (d[dim-1] - d[dim-2] * a[dim-2]) /
               (b[dim-1] - c[dim-2] * a[dim-2]);
  a[dim-2] = 0;
  b[dim-1] = 1;
  /* now all "a"s are zero, and we can do backsubstitution */
  /* note that the last row is all zeros but the last element (1) */
  for (i = dim-2; i >= 0; i--) {
   d[i] -= c[i] * d[i+1];
  }
}
