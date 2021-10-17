#ifndef __SPARSE_MAT_H__
#define __SPARSE_MAT_H__

#include "misc/list.h"

typedef struct smatrix
{
    unsigned int rows;
    unsigned int cols;
    unsigned int size;

    int* A;
    int* JA;
    list_t IA;
} matrix_t;


#endif /* __SPARSE_MAT_H__ */
