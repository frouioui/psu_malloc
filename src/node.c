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

void push_node(node_t *head, size_t size, void *current_addr)
{
    size_t increment = size + addr_size * 2 + bool_size + size_t_size;
    node_t *current = head;
    node_t *new = NULL;

    if (!current)
}