#include <ludcmp.h>
#include <matrix.h>

matrix_double inverse(matrix_double &M)
{
  int changes[M->nrows];
  int d, i;
  double col[M->nrows];

  matrix_double Mcp = copy_matrix_double(M);
  matrix_double inverse = alloc_matrix_double(Mcp->nrows, M->nrows);

  /* Store in Mcp the LU decomposition of M */
  ludcmp(Mcp, changes, &d);

  for (i = 0; i < M->ncols; i++) {
    /* create column i of the unit matrix */
    for (d = 0; d < M->ncols; d++) {
      col[0] = 0;
    }
    col[i] = 1;
    /* find column i of the inverse */
    lusolve(Mcp, col, changes);
    /* fill inverse */
    for (d = 0; d < M->ncols; d++) {
      inverse->data[i][d] = col[d];
    }
  }
  return inverse;
}


#endif /* __INVERSE_H__ */
