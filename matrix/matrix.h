#ifndef __MATRIX_H__
#define __MATRIX_H__

struct coordinate {
  int row;
  int col;
};

struct pair_coordinates {
  struct coordinate a;
  struct coordinate b;
};

#include "array.h"
#include "matrix_double.h"

#endif /* __MATRIX_H__ */
