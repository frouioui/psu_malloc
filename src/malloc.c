/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

/*! \mainpage Malloc project
 *
 * \section intro_sec Introduction
 *
 * Allocate and free dynamic memory
 *
 * \section descr_sec Description
 *
 * \subsection malloc Malloc
 *
 * The malloc() function allocates size bytes and returns a pointer
 * to the allocated memory. The memory is not initialized.
 * If size is 0, then malloc() returns either NULL, or a unique pointer
 * value that can later be successfully passed to free().
 *
 * \subsection free Free
 *
 * The free() function frees the memory space pointed to by ptr,
 * which must have been returned by a previous call to malloc(), calloc() or
 * realloc(). Otherwise, or if free(ptr) has already been called before,
 * undefined behavior occurs. If ptr is NULL, no operation is performed.
 *
 * \subsection calloc Calloc
 *
 * The calloc() function allocates memory for an array of nmemb elements of
 * size bytes each and returns a pointer to the allocated memory. The memory
 * is set to zero. If nmemb or size is 0, then calloc() returns either NULL,
 * or a unique pointer value that can later be successfully passed to free().
 *
 * \subsection realloc Realloc
 *
 *The realloc() function changes the size of the memory block pointed to by
 ptr to size bytes. The contents will be unchanged in the range from the start
 of the region up to the minimum of the old and new sizes. If the new size is
 larger than the old size, the added memory will not be initialized. If ptr is
 NULL, then the call is equivalent to malloc(size), for all values of size; if
 size is equal to zero, and ptr is not NULL, then the call is equivalent to
 free(ptr). Unless ptr is NULL, it must have been returned by an earlier call
 to malloc(), calloc() or realloc(). If the area pointed to was moved, a
 free(ptr) is done.
 *
 * \section ret_sec Return Value
 *
 * \subsection malloc Malloc and Calloc
 *
 * The malloc() and calloc() functions return a pointer to the allocated
 * memory that is suitably aligned for any kind of variable. On error, these
 * functions return NULL. NULL may also be returned by a successful call to
 * malloc() with a size of zero, or by a successful call to calloc() with nmemb
 * or size equal to zero.
 *
 * \subsection free Free
 *
 * The free() function returns no value.
 *
 * \subsection realloc Realloc
 *
 * The realloc() function returns a pointer to the newly allocated memory,
 * which is suitably aligned for any kind of variable and may be different
 * from ptr, or NULL if the request fails. If size was equal to 0, either
 * NULL or a pointer suitable to be passed to free() is returned. If realloc()
 * fails the original block is left untouched; it is not freed or moved.
 */

/**
 * \file malloc.c
 * \brief File containing the malloc functions.
 * \author Cécile CADOUL
 * \author Florent POINSARD
 */

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

/**
 * \var pthread_mutex_t lock
 * \brief Mutex lock.
 *
 * Lock needed to manage threads.
 */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * \var page_t *head
 * \brief First allocation page.
 *
 * Allocation pages are public.
 */
page_t *head = NULL;

/**
 * \fn static void *create_suballocation(page_t *page, size_t size_requested)
 * \brief Create a new sub-allocated area.
 * \param[in] page Current allocated page.
 * \param[in] size Size requested by the user.
 * \return Address of a new allocated block.
 */
static void *create_suballocation(page_t *page, size_t size_requested)
{
    node_t *n_index = NULL;

    n_index = add_new_node(page->node, page->free_space, size_requested);
    if (!n_index) {
        return (NULL);
    }
    update_free_space(page);
    return (n_index->data);
}

/**
 * \fn static void *new_page_and_node_unlock(size_t size)
 * \brief Create a new allocated page.
 * \param[in] size Size requested by the user.
 * \return Address of a new allocated block.
 */
static void *new_page_and_node_unlock(size_t size)
{
    void *address = NULL;

    address = add_new_page_and_node(size);
    pthread_mutex_unlock(&lock);
    return (address);
}

/**
 * \fn static void *create_page_node_unlock(size_t size)
 * \brief Create the first new allocated page.
 * \param[in] size Size requested by the user.
 * \return Address of a new allocated block.
 */
static void *create_page_node_unlock(size_t size)
{
    head = create_page_and_node(size);
    pthread_mutex_unlock(&lock);
    return (head->node->data);
}

/**
 * \fn void *malloc(size_t size)
 * \brief Allocates size bytes and returns a pointer to the allocated memory.
 * \param[in] size Size that will to allocate.
 * \return Address of a new allocated block.
 */
void *malloc(size_t size)
{
    void *address = NULL;
    page_t *p_index = head;

    if (size == 0)
        return (NULL);
    size = ALIGN(size);
    pthread_mutex_lock(&lock);
    if (p_index == NULL)
        return (create_page_node_unlock(size));
    while (p_index) {
        if (p_index->full == false &&
        (address = create_suballocation(p_index, size)) != NULL) {
            pthread_mutex_unlock(&lock);
            return (address);
        }
        p_index = p_index->next;
    }
    return (new_page_and_node_unlock(size));
}