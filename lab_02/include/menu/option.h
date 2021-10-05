#ifndef _OPTION_H_
#define _OPTION_H_


typedef int (*opt_func_t)(void);

typedef struct option
{
    const char* title;
    opt_func_t func;
    struct option* next;
} option_t;


option_t* option_create(const char* title, opt_func_t func);

int option_index(option_t* opt);

option_t* opt_exit();

#endif // _OPTION_H_
