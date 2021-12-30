#ifndef __OPTION_H__
#define __OPTION_H__

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

#endif /* __OPTION_H__ */
