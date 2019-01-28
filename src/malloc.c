/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

node_t *head = NULL;

static size_t power_it(size_t size)
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

void *malloc(size_t size)
{
    node_t *index = head;

    size = ALIGN(power_it(size));
    while (index && index->next && (!index->used && size <= index->size))
        index = index->next;
    if (index && index->used == false && size <= index->size) {
        index->used = true;
        return (index->data);
    } else if (index) {
        index->next = init_node(size);
        return (index->next->data);
    } else {
        head = init_node(size);
        return (head->data);
    }
    return (NULL);
}

void free(void *node)
{
    node_t *index = head;

    if (node == false)
        return;
    while (index != NULL && node != (void *)index->data)
        index = index->next;
    if (index && node == (void *)index->data)
        index->used = false;
}

// void *realloc(void *ptr, size_t size)
// {
//     (void)ptr;
//     (void)size;
//     write(1, "ra\n", 3);
//     return (ptr);
// }