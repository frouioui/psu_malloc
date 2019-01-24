/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** Source file of the malloc function
*/

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "page.h"

pthread_mutex_t lock;
page_t *head = NULL;

void *malloc(size_t size)
{
    void *address = NULL;

    pthread_mutex_lock(&lock);
    if (head == NULL) {
        head = new_page(size);
        pthread_mutex_unlock(&lock);
        return (head->node_allocated->data_addr);
    }
    address = check_free_list(size);
    if (address != NULL) {
         pthread_mutex_unlock(&lock);
        return (address);
    }
    address = check_allocate_list(size);
    if (address == NULL)
        address = allocate_new_page_and_node(size);
    pthread_mutex_unlock(&lock);
    return (address);
}

void free(void *address)
{
    (void)address;
}

void *realloc(void *ptr, size_t size)
{
    (void)ptr;
    (void)size;
    return (memcpy(malloc(size), ptr, size));
}