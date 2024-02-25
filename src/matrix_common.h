#ifndef MATRIX_COMMON_H
#define MATRIX_COMMON_H

void input(double **matrix, const int *n, const int *m, int *error);
void output(double **matrix, int n, int m);
double **dynalloc_type2(int n, int m);
double det(double **matrix, int n, int m);
void transpose(double **matrix, double **fac, int r);
void invert(double **matrix, int n);
void output_roots(double *roots, int n);
double cramer_solve(double **matrix, int n, int m, double det_A, int var);
int sle(double **matrix, int n, int m, double *roots);
void sort_vertical(double **matrix, int n, int m, double **result_matrix);
void sort_horizontal(double **matrix, int n, int m, double **result_matrix);
void sorting(double *a, int n);
void swap_values(double *a, int i, int j);

#endif