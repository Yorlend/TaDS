#ifndef _APPARTMENT_H_
#define _APPARTMENT_H_

#include "constants.h"
#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    char street[MAX_STR];
    uint16_t house;
    uint16_t appt_num;
} appartment_t;

bool apt_valid(const appartment_t* apt);
appartment_t str_to_apt(const char* str);

#endif // _APPARTMENT_H_