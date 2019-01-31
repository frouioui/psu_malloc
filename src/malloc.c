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

node_t *head = NULL;

void *malloc(size_t size)
{
    node_t *index = head;

    size = ALIGN(power_it(size));
    while (index && (index->next || (!index->used && size <= index->size)))
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