/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

/**
 * \file realloc.c
 * \brief File containing the realloc function.
 * \author Cécile CADOUL
 * \author Florent POINSARD
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

/**
 * \fn void *realloc(void *ptr, size_t size)
 * \brief Change the size of the memory block pointed to by ptr to size bytes.
 * \param[in] ptr Memory block pointer.
 * \param[in] size Size requested.
 * \return New memory block pointer.
 */
void *realloc(void *ptr, size_t size)
{
    node_t *node = NULL;
    void *new = NULL;

    if (ptr == NULL)
        return (malloc(size));
    node = (node_t *)ptr - 1;
    if (size == 0) {
        free(ptr);
        return (ptr);
    } else if (ptr != NULL) {
        new = malloc(size);
        pthread_mutex_lock(&lock);
        new = memcpy(new, ptr, node->size);
        pthread_mutex_unlock(&lock);
        free(ptr);
        return (new);
    }
    return (ptr);
}