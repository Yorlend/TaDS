#include <stdlib.h>
#include <assert.h>
#include "misc/errors.h"
#include "convert_mat.h"


static unsigned int _count_nonzero(const stdmat_t *mat)
{
    unsigned int count = 0;

    for (unsigned int row = 0; row < mat->rows; row++)
        for (unsigned int col = 0; col < mat->cols; col++)
            if (mat->data[row][col] != 0)
                count++;

    return count;
}

static int _preinit_sparse_mat(smatrix_t *mat, id_t rows, id_t cols, id_t size)
{
    list_t IA = lst_reserve(rows + 1, 0);

    if (IA.head == NULL)
        return MEM_ERR;

    data_t *A = calloc(size, sizeof(data_t));
    if (A == NULL)
    {
        lst_destroy(&IA);
        return MEM_ERR;
    }
    
    id_t *JA = calloc(size, sizeof(id_t));
    if (JA == NULL)
    {
        free(A);
        lst_destroy(&IA);
        return MEM_ERR;
    }

    mat->rows = rows;
    mat->cols = cols;
    mat->size = size;

    mat->A = A;
    mat->IA = IA;
    mat->JA = JA;

    return SUCCESS;
}

int stdm_to_smat(smatrix_t *sparse, const stdmat_t *dense)
{
    if (sparse == NULL)
        return ARGS_ERR;
    
    if (!stdm_is_valid(dense))
        return BAD_MATRIX;

    *sparse = smat_null();

    unsigned int nonzero_count = _count_nonzero(dense);
    int status = _preinit_sparse_mat(sparse, dense->rows, dense->cols, nonzero_count);
    if (status == SUCCESS)
    {
        id_t curr_id = 0;
        for (id_t row = 0; row < dense->rows; row++)
        {
            for (id_t col = 0; col < dense->cols; col++)
            {
                if (dense->data[row][col] != 0)
                {
                    sparse->A[curr_id] = dense->data[row][col];
                    sparse->JA[curr_id] = col;
                    curr_id++;
                }
            }

            lst_set(&sparse->IA, row + 1, curr_id);
        }
    }

    return SUCCESS;
}

int smat_to_stdm(stdmat_t *dense, const smatrix_t *sparse)
{
    if (dense == NULL)
        return ARGS_ERR;

    if (!smat_is_valid(sparse))
        return BAD_MATRIX;

    *dense = stdm_zero(sparse->rows, sparse->cols);
    if (!stdm_is_valid(dense))
        return MEM_ERR;

    for (id_t row = 0; row < sparse->rows; row++)
        for (id_t col = 0; col < sparse->cols; col++)
            dense->data[row][col] = smat_get(sparse, row, col);

    return SUCCESS;
}
