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

#include "node.h"
#include <unistd.h>

/**
 * \fn void *my_sbrk(node_t *previous)
 * \brief Our own srbk function for sub-allocation.
 * \param[in] previous Previous node allocated in this page.
 * \return Address of the next node allocated.
 *
 * Receives the previous node in parameter and return
 * the adrress of the next node.
 */
void *my_sbrk(node_t *previous)
{
    char *tmp = (char *)(previous + 1);

    if (previous->data_addr == NULL)
        return ((void*)previous);
    tmp += previous->node_size;
    return ((void *)tmp);
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
    return (node->data_addr);
}