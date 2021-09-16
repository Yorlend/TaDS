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

    for (uint8_t i = ind; i < len; i++)
        swap_digits(&str[i], &str[i + 1]);

    str[len] = '\0';
}

/// TODO: optimize
// static uint8_t mul_chars(char c1, char c2, uint8_t* r)
// {
//     uint8_t d1 = c1 - '0', d2 = c2 - '0', tmp = *r;
//     *r = 0;

//     return d1 * d2 + tmp;
// }

void reset_exp_float(exp_float_t* num)
{
    num->sign = SIGN_POSITIVE;
    memset(num->mantissa, 0, MAX_MANT);
    num->degree = 0;
}

status_t normalize_exp_float(exp_float_t* num)
{
    uint8_t zeros_count = 0;

    for (int i = 0; num->mantissa[i] == '0';)
    {
        remove_digit(num->mantissa, i);
        zeros_count++;
    }

    num->degree -= zeros_count;

    if (num->degree > 9999 || num->degree < -9999)
        return DEGREE_OVERFLOW;
    return SUCCESS;
}

status_t validate_exp_float(const exp_float_t* num)
{
    // Проверка на переполнение мантиссы -> округление
    // if (num->mantissa)
    if (num->degree > 9999 || num->degree < -9999)
        return DEGREE_OVERFLOW;
    
    return SUCCESS;
}

/// TODO: implement
// exp_float_t multiply(const exp_float_t* num1, const exp_float_t* num2)
// {
//     exp_float_t res;
//     reset_exp_float(&res);

//     uint8_t remainder = 0;
//     uint8_t tmp = 0;

//     for (uint8_t i = strlen(num1->mantissa) - 1; i >= 0; i--)
//         for (uint8_t j = strlen(num2->mantissa); j >= 0; j--)
//             {
//                 break;
//             }
// }
