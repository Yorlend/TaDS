#include "parser.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


static void parse_space(const char** str)
{
    while (isspace(**str))
        (*str)++;
}

static void parse_leading_zeros(const char** str)
{
    while (**str == '0')
        (*str)++;
}

static status_t parse_mantissa(exp_float_t* num, const char** str, uint8_t* p_pos)
{
    uint8_t point_count = 0;
    parse_space(str);
    parse_leading_zeros(str);
    
    uint8_t index = 0;
    while ((strchr(PARSABLE, **str) != NULL) && (**str != '\0'))
    {
        if (**str == '.')
        {
            if (point_count > 1)
                return INPUT_ERROR;
            *p_pos = index;
            point_count++;
            (*str)++;
        }

        else
        {
            if (index == MAX_MANT)
                return INPUT_ERROR;
            num->mantissa[index] = **str;
            (*str)++;
            index++;
        }
    }

    num->mantissa[index] = '\0';

    parse_space(str);
    if (**str == '\0')
        return SUCCESS;

    if (**str != 'e' && **str != 'E')
        return INPUT_ERROR;

    (*str)++;
    return SUCCESS;
}

static status_t parse_sign(exp_float_t* num, const char** str)
{
    parse_space(str);
    num->sign = SIGN_POSITIVE;

    if (**str == SIGN_NEGATIVE || **str == SIGN_POSITIVE)
    {
        num->sign = **str;
        (*str)++;
    }
    
    return SUCCESS;
}

static status_t parse_degree(exp_float_t* num, const char** str)
{
    char buf[MAX_DEG_DIGITS + 1] = "";
    char sign = SIGN_POSITIVE;

    parse_space(str);
    
    parse_leading_zeros(str);
    
    if (**str == '\0')
        return SUCCESS;
    
    if (**str == SIGN_NEGATIVE || **str == SIGN_POSITIVE)
    {
        sign = **str;
        (*str)++;
    }

    parse_leading_zeros(str);

    uint8_t index = 0;
    while ((strchr(DIGITS, **str) != NULL) && (**str != '\0'))
    {
        if (index > MAX_DEG_DIGITS)
            return INPUT_ERROR;
        buf[index] = **str;
        (*str)++;
        index++;
    }

    num->degree = atoi(buf);
    if (sign == SIGN_NEGATIVE)
        num->degree *= -1;

    if (**str == '\0')
        return SUCCESS;

    return INPUT_ERROR;
}

status_t parse_exp_float(exp_float_t* num, const char* str)
{
    uint8_t point_pos = MAX_MANT;
    if (parse_sign(num, &str) == SUCCESS &&\
        parse_mantissa(num, &str, &point_pos) == SUCCESS &&\
        parse_degree(num, &str) == SUCCESS)
    {
        if (point_pos >= MAX_MANT)
            point_pos = strlen(num->mantissa);
        num->degree += point_pos;
        parse_space(&str);
        if (*str == '\0')
            return SUCCESS;
    }

    return INPUT_ERROR;
}
