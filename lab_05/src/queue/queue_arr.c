#include "queue/queue_arr.h"
#include <stddef.h>
#include <stdlib.h>
#include <utils/errors.h>
#include <stdio.h>
#include "utils/timer.h"


static inline void q_reset(request_t **ptr, const qarr_t *queue)
{
    (*ptr)++;
    if (*ptr == queue->begin + queue->capacity)
        *ptr = queue->begin;
}

qarr_t qarr_create(uint32_t size)
{
    qarr_t res;

    res.begin = malloc(size * sizeof(request_t));

    if (res.begin != NULL)
    {
        res.capacity = size;
        res.size = 0;
        res.first = res.begin;
        res.last = res.begin;
    }

    return res;
}

void qarr_destroy(qarr_t *queue)
{
    while (queue->size > 0)
    {
        request_t value;
        qarr_pop_front(queue, &value);
    }
}

static inline int check_overflow(const qarr_t *queue)
{
    if (queue->size >= queue->capacity)
        return OVERFLOW;
    return SUCCESS;
}

int qarr_push_back(qarr_t *queue, request_t value)
{
    TIMER_BEGIN;

    int status = check_overflow(queue);

    if (status == SUCCESS && queue->size == 0)
    {
        queue->first = queue->begin;
        queue->last = queue->begin;

        *queue->last = value;
        queue->last++;
    }
    else if (status == SUCCESS)
    {
        *queue->last = value;

        q_reset(&queue->last, queue);
    }

    if (status == SUCCESS)
        queue->size++;

    TIMER_END;

    return status;
}

static inline void q_shift_first(qarr_t* queue, uint32_t amount)
{
    request_t* curr = queue->first - 1;
    if (curr < queue->begin)
        curr += queue->capacity;

    for (request_t *next = queue->first; amount > 0; amount--)
    {
        *curr = *next;
        q_reset(&curr, queue);
        q_reset(&next, queue);
    }

    queue->first--;
    if (queue->first < queue->begin)
        queue->first += queue->capacity;
}

int qarr_insert(qarr_t *queue, uint32_t pos, request_t value)
{
    int status = check_overflow(queue);

    if (status == SUCCESS)
    {
        if (pos >= queue->size)
        {
            *queue->last = value;
            q_reset(&queue->last, queue);
        }
        else if (pos == 0)
        {
            queue->first--;
            if (queue->first < queue->begin)
                queue->first += queue->capacity;
            *queue->first = value;
        }
        else
        {
            q_shift_first(queue, pos);
            request_t *ptr = queue->first + pos;
            if (ptr >= queue->begin + queue->capacity)
                ptr -= queue->capacity;
            *ptr = value;
        }

        queue->size++;
    }

    return status;
}

int qarr_pop_front(qarr_t *queue, request_t *value)
{
    TIMER_BEGIN;

    int status = SUCCESS;

    if (queue->size == 0)
        status = EMP_ERR;
    else
    {
        *value = *queue->first;

        q_reset(&queue->first, queue);
        queue->size--;
    }

    TIMER_END;

    return status;
}

void qarr_print(const qarr_t *queue)
{
    request_t *tmp = queue->first;

    printf("QUEUE SIZE: %d\n", queue->size);
    for (uint32_t i = 0; i < queue->size; i++)
    {
        printf("id: %u -- type: %u\n", tmp->id, tmp->type);

        q_reset(&tmp, queue);
    }
}
