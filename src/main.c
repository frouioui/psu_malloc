/*
** EPITECH PROJECT, 2019
** PSU_MALLOC
** File description:
** Main function
*/

#include <stdio.h>
#include "page.h"

#include <pthread.h>
pthread_mutex_t lock;

int main(void)
{
    pthread_mutex_lock(&lock);

    page_t *page = new_page(0);

    page->node_allocated->data_addr = init_node(page->node_allocated, 10);
    page->node_allocated->next = my_sbrk(page->node_allocated);
    // fprintf(stdout, "%p\n", (void*)page->node_allocated);
    // fprintf(stdout, "%p\n", page->node_allocated->data_addr);

    pthread_mutex_unlock(&lock);

    return (0);
}