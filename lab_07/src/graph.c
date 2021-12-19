#include "graph.h"
#include <stdlib.h>

node_t *node_init(unsigned int key)
{
    node_t *node = malloc(sizeof(node_t));

    node->key = key;
    node->next = NULL;

    return node;
}

graph_t *graph_init(unsigned int vertices)
{
    graph_t *graph = malloc(sizeof(graph_t));

    graph->size = vertices;
    graph->vertices = calloc(vertices, sizeof(list_t));

    return graph;
}

