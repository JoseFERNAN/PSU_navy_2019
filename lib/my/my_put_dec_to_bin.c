/*
** EPITECH PROJECT, 2019
** my_dec_to_octal.c
** File description:
** my_dec_to_octal
*/

#include <unistd.h>

void my_putchar(char);

void my_put_dec_to_bin(int nb)
{
    if (nb >= 2) {
        my_put_dec_to_bin(nb / 2);
        my_putchar(nb % 2 + 48);
    } else {
        my_putchar(nb % 2 + 48);
    }
}
