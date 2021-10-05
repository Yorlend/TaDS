#include <stdlib.h>
#include <assert.h>
#include "menu/option.h"


option_t* option_create(const char* title, opt_func_t func)
{
    option_t* opt = malloc(sizeof(option_t));
    assert(opt != NULL);

    opt->title = title;
    opt->func = func;
    opt->next = NULL;

    return opt;
}

int option_index(option_t* opt)
{
    if (opt == NULL || opt->next == NULL)
        return 0;
    
    return 1 + option_index(opt->next);
}

option_t* opt_exit()
{
    return option_create("exit", NULL);
}