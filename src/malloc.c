/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** Source file of the malloc function
*/

#include <pthread.h>
#include <stdlib.h>
#include "page.h"

pthread_mutex_t lock;

void *malloc(size_t size)
{
    void *address = NULL;
    bool done = false;

    pthread_mutex_lock(&lock);
    if (head == NULL)
        head = new_page(size);
    address = check_free_list(size);
    if (address != NULL)
        return (address);
    address = check_allocated_list(size);
    if (address == NULL)
        address = allocate_new_page_and_node(size);
    pthread_mutex_unlock(&lock);
    return (address);
}