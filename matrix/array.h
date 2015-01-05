#ifndef __ARRAY_H__
#define __ARRAY_H__

void print_array_int(int len, int *array);
void print_array_double(int len, double *array);

void interchange_array_elements_int(int *array, int i, int j);
void interchange_array_elements_double(double *array, int i, int j);

void reorder_array_int(int len, int *array, int *orders);
void reorder_array_double(int len, double *array, int *orders);

void copy_array_int(int len, int *source, int *dest);
void copy_array_double(int len, double *source, double *dest);

void multiply_array_int(int len, int *array, int k);
void multiply_array_double(int len, double *array, double k);

int absmax_array_int(int len, int *array);
double absmax_array_double(int len, double *array);

#endif /* __ARRAY_H_ */
