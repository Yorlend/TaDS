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
        printf("Negative input or 0.\n");
    else
    {
        *size = tmp;
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}

int prompt_src(int *size, int maxsize)
{
    int tmp = 0;

    printf("Input src: ");
    if (scanf("%d", &tmp) != 1)
        printf("Input NaN.\n");
    else if (tmp < 0 || tmp >= maxsize)
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
    int T = 0, src = 0;

    status = prompt_T(&T);

    if (status == EXIT_SUCCESS)
        status = prompt_file_name(filename);

    graph_t graph = { .adjmat = NULL, .size = 0 };

    if (status == EXIT_SUCCESS)
        status = graph_input(&graph, "graph.txt");

    if (status != EXIT_SUCCESS)
        printf("Incorrect input!\n");
    else
    {
        // debug_out(&graph);
        graph_output(&graph, "out");

        status = prompt_src(&src, graph.size);

        if (status == EXIT_SUCCESS)
        {
            bool res = graph_reachable(&graph, T, src);

            if (res == true)
                printf("Reachable\n");
            else
                printf("Unreachable\n");

            graph_output(&graph, "reach");
        }
    }

    graph_free(&graph);
    return status;
}