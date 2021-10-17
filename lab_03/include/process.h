#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "stdmat.h"

int input_mat_dims(id_t *rows, id_t *cols);
int input_vec(stdmat_t *vec, id_t cols);
int input_mat(stdmat_t *mat, id_t rows, id_t cols);
int test_matrices(const stdmat_t *vec, const stdmat_t *mat);
int do_auto_tests(const char* filename);

#endif /* __PROCESS_H__ */
