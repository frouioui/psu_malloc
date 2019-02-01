/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Display memory functions
*/

/**
 * \file display.c
 * \brief File containing the display functions.
 * \author Cécile CADOUL
 * \author Florent POINSARD
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

/**
 * \fn static void display_node(node_t *node, int index)
 * \brief Display sub-allocation node informations.
 * \param[in] node Current sub-allocation node.
 * \param[in] index Index of the sub-allocation node.
 */
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

/**
 * \fn static void display_page_header(page_t *page, int index)
 * \brief Display page header informations.
 * \param[in] page Current allocated page.
 * \param[in] index Index of the allocated page.
 */
static void display_page_header(page_t *page, int index)
{
    char buf[4][100];

    for (int j= 0; j < 4; j += 1)
        memset(buf[j], '\0', 100);
    sprintf(buf[0], "================ Page [%d] ================\n", index);
    sprintf(buf[1], " -- full: %d\n", page->full);
    sprintf(buf[2], " -- address: %lu\n", (ul)page);
    sprintf(buf[3], " -- size: %lu\n", page->size);
    for (int j = 0; j < 4; j += 1)
        write(1, buf[j], strlen(buf[j]));
}

/**
 * \fn static void display_page(page_t *page, int index)
 * \brief Display the current page informations.
 * \param[in] page Current allocated page.
 * \param[in] index Index of the allocated page.
 */
static void display_page(page_t *page, int index)
{
    char buf[8][100];
    node_t *tmp = page->node;
    int i = 0;

    for (int j = 0; j < 8; j += 1)
        memset(buf[j], '\0', 100);
    while (tmp && tmp->next)
        tmp = tmp->next;
    display_page_header(page, index);
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

/**
 * \fn void display_memory(page_t *page, size_t size_req)
 * \brief Display all informations about the allocation zone.
 * \param[in] page First allocated page.
 * \param[in] size_req Size requested by the user.
 */
void display_memory(page_t *page, size_t size_req)
{
    char buf[100];
    int i = 0;

    memset(buf, '\0', 100);
    sprintf(buf, "[****** MALLOC SIZE REQUESTED: %lu ******]\n", size_req);
    write(1, buf, strlen(buf));
    for (page_t *index = page; index != NULL; index = index->next, i += 1)
        display_page(index, i);
}