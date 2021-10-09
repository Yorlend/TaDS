#ifndef __GENDER_H__
#define __GENDER_H__

typedef enum
{
    UNDEFINED,
    MALE,
    FEMALE
} gender_t;

gender_t str_to_gender(const char* str);
const char* gender_to_str(gender_t gender);

#endif /* __GENDER_H__ */
