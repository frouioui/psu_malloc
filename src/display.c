/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Display memory functions
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

typedef unsigned long ul;

static void display_node(node_t *node, int index)
{
    char buf[8][100];

    for (int i = 0; i < 8; i += 1)
        memset(buf[i], '\0', 100);
    sprintf(buf[0], "    ------------ Node [%d] ------------\n", index);
    sprintf(buf[1], "     -- used: %d\n", node->used);
    sprintf(buf[1], "     -- size: %lu\n", node->size);
    sprintf(buf[2], "     -- address: %lu\n", (ul)node);
    sprintf(buf[3], "       -- data address: %lu\n", (ul)node->data);
    sprintf(buf[4], "         ----> diff: %lu == %lu ?\n",
    (ul)node->data - (ul)node, sizeof(node_t));
    sprintf(buf[5], "       -- next node address: %lu\n",
    (ul)node->next_node_addr);
    sprintf(buf[6], "         ----> diff: %lu == %ld ?\n",
    (ul)node->next_node_addr - (ul)node->data, node->size);
    sprintf(buf[7], "     -- next: %lu\n\n", (ul)node->next);
    for (int i = 0; i < 8; i += 1)
        write(1, buf[i], strlen(buf[i]));
}

static ul get_addr_dif(ul final_page_addr, ul last_node_addr)
{
    return (final_page_addr - last_node_addr);
}

static void display_page_header(page_t *page, int index, size_t size_req)
{
    char buf[5][100];

    for (int j= 0; j < 5; j += 1)
        memset(buf[j], '\0', 100);
    sprintf(buf[0], "[****** MALLOC SIZE REQUESTED: %lu ******]\n", size_req);
    sprintf(buf[1], "================ Page [%d] ================\n", index);
    sprintf(buf[2], " -- full: %d\n", page->full);
    sprintf(buf[3], " -- address: %lu\n", (ul)page);
    sprintf(buf[4], " -- size: %lu\n", page->size);
    for (int j = 0; j < 4; j += 1)
        write(1, buf[j], strlen(buf[j]));
}

static void display_page(page_t *page, int index, size_t size_req)
{
    char buf[8][100];
    node_t *tmp = page->node;
    int i = 0;

    for (int j = 0; j < 8; j += 1)
        memset(buf[j], '\0', 100);
    while (tmp && tmp->next)
        tmp = tmp->next;
    display_page_header(page, index, size_req);
    for (node_t *tmp = page->node; tmp != NULL; tmp = tmp->next, i += 1)
        display_node(tmp, i);
    sprintf(buf[0], " -- next page address: %lu\n", (ul)page->next_page_addr);
    sprintf(buf[1], "   ----> free space: %lu == %lu ?\n",
    page->free_space, get_addr_dif((ul)page->next_page_addr,
    (ul)tmp->next_node_addr));
    sprintf(buf[2], " -- next: %lu\n\n", (ul)page->next);
    sprintf(buf[3], "\n");
    for (int j = 0; j < 4; j += 1)
        write(1, buf[j], strlen(buf[j]));
}

void display_memory(page_t *page, size_t size_req)
{
    int i = 0;

    for (page_t *index = page; index != NULL; index = index->next, i += 1)
        display_page(index, i, size_req);
}