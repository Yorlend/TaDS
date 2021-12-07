#ifndef __FILE_H__
#define __FILE_H__

#include "misc/types.h"

double f_get_mean_cmp_count(const char *filename);

size_t f_sizeof(const char *filename);

int f_remove(const char *filename, data_t value, size_t *cmp_count);

#endif /* __FILE_H__ */
