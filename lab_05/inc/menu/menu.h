#ifndef __MENU_H__
#define __MENU_H__

#include <stdio.h>
#include "option.h"

typedef struct
{
    const char* text;
    option_t* option;
    opt_func_t error_handler;
} menu_t;

menu_t menu_create(const char* text);
void menu_destroy(menu_t* menu);

int menu_add_option(menu_t* menu, option_t* option);
int menu_add_error_handler(menu_t* menu, opt_func_t func);

int menu_run(menu_t* menu);
int menu_runf(FILE* input, menu_t* menu);

#endif /* __MENU_H__ */
