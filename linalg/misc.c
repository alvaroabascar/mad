#define abs(x) ((x > 0 ? x : -x))

/* Perform the pivoting process: look for the best pivot and then
 * interchange the rows accordingly. (Only partial pivoting)
 */
void do_partial_pivoting(matrix_double *A, matrix_double *B, int i,
                                           double *scaling)
{
  struct coordinate pivot = find_best_pivot_column(A, i, scaling);
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
struct coordinate find_best_pivot_column(matrix_double *A, int pos,
                                         double *scaling)
{
  int i;
  double max_pivot_val = abs(A->data[pos][pos]);
  struct coordinate best_pivot = { .row = pos, .col = pos };
  for (i = pos; i < A->nrows; i++) {
    if (abs(A->data[i][pos]) / scaling[i] > max_pivot_val) {
      max_pivot_val = abs(A->data[i][pos]) / scaling[i];
      best_pivot.row = i;
    }
  }
  return best_pivot;
}
