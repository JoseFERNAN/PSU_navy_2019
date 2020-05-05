/*
** EPITECH PROJECT, 2019
** my_printf_base.c
** File description:
** my_printf_base
*/

#include <stdlib.h>
#include <stdarg.h>
#include "../../include/my.h"

void print_octal(va_list argv)
{
    my_put_dec_to_octal(va_arg(argv, int));
}

void print_binaire(va_list argv)
{
    my_put_dec_to_bin(va_arg(argv, int));
}

void print_hexa(va_list argv)
{
    my_put_dec_to_hexa(va_arg(argv, int));
}

void print_HEXA(va_list argv)
{
    my_put_dec_to_HEXA(va_arg(argv, int));
}