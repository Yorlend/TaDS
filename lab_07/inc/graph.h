#pragma once

#include <stdbool.h>

typedef struct graph
{
    unsigned int size;
    int **adjmat;
} graph_t;

graph_t graph_init(unsigned int vertices);

void graph_output(const graph_t *graph, const char *graphname);

void graph_free(graph_t *graph);

int graph_input(graph_t *graph, const char *filename);

void graph_output(const graph_t *graph, const char *out);

void debug_out(const graph_t *graph);

bool graph_reachable(const graph_t *graph, int T, int src);
