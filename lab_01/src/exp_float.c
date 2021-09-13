#include "exp_float.h"
#include <string.h>


static void swap_digits(char* d1, char* d2)
{
    if (*d1 != *d2)
    {
        *d1 ^= *d2;
        *d2 ^= *d1;
        *d1 ^= *d2;
    }
}

static void remove_digit(char* str, uint8_t ind)
{
    uint8_t len = strlen(str);

    for (int i = ind; i < len; i++)
        swap_digits(&str[i], &str[i + 1]);

    str[len] = '\0';
}

void reset_exp_float(exp_float_t* num)
{
    num->sign = SIGN_POSITIVE;
    memset(num->mantissa, 0, MAX_MANT);
    num->degree = 0;
}

void normalize_exp_float(exp_float_t* num)
{
    uint8_t zeros_count = 0;

    for (int i = 0; num->mantissa[i] == '0';)
    {
        remove_digit(num->mantissa, i);
        zeros_count++;
    }

    num->degree -= zeros_count;
}

status_t validate_exp_float(const exp_float_t* num)
{
    
}
