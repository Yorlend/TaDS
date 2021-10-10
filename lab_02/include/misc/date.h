#ifndef _DATE_H_
#define _DATE_H_

#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    uint16_t year;      // год
    uint16_t month;     // месяц
    uint16_t day;       // день
} date_t;

// Проверяет год на високосность
bool is_leap_year(uint16_t year);

// Обнуляет дату
void reset_date(date_t* date);

// Проверяет дату на валидность
bool date_valid(const date_t* date);

// Переводит строку в дату
date_t str_to_date(const char* str);

// Переводит дату в строку
char* date_to_str(const date_t* date);

#endif // _DATE_H_