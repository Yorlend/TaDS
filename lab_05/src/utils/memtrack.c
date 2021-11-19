#include <stdlib.h>
#include "utils/memtrack.h"

typedef struct mem_list
{
    const void *addr;       // Адрес памяти
    memstate_t state;       // Состояние адреса
    struct mem_list *next;  // Следующий адрес
} mem_list_t;

static mem_list_t *addr_list;

// initialization function
void memtrack_init(void)
{
    addr_list = NULL;
}

// cleaning function
void memtrack_clean(void)
{
    while (addr_list != NULL)
    {
        mem_list_t *next = addr_list->next;
        free(addr_list);
        addr_list = next;
    }
}

static mem_list_t *_make_node(const void *addr, memstate_t state, mem_list_t *next)
{
    mem_list_t *node = malloc(sizeof(mem_list_t));

    node->addr = addr;
    node->state = state;
    node->next = next;

    return node;
}

void memtrack_toggle_addr(const void *addr, memstate_t state)
{
    if (addr_list == NULL)
        addr_list = _make_node(addr, state, NULL);
    else
    {
        mem_list_t **node = &addr_list;
        while (*node != NULL)
        {
            if (addr < (*node)->addr)
            {
                *node = _make_node(addr, state, *node);
                return;
            }
            else if ((*node)->addr == addr)
            {
                (*node)->state = state == USED ? REUSED : state;
                return;
            }
            node = &(*node)->next;
        }

        *node = _make_node(addr, state, NULL);
    }
}

void memtrack_print(addr_printer_t printer)
{
    for (mem_list_t *node = addr_list; node != NULL; node = node->next)
        printer(node->addr, node->state);
}
