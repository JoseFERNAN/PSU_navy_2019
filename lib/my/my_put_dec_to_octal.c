/*
** EPITECH PROJECT, 2019
** my_dec_to_octal.c
** File description:
** my_dec_to_octal
*/

#include <unistd.h>

void my_putchar(char);

void my_put_dec_to_octal(int nb)
{
    if (nb >= 8) {
        my_put_dec_to_octal(nb / 8);
        my_putchar(nb % 8 + 48);
    } else {
        my_putchar(nb % 8 + 48);
    }
}
