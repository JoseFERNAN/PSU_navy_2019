/*
** EPITECH PROJECT, 2020
** My Hunter
** File description:
** Windows related function
*/

#include "include/my.h"

int other_pid = 0;

char *read_line(void)
{
    char *buffer = malloc(sizeof(char) * 10);
    int size = 0;

    size = read(0, buffer, 10);
    return (buffer);
}

void get_pid(int sig, siginfo_t *info, void *context)
{
    other_pid = info->si_pid;
}

void player_one_connect(char **av)
{
    struct sigaction sa;

    my_printf("my_pid: %i\n", getpid());
    my_printf("waiting for enemy connection...\n");
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = get_pid;
    sigaction(SIGUSR1, &sa, NULL);
    pause();
    my_printf("\nenemy connected\n");
}

void player_two_connect(char **av)
{
    my_printf("my_pid: %i\n", getpid());
    if (kill(my_atoi(av[1]), SIGUSR1) < 0)
        exit(0);
    my_printf("successfully connected\n\n");
    other_pid = my_atoi(av[1]);
}

int exec1(int state)
{
    static int usr1 = 0;

    if (state == 0)
        usr1 = 0;
    if (state == 1)
        usr1 += 1;
    if (state == 2)
        return (usr1);
    return (0);
}

int exec2(int state)
{
    static int usr2 = 0;

    if (state == 0)
        usr2 = 0;
    if (state == 1)
        usr2 += 1;
    if (state == 2)
        return (usr2);
    return (0);
}

void signal_handler(int sig)
{
    if (sig == SIGUSR1)
        exec1(1);
    if (sig == SIGUSR2)
        exec2(1);
}

player_t player_1_turn(player_t player)
{
    static char *hit;

    my_printf("attack: ");
    hit = read_line();
    if  (hit[0] < 'A' || hit[0] > 'H' || hit[1] < '1' || hit[1] > '8' || hit[2] != '\n') {
        my_printf("wrong position\n");
        player_1_turn(player);
        return (player);
    }
    hit[2] = '\0';
    for (int i = 0; i < hit[0]-64; i++) {
        kill(other_pid, SIGUSR1);
        usleep(10);
    }
    kill(other_pid, SIGUSR2);
    usleep(10);
    for (int i = 0; i < hit[1]-48; i++) {
        kill(other_pid, SIGUSR1);
        usleep(10);
    }
    kill(other_pid, SIGUSR2);
    usleep(10);
    while (exec2(2) != 1 && exec1(2) != 1);
    if (exec2(2) == 1) {
        my_printf("%c%c: missed\n\n", hit[0], hit[1]);
        if (player.map2[hit[1]-49][hit[0]-65] != 'x')
            player.map2[hit[1]-49][hit[0]-65] = 'o';
    } else {
        my_printf("%c%c: hit\n\n", hit[0], hit[1]);
        player.map2[hit[1]-49][hit[0]-65] = 'x';
    }
    usleep(10);
    exec2(0);
    exec1(0);
    return (player);
}

player_t player_2_turn(player_t player)
{
    static char *hit = NULL;

    if (hit == NULL) {
        hit = malloc(sizeof(char) * 100);
        my_memset(hit, 0, 100);
    }
    my_printf("waiting for enemy's attack...\n");
    while (exec2(2) != 2) {
        if (exec2(2) == 0)
            hit[0] = exec1(2);
        if (exec2(2) == 1)
            hit[1] = exec1(2) - hit[0];
    }
    usleep(10);
    if (player.map1[hit[1]-1][hit[0]-1] == '.') {
        kill(other_pid, SIGUSR2);
        my_printf("%c%c: missed\n\n", hit[0]+64, hit[1]+48);
        player.map1[hit[1]-1][hit[0]-1] = 'o';
    } else if (player.map1[hit[1]-1][hit[0]-1] <= '1' || player.map1[hit[1]-1][hit[0]-1] >= '8') {
        kill(other_pid, SIGUSR2);
        my_printf("%c%c: missed\n\n", hit[0]+64, hit[1]+48);
    } else {
        kill(other_pid, SIGUSR1);
        my_printf("%c%c: hit\n\n", hit[0]+64, hit[1]+48);
        player.map1[hit[1]-1][hit[0]-1] = 'x';
    }
    usleep(10);
    exec2(0);
    exec1(0);
    return (player);
}

int check_map_condition(char **map)
{
    int index = 0;

    for (int i = 0; i < 8; i += 1) {
        for (int j = 0; j < 8; j += 1) {
            if (map[i][j] == 'x')
                index += 1;
        }
    }
    if (index == 3)
        return (1);
    return (0);
}

int win_condition(player_t player)
{
    if (check_map_condition(player.map1) == 1) {
        my_printf("Enemy won\n");
        return (1);
    } else if (check_map_condition(player.map2) == 1) {
        my_printf("I won\n");
        return (0);
    }
    return (2);
}

int main(int ac, char **av)
{
    player_t player;
    int ret = 0;

    if (ac == 2) {
        if ((player.map1 = init_map(av[1])) == NULL)
            return (84);
        player_one_connect(av);
        player.ID = 1;
    } else if (ac == 3) {
        if ((player.map1 = init_map(av[2])) == NULL)
            return (84);
        if (my_atoi(av[1]) <= 0)
            return (84);
        player_two_connect(av);
        player.ID = 2;
    } else {
        return (84);
    }
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    player.map2 = init_map(NULL);
    while (1) {
        my_printf("my positions:\n");
        display_map(player.map1);
        my_printf("\nenemy's positions:\n");
        display_map(player.map2);
        my_printf("\n");
        if ((ret = win_condition(player)) != 2)
            return (ret);
        if (player.ID == 1) {
            player = player_1_turn(player);
            player = player_2_turn(player);
        }
        if (player.ID == 2) {
            player = player_2_turn(player);
            player = player_1_turn(player);
        }
    }
    return (0);
}