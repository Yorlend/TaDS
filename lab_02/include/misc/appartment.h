#ifndef _APPARTMENT_H_
#define _APPARTMENT_H_

#include "constants.h"
#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    char street[MAX_STR];
    uint8_t house;
    uint16_t appt_num;
} appartment_t;

bool appartment_valid(const appartment_t* apt);
appartment_t str_to_apt(const char* str);

#endif // _APPARTMENT_H_