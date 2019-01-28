/*
** EPITECH PROJECT, 2019
** PSU_MALLOC_2018
** File description:
** Node header
*/

/**
 * \file node.h
 * \brief Node functions header
 * \author Florent POINSARD
 * \author Cécile CADOUL
 */

#ifndef NODE_H_
	#define NODE_H_

#include <stdbool.h>
#include <stdlib.h>

/**
 * \struct node_s
 * \brief Holds sub-allocated memory with its meta-data
 * \var void *data_addr Data address inside this node
 * \var size_t node_size Memory allocated size without its meta-data
 * \var bool used True if this area is used by a variable
 * \var struct node_s next Pointer on the next sub-allocated memory
 * \var struct node_s before Pointer on the previous sub-allocated memory
 */
typedef struct node_s {
    void *data_addr;
    size_t node_size;
    bool used;
    struct node_s *next;
    struct node_s *before;
} node_t;

void *init_node(node_t *node, size_t size);
void *my_sbrk(void *parrent_of_node);

#endif /* !NODE_H_ */
