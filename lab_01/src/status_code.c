#include "status_code.h"
#include "constants.h"
#include <stdio.h>


void print_status(status_t status)
{
    printf("Программа завершилась с кодом: %d\n", status);

    switch (status)
    {
    case INPUT_ERROR:
        printf("ВСТРЕЧЕНЫ НЕДОПУСТИМЫЕ СИМВОЛЫ\n");
        break;

    case MANTISSA_OVERFLOW:
        printf("ПЕРЕПОЛНЕНИЕ МАНТИССЫ\n");
        break;

    case DEGREE_OVERFLOW:
        printf("ПЕРЕПОЛНЕНИЕ СТЕПЕНИ\n");
        break;

    case DEGREE_UNDERFLOW:
        printf("МАШИННЫЙ НУЛЬ\n");
        break;

    case OVERFLOW_ERROR:
        printf("ПЕРЕПОЛНЕНИЕ СТРОКИ, ВВЕДИТЕ МЕНЕЕ %d СИМВОЛОВ\n", MAX_STR);
        break;

    case POINTS_ERROR:
        printf("В ВВЕДЕННОМ ЧИСЛЕ БОЛЕЕ ОДНОЙ ТОЧКИ\n");
        break;

    case EMPTY_ERROR:
        printf("МАНТИССА ПУСТА\n");

    default:
        break;
    }
}