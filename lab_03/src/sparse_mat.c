#include <stdlib.h>
#include "sparse_mat.h"

smatrix_t smat_null(void)
{
    smatrix_t mat;

    mat.rows = 0;
    mat.cols = 0;
    mat.size = 0;

    mat.A = NULL;
    mat.JA = NULL;
    mat.IA = lst_empty();

    return mat;
}

bool smat_is_valid(const smatrix_t* mat)
{
    if (mat == NULL)
        return false;

    bool dims_valid = mat->rows > 0 && mat->cols > 0;
    return dims_valid && mat->A != NULL && mat->JA != NULL;
}

void smat_destroy(smatrix_t* mat)
{
    if (mat != NULL)
    {
        if (mat->A != NULL)
            free(mat->A);
        if (mat->JA != NULL)
            free(mat->JA);
        lst_destroy(&mat->IA);
        *mat = smat_null();
    }
}

data_t smat_get(const smatrix_t* mat, id_t row, id_t col)
{
    if (smat_is_valid(mat) && row < mat->rows && col < mat->cols)
    {
        id_t row_begin_id = lst_get(&mat->IA, row);
        id_t row_end_id = lst_get(&mat->IA, row + 1);

        for (id_t i = row_begin_id; i < row_end_id; i++)
            if (mat->JA[i] == col)
                return mat->A[i];
    }

    return 0;
}
