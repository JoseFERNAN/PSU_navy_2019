/*
** EPITECH PROJECT, 2019
** my_dec_to_HEXA.c
** File description:
** my_dec_to_HEXA
*/

#include <unistd.h>

void my_putchar(char);

void my_put_dec_to_HEXA(int nb)
{
    if (nb >= 16) {
        my_put_dec_to_HEXA(nb / 16);
        if (nb % 16 >= 10)
            my_putchar(nb % 16 + 55);
        else
            my_putchar(nb % 16 + 48);
    } else {
        if (nb % 16 >= 10)
            my_putchar(nb % 16 + 55);
        else
            my_putchar(nb % 16 + 48);
    }
}
