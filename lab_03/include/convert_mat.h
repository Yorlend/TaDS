#ifndef __CONVERT_MAT_H__
#define __CONVERT_MAT_H__

#include "stdmat.h"
#include "sparse_mat.h"

int stdm_to_smat(smatrix_t *sparse, const stdmat_t *dense);

int smat_to_stdm(stdmat_t *dense, const smatrix_t *sparse);

#endif /* __CONVERT_MAT_H__ */
