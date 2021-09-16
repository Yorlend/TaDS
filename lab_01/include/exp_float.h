#ifndef NUMBER_H
#define NUMBER_H

#include <stdbool.h>
#include <stdint.h>
#include "constants.h"
#include "status_code.h"


typedef struct
{
    char sign;  // знак мантиссы
    char mantissa[MAX_MANT * 2];    // мантисса
    int degree; // степень
} exp_float_t;

void reset_exp_float(exp_float_t* num);
status_t normalize_exp_float(exp_float_t* num);

status_t multiply(exp_float_t* res, const exp_float_t* num1, const exp_float_t* num2);

#endif // NUMBER_H
