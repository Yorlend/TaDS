#ifndef _DORM_H_
#define _DORM_H_

#include "constants.h"
#include <stdbool.h>


#define DELIM ","

typedef struct
{
    unsigned int number;
    unsigned int room;
} dorm_t;

bool dorm_valid(const dorm_t* dorm);
dorm_t str_to_dorm(const char* str);

#endif // _DORM_H_