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

static void assign(Matrix *thiz, float* data, int data_size)
{
    assert(thiz->row * thiz->col == data_size &&
           "Data size different from matrix size");

    for (int i = 0; i < thiz->row; i++)
        for (int j = 0; j < thiz->col; j++)
            PRIV(thiz)[i*thiz->col + j] = data[i*thiz->col + j];
}

static const float epsilon = 1 / 10000.0;

static bool equal(const Matrix *l, const Matrix *r)
{
    assert(l->row == r->row && l->col == r->col && "Matrix size is different");
    for (int i = 0; i < l->row; i++)
        for (int j = 0; j < l->col; j++)
            if (PRIV(l)[i * l->col + j] + epsilon < PRIV(r)[i * r->col + j] ||
                    PRIV(r)[i * r->col + j] + epsilon < PRIV(l)[i * l->col + j])
                return false;
    return true;
}

static bool mul(Matrix *dst, const Matrix *l, const Matrix *r)
{
    assert(l->col == r->row && dst->row == l->row && dst->col == r->col
           && "Matrix multiplication fail");

    dst->priv = malloc(dst->row * dst->col * sizeof(float));
    for (int i = 0; i < dst->row; i++)
        for (int j = 0; j < dst->col; j++)
            for (int k = 0; k < l->col; k++)
                PRIV(dst)[i * dst->col + j] += PRIV(l)[i * l->col + k] *
                                               PRIV(r)[k * r->col + j];
    return true;
}

static void print(Matrix *thiz)
{
    int col = thiz->col;
    for (int i = 0; i < thiz->row; i++) {
        for (int j = 0; j < thiz->col; j++) {
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
