#include <stddef.h>
#include <stdlib.h>
#include "misc/errors.h"
#include "misc/timer.h"
#include "operations.h"
#include "convert_mat.h"

int std_mul(stdmat_t *res, const stdmat_t *v, const stdmat_t *m)
{
    if (res == NULL)
        return ARGS_ERR;

    if (!stdm_is_valid(m) || !stdm_is_valid(v))
        return BAD_MATRIX;

    if (!stdm_is_multable(v, m))
        return MUL_ERR;

    if (v->rows != 1)
        return BAD_VECTOR;

    *res = stdm_zero(v->rows, m->cols);

    if (!stdm_is_valid(res))
        return MEM_ERR;

    TIMER_BEGIN;

    for (unsigned int col = 0; col < m->cols; col++)
        for (unsigned int row = 0; row < m->rows; row++)
            res->data[0][col] += v->data[0][row] * m->data[row][col];
    
    TIMER_END;

    return SUCCESS;
}

static stdmat_t _std_transpose(stdmat_t *src)
{
    stdmat_t res = stdm_zero(src->cols, src->rows);

    for (id_t col = 0; col < src->cols; col++)
        for (id_t row = 0; row < src->rows; row++)
            res.data[col][row] = src->data[row][col];

    return res;
}

static smatrix_t _transpose(const smatrix_t *src)
{
    stdmat_t res = stdm_null();
    smatrix_t sres = smat_null();

    smat_to_stdm(&res, src);
    stdmat_t rest = _std_transpose(&res);
    stdm_to_smat(&sres, &rest);

    stdm_destroy(&res);
    stdm_destroy(&rest);

    return sres;
}

static smatrix_t _preinit_rowvec(id_t size)
{
    smatrix_t res = smat_null();

    res.rows = 1;
    res.cols = size;

    res.A = malloc(size * sizeof(data_t));
    if (res.A != NULL)
    {
        res.JA = malloc(size * sizeof(id_t));
        if (res.JA != NULL)
        {
            res.IA = lst_reserve(2, 0);
            if (res.IA.head != NULL)
                return res;

            free(res.JA);
        }

        free(res.A);
    }

    return smat_null();
}

int sparse_mul(smatrix_t *res, const smatrix_t *v, const smatrix_t *m)
{
    if (res == NULL)
        return ARGS_ERR;

    if (!smat_is_valid(v) || !smat_is_valid(m))
        return BAD_MATRIX;

    if (v->rows != 1 || v->cols != m->rows)
        return MUL_ERR;

    *res = _preinit_rowvec(m->cols);
    if (!smat_is_valid(res))
        return MEM_ERR;

    int *IP = malloc(v->cols * sizeof(int));
    if (IP == NULL)
    {
        smat_destroy(res);
        return MEM_ERR;
    }

    for (id_t i = 0; i < v->cols; i++)
        IP[i] = -1;

    for (id_t i = 0; i < v->size; i++)
        IP[v->JA[i]] = i;

    smatrix_t mt = _transpose(m);

    TIMER_BEGIN;

    node_t *IA_node = mt.IA.head;
    for (id_t row = 0; row < mt.rows; row++)
    {
        // index - позиция первого ненулевого элемента в массиве A в строке row матрицы mt
        // index_last - позиция первого ненулевого элемента в массиве А в следующей строке за row
        id_t index = IA_node->col_index;
        id_t index_last = IA_node->next->col_index;

        data_t sum = 0;

        // цикл по всем ненулевым элементам строки row матрицы mt
        for (; index < index_last; index++)
        {
            int col = IP[mt.JA[index]];
            // если соответствующий элемент в IP не равен -1 -> умножаем
            if (col != -1)
                sum += mt.A[index] * v->A[col];
        }

        // установка результата в результирующий вектор
        if (sum != 0)
        {
            res->A[res->size] = sum;
            res->JA[res->size] = row;
            res->size++;
        }

        IA_node = IA_node->next;
    }

    // обновление последнего элемента в списке IA
    res->IA.head->next->col_index = res->size;

    TIMER_END;

    smat_destroy(&mt);
    free(IP);
    return SUCCESS;
}

static bool _stdm_eq_smat(const stdmat_t *stdm, const smatrix_t *smat)
{
    if (!stdm_is_valid(stdm) || !smat_is_valid(smat))
        return false;

    if (stdm->rows != smat->rows || stdm->cols != smat->cols)
        return false;

    for (id_t row = 0; row < stdm->rows; row++)
        for (id_t col = 0; col < stdm->cols; col++)
            if (stdm->data[row][col] != smat_get(smat, row, col))
                return false;

    return true;
}

int test_mul(bool *correct, double *time_std, double *time_spa, stdmat_t *res, const stdmat_t *v, const stdmat_t *m)
{
    smatrix_t sres = smat_null();
    smatrix_t sv = smat_null();
    smatrix_t sm = smat_null();

    int status = CONVERT_ERR;

    if (stdm_to_smat(&sm, m) == SUCCESS && stdm_to_smat(&sv, v) == SUCCESS)
    {
        int status_1 = std_mul(res, v, m);

        if (time_std != NULL)
            *time_std = TIMER_NANOSECONDS;

        int status_2 = sparse_mul(&sres, &sv, &sm);

        if (time_spa != NULL)
            *time_spa = TIMER_NANOSECONDS;

        if (correct != NULL)
            *correct = _stdm_eq_smat(res, &sres);

        smat_destroy(&sm);
        smat_destroy(&sv);
        smat_destroy(&sres);

        status = SUCCESS;
    }

    return status;
}

int run_tests(FILE* file, id_t dims_start, id_t dims_step, id_t dims_end, double percent_step, unsigned int iterations)
{
    fprintf(file, "percent,dims,time_std,time_sparse\n");

    for (double percent = 0; percent <= 100; percent += percent_step)
    {
        for (id_t dim = dims_start; dim <= dims_end; dim += dims_step)
        {
            stdmat_t m = stdm_zero(dim, dim);
            stdmat_t v = stdm_zero(1, dim);

            stdm_randomize(&m, percent);
            stdm_randomize(&v, percent);

            stdmat_t res = stdm_null();

            double time_std = 0;
            double time_sparse = 0;
            double time_std_sum = 0;
            double time_sparse_sum = 0;

            for (unsigned int i = 0; i < iterations; i++)
            {
                if (test_mul(NULL, &time_std, &time_sparse, &res, &v, &m) == SUCCESS)
                {
                    time_std_sum += time_std;
                    time_sparse_sum += time_sparse;
                }
            }

            time_std = time_std_sum / iterations;
            time_sparse = time_sparse_sum / iterations;

            fprintf(file, "%.1lf,%u,%lf,%lf\n", percent, dim, time_std, time_sparse);
            fflush(file);
        }
    }

    return SUCCESS;
}
