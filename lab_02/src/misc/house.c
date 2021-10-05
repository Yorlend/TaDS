#include "misc/house.h"
#include <string.h>


housing_t str_to_housing(const char* str)
{
    if (str != NULL)
    {
        if (!strcmp(str, "dorm"))
            return DORM;
        
        if (!strcmp(str, "appartment"))
            return APPARTMENT;
    }
    
    return UNKNOWN;
}

const char* housing_to_str(housing_t housing)
{
    switch (housing)
    {
    case DORM:
        return "dorm";
    
    case APPARTMENT:
        return "appart.";

    default:
        return "?";
    }
}
