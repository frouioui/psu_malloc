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
    node_t *node = (void *)ptr - sizeof(node_t);
    void *new = NULL;

    if (ptr == NULL)
        return (malloc(size));
    if (ptr != NULL && size == 0) {
        free(ptr);
        return (ptr);
    } else if (ptr != NULL) {
        new = malloc(size);
        new = memcpy(ptr, ptr, node->size);
        free(ptr);
        return (new);
    }
    return (ptr);
}