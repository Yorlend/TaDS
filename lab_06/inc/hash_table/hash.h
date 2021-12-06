#ifndef __HASH_H__
#define __HASH_H__

#include "misc/types.h"
#include <stdbool.h>
#include <stddef.h>


typedef size_t (*hf_t)(int);

typedef struct
{
    data_t key;
    bool valid;
} hash_data_t;

typedef struct
{
    size_t size;
    size_t step;
    hash_data_t value;
    hf_t func;
} hash_t;

/**
 * @brief 
 * 
 * @param size 
 * @param step 
 * @param func 
 * @return hash_t* 
 */
hash_t *hash_init(size_t size, size_t step, hf_t func);

#endif /* __HASH_H__ */
