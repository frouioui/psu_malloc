/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** Source file of the list functions
*/

#include <stdlib.h>
#include "page.h"
#include "node.h"

// Need to split the node, inserting a new node just ahead of
// the given one.
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

void *check_free_list(size_t size)
{
    node_t *index = NULL;

    if (head->node_freed == NULL)
        return (NULL);
    index = head->node_freed;
    while (index != NULL) {
        if (index->node_size <= size / 2 + sizeof(node_t)) {
            split_node(index)
            return ((void*)(index->data_addr));
        } else if (index->node_size <= size) {
            return ((void*)(index->data_addr));
        }
        index = index->next;
    }
    return (NULL);
}

void *check_allocate_list(size_t size)
{
    size_t total_size = 0;
    node_t *index = NULL;
    node_t *new = NULL;

    if (head->node_allocated == NULL)
        return (NULL);
    index = head->node_allocated;
    while (index->next != NULL) {
        index = index->next;
        total_size += sizeof(node_t) + 
    }
    new = (void*)(index + sizeof(size_t) + index->node_size + 1);
    return (new);
}