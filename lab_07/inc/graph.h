#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct node
{
    unsigned int key;
    struct node *next;
} node_t;

typedef struct list
{
    node_t *head;
} list_t;

typedef struct graph
{
    unsigned int size;
    list_t *vertices;
} graph_t;

node_t *node_init(unsigned int key);

graph_t *graph_init(unsigned int vertices);

void graph_output(const graph_t *graph, const char *graphname);


#endif /* __GRAPH_H__ */
