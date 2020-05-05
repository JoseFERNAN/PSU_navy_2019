/*
** EPITECH PROJECT, 2020
** My Hunter
** File description:
** Windows related function
*/

#include "include/my.h"

char *read_map(char *path)
{
    struct stat sd;
    char *buffer;
    int fd;

    if (stat(path, &sd) == -1)
        exit(84);
    buffer = malloc(sizeof(char) * (sd.st_size + 1));
    my_memset(buffer, 0, sd.st_size + 1);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (NULL);
    read(fd, buffer, sd.st_size + 1);
    close(fd);
    return (buffer);
}

char *clean_str_pos(char *str)
{
    for (int j = 0; str[j]; j++)
        if (str[j] >= 'A' && str[j] <= 'Z')
            str[j] -= 16;
    return (str);
}

void drop_navy_on_map(char **map, char **arr)
{
    for (int i = 0; arr[i] != NULL; i += 3) {
        for (int j = 0; j < arr[i][0]-48; j++) {
            if (arr[i+1][0] == arr[i+2][0]) {
                map[arr[i+1][1]-49+j][arr[i+1][0]-49] = arr[i][0];
            } else {
                map[arr[i+1][1]-49][arr[i+1][0]-49+j] = arr[i][0];
            }
        }
    }
}

void display_map(char **map)
{
    my_printf(" |A B C D E F G H\n");
    my_printf("-+---------------\n");
    for (int i = 0; i < 8; i++) {
        my_printf("%i|", i+1);
        for (int j = 0; j < 8; j++) {
            my_printf("%c", map[i][j]);
            if (j < 7)
                my_printf(" ");
        }
        my_printf("\n");
    }
}

char **init_map(char *path)
{
    char **map = malloc(sizeof(char *) * 8);
    char **arr;

    for (int i = 0; i < 8; i++)
        map[i] = malloc(sizeof(char) * 8);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            map[i][j] = '.';
    if (path == NULL)
        return (map);
    arr = my_str_to_word_array_char(read_map(path), ':');
    if (check_valid_map(read_map(path), arr) == 84)
        return (NULL);
    for (int i = 0; arr[i]; i++)
        arr[i] = clean_str_pos(arr[i]);
    drop_navy_on_map(map, arr);
    return (map);
}