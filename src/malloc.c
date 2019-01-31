/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
page_t *head = NULL;

void *create_suballocation(page_t *page, size_t size_requested)
{
    node_t *n_index = NULL;

    n_index = add_new_node(page->node, page->free_space,
                                            size_requested);

    if (!n_index) {
        return (NULL);
    }
    update_free_space(page);
    return (n_index->data);
}


void *malloc(size_t size)
{
    void *address = NULL;
    page_t *p_index = head;

    if (size == 0)
        return (NULL);
    size = ALIGN(size);
    if (p_index == NULL) {
        head = create_page_and_node(size);
        display_memory(head, size);
        return (head->node->data);
    }
    while (p_index) {
        if (p_index->full == false &&
        (address = create_suballocation(p_index, size)) != NULL) {
            display_memory(head, size);
            return (address);
        }
        p_index = p_index->next;
    }
    address = add_new_page_and_node(size);
    display_memory(head, size);
    return (address);
}

void *calloc(size_t nmemb, size_t size)
{
    void *address = NULL;

    if (nmemb == 0 || size == 0)
        return (NULL);
    address = malloc(nmemb * size);
    if (address == NULL)
        return (NULL);
    bzero(address, nmemb * size);
    return (address);
}