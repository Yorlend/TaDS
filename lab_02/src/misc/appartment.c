#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "misc/appartment.h"
#include <stdlib.h>
#include <string.h>


bool appartment_valid(const appartment_t* apt)
{
    return strlen(apt->street) != 0;
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
