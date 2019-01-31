/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

void free(void *node)
{
    page_t *p_index = head;
    node_t *n_index = NULL;

    if (p_index == NULL)
        return;
    while (p_index != NULL) {
        n_index = p_index->node;
        while (n_index != NULL && node != (void *)n_index->data) {
            n_index = n_index->next;
        }
        p_index = p_index->next;
    }
    pthread_mutex_lock(&lock);
    if (n_index && node == (void *)n_index->data)
        n_index->used = false;
    // TODO: merge the next node if it is free = true too

    // TODO: check if the current page is the last one and if it is
    // we must free its memory.
    pthread_mutex_unlock(&lock);
}