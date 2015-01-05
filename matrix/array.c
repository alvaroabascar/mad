#include <stdio.h>
#include "array.h"
#define max(x) ((x > 0) ? x : -x)

/* print */

void print_array_int(int len, int *array)
{
  int i;
  printf("{");
  for (i = 0; i < len; i++) {
    printf("%10d%s", array[i], (i < len - 1) ? ", " : "}\n");
  }
}

void print_array_double(int len, double *array)
{
  int i;
  printf("{");
  for (i = 0; i < len; i++) {
    printf("%10.4f%s", array[i], (i < len - 1) ? ", " : "}\n");
  }
}

/* interchange elements */

void interchange_array_elements_int(int *array, int i, int j)
{
  int tmp;
  tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

void interchange_array_elements_double(double *array, int i, int j)
{
  double tmp;
  tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

/* reorder elements */

void reorder_array_int(int len, int *array, int *orders_arg)
{
  int i;
  int orders[len];
  /* copy orders array to avoid destroying it */
  for (i = 0; i < len; i++) {
    orders[i] = orders_arg[i];
  }
  for (i = 0; i < len; i++) {
    while (orders[i] != i) {
      interchange_array_elements_int(array, i, orders[i]);
      interchange_array_elements_int(orders, i, orders[i]);
    }
  }
}

void reorder_array_double(int len, double *array, int *orders_arg)
{
  int i;
  int orders[len];
  /* copy orders array to avoid destroying it */
  for (i = 0; i < len; i++) {
    orders[i] = orders_arg[i];
  }
  for (i = 0; i < len; i++) {
    while (orders[i] != i) {
      interchange_array_elements_double(array, i, orders[i]);
      interchange_array_elements_int(orders, i, orders[i]);
    }
  }
}

/* copy arrays */

void copy_array_int(int len, int *source, int *dest)
{
  int i;
  for (i = 0; i < len; i++) {
    dest[i] = source[i];
  }
}

void copy_array_double(int len, double *source, double *dest)
{
  int i;
  for (i = 0; i < len; i++) {
    dest[i] = source[i];
  }
}

/* multiply */

void multiply_array_int(int len, int *array, int k)
{
  int i;
  for (i = 0; i < len; i++) {
    array[i] *= k;
  }
}

void multiply_array_double(int len, double *array, double k)
{
  int i;
  for (i = 0; i < len; i++) {
    array[i] *= k;
  }
}

/* absolute value */

int absmax_array_int(int len, int *array)
{
  int max = 0;
  while (len-- > 0) {
    if (abs(array[len]) > max) {
      max = array[len];
    }
  }
  return max;
}

double absmax_array_double(int len, double *array)
{
  double max = 0;
  while (len-- > 0) {
    if (abs(array[len]) > max) {
      max = array[len];
    }
  }
  return max;
}
