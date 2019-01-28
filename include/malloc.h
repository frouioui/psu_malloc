/*
** EPITECH PROJECT, 2019
** PSU_MALLOC
** File description:
** Malloc header
*/

#ifndef MALLOC_H_
	#define MALLOC_H_

#include <stdlib.h>
#include "page.h"

void *malloc(size_t size);
void free(void *address);
void *realloc(void *ptr, size_t size);
size_t calcul_size_allocation(size_t size);
void *create_new_node(page_t *page, size_t size);

// DEBUG
void my_putstr(char *str);
void my_putnbr(int nb);

extern page_t *head;

#endif /* !MALLOC_H_ */
