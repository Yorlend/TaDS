#include "queue/queue_list.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "utils/errors.h"
#include <stdbool.h>
#include "utils/timer.h"
#include "utils/memtrack.h"


qlist_t qlist_create(void)
{
    qlist_t queue = { .first = NULL, .last = NULL, .size = 0U };
    return queue; 
}

void qlist_destroy(qlist_t *queue)
{
    while (queue->size > 0U)
    {
        request_t value;
        qlist_pop_front(queue, &value);
    }
}

static inline node_t* allocate_node(request_t value)
{
    node_t *res = malloc(sizeof(node_t));

    if (res != NULL)
    {
        res->data = value;
        res->next = NULL;
    }

    return res;
}

int qlist_push_back(qlist_t *queue, request_t value)
{
    TIMER_BEGIN;
    
    int status = SUCCESS;


    node_t *node = allocate_node(value);
    if (node == NULL)
        status = MEM_ERR;
    else
    {
        if (queue->size == 0)
            queue->first = node;
        else
            queue->last->next = node;

        queue->last = node;
        queue->size++;
    }

    TIMER_END;

    if (status == SUCCESS)
        memtrack_toggle_addr((const void *)node, USED);

    return status;
}

int qlist_insert(qlist_t *queue, uint32_t pos, request_t value)
{
    if (pos > queue->size)
        pos = queue->size;

    node_t *node = allocate_node(value);
    if (node == NULL)
        return MEM_ERR;

    if (queue->size == 0)
    {
        queue->first = node;
        queue->last = node;
    }
    else if (pos == 0)
    {
        node->next = queue->first;
        queue->first = node;
    }
    else if (pos == queue->size)
    {
        queue->last->next = node;
        queue->last = node;
    }
    else
    {
        node_t *before = NULL;
        node_t *after = queue->first;

        for (uint8_t i = 0; i < pos; i++)
        {
            before = after;
            after = after->next;
        }

        before->next = node;
        node->next = after;
    }

    queue->size++;
    return SUCCESS;
}

int qlist_pop_front(qlist_t *queue, request_t *value)
{
    TIMER_BEGIN;

    int status = SUCCESS;


    if (queue->size > 0)
    {
        node_t *node = queue->first;

        queue->first = node->next;

        *value = node->data;
        free(node);

        if (queue->size == 1)
            queue->last = NULL;

        memtrack_toggle_addr((const void *)node, UNUSED);

        queue->size--;
    }
    
    else
        status = EMP_ERR;

    TIMER_END;

    return status;
}

void qlist_print(const qlist_t *queue)
{
    node_t *head = queue->first;

    printf("QUEUE SIZE: %d\n", queue->size);
    while (head != NULL)
    {
        printf("id: %u -- type: %u\n", head->data.id, head->data.type);
        head = head->next;
    }
}
