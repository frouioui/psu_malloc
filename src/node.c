/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Node fuctions
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

void init_node(node_t *node, size_t size_requested)
{
    node->size = size_requested;
    node->data = get_addr(node, sizeof(node_t));
    node->used = true;
    node->next = NULL;
    node->next_node_addr = get_addr(node->data, size_requested);
}

node_t *init_new_node(node_t *previous, size_t size_requested)
{
    node_t *new_node = NULL;

    if (!previous)
        return (NULL);
    new_node = previous->next_node_addr;
    init_node(new_node, size_requested);
    return (new_node);
}

void split_node(node_t *node, size_t size_node_a)
{
    node_t *new = node->next_node_addr;

    init_node(node, node->size - size_node_a - sizeof(node_t));
    new->next = node->next;
    new->used = false;
    node->next = new;
    node->size = size_node_a;
}

void *check_new_node_free(node_t *node, size_t size_requested)
{
    if (!node->used && size_requested + sizeof(node_t) <= node->size) {
        split_node(node, size_requested);
        return (node);
    } else if (node->used == false && size_requested <= node->size) {
        node->used = true;
        return (node);
    }
    return (NULL);
}

node_t *add_new_node(node_t *node, size_t free_space, size_t size_requested)
{
    node_t *tmp = node;
    void *address_tmp = NULL;

    if (size_requested + sizeof(node_t) > free_space)
        return (NULL);
    if (tmp && tmp->next == NULL)
        address_tmp = check_new_node_free(tmp, size_requested);
    if (address_tmp != NULL)
        return (address_tmp);
    while (tmp && tmp->next) {
        if (tmp->used == false && size_requested <= tmp->size) {
            tmp->used = true;
            return (tmp);
        }
        tmp = tmp->next;
    }
    if (tmp && !tmp->next)
        tmp->next = init_new_node(tmp, size_requested);
    return (tmp->next);
}