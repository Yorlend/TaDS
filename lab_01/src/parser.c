#include "parser.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/**
 * Парсинг пробельных символов
 * 
 * \param[in] str строка для парсинга
 */
static void parse_space(const char** str)
{
    while (isspace(**str))
        (*str)++;
}

/**
 * Проверка на валидность всех символов в строке
 * 
 * \param[in] str строка для парсинга
 * 
 * \return Код Ошибки
 */
static status_t check_valid(const char* str)
{
    while (*str)
    {
        if (strchr(DIGITS "+-.eE \t\n", *str) == NULL)
            return INPUT_ERROR;
        str++;
    }
    return SUCCESS;
}

/**
 * Парсинг незначащих нулей
 * 
 * \param[in] str строка для парсинга
 * 
 * \return значение флага (удалялись ли нули)
 */
static uint8_t parse_leading_zeros(const char** str)
{
    uint8_t flag = 0;
    
    while (**str == '0')
    {
        flag = 1;
        (*str)++;
    }
    
    return flag;
}

/**
 * Парсинг мантиссы
 * 
 * \param[out] num указатель на число (тип exp_float*)
 * \param[out] p_pos позиция точки в строке
 * \param[in] str строка для парсинга
 * 
 * \return Код Ошибки
 * 
 * \details Производит парсинг мантиссы, занося её в поле num->mantissa и запоминая позицию точки.
 */
static status_t parse_mantissa(exp_float_t* num, const char** str, uint8_t* p_pos)
{
    uint8_t point_count = 0;
    parse_space(str);

    uint8_t flag = parse_leading_zeros(str);
    
    uint8_t index = 0;
    while ((strchr(PARSABLE, **str) != NULL) && (**str != '\0'))
    {
        if (**str == '.')
        {
            if (point_count > 0)
                return POINTS_ERROR;
            *p_pos = index;
            point_count++;
            (*str)++;
        }

        else
        {
            if (index == MAX_MANT)
                return MANTISSA_OVERFLOW;
            num->mantissa[index] = **str;
            (*str)++;
            index++;
        }
    }

    num->mantissa[index] = '\0';

    if (!flag && strlen(num->mantissa) == 0)
        return EMPTY_ERROR;

    parse_space(str);
    return SUCCESS;
}

/**
 * Парсинг знака
 * 
 * \param[out] num указатель на число (тип exp_float_t*)
 * \param[in] str строка для парсинга
 */
static void parse_sign(exp_float_t* num, const char** str)
{
    parse_space(str);
    num->sign = SIGN_POSITIVE;

    if (**str == SIGN_NEGATIVE || **str == SIGN_POSITIVE)
    {
        num->sign = **str;
        (*str)++;
    }
}

/**
 * Парсинг степени
 * 
 * \param[out] num указатель на число (тип exp_float_t*)
 * \param[in] str строка для парсинга
 * 
 * \return Код Ошибки
 */
static status_t parse_degree(exp_float_t* num, const char** str)
{
    char buf[MAX_DEG_DIGITS + 1] = "";
    char sign = SIGN_POSITIVE;

    parse_space(str);

    if (**str == '\0')
        return SUCCESS;
    
    if (**str != 'e' && **str != 'E')
        return INPUT_ERROR;
    (*str)++;

    parse_space(str);
    
    if (**str == SIGN_NEGATIVE || **str == SIGN_POSITIVE)
        sign = *((*str)++);

    parse_space(str);
    parse_leading_zeros(str);

    uint8_t index = 0;
    while ((strchr(DIGITS, **str) != NULL) && (**str != '\0'))
    {
        if (index > MAX_DEG_DIGITS)
            return DEGREE_OVERFLOW;
        buf[index] = **str;
        (*str)++;
        index++;
    }

    num->degree = atoi(buf);
    if (sign == SIGN_NEGATIVE)
        num->degree *= -1;

    parse_space(str);
    if (**str == '\0')
        return SUCCESS;

    return INPUT_ERROR;
}

/**
 * Парсинг числа
 * 
 * \param[out] num указатель на число (тип exp_float_t*)
 * \param[in] str строка для парсинга
 * 
 * \return Код Ошибки
 * 
 * \details В данной функции осуществляется парсинг числа и первичная проверка на переполнение проверка
 * \details выполняется в данной функции, чтобы не хранить положение точки в структуре exp_float_t
 */
status_t parse_exp_float(exp_float_t* num, const char* str)
{
    status_t exit_code = check_valid(str);

    parse_sign(num, &str);
    uint8_t point_pos = MAX_MANT;
    if (exit_code == SUCCESS &&\
        ((exit_code = parse_mantissa(num, &str, &point_pos)) == SUCCESS) &&\
        ((exit_code = parse_degree(num, &str)) == SUCCESS))
    {
        if (point_pos >= MAX_MANT)
            point_pos = strlen(num->mantissa);
        num->degree += point_pos;
        parse_space(&str);
        if (*str != '\0')
            exit_code = INPUT_ERROR;
    }

    return exit_code;
}
