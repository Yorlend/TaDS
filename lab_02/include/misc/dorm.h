#ifndef _DORM_H_
#define _DORM_H_

#include "constants.h"
#include <stdbool.h>
#include <stdint.h>


#define DELIM ","

typedef struct
{
    uint16_t number;
    uint16_t room;
} dorm_t;

bool dorm_valid(const dorm_t* dorm);
dorm_t str_to_dorm(const char* str);

#endif // _DORM_H_