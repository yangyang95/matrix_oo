#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PRIV(x) \
    ((float *) ((x)->priv))

static float* matrix_alloc(int row, int col)
{
    float *values = (float *)calloc(row * col, sizeof(float));
    return values;
}

static Matrix* create(int row, int col)
{
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->row = row;
    matrix->col = col;
    matrix->priv = matrix_alloc(row, col);
    return matrix;
}

static void assign(Matrix *thiz, int row, int col, float* data)
{
    assert(thiz->row == row && thiz->col == col
           && "Input data size doesn't match");

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            PRIV(thiz)[i*col + j] = data[i*col + j];
}

static const float epsilon = 1 / 10000.0;

static bool equal(const Matrix *l, const Matrix *r)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (PRIV(l)[i * l->col + j] + epsilon < PRIV(r)[i * r->col + j] ||
                    PRIV(r)[i * r->col + j] + epsilon < PRIV(l)[i * l->col + j])
                return false;
    return true;
}

static bool mul(Matrix *dst, const Matrix *l, const Matrix *r)
{
    /* FIXME: error hanlding */
    dst->priv = malloc(4 * 4 * sizeof(float));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                PRIV(dst)[i * dst->col + j] += PRIV(l)[i * l->col + k] *
                                               PRIV(r)[k * r->col + j];
    return true;
}

static void print(Matrix *thiz)
{
    int col = thiz->col;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%5g ", PRIV(thiz)[i*col + j]);
        }
        printf("\n");
    }
}


MatrixAlgo NaiveMatrixProvider = {
    .create = create,
    .assign = assign,
    .equal = equal,
    .mul = mul,
    .print = print,
};
