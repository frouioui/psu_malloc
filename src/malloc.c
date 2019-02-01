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
    // write(1, "1-0\n", 4);

    n_index = add_new_node(page->node, page->free_space,
                                            size_requested);

    if (!n_index) {
    // write(1, "1-1\n", 4);
        return (NULL);
    }
    update_free_space(page);
    // write(1, "1-2\n", 4);
    return (n_index->data);
}


void *malloc(size_t size)
{
    void *address = NULL;
    page_t *p_index = head;

    // write(1, "000\n", 4);
    if (size == 0)
        return (NULL);
    size = ALIGN(size);
    pthread_mutex_lock(&lock);
    if (p_index == NULL) {
        // write(1, "0\n", 2);
        head = create_page_and_node(size);
        // display_memory(head, size);
        pthread_mutex_unlock(&lock);
        return (head->node->data);
    }
    while (p_index) {
        // write(1, "2\n", 2);
        if (p_index->full == false &&
        (address = create_suballocation(p_index, size)) != NULL) {
            // write(1, "1\n", 2);
            // display_memory(head, size);
            pthread_mutex_unlock(&lock);
            return (address);
        }
        p_index = p_index->next;
    }
    // write(1, "3\n", 2);
    address = add_new_page_and_node(size);
    pthread_mutex_unlock(&lock);
    // display_memory(head, size);
    return (address);
}

void *calloc(size_t nmemb, size_t size)
{
    void *address = NULL;

    // write(1, "010\n", 4);
    if (nmemb == 0 || size == 0)
        return (NULL);
    // write(1, "011\n", 4);
    address = malloc(nmemb * size);
    // write(1, "012\n", 4);
    if (address == NULL)
        return (NULL);
    // write(1, "013\n", 4);
    bzero(address, nmemb * size);
    // write(1, "014\n", 4);
    return (address);
}