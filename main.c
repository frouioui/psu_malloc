/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** main test file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>

struct toto_s {
    int c;
    int b;
};

int main(int argc, char const *argv[])
{
    printf("%d\n", getpagesize());
    return (0);
}
