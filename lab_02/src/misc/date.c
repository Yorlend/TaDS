#include "misc/date.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


static bool parse_field(const char** str, uint16_t* num)
{
    const char* c = *str;

    while (isdigit(**str))
        (*str)++;

    *num = atoi(c);
    return true;
}

static bool parse(const char** str, char sym)
{
    if (str == NULL || *str == NULL || **str != sym)
        return false;

    ++*str;
    return true;
}

bool is_leap_year(uint16_t year)
{
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

void reset_date(date_t* date)
{
    date->day = 0;
    date->month = 0;
    date->year = 0;
}

bool date_valid(const date_t* date)
{
    if (date->day < 1 || 31 < date->day)
        return false;

    if (date->month < 1 || 12 < date->month)
        return false;
    
    if (date->year < 1896 || 2021 < date->year)
        return false;

    if (date->month == 2)
    {
        if (is_leap_year(date->year))
        {
            if (date->day > 29)
                return false;
        }
        else if (date->day > 28)
            return false;
    }

    if ((date->month - 1 + (date->month > 6)) % 2 == 1)
        if (date->day > 30)
            return false;

    return true; 
}

date_t str_to_date(const char* str)
{
    date_t date;
    reset_date(&date);

    if (str != NULL)
    {
        if (!(parse_field(&str, &date.day) &&
            parse(&str, '.') &&
            parse_field(&str, &date.month) &&
            parse(&str, '.') &&
            parse_field(&str, &date.year) &&
            parse(&str, '\0') &&
            date_valid(&date)))
        {
            reset_date(&date);
        }
    }

    return date;
}

char* date_to_str(const date_t* date)
{
    static char buffer[11];

    snprintf(buffer, 11, "%02d.%02d.%04d", date->day, date->month, date->year);

    return buffer;
}
