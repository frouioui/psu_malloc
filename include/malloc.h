/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** header file of the malloc function and struct
*/

#if !defined(_MALLOC_H)
#define _MALLOC_H

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#ifdef __x86_64__
    #define ALIGN(x) ((((x - 1) >> 3) << 3) + 8)
#else
    #define ALIGN(x) ((((x - 1) >> 2) << 2) + 4)
#endif

struct node_s {
    size_t size;
    void *data;
    bool used;
    struct node_s *next;
};

typedef struct node_s node_t;

extern node_t *head;
extern pthread_mutex_t lock;

size_t power_it(size_t size);
node_t *init_node(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *node);
void *malloc(size_t size);

#endif // _MALLOC_H
