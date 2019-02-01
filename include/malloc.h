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
    void *next_node_addr;
    struct node_s *next;
};

typedef struct node_s node_t;

struct page_s {
    size_t size;
    bool full;
    node_t *node;
    size_t free_space;
    void *next_page_addr;
    struct page_s *next;
};

typedef struct page_s page_t;

typedef unsigned long ul;

extern page_t *head;
extern pthread_mutex_t lock;

page_t *create_page_and_node(size_t size_requested);
void *add_new_page_and_node(size_t size_requested);

node_t *add_new_node(node_t *node, size_t free_space, size_t size_requested);
void init_node(node_t *node, size_t size_requested);

size_t get_free_space(void *final_adrress, void *last_address);
void update_free_space(page_t *page);

void *get_addr(void *addr, size_t offset);

void display_memory(page_t *page, size_t size);

void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *node);

#endif // _MALLOC_H
