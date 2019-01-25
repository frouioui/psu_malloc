/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** Source file of the malloc function
*/

/**
 * \file malloc.c
 * \brief File that contains the main functions
 * \author Florent POINSARD
 * \author Cécile CADOUL
 */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "page.h"

/**
 * \var pthread_mutex_t lock
 * Lock mutex needed to manage thread.
 */
pthread_mutex_t lock;

/**
 * \var page_t *head
 * Head of the allocated pages.
 */
page_t *head = NULL;

/**
 * \fn void *malloc(size_t size)
 * \brief Main malloc function.
 * \param[in] size Size to be allocated.
 * \return Address of the allocated memory.
 *
 * Receives a size in parameter and realises a memory allocation.
 */
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

/**
 * \fn void free(void * address)
 * \brief Main free function.
 * \param[in] address Memory address to release.
 *
 * Receives an adress in parameter and release its allocated memory.
 */
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