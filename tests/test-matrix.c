#include "matrix.h"
#include <stdio.h>

MatrixAlgo *matrix_providers[] = {
    &NaiveMatrixProvider,
};

int main()
{
    MatrixAlgo *algo = matrix_providers[0];

    float A[4][5] = {
        { 1, 2, 3, 4, 5,},
        { 5, 6, 7, 8, 9,},
        { 1, 2, 3, 4, 5,},
        { 5, 6, 7, 8, 9,},
    };

    float B[5][4] = {
        { 1, 2, 3, 4,},
        { 5, 6, 7, 8,},
        { 1, 2, 3, 4,},
        { 5, 6, 7, 8,},
        { 1, 2, 3, 4,},
    };

    float ans[4][4] = {
        { 39,  54,  69,  84, },
        { 91, 126, 161, 196, },
        { 39,  54,  69,  84, },
        { 91, 126, 161, 196, },
    };

    int A_size = sizeof(A) / sizeof(A[0][0]);
    int B_size = sizeof(B) / sizeof(B[0][0]);
    int ans_size = sizeof(ans) / sizeof(ans[0][0]);

    Matrix *dst, *m, *n, *fixed;

    m = algo->create(4, 5);
    n = algo->create(5, 4);
    dst = algo->create(4, 4);
    fixed = algo->create(4, 4);

    algo->assign(m, *A, A_size);
    algo->assign(n, *B, B_size);
    algo->assign(fixed, *ans, ans_size);

    algo->mul(dst, m, n);

    printf("Matrix multiplication get :\n\n");
    algo->print(dst);

    if (algo->equal(dst, fixed))
        return 0;
    return -1;
}
