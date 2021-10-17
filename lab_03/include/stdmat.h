#ifndef __STDMAT_H__
#define __STDMAT_H__

#include <stdbool.h>
#include <stddef.h>
#include "misc/types.h"

typedef struct stdmat
{
    id_t rows;
    id_t cols;
    data_t** data;
} stdmat_t;

// Инициализация по-умолчанию
stdmat_t stdm_null(void);

// Нулевая матрица заданного размера
stdmat_t stdm_zero(id_t rows, id_t cols);

// Освобождение памяти
void stdm_destroy(stdmat_t* mat);

// Проверка на корректность данных в матрице
bool stdm_is_valid(const stdmat_t* mat);

// Проверка на возможность перемножить две матрицы
bool stdm_is_multable(const stdmat_t* left, const stdmat_t *right);

// Случайная матрица
int stdm_randomize(stdmat_t* mat, double zero_percent);

size_t stdm_calc_mem(const stdmat_t *mat);

#endif /* __STDMAT_H__ */
