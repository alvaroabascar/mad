#include <stdio.h>
#include <matrix.h>
#include <gaussjbs.h>
#include <stdlib.h>

#define NREPS 100000
#define NROWS 1000

int main(int argc, char *argv[])
{
  int i;
  matrix_double A = alloc_matrix_double(NROWS, NROWS);
  srand(100);
  for (i = 0; i < NREPS; i++) {
    interchange_rows_matrix_double(&A, rand() % NROWS, rand() % NROWS);
  }
  return 0;
}
