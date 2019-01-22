/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Page header
*/

#ifndef PAGE_H_
	#define PAGE_H_

#include "node.h"

typedef struct page_s {
    node_t *node;
    size_t pagesize;
    struct page_s *next;
} page_t;

#endif /* !PAGE_H_ */
