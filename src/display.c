/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Display memory functions
*/

#include <stdio.h>
#include "malloc.h"

void display_node(node_t *node, int index)
{
    printf("    ------------ Node [%d] ------------\n", index);
    printf("     -- used: %d\n", node->used);
    printf("     -- address: %lu\n", (unsigned long)node);
    printf("       -- data address: %lu\n", (unsigned long)node->data);
    printf("     ----> diff: %lu == %lu ?\n", (unsigned long)node->data - (unsigned long)node, sizeof(node_t));
    printf("       -- next node address: %lu\n", (unsigned long)node->next_node_addr);
    printf("       ----> diff: %lu == %ld ?\n", (unsigned long)node->next_node_addr - (unsigned long)node->data, node->size);
    printf("     -- next: %lu\n\n", (unsigned long)node->next);
}

void display_page(page_t *page, int index)
{
    node_t *tmp = page->node;
    unsigned long addr_diff = 0;
    int i = 0;

    while (tmp && tmp->next)
        tmp = tmp->next;
    addr_diff = (unsigned long)page->next_page_addr - (unsigned long)tmp->next_node_addr;
    printf("================ Page [%d] ================\n", index);
    printf(" -- full: %d\n", page->full);
    printf(" -- address: %lu\n", (unsigned long)page);
    printf(" -- size: %lu\n", page->size);
    for (node_t *tmp = page->node; tmp != NULL; tmp = tmp->next, i += 1)
        display_node(tmp, i);
    printf(" -- next page address: %lu\n", (unsigned long)page->next_page_addr);
    printf(" ----> free space: %lu == %lu ?\n", page->free_space, addr_diff);
    printf(" -- next: %lu\n\n", (unsigned long)page->next);
    printf("\n");
}

void display_memory(page_t *page)
{
    int i = 0;

    for (page_t *index = page; index != NULL; index = index->next, i += 1)
        display_page(index, i);
}