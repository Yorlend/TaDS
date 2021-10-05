#ifndef _HOUSE_H_
#define _HOUSE_H_


typedef enum
{
    UNKNOWN,
    DORM,
    APPARTMENT
} housing_t;

housing_t str_to_housing(const char* str);
const char* housing_to_str(housing_t housing);

#endif // _HOUSE_H_