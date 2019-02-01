/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

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
        // write(1, "4\n", 2);
        new = malloc(size);
        pthread_mutex_lock(&lock);
        new = memcpy(new, ptr, node->size);
        pthread_mutex_unlock(&lock);
        free(ptr);
        // write(1, "6\n", 2);
        return (new);
    }
    return (ptr);
}