#include "stack/array_stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "misc/errors.h"
#include "misc/timer.h"
#include "misc/colors.h"

astack_t astack_null(void)
{
    astack_t stack;

    stack.data = NULL;
    stack.data_size = 0;
    stack.top_low = NULL;
    stack.top_high = NULL;

    return stack;
}

astack_t astack_empty(size_t size)
{
    astack_t stack = astack_null();

    if (size > 0)
    {
        stack.data = calloc(size, sizeof(data_t));
        stack.data_size = size;
        stack.top_high = stack.data + size;
        stack.top_low = stack.data - 1;
    }

    return stack;
}

void astack_destroy(astack_t *stack)
{
    if (stack->data != NULL)
    {
        free(stack->data);
        *stack = astack_null();
    }
}

bool astack_is_valid(const astack_t *stack)
{
    return stack != NULL && stack->data != NULL &&
           stack->top_low < stack->top_high;
}

int astack_push_low(astack_t *stack, data_t value)
{
    TIMER_BEGIN;

    if (!astack_is_valid(stack))
        return STACK_INVALID;

    if (stack->top_high - stack->top_low <= 1)
        return STACK_OVERFLOW;

    *(++stack->top_low) = value;

    TIMER_END;

    return SUCCESS;
}

int astack_push_high(astack_t *stack, data_t value)
{
    TIMER_BEGIN;

    if (!astack_is_valid(stack))
        return STACK_INVALID;

    if (stack->top_high - stack->top_low <= 1)
        return STACK_OVERFLOW;

    *(--stack->top_high) = value;

    TIMER_END;

    return SUCCESS;
}

int astack_pop_low(astack_t *stack, data_t *value)
{
    TIMER_BEGIN;

    if (!astack_is_valid(stack))
        return STACK_INVALID;

    if (stack->top_low < stack->data)
        return STACK_EMPTY;

    *value = *(stack->top_low--);

    TIMER_END;

    return SUCCESS;
}

int astack_pop_high(astack_t *stack, data_t *value)
{
    TIMER_BEGIN;

    if (!astack_is_valid(stack))
        return STACK_INVALID;

    if (stack->top_high >= stack->data + stack->data_size)
        return STACK_EMPTY;

    *value = *(stack->top_high++);

    TIMER_END;

    return SUCCESS;
}

void astack_low_print(const astack_t *stack)
{
    if (astack_is_valid(stack))
    {
        printf("Стек, идущий от начала массива к концу:\n");

        data_t *tmp = stack->top_low;
        while (tmp >= stack->data)
            printf("%.2lf\n", *(tmp--));

        size_t size = stack->top_low - stack->data + 1;
        if (size > 0)
            printf(CLR_GREEN("Количество элементов: %lu\n"), size);
        else
            printf(CLR_GREEN("Стек пуст.\n"));
    }
}

void astack_high_print(const astack_t *stack)
{
    if (astack_is_valid(stack))
    {
        printf("Стек, идущий от конца массива к началу:\n");

        data_t *tmp = stack->top_high;
        while (tmp < stack->data + stack->data_size)
            printf("%.2lf\n", *(tmp++));

        size_t size = stack->data + stack->data_size - stack->top_high;
        if (size > 0)
            printf(CLR_GREEN("Количество элементов: %lu\n"), size);
        else
            printf(CLR_GREEN("Стек пуст.\n"));
    }
}

size_t astack_sizeof(const astack_t *stack)
{
    return sizeof(astack_t) + stack->data_size * sizeof(data_t);
}
