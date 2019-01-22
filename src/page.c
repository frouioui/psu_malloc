/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Page functions
*/

#include "page.h"

page_t *new_page(size_t times)
{
    size_t size = getpagesize();
    page_t *new = NULL;

    if (times == 0)
        times = 1;
    size * DEFAULT_MULTIPLICATION_FACTOR * times;
    new = sbrk(size);
    new->before = NULL;
    new->next = NULL;
    new->pagesize = size;
    new->node_allocated = new + sizeof(page_t);
    new->node_allocated->data_addr = NULL;
    new->node_allocated->next = NULL;
    new->node_allocated->before = NULL;
    new->node_allocated->node_size = 0;
    new->node_allocated->used = false;
    new->node_freed = NULL;
    return (new);
}

