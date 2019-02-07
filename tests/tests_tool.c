/*
** EPITECH PROJECT, 2019
** PSU_Malloc
** File description:
** test file of the tool file
*/

#include <criterion/criterion.h>
#include "malloc.h"

Test(get_addr, check_value)
{
    void *ref = malloc(5);
    void *address = get_addr(ref, 2);

    cr_assert_eq(ref + 2, address);
}

Test(update_free, simple_check)
{
    page_t *page = malloc(sizeof(page_t));

    update_free_space(page);
}