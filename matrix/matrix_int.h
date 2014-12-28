#ifndef __MATRIX_INT_H__
#define __MATRIX_INT_H__

#include <stdlib.h>

typedef struct {
  size_t ncols;
  size_t nrows;
  int **data;
} matrix_int;

#endif /* __MATRIX_INT__ */
