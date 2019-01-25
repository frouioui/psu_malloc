/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** Source file of the list functions
*/

/**
 * \file lists.c
 * \brief File that contains the list management
 *  functions
 * \author Florent POINSARD
 * \author Cécile CADOUL
 */

#include <stdlib.h>
#include "malloc.h"

/**
 * \fn void split_node(node_t *node)
 * \brief Need to split the node, inserting a new node just ahead of
 *        the given one.
 * \param[in] node Node to be split.
 */
static void split_node(node_t *node)
{
    node_t *new = NULL;

    new = (void*)(node + sizeof(node_t) + node->node_size);
    new->data_addr = (void*)(new + sizeof(node_t));
    new->used = false;
    new->next = node->next->next;
    new->before = node;
    node->next = new;
}

/**
 * \fn void *add_to_allocated_list(node_t *to_add)
 * \brief Need to split the node, inserting a new node just ahead of
 *        the given one.
 * \param[in] to_add Node to add to the allocated nodes list.
 * \return New allocated node
 */
static void *add_to_allocated_list(node_t *to_add)
{
    node_t *index_n = NULL;
    page_t *index_p = head;

    for (size_t total = 0; index_p; total = 0) {
        index_n = index_p->node_allocated;
        while (index_n != NULL && index_n->next != NULL) {
            index_n = index_n->next;
            total += sizeof(node_t) + index_n->node_size;
        }
        if (total + to_add->node_size + sizeof(node_t) <= index_p->pagesize) {
            (index_n != NULL) ? (index_n->next = to_add) : (index_n = to_add);
            (index_n == to_add) ? (to_add->before = NULL) :
            (to_add->before = index_n);
            return (init_node(to_add, to_add->node_size));
        }
        index_p = index_p->next;
    }
    return (NULL);
}

/**
 * \fn void *check_free_list(size_t size)
 * \brief Check if there is a free node large enough to hold the new allocation
 * \param[in] size Size requested for the new allocation.
 * \return Address of a large enough node or NULL
 */
void *check_free_list(size_t size)
{
    node_t *index = NULL;

    if (head->node_freed == NULL)
        return (NULL);
    index = head->node_freed;
    while (index != NULL) {
        if (size <= index->node_size / 2 + sizeof(node_t)) {
            split_node(index);
            return (add_to_allocated_list(index));
        } else if (size <= index->node_size) {
            return (add_to_allocated_list(index));
        }
        index = index->next;
    }
    return (NULL);
}

/**
 * \fn void *check_allocate_list(size_t size)
 * \brief Check if there is enough place to add a new node in allocation list
 * \param[in] size Size requested for the new allocation.
 * \return Address of a new allocated node or NULL
 */
void *check_allocate_list(size_t size)
{
    node_t *index_n = NULL;
    node_t *new = NULL;
    page_t *index_p = head;

    for (size_t total_size = 0; index_p; total_size = 0) {
        index_n = index_p->node_allocated;
        while (index_n != NULL && index_n->next != NULL) {
            index_n = index_n->next;
            total_size += sizeof(node_t) + index_n->node_size;
        }
        if (total_size + size + sizeof(node_t) <= index_p->pagesize) {
            new = my_sbrk(index_n);
            (index_n != NULL) ? (index_n->next = new) : (index_n = new);
            (index_n == new) ? (new->before = NULL) : (new->before = index_n);
            return (init_node(new, size));
        }
        index_p = index_p->next;
    }
    return (NULL);
}
