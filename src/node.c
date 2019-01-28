/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Node functions
*/

/**
 * \file node.c
 * \brief File that contains the node functions
 * \author Florent POINSARD
 * \author Cécile CADOUL
 */

#include <unistd.h>
#include "node.h"
#include "page.h"

/**
 * \fn void *my_sbrk(node_t *previous)
 * \brief Our own srbk function for sub-allocation.
 * \param[in] previous Previous node allocated in this page.
 * \return Address of the next node allocated.
 *
 * Receives the previous node in parameter and return
 * the adrress of the next node.
 */
void *my_sbrk(void *parrent_of_node)
{
    page_t *page = parrent_of_node;
    void *biggest = page + 1;
    node_t *current = page->node_allocated;

    if (page->node_allocated == NULL && page->node_freed == NULL)
        return ((void *)page + sizeof(page_t));
    while (current) {
        if ((void *)(current->data_addr + current->node_size) > biggest)
            biggest = (void *)(current->data_addr + current->node_size);
        current = current->next;
    }
    current = page->node_freed;
    while (current) {
        if ((void *)(current->data_addr + current->node_size) > biggest)
            biggest = (void *)(current->data_addr + current->node_size);
        current = current->next;
    }
    return (biggest );
}

static void insert_node_in_page(page_t *page, node_t *node)
{
    node_t *current_node = page->node_allocated;

    if (current_node == NULL) {
        page->node_allocated = node;
        return;
    }
    while (current_node->next)
        current_node = current_node->next;
    current_node->next = node;
    node->before = current_node;
    node->next = NULL;
}

/**
 * \fn void *init_node(node_t *node, size_t size)
 * \brief Initalizes node fields.
 * \param[in] node Node to be initialized.
 * \param[in] size Size requested for the allocation.
 * \return Address of the data inside the node.
 *
 * Initializes all node's fields and returns the address needed by the user.
 */
void *init_node(node_t *node, size_t size)
{
    node->node_size = size;
    node->used = true;
    node->data_addr = (void *)(node + 1);
    node->next = NULL;
    node->before = NULL;
    return (node->data_addr);
}

void *create_new_node(page_t *page, size_t size)
{
    node_t *new = NULL;
    void *ret = NULL;

    new = my_sbrk(page);
    ret = init_node(new, size);
    insert_node_in_page(page, new);
    return (ret);
}