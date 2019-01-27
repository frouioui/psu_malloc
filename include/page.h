/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Page header
*/

/**
 * \file page.h
 * \brief Page functions header
 * \author Florent POINSARD
 * \author Cécile CADOUL
 */

#ifndef PAGE_H_
#define PAGE_H_

#include <stdlib.h>
#include <unistd.h>
#include "node.h"

/**
 * \struct page_s
 * \brief Holds main allocated memory with its meta-data
 * \var node_t node_allocated Pointer to the sub allocated memory area
 * \var node_t node_freed Pointer to the sub freed memory area
 * \var size_t pagesize Size of this main allocated memory
 * \var strcut page_s next Pointer on the next main allocated memory
 * \var strcut page_s before Pointer on the previous main allocated memory
 */
typedef struct page_s {
    node_t *node_allocated;
    node_t *node_freed;
    size_t pagesize;
    struct page_s *next;
    struct page_s *before;
} page_t;

extern const size_t DEFAULT_MULTIPLICATION_FACTOR;

page_t *new_page(size_t size);
void *allocate_new_page_and_node(size_t size);
void *check_allocate_list(size_t size);
void *check_free_list(size_t size);
void change_list(page_t *page, node_t *to_move);

#endif /* !PAGE_H_ */
