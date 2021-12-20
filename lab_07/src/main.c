#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int prompt_file_name(char *buffer)
{
    printf("Input file name: ");
    if (scanf("%s", buffer) != 1)
        printf("Incorrect input.\n");
    else
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}

int prompt_T(int *size)
{
    int tmp = 0;

    printf("Input T (max length): ");
    if (scanf("%d", &tmp) != 1)
        printf("Input NaN.\n");
    else if (tmp <= 0)
        printf("Incorrect input.\n");
    else
    {
        *size = tmp;
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}

int main(void)
{
    char filename[256];
    int status = EXIT_SUCCESS;
    int T;

    status = prompt_T(&T);

    status = prompt_file_name(filename);

    graph_t graph = { .adjmat = NULL, .size = 0 };

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