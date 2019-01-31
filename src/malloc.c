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
    // write(1, "malloc\n", sizeof("malloc\n"));
    void *address = NULL;
    page_t *p_index = head;

    if (size == 0)
        return (NULL);
    size = ALIGN(size);
    if (p_index == NULL) {
        head = create_page_and_node(size);
        write(1, "2", 1);
        return (head->node->data);
    }
    while (p_index && p_index->full == true) {
        p_index = p_index->next;
    }
    if (p_index) {
        write(1, "3", 1);
        address = create_suballocation(p_index, size);
        write(1, "9", 1);
    }
    if (!p_index || !address) {
        p_index->next = add_new_page_and_node(size);
        address = p_index->next->node->data;
    }
    // write(1, "END malloc\n", sizeof("END malloc\n"));
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