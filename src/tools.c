/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

/**
 * \file tools.c
 * \brief File containing tools functions
 * \author Cécile CADOUL
 * \author Florent POINSARD
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

/**
 * \fn void *get_addr(void *addr, size_t offset)
 * \brief Commpute an address thanks to another one and an offset.
 * \param[in] addr Reference address.
 * \param[in] offset Desired offset.
 * \return New calculated address.
 */
void *get_addr(void *addr, size_t offset)
{
    char *new_add = (char *)addr;

    offset = ALIGN(offset);
    new_add += offset;
    return ((void *)new_add);
}

/**
 * \fn size_t get_free_space(void *final_adrress, void *last_address)
 * \brief Compute free space in the current page.
 * \param[in] final_adrress Address of the page end.
 * \param[in] last_address Address of the last sub-allocation.
 * \return Free space in the current page.
 */
size_t get_free_space(void *final_adrress, void *last_address)
{
    return ((char *)final_adrress - (char *)last_address);
}

/**
 * \fn void update_free_space(page_t *page)
 * \brief Update free space in the page given as parameter.
 * \param[in] page Current page.
 */
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