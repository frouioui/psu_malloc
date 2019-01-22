/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc_bootstrap
** File description:
** Source file containing the basic function
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *malloc(size_t size)
{
    (void)size;
    write(1, "c", 1);
    return NULL;
}