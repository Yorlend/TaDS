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
    printf("Введите id студента: ");
    char dummy;

    if (scanf("%lu%c", &id, &dummy) != 2)
        printf("Введите корректный id!\n");
    else if (stable_remove(&table, id) != SUCCESS)
        printf("Невозможно удалить студента. Введите корректный id\n");
    else
    {
        printf("Студент успешно удален из таблицы\n");
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

    printf("Введите дату поступления ");

    if (scanf("%hu%c", &year, &dummy) != 2)
        printf("Некорректная дата. Введите корректную дату в следующем формате: ДД.ММ.ГГГГ\n");
    else
        stable_cond_print(&table, year);

    return SUCCESS;
}

int sort_table_opt(void)
{
    uint16_t type;
    char dummy;

    printf(" 1. Сортировка выбором\n");
    printf(" 2. Сортировка слиянием\n");
    printf("Выберите алгоритм сортировки: ");

    if (scanf("%hu%c", &type, &dummy) != 2 || type == 0 || type > 2)
        printf("Неверно указан алгоритм сортировки.\n");
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

        printf("Таблица отсортирована!\nЗатраченное Время:  %ldus\n", dt);
        printf("Затраченная Память: %zu байт\n", memsize);
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

    printf(" 1. Сортировка выбором\n");
    printf(" 2. Сортировка слиянием\n");
    printf("Выберите алгоритм сортировки: ");

    if (scanf("%hu%c", &type, &dummy) != 2 || type == 0 || type > 2)
        printf("Неверно указан алгоритм сортировки.\n");
    else
    {
        sort_t sorts[] = {[1] = selection_sort, [2] = merge_sort};

        timer_start();
        keytable_sort(&keytable, sorts[type]);
        long dt = timer_end();
        size_t memsize = sizeof(table) + sizeof(student_t) * table.size;

        if (type == 1)
            memsize += selection_mem(keytable.size, sizeof(keytable.data[0]));

        if (type == 2)
            memsize += merge_mem(keytable.size, sizeof(keytable.data[0]));

        printf("Таблица ключей отсортирована!\nЗатраченное Время:  %ldus\n", dt);
        printf("Затраченная Память: %zu байт\n", memsize);
    }

    return SUCCESS;
}

int print_table_key_opt(void)
{
    stable_print_key(&table, &keytable);
    return SUCCESS;
}

int error_handler(void)
{
    printf("Введите корректное значение пункта меню.\n");
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
        printf("не удалось загрузить данные.\n");
    else
    {
        menu_t menu = menu_create("======== [Меню] ========");
        menu_add_error_handler(&menu, error_handler);
        menu_add_option(&menu, option_create("сортировать таблицу", sort_table_opt));
        menu_add_option(&menu, option_create("сортировать таблицу ключей", sort_keytable_opt));
        menu_add_option(&menu, option_create("удалить студента", remove_stud_opt));
        menu_add_option(&menu, option_create("добавить студента", add_stud_opt));
        menu_add_option(&menu, option_create("поиск студентов", cond_print_opt));
        menu_add_option(&menu, option_create("вывод таблицы студентов", print_table_opt));
        menu_add_option(&menu, option_create("вывод таблицы ключей", print_keytable_opt));
        menu_add_option(&menu, option_create("вывод таблицы студентов по таблице ключей", print_table_key_opt));
        menu_add_option(&menu, option_create("вывести график сравнения сортировок", graph_opt));

        status = menu_run(&menu);

        menu_destroy(&menu);
        stable_destroy(&table);
        keytable_destroy(&keytable);
    }

    return status;
}
