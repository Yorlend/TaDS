#include <stdlib.h>
#include <ctype.h>
#include "menu/menu.h"

#define MAX_INPUT_LINE_SIZE 256


menu_t menu_create(const char* text)
{
    menu_t menu;
    menu.text = text;
    menu.option = opt_exit();

    return menu;
}

void menu_destroy(menu_t* menu)
{
    while (menu->option != NULL)
    {
        option_t* next = menu->option->next;
        free(menu->option);
        menu->option = next;
    }
}

int menu_add_option(menu_t* menu, option_t* option)
{
    if (menu == NULL || option == NULL)
        return 1;

    option->next = menu->option;
    menu->option = option;

    return 0;
}

int menu_run(menu_t* menu)
{
    return menu_runf(stdin, menu);
}

static void _menu_print(menu_t* menu)
{
    printf("%s\n", menu->text);

    for (option_t* opt = menu->option; opt != NULL; opt = opt->next)
        printf("[%d]: %s\n", option_index(opt), opt->title);
}

static int _menu_prompt(FILE* input, char* buf, size_t max_size)
{
    printf("> ");

    if (fgets(buf, max_size, input) == NULL)
        return 1;
    
    return 0;
}

static int _str_to_uint(const char* str, int* res)
{
    while (isspace(*str))
        str++;

    for (*res = 0; isdigit(*str); str++)
        *res = 10 * *res + (*str - '0');
    
    while (isspace(*str))
        str++;
    
    if (*str != '\0')
        return 1;

    return 0;    
}

int menu_runf(FILE* input, menu_t* menu)
{
    char input_line[MAX_INPUT_LINE_SIZE];
    int status;
    int opt_index;
    option_t* opt;

    while (1)
    {
        _menu_print(menu);

        status = _menu_prompt(input, input_line, MAX_INPUT_LINE_SIZE);
        if (status != 0)
            return status;
        
        status = _str_to_uint(input_line, &opt_index);
        if (status != 0)
            return status;
        else if (opt_index > option_index(menu->option))
            return 3;
        else if (opt_index == 0)
            return 0;
        
        opt = menu->option;
        while (option_index(opt) > opt_index)
            opt = opt->next;
        
        status = opt->func();
        if (status != 0)
            return status;
    }
}
