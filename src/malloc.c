/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
node_t *head = NULL;

void *malloc(size_t size)
{
    node_t *index = head;
    void *address = NULL;

    size = ALIGN(power_it(size));
    while (index && (index->next || (!index->used && size <= index->size)))
        index = index->next;
    pthread_mutex_lock(&lock);
    if (index && index->used == false && size <= index->size) {
        index->used = true;
        address = index->data;
    } else if (index) {
        index->next = init_node(size);
        address = index->next->data;
    } else {
        head = init_node(size);
        address = head->data;
    }
    pthread_mutex_unlock(&lock);
    return (address);
}