/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the calloc fuction
*/

/**
 * \file calloc.c
 * \brief File containing the calloc function.
 * \author Cécile CADOUL
 * \author Florent POINSARD
 */

#include <stdio.h>
#include "malloc.h"

/**
 * \fn void *calloc(size_t nmemb, size_t size)
 * \brief Allocate memory for an array of nmemb elements of size bytes each
 * and returns a pointer to the allocated memory. The memory is set to zero.
 * \param[in] nmemb Number of elements in an array.
 * \param[in] size Size to be allocated in each elements.
 * \return Address of a new allocated block.
 */
void *calloc(size_t nmemb, size_t size)
{
    void *address = NULL;

    if (nmemb == 0 || size == 0)
        return (NULL);
    address = malloc(nmemb * size);
    if (address == NULL)
        return (NULL);
    bzero(address, nmemb * size);
    return (address);
}