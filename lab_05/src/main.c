#include "utils/styles.h"
#include "utils/errors.h"
#include "utils/timer.h"
#include "utils/memtrack.h"
#include "menu/menu.h"
#include "commands.h"

#define BUF_SIZE 256

int main(void)
{
    calc_cpu_freq();

    memtrack_init();
    int status = init_queues();

    if (status != SUCCESS)
        printf(STY_ERROR("Не удалось инициализировать стеки.\n"));
    else
    {
        menu_t menu = menu_create("Меню:");

        menu_add_option(&menu, option_create("Моделирование", opt_auto_model));
        menu_add_option(&menu, option_create("Ручное тестирование", opt_manual));

        menu_add_error_handler(&menu, error_handler);

        status = menu_run(&menu);
        menu_destroy(&menu);
    }

    memtrack_clean();
    return status;
}