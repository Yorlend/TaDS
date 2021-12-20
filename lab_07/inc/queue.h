#pragma once

typedef struct node
{
    int key;
    struct node *next;
} node_t;


typedef struct
{
    node_t *first;
    node_t *last;
} queue_t;

queue_t queue_empty(void);

void queue_push(queue_t *queue, int key);

int queue_pop(queue_t *queue);

void queue_destroy(queue_t *queue);
