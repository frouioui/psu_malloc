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

// Create a brand new page.
page_t *new_page(size_t times)
{
    size_t size = getpagesize();
    page_t *new = NULL;

    if (times == 0)
        times = 1;
    size *= DEFAULT_MULTIPLICATION_FACTOR * times;
    new = sbrk(size);
    new->before = NULL;
    new->next = NULL;
    new->pagesize = size;
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
    size_t times = 2;
    void *address = NULL;
    page_t *index = head;

    while (index != NULL && index->next != NULL)
        index = index->next;
    for (size_t tmp = 0; tmp < size; times += times) {
        tmp *= DEFAULT_MULTIPLICATION_FACTOR * times;
    }
    index->next = new_page(times);
    index->next->before = index;
    index = index->next;
    return (check_allocate_list(size));
}