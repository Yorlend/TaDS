#include <stdio.h>
#include "utils/errors.h"
#include "utils/styles.h"
#include "utils/types.h"
#include "utils/timer.h"
#include "utils/memtrack.h"
#include "menu/menu.h"
#include "queue/queue.h"
#include "model.h"
#include "commands.h"

#define BUF_SIZE    256
#define Q_MAX       5

static queue_t queue_arr;
static queue_t queue_lst;

static int input_ulong(unsigned long *value)
{
    char buf[BUF_SIZE];

    if (fgets(buf, BUF_SIZE, stdin) == NULL)
        return INP_ERR;

    char *ptr = NULL;
    *value = strtoul(buf, &ptr, 10);

    if (*ptr != '\n')
        return INP_ERR;

    return SUCCESS;
}

static int input_data(request_t *value)
{
    unsigned long id;
    int status = input_ulong(&id);
    if (status == SUCCESS)
    {
        value->id = id;
        value->type = 1;
    }
    return status;
}

static int input_time_intv(time_intv_t *value)
{
    char buf[BUF_SIZE];

    if (fgets(buf, BUF_SIZE, stdin) == NULL)
        return INP_ERR;

    char *ptr = NULL;
    value->min = strtod(buf, &ptr);
    if (*ptr != ' ')
        return INP_ERR;

    value->max = strtod(ptr, &ptr);
    if (*ptr != '\n')
        return INP_ERR;

    return SUCCESS;
}

int init_queues(void)
{
    queue_arr = queue_create(ARRAY_QUEUE, Q_MAX);
    queue_lst = queue_create(LIST_QUEUE, Q_MAX);

    return SUCCESS;
}

int opt_run_model(void)
{
    int status = model_reset(800);
    if (status != SUCCESS)
        printf("Ошибка при инициализации моделируемого аппарата.\n");
    else
    {
        model_result_t result = model_run(1000, model_default_params());
        if (result.status != SUCCESS)
        {
            printf("Произошла ошибка при моделировании.\n");
            printf("Аппарат будет возвращён в начальное состояние.\n");
            model_reset(300);
        }
    }

    return SUCCESS;
}

static int check_time_intv(int status, time_intv_t intv)
{
    if (status == SUCCESS && intv.max < intv.min)
    {
        printf("Неверно введён временной интервал.\n");
        return INP_ERR;
    }
    return status;
}

static int input_model_params(params_t *params)
{
    printf("Ввод временных параметров моделирования.\n");
    printf("Пример ввода интервала: 0.1 5.21\n");
    printf("Введите временной промежуток T1: ");

    int status = input_time_intv(&params->t1);
    status = check_time_intv(status, params->t1);

    if (status == SUCCESS)
    {
        printf("Введите временной промежуток T2: ");
        status = input_time_intv(&params->t2);
        status = check_time_intv(status, params->t2);
    }
    if (status == SUCCESS)
    {
        printf("Введите временной промежуток T3: ");
        status = input_time_intv(&params->t3);
        status = check_time_intv(status, params->t3);
    }
    
    return status;
}

int opt_change_model(void)
{
    int status = model_reset(800);
    if (status != SUCCESS)
        printf("Ошибка при инициализации моделируемого аппарата.\n");
    else
    {
        params_t params;
        status = input_model_params(&params);
        if (status != SUCCESS)
            printf("Ошибка при вводе параметров моделирования.\n");
        else
        {
            model_result_t result = model_run(1000, params);
            if (result.status != SUCCESS)
            {
                printf("Произошла ошибка при моделировании.\n");
                printf("Аппарат будет возвращён в начальное состояние.\n");
                model_reset(300);
            }
        }
    }

    return SUCCESS;
}

static void mem_printer(const void *addr, memstate_t state)
{
    printf("Адрес: %p, состояние: ", addr);
    switch (state)
    {
    default:
    case UNUSED:
        printf(CLR_GREEN("не используется\n"));
        break;
    case USED:
        printf(CLR_RED("используется\n"));
        break;
    case REUSED:
        printf(CLR_YELLOW("переиспользуется\n"));
        break;
    }
}

int opt_output(void)
{
    queue_print(&queue_lst);

    unsigned long mem_lst = sizeof(qlist_t) + queue_lst.imp.lst.size * sizeof(node_t);
    unsigned long mem_arr = sizeof(qarr_t) + queue_arr.imp.arr.capacity * sizeof(request_t);

    printf("Память, затраченная на хранение очереди списком: %zu байт.\n", mem_lst);
    printf("\tНа хранение одного элемента %zu байт.\n", sizeof(node_t));

    printf("Память, затраченная на хранение очереди массивом: %zu байт.\n", mem_arr);
    printf("\tНа хранение одного элемента %zu байт.\n", sizeof(request_t));

    printf(STY_INFO("Список адресов:\n"));
    memtrack_print(mem_printer);

    return SUCCESS;
}

static inline int queues_push(request_t value)
{
    int status = SUCCESS;

    status = queue_push_back(&queue_arr, value);
    if (status == SUCCESS)
    {
        printf(STY_INFO("Время добавления в массив: %llu тиков\n"), TIMER_TICKS);
        status = queue_push_back(&queue_lst, value);
    }

    if (status == SUCCESS)
        printf(STY_INFO("Время добавления в список: %llu тиков\n"), TIMER_TICKS);

    return status;
}

int opt_push(void)
{
    request_t value;

    printf("Введите число для вставки: ");
    if (input_data(&value) != SUCCESS)
        printf(STY_ERROR("Некорректные данные\n"));
    else if (queues_push(value) != SUCCESS)
        printf(STY_ERROR("Переполнение очереди\n"));

    return SUCCESS;
}

static inline int queues_pop(request_t *value)
{
    int status = SUCCESS;

    status = queue_pop_front(&queue_arr, value);
    if (status == SUCCESS)
    {
        printf(STY_INFO("Время извлечения из массива: %llu тиков\n"), TIMER_TICKS);
        status = queue_pop_front(&queue_lst, value);
    }

    if (status == SUCCESS)
        printf(STY_INFO("Время извлечения из списка: %llu тиков\n"), TIMER_TICKS);

    return status;
}

int opt_pop(void)
{
    request_t value;

    if (queues_pop(&value) == EMP_ERR)
        printf(STY_WARNING("Очередь пуста. Нечего извлекать.\n"));
    else
    {
        printf(STY_INFO("Извлечено значение из стека: %u\n"), value.id);
        queue_print(&queue_lst);
    }

    return SUCCESS;
}

int opt_auto_model(void)
{
    menu_t menu = menu_create("Меню автотестирования:");

    menu_add_option(&menu, option_create("Запустить с параметрами по-умолчанию", opt_run_model));
    menu_add_option(&menu, option_create("Запустить с модифицированными параметрами", opt_change_model));

    menu_add_error_handler(&menu, error_handler);

    int status = menu_run(&menu);
    (void)status;
    menu_destroy(&menu);
    memtrack_clean();

    return SUCCESS;
}

int opt_manual(void)
{
    int status = init_queues();

    if (status != SUCCESS)
        printf(STY_ERROR("Не удалось инициализировать очереди.\n"));

    else
    {

        menu_t menu = menu_create("Меню ручного тестирования:");

        menu_add_option(&menu, option_create("Вставить элемент в очередь", opt_push));
        menu_add_option(&menu, option_create("Удалить элемент из очереди", opt_pop));

        menu_add_option(&menu, option_create("Вывести очереди", opt_output));

        menu_add_error_handler(&menu, error_handler);

        status = menu_run(&menu);
        (void)status;
        menu_destroy(&menu);
        memtrack_clean();

        queue_destroy(&queue_arr);
        queue_destroy(&queue_lst);
    }


    return SUCCESS;
}

int error_handler(void)
{
    printf(STY_ERROR("Неверная опция меню. Повторите ввод.\n"));
    return SUCCESS;
}
