#include <stdio.h>
#include "misc/errors.h"
#include "misc/types.h"
#include "misc/styles.h"
#include "misc/timer.h"
#include "stack/array_stack.h"
#include "stack/list_stack.h"
#include "memtrack/memtrack.h"
#include "commands.h"
#include <unistd.h>

#define DEFAULT_STACK_CAPACITY 10
#define BUF_SIZE 256

static astack_t array_stack;
static lstack_t list_stack;

int init_stacks(void)
{
    list_stack = lstack_empty(DEFAULT_STACK_CAPACITY);
    array_stack = astack_empty(DEFAULT_STACK_CAPACITY);

    return astack_is_valid(&array_stack) ? SUCCESS : MEM_ERR;
}

static int input_data(data_t *value)
{
    char buf[BUF_SIZE];

    if (fgets(buf, BUF_SIZE, stdin) == NULL)
        return INP_ERR;

    char *ptr = NULL;
    *value = strtof(buf, &ptr);

    if (*ptr != '\n')
        return INP_ERR;

    return SUCCESS;
}

int opt_output_astack(void)
{
    astack_low_print(&array_stack);
    astack_high_print(&array_stack);

    printf(STY_INFO("Объем памяти занимаемой всей структурой:             %lu байт\n"), astack_sizeof(&array_stack));
    printf(STY_INFO("Объем памяти требуемой для хранения одного элемента: %lu байт\n"), sizeof(data_t));

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

int opt_output_lstack(void)
{
    lstack_print(&list_stack);

    printf(STY_INFO("Объем памяти занимаемой всей структурой:             %lu байт\n"), lstack_sizeof(&list_stack));
    printf(STY_INFO("Объем памяти требуемой для хранения одного элемента: %lu байт\n"), sizeof(node_t));

    printf(STY_INFO("Список адресов:\n"));
    memtrack_print(mem_printer);

    return SUCCESS;
}

int opt_push_low(void)
{
    data_t value = 0;

    printf("Введите число для вставки: ");
    if (input_data(&value) != SUCCESS)
        printf(STY_ERROR("Некорректные данные\n"));
    else if (astack_push_low(&array_stack, value) != SUCCESS)
        printf(STY_ERROR("Переполнение стека\n"));
    else
        printf(STY_INFO("Время добавления: %llu тиков\n"), TIMER_TICKS);

    return SUCCESS;
}

int opt_push_high(void)
{
    data_t value = 0;

    printf("Введите число для вставки: ");
    if (input_data(&value) != SUCCESS)
        printf(STY_ERROR("Некорректные данные\n"));
    else if (astack_push_high(&array_stack, value) != SUCCESS)
        printf(STY_ERROR("Переполнение стека\n"));
    else
        printf(STY_INFO("Время добавления: %llu тиков\n"), TIMER_TICKS);

    return SUCCESS;
}

int opt_push_list(void)
{
    data_t value = 0;

    printf("Введите число для вставки: ");
    if (input_data(&value) != SUCCESS)
        printf(STY_ERROR("Некорректные данные\n"));
    else if (lstack_push(&list_stack, value) != SUCCESS)
        printf(STY_ERROR("Переполнение стека\n"));
    else
        printf(STY_INFO("Время добавления: %llu тиков\n"), TIMER_TICKS);

    return SUCCESS;
}

int opt_pop_low(void)
{
    data_t value;

    if (astack_pop_low(&array_stack, &value) == STACK_EMPTY)
        printf(STY_WARNING("Стек пуст. Нечего извлекать.\n"));
    else
    {
        printf(STY_INFO("Извлечено значение из стека: %.2lf\n"), value);
        astack_low_print(&array_stack);

        printf(STY_INFO("Время извлечения: %llu тиков\n"), TIMER_TICKS);
    }

    return SUCCESS;
}

int opt_pop_high(void)
{
    data_t value;

    if (astack_pop_high(&array_stack, &value) == STACK_EMPTY)
        printf(STY_WARNING("Стек пуст. Нечего извлекать.\n"));
    else
    {
        printf(STY_INFO("Извлечено значение из стека: %.2lf\n"), value);
        astack_low_print(&array_stack);

        printf(STY_INFO("Время извлечения: %llu тиков\n"), TIMER_TICKS);
    }

    return SUCCESS;
}

int opt_pop_list(void)
{
    data_t value;

    if (lstack_pop(&list_stack, &value) == STACK_EMPTY)
        printf(STY_WARNING("Стек пуст. Нечего извлекать.\n"));
    else
    {
        printf(STY_INFO("Извлечено значение из стека: %.2lf\n"), value);
        lstack_print(&list_stack);

        printf(STY_INFO("Время извлечения: %llu тиков\n"), TIMER_TICKS);
    }

    return SUCCESS;
}

int error_handler(void)
{
    printf(STY_ERROR("Неверная опция меню. Повторите ввод.\n"));
    return SUCCESS;
}
