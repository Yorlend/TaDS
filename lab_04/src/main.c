#include "misc/styles.h"
#include "misc/errors.h"
#include "menu/menu.h"
#include "misc/timer.h"
#include "memtrack/memtrack.h"
#include "commands.h"

int main(void)
{
    calc_cpu_freq();

    memtrack_init();
    int status = init_stacks();

    if (status != SUCCESS)
        printf(STY_ERROR("Не удалось инициализировать стеки.\n"));
    else
    {
        menu_t menu = menu_create("Меню:");

        menu_add_option(&menu, option_create("Вывести стеки в массиве", opt_output_astack));
        menu_add_option(&menu, option_create("Вывести стек на списке", opt_output_lstack));

        menu_add_option(&menu, option_create("Вставить в нижний стек в массиве", opt_push_low));
        menu_add_option(&menu, option_create("Вставить в верхний стек в массиве", opt_push_high));
        menu_add_option(&menu, option_create("Вставить в стек на списке", opt_push_list));

        menu_add_option(&menu, option_create("Удалить из нижнего стека в массиве", opt_pop_low));
        menu_add_option(&menu, option_create("Удалить из верхнего стека в массиве", opt_pop_high));
        menu_add_option(&menu, option_create("Удалить из стека на списке", opt_pop_list));

        menu_add_error_handler(&menu, error_handler);

        status = menu_run(&menu);
        menu_destroy(&menu);
    }

    memtrack_clean();
    return status;
}