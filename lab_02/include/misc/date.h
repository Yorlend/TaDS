#ifndef _DATE_H_
#define _DATE_H_

#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    uint16_t year;
    uint16_t month;
    uint16_t day;
} date_t;

void reset_date(date_t* date);

bool date_valid(const date_t* date);

date_t str_to_date(const char* str);
char* date_to_str(const date_t* date);

#endif // _DATE_H_