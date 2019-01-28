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
#include "node.h"
#include "page.h"

/**
 * \fn void split_node(node_t *node)
 * \brief Need to split the node, inserting a new node just ahead of
 *        the given one.
 * \param[in] node Node to be split.
 */
void split_node(node_t *node)
{
    node_t *new = NULL;

    new = (void *)((void *)node + sizeof(node_t) + node->node_size / 2);
    new->data_addr = (void *)((void *)new + sizeof(node_t));
    new->used = false;
    if (node->next != NULL)
        node->next->before = new;
    new->next = node->next;
    node->next = new;
    new->before = node;
    node->node_size /= 2;
    node->next->node_size = node->node_size;
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
            total += sizeof(node_t) + index_n->node_size;
            index_n = index_n->next;
        }
        if (total + to_add->node_size + sizeof(node_t) <= index_p->pagesize) {
            (index_n != NULL) ? (index_n->next = to_add) : (index_n = to_add);
            (index_n == to_add) ? (to_add->before = NULL) :
                (to_add->before = index_n);
            to_add->next = NULL;
            return ((void *)to_add->data_addr);
        }
        index_p = index_p->next;
    }
    return (NULL);
}

static size_t calcul_size_in_page(page_t *page)
{
    size_t size = 0;
    node_t *alloc = page->node_allocated;
    node_t *freed = page->node_freed;

    while (alloc) {
        size += alloc->node_size + sizeof(node_t);
        alloc = alloc->next;
    }
    while (freed) {
        size += freed->node_size + sizeof(node_t);
        freed = freed->next;
    }
    return (size);
}

static void *check_page_for_free(page_t *page, size_t size)
{
    node_t *index = NULL;

    index = page->node_freed;
    while (index != NULL) {
        if (size <= index->node_size / 2 + sizeof(node_t) * 2) {
            // split_node(index);
            page->node_freed = remove_from_free_list(page, index);
            return (add_to_allocated_list(index));
        } else if (size <= index->node_size) {
            page->node_freed = remove_from_free_list(page, index);
            return (add_to_allocated_list(index));
        }
        index = index->next;
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
    void *ret = NULL;
    page_t *page = head;

    while (page != NULL) {
        ret = check_page_for_free(page, size);
        if (ret != NULL)
            return (ret);
        page = page->next;
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
    page_t *index_p = head;

    for (size_t total_size = 0; index_p; total_size = 0) {
        total_size = calcul_size_in_page(index_p);
        if (total_size + size + sizeof(node_t) <= index_p->pagesize) {
            return (create_new_node(index_p, size));
        }
        index_p = index_p->next;
    }
    return (NULL);
}
