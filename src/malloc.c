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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "page.h"
#include "malloc.h"

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

// void my_putchar(char c)
// {
//     write(1, &c, 1);
// }

// void my_putstr(char *str)
// {
//     for (unsigned int i = 0; str[i]; i++)
//         my_putchar(str[i]);
// }

// void my_putnbr(int nb)
// {
//     int modulo;

//     modulo = 0;
//     if (nb <= 9 && nb >= 0)
//         my_putchar(nb + '0');
//     if (nb < 0) {
//         my_putchar('-');
//         nb = nb * (- 1);
//         if (nb <= 9 && nb >=0)
//         my_putnbr(nb);
//     }
//     if (nb > 9) {
//         modulo = nb % 10;
//         my_putnbr(nb / 10);
//         my_putchar(modulo + '0');
//     }
// }

/**
 * \fn void *malloc(size_t size)
 * \brief Main malloc function.
 * \param[in] size Size to be allocated.
 * \return Address of the allocated memory.
 *
 * Receives a size in parameter and realises a memory allocation.
 */
void *my_malloc(size_t size)
{
    void *address = NULL;
    
    pthread_mutex_lock(&lock);
    size = calcul_size_allocation(size);

    // BEGIN DEBUG
    // static size_t total_alloc = 0;
    // total_alloc += size;
    // write(1, "malloc\n", 7);
    // my_putnbr(size);
    // write(1, "\n", 1);
    // my_putnbr(total_alloc);
    // write(1, "\n", 1);
    // END DEBUG

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
    // my_putstr("FINISH\n");
    return (address);
}

/**
 * \fn void free(void * address)
 * \brief Main free function.
 * \param[in] address Memory address to release.
 *
 * Receives an adress in parameter and release its allocated memory.
 */
void my_free(void *address)
{
    page_t *current = head;
    node_t *node = current->node_allocated;
    bool freed = false;

    // BEGIN DEBUG
    // write(1, "free\n", 5);
    // END DEBUG

    while (current && freed == false) {
        while (node && freed == false) {
            (node->data_addr == address) ? (change_list(current, node)) : (1);
            (node->data_addr == address) ? (freed = true) : (freed = false);
            node = node->next;
        }
        current = current->next;
    }
}

// void *realloc(void *ptr, size_t size)
// {
    
// }