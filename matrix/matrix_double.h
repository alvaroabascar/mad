#ifndef __MATRIX_DOUBLE_H__
#define __MATRIX_DOUBLE_H__

#include <stdlib.h>

typedef struct {
  size_t ncols;
  size_t nrows;
  double **data;
} matrix_double;

#endif /* __MATRIX__ */
