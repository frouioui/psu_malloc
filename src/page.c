/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Page fuctions
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

const size_t MIN_PAGES = 512;

page_t *create_page_and_node(size_t size_requested)
{
    page_t *page = NULL;
    size_t page_size = getpagesize() * MIN_PAGES;

    while (page_size < size_requested + sizeof(page_t))
        page_size += getpagesize();
    page = sbrk(page_size);
    page->size = page_size;
    page->full = false;
    page->next = NULL;
    page->next_page_addr = get_addr(page, page->size);
    page->node = get_addr(page, sizeof(page_t));
    init_node(page->node, size_requested);
    page->free_space = get_free_space(page->next_page_addr,
        page->node->next_node_addr);
    return (page);
}

void *add_new_page_and_node(size_t size_requested)
{
    page_t *index = head;

    while (index != NULL && index->next != NULL)
        index = index->next;
    if (index != NULL)
        index->next = create_page_and_node(size_requested);
    return (index->next->node->data);
}