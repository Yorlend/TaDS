#include <stdlib.h>
#include "misc/errors.h"
#include "stdmat.h"

stdmat_t stdm_null(void)
{
    stdmat_t mat;

    mat.rows = 0;
    mat.cols = 0;
    mat.data = NULL;

    return mat;
}

stdmat_t stdm_zero(id_t rows, id_t cols)
{
    stdmat_t mat = stdm_null();

    if (rows > 0 && cols > 0)
    {
        mat.data = calloc(rows * sizeof(data_t *) + rows * cols * sizeof(data_t), 1);
        if (mat.data != NULL)
        {
            for (id_t row = 0; row < rows; row++)
                mat.data[row] = (data_t *)((char *)((data_t *)mat.data + rows) + row * cols * sizeof(data_t));

            mat.rows = rows;
            mat.cols = cols;
        }
    }

    return mat;
}

void stdm_destroy(stdmat_t *mat)
{
    if (mat != NULL && mat->data != NULL)
    {
        free(mat->data);
        *mat = stdm_null();
    }
}

bool stdm_is_valid(const stdmat_t *mat)
{
    return mat != NULL && mat->data != NULL && mat->rows > 0 && mat->cols > 0;
}

bool stdm_is_multable(const stdmat_t *left, const stdmat_t *right)
{
    if (!stdm_is_valid(left) || !stdm_is_valid(right))
        return false;

    return left->cols == right->rows;
}

int stdm_randomize(stdmat_t *mat, double zero_percent)
{
    if (!stdm_is_valid(mat))
        return BAD_MATRIX;

    if (zero_percent < 0 || 100 < zero_percent)
        return BAD_PERCENT;

    unsigned int non_zero = mat->cols * mat->rows  * (100 - zero_percent) / 100;

    for (id_t i = 0; i < non_zero;)
    {
        id_t row = rand() % mat->rows;
        id_t col = rand() % mat->cols;

        if (mat->data[row][col] == 0)
        {
            i++;
            mat->data[row][col] = -100 + rand() % 200;
        }
    }

    return SUCCESS;

    // for (id_t row = 0; row < mat->rows; row++)
    // {
    //     for (id_t col = 0; col < mat->cols; col++)
    //     {
    //         if (rand() % 100 < zero_percent)
    //             mat->data[row][col] = 0;
    //         else
    //             mat->data[row][col] = -100 + rand() % 200;
    //     }
    // }
}

size_t stdm_calc_mem(const stdmat_t *mat)
{
    return sizeof(stdmat_t) + mat->rows * sizeof(data_t *) + mat->rows * mat->cols * sizeof(data_t);
}
