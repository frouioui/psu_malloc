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
    while (index && (index->next || (!index->used && size <= index->size)))
        index = index->next;
    pthread_mutex_lock(&lock);
    if (index && index->used == false && size <= index->size) {
        index->used = true;
        pthread_mutex_unlock(&lock);
        return (index->data);
    } else if (index) {
        index->next = init_node(size);
        pthread_mutex_unlock(&lock);
        return (index->next->data);
    } else {
        head = init_node(size);
        pthread_mutex_unlock(&lock);
        return (head->data);
    }
    pthread_mutex_unlock(&lock);
    return (NULL);
}

void free(void *node)
{
    node_t *index = head;

    if (node == false)
        return;
    while (index != NULL && node != (void *)index->data)
        index = index->next;
    // pthread_mutex_lock(&lock);
    if (index && node == (void *)index->data)
        index->used = false;
    // pthread_mutex_unlock(&lock);
}

void *realloc(void *ptr, size_t size)
{
    node_t *node = (void *)ptr - sizeof(node_t);
    void *new = NULL;

    if (ptr == NULL)
        return (malloc(size));
    if (ptr != NULL && size == 0) {
        free(ptr);
        return (ptr);
    } else if (ptr != NULL) {
        new = malloc(size);
        // pthread_mutex_lock(&lock);
        new = memcpy(ptr, ptr, node->size);
        pthread_mutex_unlock(&lock);
        free(ptr);
        return (new);
    }
    return (ptr);
}