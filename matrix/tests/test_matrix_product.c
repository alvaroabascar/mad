#include <matrix.h>

int main(int argc, char *argv[])
{
  matrix_double m = alloc_matrix_double(2, 2);
  matrix_double n = alloc_matrix_double(2, 2);
  matrix_double prod;
  m.data[0][0] = 1;
  m.data[0][1] = 1;
  m.data[1][0] = 1;
  m.data[1][1] = 1;

  n.data[0][0] = 2;
  n.data[0][1] = 2;
  n.data[1][0] = 2;
  n.data[1][1] = 2;

  prod = matrix_product_matrix_double(m, n);
  print_matrix_double(prod);
  return 0;
}
