#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "misc/appartment.h"
#include <stdlib.h>
#include <string.h>


bool apt_valid(const appartment_t* apt)
{
    if (strlen(apt->street) == 0)
        return false;
    
    if (apt->house > 89 || apt->house < 1)
        return false;

    if (apt->appt_num > 999 || apt->appt_num < 1)
        return false;

    return true;
}

appartment_t str_to_apt(const char* str)
{
    appartment_t res = { 0 };

    if (str == NULL)
        return res;

    str = strdup(str);
    if (str != NULL)
    {
        char* tmp = strtok(str, ",");

        if (tmp != NULL)
        {
            if (strlen(tmp) < MAX_STR)
            {
                strcpy(res.street, tmp);
                tmp = strtok(NULL, ",");
            }
            else
                tmp = NULL;
        }

        if (tmp != NULL)
        {
            res.house = atoi(tmp);
            tmp = strtok(NULL, ",");
        }

        if (tmp != NULL)
            res.appt_num = atoi(tmp);

        free(str);
    }

    return res;
}
