#ifndef _DORM_H_
#define _DORM_H_

#include "constants.h"
#include <stdbool.h>
#include <stdint.h>


#define DELIM ","

typedef struct
{
    uint16_t number;    // Номер общежития
    uint16_t room;      // Номер комнаты
} dorm_t;

// Проверка на валидность
bool dorm_valid(const dorm_t* dorm);

// Перевод строки в общежитие
dorm_t str_to_dorm(const char* str);

#endif // _DORM_H_