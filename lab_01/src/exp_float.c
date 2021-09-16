#include "exp_float.h"
#include <string.h>
#include <stdio.h>


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

static void round_exp(exp_float_t* num)
{
    if (num->mantissa[MAX_MANT] >= '5')
    {
        int ind = MAX_MANT - 1;
        while (ind >= 0 && num->mantissa[ind] == '9')
            num->mantissa[ind--] = '\0';
        num->mantissa[ind] += 1;
    }

    num->mantissa[MAX_MANT] = '\0';
}

static uint8_t mul_chars(char c1, char c2, uint8_t* r)
{
    uint8_t d1 = c1 - '0', d2 = c2 - '0', res = d1 * d2 + *r;
    *r = res / 10;

    return res % 10;
}

static char mul_signs(char sig1, char sig2)
{
    if (sig1 == sig2)
        return SIGN_POSITIVE;
    else
        return SIGN_NEGATIVE;
}

void reset_exp_float(exp_float_t* num)
{
    num->sign = SIGN_POSITIVE;
    memset(num->mantissa, 0, MAX_MANT * 2);
    num->degree = 0;
}

status_t normalize_exp_float(exp_float_t* num)
{
    while (num->mantissa[0] == '0')
    {
        num->degree--;    
        remove_digit(num->mantissa, 0);
    }

    if (num->mantissa[0] == '\0')
        num->degree = 0;

    if (num->degree > MAX_DEG)
        return DEGREE_OVERFLOW;
    else if (num->degree < -MAX_DEG)
        return DEGREE_UNDERFLOW;
    return SUCCESS;
}

status_t multiply(exp_float_t* res, const exp_float_t* num1, const exp_float_t* num2)
{
    status_t exit_code = SUCCESS;
    reset_exp_float(res);

    uint8_t remainder;
    uint8_t tmp = 0;
    for (int8_t i = strlen(num1->mantissa) - 1; i >= 0; i--)
    {
        remainder = 0;
        for (int8_t j = strlen(num2->mantissa) - 1; j >= 0; j--)
        {
            tmp = mul_chars(num1->mantissa[i], num2->mantissa[j], &remainder);
            if (res->mantissa[i + j + 1] + tmp > 9)
                remainder++;
            res->mantissa[i + j + 1] = (res->mantissa[i + j + 1] + tmp) % 10;
        }
        res->mantissa[i] += remainder;
    }

    int8_t flag = 0;
    for (int8_t i = MAX_MANT * 2 - 1; i >= 0; i--)
        if (flag || (res->mantissa[i] != '\0' && (flag = 1)))
            res->mantissa[i] += '0';

    res->sign = mul_signs(num1->sign, num2->sign);
    res->degree = num1->degree + num2->degree;

    exit_code = normalize_exp_float(res);

    if (exit_code == SUCCESS && strlen(res->mantissa) > MAX_MANT)
        round_exp(res);

    return exit_code;
}
