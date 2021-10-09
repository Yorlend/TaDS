#ifndef __HOUSE_H__
#define __HOUSE_H__


typedef enum
{
    UNKNOWN,
    DORM,
    APPARTMENT
} housing_t;

housing_t str_to_housing(const char* str);
const char* housing_to_str(housing_t housing);

#endif /* __HOUSE_H__ */
