#include "exp_float.h"
#include <string.h>
#include <stdio.h>


/**
 * Функция обмена двух символов
 * 
 * \param[in] d1 первый символ
 * \param[in] d2 второй символ
 */
static void swap_digits(char* d1, char* d2)
{
    if (*d1 != *d2)
    {
        *d1 ^= *d2;
        *d2 ^= *d1;
        *d1 ^= *d2;
    }
}

/**
 * Функция удаления символа из строки по индексу
 * 
 * \param[out] str строка, из которой происходит удаление
 * \param[in] ind индекс символа, подлежащего удалению
 */
static void remove_digit(char* str, uint8_t ind)
{
    uint8_t len = strlen(str);

    for (uint8_t i = ind; i < len; i++)
        swap_digits(&str[i], &str[i + 1]);

    str[len] = '\0';
}

/**
 * Функция округления числа
 * 
 * \param[in] num указатель на число (тип exp_float_t*)
 */
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

/**
 * Функция умножения двух разрядов
 * 
 * \param[in] c1 первый символ
 * \param[in] с2 второй символ
 * \param[out] r остаток
 * 
 * \return значение последнего разряда при умножении
 */
static uint8_t mul_chars(char c1, char c2, uint8_t* r)
{
    uint8_t d1 = c1 - '0', d2 = c2 - '0', res = d1 * d2 + *r;
    *r = res / 10;

    return res % 10;
}

/**
 * Функция определения знака после умножения
 * 
 * \param[in] sign1 знак первого числа
 * \param[in] sign2 знак второго числа
 * 
 * \return знак (+/-)
 */
static char mul_signs(char sign1, char sign2)
{
    if (sign1 == sign2)
        return SIGN_POSITIVE;
    else
        return SIGN_NEGATIVE;
}

/**
 * Функция "обнуляет" значения полей числа (exp_float_t)
 * 
 * \param[out] num указатель на число (exp_float_t*) 
 */
void reset_exp_float(exp_float_t* num)
{
    num->sign = SIGN_POSITIVE;
    memset(num->mantissa, 0, MAX_MANT * 2);
    num->degree = 0;
}

/**
 * Функция нормализации мантиссы и степени числа
 * 
 * \param[out] num указатель на число (exp_float_t*)
 * 
 * \return Код ошибки
 */
void normalize_exp_float(exp_float_t* num)
{
    while (num->mantissa[0] == '0')
    {
        num->degree--;    
        remove_digit(num->mantissa, 0);
    }

    if (num->mantissa[0] == '\0')
        num->degree = 0;
}

status_t check_degree(const exp_float_t* num)
{
    if (num->degree > MAX_DEG)
        return DEGREE_OVERFLOW;
    else if (num->degree < -MAX_DEG)
        return DEGREE_UNDERFLOW;
    return SUCCESS;
}

/**
 * Функция умножения двух чисел
 * 
 * \param[out] res результирующее число
 * \param[in] num1 первое число
 * \param[in] num2 второе число
 * 
 * \return Код Ошибки
 * 
 * \details Используется алгоритм умножения чисел столбиком.
 * \details Каждый разряд одного умножается с разрядом другого числа во вложенном цикле.
 * \details После выполнения умножения происходит форматирование, округление и нормализация
 */
status_t multiply(exp_float_t* res, const exp_float_t* num1, const exp_float_t* num2)
{
    status_t exit_code = SUCCESS;
    reset_exp_float(res);

    uint8_t remainder;
    uint8_t tmp = 0;

    // Цикл по всем символам num1 с конца
    for (int8_t i = strlen(num1->mantissa) - 1; i >= 0; i--)
    {
        remainder = 0; // остаток
        // Цикл по всем символам num2 с конца  
        for (int8_t j = strlen(num2->mantissa) - 1; j >= 0; j--)
        {
            // значение результирующего разряда в tmp, remainder хранит остаток
            tmp = mul_chars(num1->mantissa[i], num2->mantissa[j], &remainder);
            if (res->mantissa[i + j + 1] + tmp > 9)
                remainder++;
            res->mantissa[i + j + 1] = (res->mantissa[i + j + 1] + tmp) % 10;
        }
        // "переполнение" остатка
        res->mantissa[i] += remainder;
    }

    int8_t flag = 0;
    // преобразование из массива цифр в массив символов
    for (int8_t i = MAX_MANT * 2 - 1; i >= 0; i--)
        if (flag || (res->mantissa[i] != '\0' && (flag = 1)))
            res->mantissa[i] += '0';

    // определение знака результирующего числа
    res->sign = mul_signs(num1->sign, num2->sign);
    // определение степени результирующего числа
    res->degree = num1->degree + num2->degree;

    // удаление незначащих нулей
    normalize_exp_float(res);

    // округление, если требуется
    if (exit_code == SUCCESS && strlen(res->mantissa) > MAX_MANT)
        round_exp(res);

    if (exit_code == SUCCESS)
    exit_code = check_degree(res);
        

    return exit_code;
}
