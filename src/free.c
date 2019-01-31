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
    // node_t *index = head;
    write(1, "free\n", sizeof("free\n"));
    (void)node;
    // if (node == false)
    //     return;
    // while (index != NULL && node != (void *)index->data)
    //     index = index->next;
    // pthread_mutex_lock(&lock);
    // if (index && node == (void *)index->data)
    //     index->used = false;
    // pthread_mutex_unlock(&lock);
}