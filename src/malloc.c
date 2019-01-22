/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** Source file of the malloc function
*/

#include <stdlib.h>
#include "page.h"

void *malloc(size_t size)
{
    void *address = NULL;
    bool done = false;

    if (head == NULL)
        head = new_page(0);
    address = check_free_list(size);
    if (address != NULL)
        return address;
    address = check_allocated_list(size);
    if (address == NULL)
        address = allocate_new_page_and_node(size);
    return (address);
}