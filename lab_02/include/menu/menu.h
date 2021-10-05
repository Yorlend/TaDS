#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>
#include "option.h"

typedef struct
{
    const char* text;
    option_t* option;
} menu_t;

menu_t menu_create(const char* text);
void menu_destroy(menu_t* menu);

int menu_add_option(menu_t* menu, option_t* option);

int menu_run(menu_t* menu);
int menu_runf(FILE* input, menu_t* menu);


#endif // _MENU_H_
