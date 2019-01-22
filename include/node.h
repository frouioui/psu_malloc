/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Node header
*/

#ifndef NODE_H_
	#define NODE_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct node_s {
    void *data_addr;
    size_t node_size;
    bool used;
    struct node_s *next;
    struct node_s *before;
} node_t;

#endif /* !NODE_H_ */
