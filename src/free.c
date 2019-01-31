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