#include "queue/queue.h"

queue_t queue_create(qtype_t type, uint32_t size)
{
    queue_t queue;

    queue.type = type;
    if (type == LIST_QUEUE)
        queue.imp.lst = qlist_create();
    else
        queue.imp.arr = qarr_create(size);

    return queue;
}

void queue_destroy(queue_t *queue)
{
    if (queue->type == LIST_QUEUE)
        qlist_destroy(&queue->imp.lst);
    else
        qarr_destroy(&queue->imp.arr);
}

int queue_push_back(queue_t *queue, request_t value)
{
    if (queue->type == LIST_QUEUE)
        return qlist_push_back(&queue->imp.lst, value);
    return qarr_push_back(&queue->imp.arr, value);
}

int queue_insert(queue_t *queue, uint32_t pos, request_t value)
{
    if (queue->type == LIST_QUEUE)
        return qlist_insert(&queue->imp.lst, pos, value);
    return qarr_insert(&queue->imp.arr, pos, value);
}

int queue_pop_front(queue_t *queue, request_t *value)
{
    if (queue->type == LIST_QUEUE)
        return qlist_pop_front(&queue->imp.lst, value);
    return qarr_pop_front(&queue->imp.arr, value);
}

void queue_print(const queue_t *queue)
{
    if (queue->type == LIST_QUEUE)
        qlist_print(&queue->imp.lst);
    else
        qarr_print(&queue->imp.arr);
}

uint32_t queue_size(const queue_t *queue)
{
    if (queue->type == LIST_QUEUE)
        return queue->imp.lst.size;
    else
        return queue->imp.arr.size;
}
