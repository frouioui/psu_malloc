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

#endif // _MALLOC_H
