/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

/**
 * \file free.c
 * \brief File containing the free functions.
 * \author Cécile CADOUL
 * \author Florent POINSARD
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

/**
 * \fn void release_memory(page_t *p_index, page_t *previous)
 * \brief Release memory to the system.
 * \param[in] p_index Pointer on the current memory space allocated.
 * \param[in] previous Pointer on the previous memory space allocated.
 */
void release_memory(page_t *p_index, page_t *previous)
{
    node_t *index = NULL;
    bool used = false;

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

/**
 * \fn void free(void *node)
 * \brief Free the memory space pointed to by ptr.
 * \param[in] node Pointer on the memory space allocated.
s */
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
    pthread_mutex_unlock(&lock);
}