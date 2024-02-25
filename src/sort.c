#include <stdio.h>
#include <stdlib.h>

#include "matrix_common.h"

int main() {
    double **matrix = NULL, **result = NULL;
    int n = 0, m = 0;
    int error = 0;
    if ((scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0)) {
        error = 1;
    }
    matrix = dynalloc_type2(n, m);
    if (matrix == NULL) {
        error = 1;
    }
    if (error == 0) {
        input(matrix, &n, &m, &error);
    }
    result = dynalloc_type2(n, m);
    if (result != 0 && error == 0) {
        sort_vertical(matrix, n, m, result);
        output(result, n, m);
        printf("\n");
        sort_horizontal(matrix, n, m, result);
        output(result, n, m);
    } else
        printf("n/a");
    free(matrix);
    free(result);
    return 0;
}
