#include "graph.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


graph_t graph_init(unsigned int vertices)
{
    graph_t graph = { .size = 0, .adjmat = NULL };

    graph.size = vertices;
    graph.adjmat = calloc(vertices, sizeof(int*));

    for (unsigned int i = 0; i < vertices; i++)
        graph.adjmat[i] = calloc(vertices, sizeof(int));

    return graph;
}

void graph_free(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
        free(graph->adjmat[i]);

    free(graph->adjmat);
}

static int __read_edge(FILE *f, graph_t *graph)
{
    int i, j, road_len;
    if (fscanf(f, "%d%d%d", &i, &j, &road_len) != 3 || i < 0 || j < 0 || 
        road_len < 1 || i >= graph->size || j >= graph->size)
        return EXIT_FAILURE;
    
    graph->adjmat[i][j] = road_len;
    graph->adjmat[j][i] = road_len;

    return EXIT_SUCCESS;
}

static int __file_is_empty(FILE *f)
{
    int status = EXIT_SUCCESS;

    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0)
        status = EXIT_FAILURE;

    rewind(f);
    return status;
}

static int graph_input_fp(FILE *f, graph_t *graph)
{
    if (__file_is_empty(f))
        return EXIT_FAILURE;

    int status = EXIT_SUCCESS;
    int size = 0;

    if (fscanf(f, "%d", &size) != 1 || size < 1)
    {
        printf("Bad graph size\n");
        status = EXIT_FAILURE;
    }

    if (status == EXIT_SUCCESS)
        *graph = graph_init(size);
    
    if (status == EXIT_SUCCESS)
    {
        while (!(status = __read_edge(f, graph)));

        if (feof(f))
            status = EXIT_SUCCESS;
    }

    return status;
}

int graph_input(graph_t *graph, const char *filename)
{
    FILE *f = fopen(filename, "r");
    int status = EXIT_SUCCESS;

    if  (f == NULL)
        status = EXIT_FAILURE;
    else
    {
        status = graph_input_fp(f, graph);
        fclose(f);
    }

    return status;
}

void graph_output(const graph_t *graph, const char *out)
{
    if (graph == NULL || out == NULL)
        return;

    char buffer[256];

    snprintf(buffer, 256, "%s.dot", out);
    
    FILE *f = fopen(buffer, "w");

    if (f != NULL)
    {
        fprintf(f, "graph g {\n");

        for (int i = 0; i < graph->size; i++)
            fprintf(f, "    %d;\n", i);

        for (int i = 0; i < graph->size; i++)
            for (int j = i + 1; j < graph->size; j++)
            {
                if (graph->adjmat[i][j] != 0)
                    fprintf(f, "    %d -- %d [label=%d];\n", i, j, graph->adjmat[i][j]);
            }
        fprintf(f, "}");

        fclose(f);
    }

    snprintf(buffer, 256, "dot -Tpng -o%s.png %s.dot", out, out);
    system(buffer);
}

void debug_out(const graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
            printf("%d ", graph->adjmat[i][j]);
        printf("\n");
    }
}

int *__limits_array(int size)
{
    int *arr = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        arr[i] = INT_MAX;
    
    return arr;
}

static void __dijkstra(const graph_t *graph, int *arr, int T, int src)
{
    queue_t q_vert = queue_empty();
    queue_push(&q_vert, src);
    arr[src] = 0;
    (void)T;

    while (q_vert.first != NULL)
    {
        int key = queue_pop(&q_vert);
        for (int i = 0; i < graph->size; i++)
        {
            if (i == key || i == src || graph->adjmat[key][i] == 0)
                continue;
            if (graph->adjmat[key][i] + arr[key] < arr[i])
            {
                arr[i] = graph->adjmat[key][i] + arr[key];
                queue_push(&q_vert, i);
            }
        }
    }
}

static void __swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

static void __sort_three_ints(int *a, int *b, int *c)
{
    if (*a > *b)
        __swap(a, b);
    if (*b > *c)
        __swap(b, c);
    if (*a > *b)
        __swap(a, b);
}

int __dijkstra_check(int* arr, int size, int T)
{
    for (int i = 0; i < size; i++)
        if (arr[i] > T)
            return i;

    return -1;
}

static void __roads_print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d\t", i);
    printf("\n");

    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");
}

bool graph_reachable(const graph_t *graph, int T, int src)
{
    int n1 = 0, n2 = 0, n3 = 0;

    int *arr = __limits_array(graph->size);
    __dijkstra(graph, arr, T, src);

    int unreachable = __dijkstra_check(arr, graph->size, T);

    if (unreachable != -1)
    {
        printf("Input road lengths: ");
        if (scanf("%d%d%d", &n1, &n2, &n3) != 3 || n1 < 1 || n2 < 1 || n3 < 1)
            printf("Bad road input");
        else
        {
            __sort_three_ints(&n1, &n2, &n3);
            int tmp[] = {n1, n2, n3};
            for (int i = 0; i < 3; i++)
            {
                graph->adjmat[src][unreachable] = tmp[i];
                graph->adjmat[unreachable][src] = tmp[i];

                __dijkstra(graph, arr, T, src);
                unreachable = __dijkstra_check(arr, graph->size, T);
                if (unreachable == -1)
                    break;
            }
        }
    }

    __roads_print(arr, graph->size);

    free(arr);
    if (unreachable != -1)
        return false;
    return true;
}
