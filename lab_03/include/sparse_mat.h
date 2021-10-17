#ifndef __SPARSE_MAT_H__
#define __SPARSE_MAT_H__

#include "misc/types.h"
#include "misc/list.h"
#include <stdbool.h>

typedef struct smatrix
{
    id_t rows;
    id_t cols;
    id_t size;

    data_t* A;
    id_t* JA;
    list_t IA;
} smatrix_t;

// Представление разреженной матрицы по-умолчанию
smatrix_t smat_null(void);

// Проверка на корректность разреженной матрицы
bool smat_is_valid(const smatrix_t* mat);

// Освобождение памяти
void smat_destroy(smatrix_t* mat);

// Получение элемента по индексам
data_t smat_get(const smatrix_t* mat, id_t row, id_t col);


#endif /* __SPARSE_MAT_H__ */
