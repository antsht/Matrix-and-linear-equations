#include "matrix_common.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n, int m) {
    if (n == 1) return matrix[0][0];
    double ans = 0;
    double **minor = dynalloc_type2(n - 1, m - 1);
    int l = 1;
    for (int i = 0; i < n; ++i) {
        int x = 0, y = 0;
        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (i == k) continue;
                minor[x][y] = matrix[j][k];
                ++y;
                if (y == n - 1) {
                    y = 0;
                    ++x;
                }
            }
        }
        ans += l * matrix[0][i] * det(minor, n - 1, m - 1);
        l *= (-1);
    }
    free(minor);
    return ans;
}

void input(double **arr, const int *n, const int *m, int *error) {
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%lf", &arr[i][j]) != 1) {
                *error = 1;
                break;
            }
        }
        if (*error == 1) break;
    }
}

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%lf", matrix[i][j]);
            if (j != m - 1) printf(" ");
        }
        if (i != n - 1) printf("\n");
    }
}

double **dynalloc_type2(int n, int m) {
    int status = 0;
    double **single_array_matrix = (double **)malloc(n * m * sizeof(double) + n * sizeof(double *));
    if (single_array_matrix != NULL) {
        double *ptr = (double *)(single_array_matrix + n);
        for (int i = 0; i < n; i++) single_array_matrix[i] = ptr + m * i;
    } else {
        status = -1;
    }
    if (status == -1) {
        free(single_array_matrix);
    }
    return status == 0 ? single_array_matrix : NULL;
}

void invert(double **matrix, int f) {
    double **b, **fac;
    b = dynalloc_type2(f, f);
    fac = dynalloc_type2(f, f);
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++) {
        for (p = 0; p < f; p++) {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++) {
                for (j = 0; j < f; j++) {
                    if (i != q && j != p) {
                        b[m][n] = matrix[i][j];
                        if (n < (f - 2))
                            n++;
                        else {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * det(b, f - 1, f - 1);
        }
    }
    transpose(matrix, fac, f);
    free(b);
    free(fac);
}
void transpose(double **matrix, double **fac, int r) {
    int i, j;
    double **b, **inverse, d;
    b = dynalloc_type2(r, r);
    inverse = dynalloc_type2(r, r);

    for (i = 0; i < r; i++) {
        for (j = 0; j < r; j++) {
            b[i][j] = fac[j][i];
        }
    }
    d = det(matrix, r, r);
    for (i = 0; i < r; i++) {
        for (j = 0; j < r; j++) {
            inverse[i][j] = b[i][j] / d;
        }
    }
    for (i = 0; i < r; i++) {
        for (j = 0; j < r; j++) {
            matrix[i][j] = inverse[i][j];
        }
    }
    free(b);
    free(inverse);
}

void output_roots(double *roots, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.6lf", roots[i]);
        if (i != n - 1) printf(" ");
    }
}
int sle(double **matrix, int n, int m, double *roots) {
    double det_a = det(matrix, n, n);
    for (int i = 0; i < n; ++i) roots[i] = cramer_solve(matrix, n, m, det_a, i);
    return 0;
}
double cramer_solve(double **matrix, int n, int m, double det_A, int var) {
    double **tmp = dynalloc_type2(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) tmp[i][j] = matrix[i][j];
    }
    for (int i = 0; i < n; ++i) tmp[i][var] = matrix[i][m - 1];
    double det_tmp = det(tmp, n, n);
    free(tmp);

    return det_tmp / det_A;
}

void sort_vertical(double **matrix, int n, int m, double **result_matrix) {
    double *ptr = (double *)(matrix + n);
    sorting(ptr, n * m);
    int dir = 1;
    for (int i = 0; i < n; i++) {
        if (dir == 1)
            for (int j = 0; j < m; j++) {
                result_matrix[j][i] = ptr[i * m + j];
            }
        else
            for (int j = 0; j < m; j++) {
                result_matrix[m - j - 1][i] = ptr[i * m + j];
            }
        dir *= -1;
    }
}

void sort_horizontal(double **matrix, int n, int m, double **result_matrix) {
    double *ptr = (double *)(matrix + n);
    sorting(ptr, n * m);
    int dir = 1;
    for (int i = 0; i < n; i++) {
        if (dir == 1)
            for (int j = 0; j < m; j++) {
                result_matrix[i][j] = ptr[i * m + j];
            }
        else
            for (int j = 0; j < m; j++) {
                result_matrix[i][m - j - 1] = ptr[i * m + j];
            }
        dir *= -1;
    }
}

void sorting(double *a, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < (n - 1) - i; j++) {
            if (a[j] > a[j + 1]) {
                swap_values(a, j, j + 1);
            }
        }
}

void swap_values(double *a, int i, int j) {
    double tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}