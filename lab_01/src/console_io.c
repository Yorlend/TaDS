#include "console_io.h"
#include "parser.h"
#include <string.h>
#include <stdio.h>

static void entry_instruction()
{
    printf("\n%120s\n\n", "=====УМНОЖЕНИЕ ДВУХ ДЕЙСТВИТЕЛЬНЫХ ЧИСЕЛ=====");
    printf("\n%30s\n", "ПРАВИЛА ВВОДА");
    printf("1. Числа вводятся со знаком (+)/(-) или без знака\n");

}

status_t input_number(exp_float_t* num)
{
    char str[MAX_STR + 1] = "";
    char* p = NULL;
    entry_instruction();
    
    printf("%32s%d%9d%10d%10d%3d%4d\n", "", 1, 10, 20, 30, 1, 5);
    printf("%31s±|--------|---------|---------|e±|---|\n", "");
    printf("Введите действительное число:  ");
    if (fgets(str, MAX_STR + 1, stdin) == NULL || (int)strlen(str) > MAX_STR)
        return INPUT_ERROR;

    if ((p = strchr(str, '\n')))
        *p = '\0';

    reset_exp_float(num);
    parse_exp_float(num, str);
    normalize_exp_float(num);
    
    return SUCCESS;
}

void output_number(const exp_float_t* num)
{
    printf("%c0.%se%d\n", num->sign, num->mantissa, num->degree);
}
