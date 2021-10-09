#include "misc/status.h"
#include "misc/timer.h"
#include "menu/menu.h"
#include "studtable.h"
#include <stdlib.h>
#include "keytable.h"


static studtable_t table;
static keytable_t keytable;

int print_table_opt(void)
{
    stable_print(&table);
    return SUCCESS;
}

int remove_stud_opt(void)
{
    size_t id;
    printf("Enter student id: ");
    char dummy;

    if (scanf("%lu%c", &id, &dummy) != 2)
        printf("Bad student id.\n");
    else if (stable_remove(&table, id) != SUCCESS)
        printf("Could not remove student.\n");
    else
    {
        printf("Successfuly removed student.\n");
        update_keytable(&keytable, &table);
    }

    return SUCCESS;
}

int add_stud_opt(void)
{
    student_t stud;

    if (input_student(&stud) == SUCCESS)
    {
        stable_push_back(&table, &stud);
        update_keytable(&keytable, &table);
    }

    return SUCCESS;
}

int cond_print_opt(void)
{
    uint16_t year;
    char dummy;

    printf("Enter students' enroll year: ");

    if (scanf("%hu%c", &year, &dummy) != 2)
        printf("Bad enroll year.\n");
    else
        stable_cond_print(&table, year);

    return SUCCESS;
}

int sort_table_opt(void)
{
    uint16_t type;
    char dummy;

    printf(" 1. selection sort\n");
    printf(" 2. merge sort\n");
    printf("Enter sort type: ");

    if (scanf("%hu%c", &type, &dummy) != 2 || type == 0 || type > 2)
        printf("Bad sort type.\n");
    else
    {
        sort_t sorts[] = {[1] = selection_sort, [2] = merge_sort};

        timer_start();
        stable_sort(&table, sorts[type]);
        long dt = timer_end();
        size_t memsize;

        if (type == 1)
            memsize = selection_mem(table.size, sizeof(table.data[0]));

        if (type == 2)
            memsize = merge_mem(table.size, sizeof(table.data[0]));

        printf("Table sorted! time: %ldus\n", dt);
        printf("Memory used:%8s%zu byte(s)\n", "", memsize);
    }

    return SUCCESS;
}

int graph_opt(void)
{
    system("make sorts > /dev/null");
    return SUCCESS;
}

int print_keytable_opt(void)
{
    print_keytable(&keytable);
    return SUCCESS;
}

int sort_keytable_opt(void)
{
    uint16_t type;
    char dummy;

    printf(" 1. selection sort\n");
    printf(" 2. merge sort\n");
    printf("Enter sort type: ");

    if (scanf("%hu%c", &type, &dummy) != 2 || type == 0 || type > 2)
        printf("Bad sort type.\n");
    else
    {
        sort_t sorts[] = {[1] = selection_sort, [2] = merge_sort};

        timer_start();
        keytable_sort(&keytable, sorts[type]);
        long dt = timer_end();
        size_t memsize;

        if (type == 1)
            memsize = selection_mem(keytable.size, sizeof(keytable.data[0]));

        if (type == 2)
            memsize = merge_mem(keytable.size, sizeof(keytable.data[0]));

        printf("Keytable sorted! time: %ldus\n", dt);
        printf("Memory used:%11s%zu byte(s)\n", "", memsize);
    }

    return SUCCESS;
}

int print_table_key_opt(void)
{
    stable_print_key(&table, &keytable);
    return SUCCESS;
}

int main(int argc, const char* argv[])
{
    status_t status;
    if (argc == 2)
        status = stable_load(&table, argv[1]);
    else
        status = stable_load(&table, "data.txt");

    if (status == SUCCESS)
    {
        init_keytable(&keytable);
        update_keytable(&keytable, &table);
    }

    if (status != SUCCESS)
        printf("could not load data file\n");
    else
    {
        menu_t menu = menu_create("=== [MENU] ===");
        menu_add_option(&menu, option_create("sort table", sort_table_opt));
        menu_add_option(&menu, option_create("sort keytable", sort_keytable_opt));
        menu_add_option(&menu, option_create("remove student", remove_stud_opt));
        menu_add_option(&menu, option_create("add student", add_stud_opt));
        menu_add_option(&menu, option_create("search students", cond_print_opt));
        menu_add_option(&menu, option_create("print table", print_table_opt));
        menu_add_option(&menu, option_create("print keytable", print_keytable_opt));
        menu_add_option(&menu, option_create("print table by keytable", print_table_key_opt));
        menu_add_option(&menu, option_create("show sorting algorithms time complexity graph", graph_opt));

        status = menu_run(&menu);

        menu_destroy(&menu);
        stable_destroy(&table);
        keytable_destroy(&keytable);
    }

    return status;
}
