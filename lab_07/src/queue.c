#include "queue.h"
#include <stdlib.h>


static node_t *init_node(int key)
{
    node_t *node = malloc(sizeof(node_t));

    if (node != NULL)
    {
        node->key = key;
        node->next = NULL;
    }

    return node;
}

queue_t queue_empty(void)
{
    return (queue_t) { .first = NULL, .last = NULL };
}

void queue_push(queue_t *queue, int key)
{
    if (queue == NULL)
        return;

    node_t *node = init_node(key);

    if (queue->first == NULL)
    {
        queue->first = node;
        queue->last = node;
    }
    else
    {
        queue->last->next = node;
        queue->last = node;
    }
}

int queue_pop(queue_t *queue)
{
    if (queue == NULL || queue->first == NULL)
        return -1;

    int key = queue->first->key;
    node_t *tmp = queue->first;
    queue->first = queue->first->next;
    free(tmp);

    return key;
}

void queue_destroy(queue_t *queue)
{
    while (queue->first != NULL)
        queue_pop(queue);
}
