/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Node functions
*/

#include "node.h"
#include <unistd.h>

const size_t addr_size = 8;
const size_t bool_size = 8;
const size_t size_t_size = 8;

/**
*
*/
void *my_sbrk(node_t *previous)
{
    char *tmp = (char *)(previous + 1);

    if (previous->data_addr == NULL)
        return ((void*)previous);
    tmp += previous->node_size;
    return ((void *)tmp);
}

void *init_node(node_t *node, size_t size)
{
    node->node_size = size;
    node->used = true;
    node->data_addr = (void *)(node + 1);
    node->next = NULL;
    return (node->data_addr);
}