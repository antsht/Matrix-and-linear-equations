#include <stdio.h>
#include <stdlib.h>

#include "matrix_common.h"

int main() {
    double **matrix = NULL;
    int n = 0, m = 0;
    int error = 0;
    if ((scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0 || n != m)) {
        error = 1;
    }
    matrix = dynalloc_type2(n, m);
    if (matrix == NULL) {
        error = 1;
    }
    if (error == 0) {
        input(matrix, &n, &m, &error);
    }
    if (error == 0) {
        double ans = det(matrix, n, m);
        printf("%.6lf", ans);
    } else {
        printf("n/a");
    }
    free(matrix);
    return 0;
}
