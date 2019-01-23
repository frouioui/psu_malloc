/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Page functions
*/

#include "page.h"

// Default multiplication factor for the page.
// Number of pagesize that sbrk will ask for to the system.
const size_t DEFAULT_MULTIPLICATION_FACTOR = 32;

static size_t get_alloc_size(size_t size)
{
    size_t alloc_size = getpagesize();

    alloc_size *= DEFAULT_MULTIPLICATION_FACTOR;
    for (; alloc_size < size; times += times) {
        alloc_size *= times;
    }
    return (alloc_size);
}

// Create a brand new page.
page_t *new_page(size_t size)
{
    size_t alloc_size = get_alloc_size(size);
    page_t *new = NULL;

    new = sbrk(alloc_size);
    new->before = NULL;
    new->next = NULL;
    new->pagesize = alloc_size;
    new->node_allocated = (void *)(new + sizeof(page_t));
    new->node_allocated->data_addr = NULL;
    new->node_allocated->next = NULL;
    new->node_allocated->before = NULL;
    new->node_allocated->node_size = 0;
    new->node_allocated->used = false;
    new->node_freed = NULL;
    return (new);
}

// Allocates a new page and then will create a new node.
void *allocate_new_page_and_node(size_t size)
{
    void *address = NULL;
    page_t *index = head;

    if (index == NULL)
        index = new_page(size);
    while (index != NULL && index->next != NULL)
        index = index->next;
    if (index != NULL) {
        index->next = new_page(size);
        index->next->before = index;
    } else
        index = new_page(size);
    return (check_allocate_list(size));
}