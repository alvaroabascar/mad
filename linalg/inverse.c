#include <stdio.h>
#include <matrix.h>
#include <ludcmp.h>

matrix_double inverse(matrix_double M)
{
  int changes[M.nrows];
  int d, i;
  double col[M.nrows];

  matrix_double Mcp = copy_matrix_double(M);
  matrix_double inverse = alloc_matrix_double(M.nrows, M.nrows);

  /* Store in Mcp the LU decomposition of M */
  if (ludcmp(Mcp, changes, &d)) {
    fprintf(stderr, "inverse: singular matrix\n");
    inverse.nrows = 0;
    inverse.ncols = 0;
    return inverse;
  }

  for (i = 0; i < M.ncols; i++) {
    /* create column i of the unit matrix */
    for (d = 0; d < M.ncols; d++) {
      col[0] = 0;
    }
    col[i] = 1;
    /* find column i of the inverse */
    lusolve(Mcp, col, changes);
    /* fill inverse */
    for (d = 0; d < M.ncols; d++) {
      inverse.data[i][d] = col[d];
    }
  }
  return inverse;
}
