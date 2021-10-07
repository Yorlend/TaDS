#include "menu/menu.h"

#include "studtable.h"

static studtable_t table;

// int print_table(void)
// {
//     printf("table:\n");
//     if (stable_valid(&table))
//     {
//         for (int i = 0; i < table.size; i++)
//             stud_write_row(table.data + i);
//     }
//     return 0;
// }

int main(int argc, const char* argv[])
{
    int status = stable_load(&table, "data.txt");

    // student_t stud;

    // status = input_student(&stud);
    
    // if (status == SUCCESS)
    //     status = stable_push_back(&table, &stud);

    for (size_t id = 0; table.size > 1; id++)
    {
        status = stable_remove(&table, 0);
    }

    status = stable_remove(&table, 0);
    if (status == SUCCESS)
        stable_print(&table);

    // if (status != 0)
    //     printf("could not load data file\n");
    // else
    // {
    //     menu_t menu = menu_create("=== [MENU] ===");
    //     menu_add_option(&menu, option_create("print table", print_table));

    //     status = menu_run(&menu);
    //     menu_destroy(&menu);
    // }

    stable_destroy(&table);
    return status;
}
