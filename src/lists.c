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

static void *add_to_allocated_list(node_t *to_add)
{
    node_t *index = page->node_allocated;
    node_t *index = NULL;
    node_t *new = NULL;
    page_t *index_page = head;

    for (size_t total = 0; index_page; total = 0) {
        index = index_page->node_allocated;
        while (index != NULL && index->next != NULL) {
            index = index->next;
            total += sizeof(node_t) + index->node_size;
        }
        if (total + to_add->node_size + sizeof(node_t) <= index_page->pagesize) {
            (index != NULL) ? (index->next = to_add) : (index = to_add);
            to_add->before = index;
            return (init_node(to_add, to_add->node_size));
        }
        index_page = index_page->next;
    }
    return (NULL);
}

void *check_free_list(size_t size)
{
    node_t *index = NULL;

    if (head->node_freed == NULL)
        return (NULL);
    index = head->node_freed;
    while (index != NULL) {
        if (index->node_size <= size / 2 + sizeof(node_t)) {
            split_node(index);
            return (add_to_allocated_list(index));
        } else if (index->node_size <= size) {
            return (add_to_allocated_list(index));
        }
        index = index->next;
    }
    return (NULL);
}

void *check_allocate_list(size_t size)
{
    node_t *index = NULL;
    node_t *new = NULL;
    page_t *index_page = head;

    for (size_t total_size = 0; index_page; total_size = 0) {
        index = index_page->node_allocated;
        while (index != NULL && index->next != NULL) {
            index = index->next;
            total_size += sizeof(node_t) + index->node_size;
        }
        if (total_size + size + sizeof(node_t) <= index_page->pagesize) {
            new = my_sbrk(index);
            (index != NULL) ? (index->next = new) : (index = new);
            new->before = index;
            return (init_node(new, size));
        }
        index_page = index_page->next;
    }
    return (NULL);
}

