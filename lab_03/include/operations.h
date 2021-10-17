#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <stdio.h>
#include "stdmat.h"
#include "sparse_mat.h"

// Умножение вектора-строки на матрицу в обычной форме
int std_mul(stdmat_t *res, const stdmat_t *v, const stdmat_t *m);

// Умножение вектора-строки на матрицу в разреженной форме
int sparse_mul(smatrix_t *res, const smatrix_t *v, const smatrix_t *m);

// Тестирование алгоритмов
// correct - оба алгоритма рассчитали одну и ту же матрицу
int test_mul(bool *correct, double *time_std, double *time_spa, stdmat_t *res, const stdmat_t *v, const stdmat_t *m);

// Формирование данных о времени выполнения алгоритмов в формате CSV
int run_tests(FILE* file, id_t dims_start, id_t dims_step, id_t dims_end, double percent_step, unsigned int iterations);

#endif /* __OPERATIONS_H__ */
