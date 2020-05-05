/*
** EPITECH PROJECT, 2019
** my
** File description:
** My Header
*/

#include "include.h"

typedef struct player {
    int ID;
    char **map1;
    char **map2;
} player_t;

void my_printf(char *, ...);
void print_int(va_list);
void print_unsigned_int(va_list);
void print_modulo(va_list);
void print_pointer(va_list);
void print_octal(va_list);
void print_binaire(va_list);
void print_hexa(va_list);
void print_HEXA(va_list);
void print_str(va_list);
void print_car(va_list);
void my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr_unsigned(long int);
void my_put_dec_to_octal(int);
void my_put_dec_to_bin(int);
void my_put_dec_to_hexa(int);
void my_put_dec_to_HEXA(int);
int my_put_nbr(int nb);

int my_atoi(char const *);
char *my_itostr(int);
void my_memset(char *, int, int);
int my_strlen(char const *);
char **my_str_to_word_array_char(char *, char);
char **my_str_to_word_array(char *);
int my_strcmp(char const *, char const *);

char **init_map(char *path);
void display_map(char **map);
void drop_navy_on_map(char **map, char **arr);
char *clean_str_pos(char *str);
char *read_map(char *path);
int check_valid_map(char *buff, char **arr);
char **check_boat_sizes(char *buff);
