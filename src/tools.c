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

size_t power_it(size_t size)
{
    size_t res = getpagesize();

    while (res <= size)
        res *= 2;
    return (res);
}

node_t *init_node(size_t size)
{
    node_t *node = sbrk(size);

    node->used = true;
    node->size = size - sizeof(node_t);
    node->next = NULL;
    node->data = node + 1;
    return (node);
}