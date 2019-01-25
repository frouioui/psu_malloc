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

extern page_t *head;

#endif /* !MALLOC_H_ */
