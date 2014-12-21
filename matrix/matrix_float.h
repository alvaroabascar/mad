#ifndef __MATRIX_FLOAT_H__
#define __MATRIX_FLOAT_H__

#include <stdlib.h>

typedef struct {
  size_t ncols;
  size_t nrows;
  float **data;
} matrix_float;

#endif /* __MATRIX__ */
