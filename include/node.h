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

void *init_node(node_t *node, size_t size);
void *my_sbrk(node_t *previous);

#endif /* !NODE_H_ */
