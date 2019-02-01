/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

void *get_addr(void *addr, size_t offset)
{
    char *new_add = (char *)addr;

    offset = ALIGN(offset);
    new_add += offset;
    return ((void *)new_add);
}

size_t get_free_space(void *final_adrress, void *last_address)
{
    return ((char *)final_adrress - (char *)last_address);
}

void update_free_space(page_t *page)
{
    node_t *index = page->node;

    while (index && index->next)
        index = index->next;
    page->free_space = get_free_space(page->next_page_addr,
        index->next_node_addr);
    if (page->free_space <= sizeof(node_t) + ALIGN(1))
        page->full = true;
}