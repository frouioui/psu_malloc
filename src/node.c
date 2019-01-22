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

void *my_sbrk(node_t *previous)
{
    if (previous->data_addr == NULL)
        return ((void*)previous);
    return ((void *)(previous + sizeof(node_t) + previous->node_size));
}