#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "misc/dorm.h"

#include <string.h>
#include <stdlib.h>
#include "misc/status.h"


bool dorm_valid(const dorm_t* dorm)
{
    if (dorm->number < 1 || dorm->number > 10)
        return false;

    if (dorm->room < 1 || dorm->room > 899)
        return false;

    return true;
}

dorm_t str_to_dorm(const char* str)
{
    dorm_t result = { 0 };
    status_t status = SUCCESS;
    str = strdup(str);

    if (str == NULL)
        status = MEMORY_ERROR;
    else
    {
        char* tok = strtok(str, DELIM);

        result.number = atoi(tok);
        tok = strtok(NULL, DELIM);
        result.room = atoi(tok);
        
        free(str);
    }

    return result;
}
