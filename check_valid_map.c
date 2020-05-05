/*
** EPITECH PROJECT, 2020
** My Hunter
** File description:
** Windows related function
*/

#include "include/my.h"

int check_valid_buffer(char *buff)
{
    int index = 0;

    if (my_strlen(buff) != 32)
        return (84);
    for (int i = 0; i < 32; i++) {
        index = i % 8;
        if ((index == 1 || index == 4) && buff[i] != ':')
            return (84);
        if ((index == 3 || index == 6) && (buff[i] < '1' || buff[i] > '8'))
            return (84);
        if ((index == 0) && (buff[i] < '2' || buff[i] > '5'))
            return (84);
        if ((index == 2 || index == 5) && (buff[i] < 'A' || buff[i] > 'H'))
            return (84);
        if ((index == 7) && (buff[i] != '\n'))
            return (84);
    }
    if (buff[0] + buff[8] + buff[16] + buff[24] - 4*48 != 14)
        return (84);
    return (0);
}

int check_valid_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; i += 3) {
        if ((arr[i+1][0] != arr[i+2][0]) && (arr[i+1][1] != arr[i+2][1]))
            return (84);
    }
    return (0);
}

char **check_boat_sizes(char *buff)
{
    char **map = my_str_to_word_array_char(buff, ':');
    map[13] = NULL;
    int x = map[5][0] - map[4][0] + 1;
    for (int i = 0; i <= 9; i += 3) {
        if (map[i+1][0] == map[i+2][0] && my_atoi(map[i]) != map[i+2][1] - map[i+1][1] + 1) {
            return (84);
        }
        if (map[i+1][1] == map[i+2][1]) {
            if(map[i+1][0] - map[i+2][0] + 1 != my_atoi(map[i]) && map[i+2][0] - map[i+1][0] + 1 != my_atoi(map[i])) {
                return (84);
            }
        }
    }
    return (0);
}

int check_valid_map(char *buff, char **arr)
{
    if (check_valid_buffer(buff) == 84)
        return (84);
    if (check_valid_arr(arr) == 84)
        return (84);
    if (check_boat_sizes(buff) == 84)
        return (84);
    return (0);
}