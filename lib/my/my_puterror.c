/*
** EPITECH PROJECT, 2019
** my_puterror.c
** File description:
** my_puterror
*/

#include <unistd.h>

void my_puterrorchar(char c)
{
    write(2, &c, 1);
}

int my_puterror(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        my_puterrorchar(str[i]);
        i++;
    }
    return (0);
}
