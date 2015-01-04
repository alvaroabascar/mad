#ifndef __LUDCMP_H__
#define __LUDCMP_H__

int ludcmp(matrix_double A, int *changes, int *d);
void lusolve(matrix_double LU, double *B, int *changes);
double determinant(matrix_double A);

#endif /* __LUDCMP_H__ */
