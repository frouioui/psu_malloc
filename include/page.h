/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Page header
*/

#ifndef PAGE_H_
	#define PAGE_H_

#include <stdlib.h>
#include <unistd.h>
#include "node.h"

typedef struct page_s {
    node_t *node_allocated;
    node_t *node_freed;
    size_t pagesize;
    struct page_s *next;
    struct page_s *before;
} page_t;

extern const size_t DEFAULT_MULTIPLICATION_FACTOR;

page_t *new_page(size_t size);

page_t *head = NULL;

#endif /* !PAGE_H_ */
