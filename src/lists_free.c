/*
** EPITECH PROJECT, 2019
** PSU_malloc_2019
** File description:
** Functions decicated to the free list
*/

#include "malloc.h"
#include "node.h"
#include "page.h"

void *remove_from_free_list(page_t *page, node_t *index)
{
    node_t *current = page->node_freed;

    while (current && current != index) {
        current = current->next;
    }
    if (current && current == index) {
        if (current->before) {
            current->before->next = current->next;
            (current->next != NULL) ?
                (current->next->before = current->before) : 0;
        } else if (current->next != NULL) {
            current = current->next;
            current->before = NULL;
        } else {
            return (NULL);
        }
    }
    while (current->before)
        current = current->before;
    return ((void *)current);
}