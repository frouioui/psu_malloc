/*
** EPITECH PROJECT, 2019
** malloc
** File description:
** Main file of the malloc fuctions
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

const size_t MIN_PAGES = 512;

void *get_addr(void *addr, size_t offset)
{
    char *new_add = (char *)addr;

    new_add += offset;
    return ((void *)new_add);
}

void init_node(node_t *node, size_t size_requested)
{
    char *tmp_add = NULL;

    node->size = size_requested;
    node->data = (void *)(node + 1);
    node->used = true;
    node->next = NULL;
    tmp_add = get_addr(node->data, size_requested);
    node->next_node_addr = (void *)(tmp_add);
}

size_t get_free_space(void *final_adrress, void *last_address)
{
    return ((char *)final_adrress - (char *)last_address);
}

page_t *create_page_and_node(size_t size_requested)
{
    page_t *page = NULL;
    size_t page_size = getpagesize() * MIN_PAGES;

    while (page_size < size_requested + sizeof(page_t))
        page_size += getpagesize();
    page = sbrk(page_size);
    page->size = page_size;
    page->full = false;
    page->next = NULL;
    page->next_page_addr = get_addr(page, page->size);
    page->node = get_addr(page, sizeof(page_t));
    init_node(page->node, size_requested);
    page->free_space = get_free_space(page->next_page_addr,
        page->node->next_node_addr);
    return (page);
}

void *add_new_page_and_node(size_t size_requested)
{
    page_t *index = head;

    while (index != NULL && index->next != NULL)
        index = index->next;
    if (index != NULL)
        index->next = create_page_and_node(size_requested);
    return (index->next->node->data);
}

node_t *init_new_node(node_t *previous, size_t size_requested)
{
    node_t *new_node = NULL;

    if (!previous)
        return (NULL);
    new_node = previous->next_node_addr;
    init_node(new_node, size_requested);
    return (new_node);
}

void split_node(node_t *node, size_t size_node_a)
{
    node_t *new = node->next_node_addr;

    init_node(node, node->size - size_node_a - sizeof(node_t));
    new->next = node->next;
    new->used = false;
    node->next = new;
    node->size = size_node_a;
}

node_t *add_new_node(node_t *node, size_t free_space, size_t size_requested)
{
    node_t *tmp = node;

    if (size_requested + sizeof(node_t) > free_space) {
        return (NULL);
    }
    while (tmp && tmp->next) {
        if (!tmp->used && size_requested + sizeof(node_t) <= tmp->size) {
            split_node(tmp, size_requested);
            return (tmp);
        } else if (tmp->used == false && size_requested <= tmp->size) {
            tmp->used = true;
            return (tmp);
        }
        tmp = tmp->next;
    }
    if (tmp && !tmp->next) {
        tmp->next = init_new_node(tmp, size_requested);
        return (tmp->next);
    }
    return (NULL);
}

void update_free_space(page_t *page)
{
    node_t *index = page->node;

    while (index && index->next)
        index = index->next;
    page->free_space = get_free_space(page->next_page_addr,
        index->next_node_addr);
    if (page->free_space <= sizeof(node_t) + ALIGN(1))
        page->full = true;
}