/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

void merge_node(node_t *node)
{
    node->size += sizeof(node_t) + node->next->size;
    node->next = node->next->next;
    node->next_node_addr = (void *)get_addr(node, node->size + sizeof(node_t));
}

void release_memory(page_t *p_index, page_t *previous)
{
    node_t *index = NULL;
    bool used = false;

    // if (p_index == NULL && previous) {
    //     sbrk(previous->size * -1);
    //     return;
    // }
    index = p_index->node;
    while (index && used == false) {
        if (index->used == true)
            used = true;
        index = index->next;
    }
    if (used == false && index == NULL)
        sbrk(p_index->size * -1);
    if (previous)
        previous->next = NULL;
    else
        head = NULL;
}

void free(void *node)
{
    page_t *p_index = head;
    // page_t *p_prev_index = NULL;
    node_t *n_index = NULL;

    if (p_index == NULL)
        return;
    while (p_index != NULL) {
        n_index = p_index->node;
        while (n_index != NULL && node != (void *)n_index->data) {
            n_index = n_index->next;
        }
        // if (node == (void *)n_index->data)
        //     break;
        // p_prev_index = p_index;
        p_index = p_index->next;
    }
    pthread_mutex_lock(&lock);
    if (n_index && node == (void *)n_index->data)
        n_index->used = false;
    if (n_index && n_index->used == false && n_index->next && n_index->used == false)
        merge_node(n_index);

    // release_memory(p_index, p_prev_index);

    pthread_mutex_unlock(&lock);
}