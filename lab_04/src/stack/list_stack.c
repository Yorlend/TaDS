#include <stdio.h>
#include "misc/errors.h"
#include "misc/timer.h"
#include "misc/colors.h"
#include "memtrack/memtrack.h"
#include "stack/list_stack.h"

lstack_t lstack_empty(size_t capacity)
{
    lstack_t res;
    res.top = NULL;
    res.size = 0;
    res.capacity = capacity;

    return res;
}

void lstack_destroy(lstack_t *stack)
{
    while (stack->top != NULL)
    {
        node_t *prev = stack->top->prev;
        free(stack->top);
        stack->top = prev;
    }

    stack->size = 0;
}

bool lstack_is_empty(const lstack_t *stack)
{
    if (stack->size == 0 || stack->top == NULL)
        return true;
    return false;
}

int lstack_push(lstack_t *stack, data_t value)
{
    TIMER_BEGIN;

    if (stack->capacity != UNBOUND && stack->size == stack->capacity)
        return STACK_OVERFLOW;

    node_t *new = malloc(sizeof(node_t));

    if (new == NULL)
        return MEM_ERR;

    new->value = value;
    new->prev = stack->top;
    stack->top = new;
    stack->size++;

    TIMER_END;

    memtrack_toggle_addr((const void *)new, USED);

    return SUCCESS;
}

int lstack_pop(lstack_t *stack, data_t *value)
{
    TIMER_BEGIN;

    node_t *last_top = stack->top;

    if (lstack_is_empty(stack))
        return STACK_EMPTY;

    *value = stack->top->value;

    node_t *prev = stack->top->prev;

    free(stack->top);
    stack->top = prev;
    stack->size--;

    TIMER_END;

    memtrack_toggle_addr((const void *)last_top, UNUSED);

    return SUCCESS;
}

static void _node_print(const node_t *node)
{
    if (node != NULL)
    {
        printf("значение: %10.2lf\tадрес: %p \t адрес предыдущего: %p\n",
               node->value, (const void *)node, (const void *)node->prev);
        _node_print(node->prev);
    }
}

void lstack_print(const lstack_t *stack)
{
    if (stack != NULL)
    {
        if (stack->size != 0)
        {
            _node_print(stack->top);
            printf(CLR_GREEN("Количество элементов: %lu\n"), stack->size);
        }
        else
            printf(CLR_GREEN("Стек пуст.\n"));
    }
}

size_t lstack_sizeof(const lstack_t *stack)
{
    return sizeof(lstack_t) + stack->size * sizeof(node_t);
}
