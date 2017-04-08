#include "matrix.h"
#include <stdio.h>

MatrixAlgo *matrix_providers[] = {
    &NaiveMatrixProvider,
};

int main()
{
    MatrixAlgo *algo = matrix_providers[0];

    float A[4][4] = {
        { 1, 2, 3, 4, },
        { 5, 6, 7, 8, },
        { 1, 2, 3, 4, },
        { 5, 6, 7, 8, },
    };

    float B[4][4] = {
        { 1, 2, 3, 4, },
        { 5, 6, 7, 8, },
        { 1, 2, 3, 4, },
        { 5, 6, 7, 8, },
    };

    float ans[4][4] = {
        { 34,  44,  54,  64, },
        { 82, 108, 134, 160, },
        { 34,  44,  54,  64, },
        { 82, 108, 134, 160, },
    };

    Matrix *dst, *m, *n, *fixed;

    m = algo->create(4, 4);
    n = algo->create(4, 4);
    dst = algo->create(4, 4);
    fixed = algo->create(4, 4);

    algo->assign(m, 4, 4, *A);
    algo->assign(n, 4, 4, *B);
    algo->assign(fixed, 4, 4, *ans);

    algo->mul(dst, m, n);

    printf("Matrix multiplication get :\n\n");
    algo->print(dst);

    if (algo->equal(dst, fixed))
        return 0;
    return -1;
}
