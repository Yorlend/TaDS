#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

// typedef double data_t;

typedef struct
{
    uint32_t type;
    uint32_t id;
} request_t;

typedef struct
{
    double min;
    double max;
} time_intv_t;


#endif /* __TYPES_H__ */
