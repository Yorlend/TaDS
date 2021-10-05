#include "misc/gender.h"
#include <string.h>


gender_t str_to_gender(const char* str)
{
    gender_t gender = UNDEFINED;

    if (str != NULL)
    {
        if (!strcmp(str, "M"))
            gender = MALE;

        if (!strcmp(str, "F"))
            gender = FEMALE;
    }

    return gender;
}

const char* gender_to_str(gender_t gender)
{
    switch (gender)
    {
    default:
    case UNDEFINED:
        return "?";
    
    case MALE:
        return "M";
    
    case FEMALE:
        return "F";
    }
}
