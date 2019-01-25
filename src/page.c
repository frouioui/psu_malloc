/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Page functions
*/

/**
 * \file page.c
 * \brief File that contains the page functions
 * \author Florent POINSARD
 * \author Cécile CADOUL
 */

#include "malloc.h"
/**
 * \var size_t DEFAULT_MULTIPLICATION_FACTOR
 * \brief Default multiplication factor for the page.
 *
 * Number of pagesize that sbrk will ask for to the system.
 */
const size_t DEFAULT_MULTIPLICATION_FACTOR = 32;

/**
 * \fn static size_t get_alloc_size(size_t size)
 * \brief Return the allocation size needed.
 * \param[in] size Size requested by the user.
 * \return Allocation size calculated from the size requested.
 */
static size_t get_alloc_size(size_t size)
{
    size_t alloc_size = getpagesize();
    size_t times = 2;

    alloc_size *= DEFAULT_MULTIPLICATION_FACTOR;
    for (; alloc_size < size; times += times) {
        alloc_size *= times;
    }
    return (alloc_size);
}

/**
 * \fn page_t *new_page(size_t size)
 * \brief Create a brand new page.
 * \param[in] size Size requested by the user.
 * \return A brand new page.
 */
page_t *new_page(size_t size)
{
    size_t alloc_size = get_alloc_size(size);
    page_t *new = NULL;

    new = sbrk(alloc_size);
    new->before = NULL;
    new->next = NULL;
    new->pagesize = alloc_size;
    new->node_allocated = (void *)(new + 1);
    new->node_allocated->data_addr = (void *)(new->node_allocated + 1);
    new->node_allocated->next = NULL;
    new->node_allocated->before = NULL;
    new->node_allocated->node_size = size;
    new->node_allocated->used = false;
    new->node_freed = NULL;
    return (new);
}

/**
 * \fn void *allocate_new_page_and_node(size_t size)
 * \brief Allocates a new page and then will create a new node.
 * \param[in] size Size requested by the user.
 * \return A new allocated page.
 */
void *allocate_new_page_and_node(size_t size)
{
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