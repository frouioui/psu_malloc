/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Page fuctions
*/

/**
 * \file page.c
 * \brief File containing the page functions
 * \author Cécile CADOUL
 * \author Florent POINSARD
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"


/**
 * \var size_t MIN_PAGES
 * \brief Default multiplication factor for the page.
 *
 * Number of pagesize that sbrk will ask for to the system.
 */
const size_t MIN_PAGES = 512;

/**
 * \fn page_t *create_page_and_node(size_t size_requested)
 * \brief Create a new allocated page.
 * \param[in] size_requested Size requested by the user.
 * \return New allocated page.
 */
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

/**
 * \fn void *add_new_page_and_node(size_t size_requested)
 * \brief Add a new allocated page.
 * \param[in] size_requested Size requested by the user.
 * \return Address of a new allocated page.
 */
void *add_new_page_and_node(size_t size_requested)
{
    page_t *index = head;

    while (index != NULL && index->next != NULL)
        index = index->next;
    if (index != NULL)
        index->next = create_page_and_node(size_requested);
    return (index->next->node->data);
}