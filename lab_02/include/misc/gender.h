#ifndef _GENDER_H_
#define _GENDER_H_

typedef enum
{
    UNDEFINED,
    MALE,
    FEMALE
} gender_t;

gender_t str_to_gender(const char* str);
const char* gender_to_str(gender_t gender);

#endif // _GENDER_H_