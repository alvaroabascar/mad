#ifndef __ARRAY_H__
#define __ARRAY_H__

void print_array_int(int len, int *array);
void print_array_double(int len, double *array);

void interchange_array_elements_int(int *array, int i, int j);
void interchange_array_elements_double(double *array, int i, int j);

void reorder_array_int(int len, int *array, int *orders);
void reorder_array_double(int len, double *array, int *orders);

void copy_vector_int(int len, int *source, int *dest);
void copy_vector_double(int len, double *source, double *dest);

void multiply_vector_int(int len, int *vector, int k);
void multiply_vector_double(int len, double *vector, int k);

int absmax_vector_int(int len, int *vector);
double absmax_vector_double(int len, double *vector);

#endif /* __ARRAY_H_ */
