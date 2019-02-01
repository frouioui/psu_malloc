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

void merge_node(node_t *node)
{
    node->size += sizeof(node_t) + node->next->size;
    node->next = node->next->next;
    node->next_node_addr = (void *)get_addr(node->data, node->size);
}

void free(void *node)
{
    page_t *p_index = head;
    node_t *n_index = NULL;
    bool find = false;
    // (void)node;
    // write(2, "000\n", 4);
    if (p_index == NULL)
        return;
    while (p_index != NULL && !find) {
        n_index = p_index->node;
        // write(2, "001\n", 4);
        while (n_index != NULL && !find) {
            // write(2, "002\n", 4);
            if (node == n_index->data) {
                write(2, "003\n", 4);
                find = true;
            }
            n_index = n_index->next;
        }
        p_index = p_index->next;
    }
    // write(2, "004\n", 4);
    pthread_mutex_lock(&lock);
    if (n_index && node == n_index->data) {
        n_index->used = false;
        write(2, "005\n", 4);
    }
    // write(2, "006\n", 4);
    // TODO: merge the next node if it is free = true too

    write(1, "q", 1);

    // TODO: check if the current page is the last one and if it is
    // we must free its memory.
    pthread_mutex_unlock(&lock);
}