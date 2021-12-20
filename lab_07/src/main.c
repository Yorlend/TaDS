#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


#define VERTICES 10

int main(void)
{
    int status = EXIT_SUCCESS;

    graph_t graph;

    status = graph_input(&graph, "graph.txt");
    if (status != EXIT_SUCCESS)
        printf("Incorrect input!\n");
    else
    {
        // debug_out(&graph);
        graph_output(&graph, "out");

        bool res = graph_reachable(&graph, 10, 0);

        if (res == true)
            printf("Reachable\n");

        graph_output(&graph, "reach");
    }

    graph_free(&graph);
    return status;
}