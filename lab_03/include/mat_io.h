#ifndef __MAT_IO_H__
#define __MAT_IO_H__

#include <stdio.h>
#include "stdmat.h"
#include "sparse_mat.h"

// Выводит информацию о программе на экран
void print_header();

int scan_stdmat(FILE *file, stdmat_t *mat);

// Выводит матрицу в виде матрицы
int print_stdmat(FILE *file, const stdmat_t *mat);
int print_smat(FILE *file, const smatrix_t *mat);

// выводит описание структуры
int print_smat_info(FILE *file, const smatrix_t *mat);

#endif /* __MAT_IO_H__ */
