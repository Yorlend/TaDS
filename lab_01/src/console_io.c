#include "console_io.h"
#include "parser.h"
#include <string.h>
#include <stdio.h>


void print_rules()
{
    printf("\n\n%30s=======Умножение двух вещественных чисел, выходящих за рамки разрядной сетки=======\n", "");
    printf("-----------> Правила ввода:\n");
    printf("1. Числа могут вводится так со знаком (+ или -), так и без знака.\n");
    printf("2. Числа могут быть введены как в экспоненциальном виде, так и в обычном.\n");
    printf("3. В мантиссе может содержаться не более 30 цифр.\n");
    printf("4. В порядке может содержаться не более 5 цифр.\n");
}

/**
 * Вводит число с клавиатуры.
 * \param[out] num число типа exp_float_t
 * 
 * \return Код Ошибки
 * 
 * \details В данной функции учитываются ошибки, связанные с неверным вводом,
 * \details а также производится парсинг числа из строки в СД exp_float_t
 */
status_t input_number(exp_float_t* num)
{
    status_t exit_code = SUCCESS;
    char str[MAX_STR] = "";
    char* p = NULL;
    
    printf("%32s%d%9d%10d%10d%3d%4d\n", "", 1, 10, 20, 30, 1, 5);
    printf("%31s±|--------|---------|---------|e±|---|\n", "");
    printf("Введите действительное число:  ");
    if (fgets(str, MAX_STR, stdin) == NULL || (int)strlen(str) == MAX_STR - 1)
        exit_code = OVERFLOW_ERROR;

    // Замена символа новой строки при вводе с клавиатуры
    if ((p = strchr(str, '\n')))
        *p = '\0';

    if (exit_code == SUCCESS)
    {
        reset_exp_float(num);
        exit_code = parse_exp_float(num, str);
    }

    if (exit_code == SUCCESS)
        exit_code = normalize_exp_float(num);
    
    return exit_code;
}

/**
 * Вывод результата умножения вместе с разрядной сеткой.
 * 
 * \param[in] num число типа exp_float_t
 */
void output_number(const exp_float_t* num)
{
    printf("%32s%d%9d%10d%10d%3d%4d\n", "", 1, 10, 20, 30, 1, 5);
    printf("%29s±  |--------|---------|---------|e±|---|\n", "");
    printf("Результат умножения чисел:%3s", "");
    printf("%c0.%se", num->sign, num->mantissa);
    if (num->degree >= 0)
        printf("+");
    printf("%d\n", num->degree);
}
