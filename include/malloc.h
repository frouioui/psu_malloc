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

extern pthread_mutex_t lock;
extern page_t *head;

#endif /* !MALLOC_H_ */
