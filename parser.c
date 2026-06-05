#include "codexion.h"

int is_num(char *av)
{
    int i;
    i = 0; 
    while (av[i] != '\0')
        {
            if(av[i] < '0' || av[i] > '9')
            {
                return (1);
            }
            i++;
        }
    return (0);
}

int parser_input(int ac, char **av)
{
    if (ac != 9)
    {
        printf("%s", "Error: parameter must be exaclty 8");
        return (1);
    }
    if (is_num(av[1]) != 0 || atoi(av[1]) <= 0)
    {
        printf("%s", "Error: num_coders must be a positive int");
        return (1);
    }
    if (is_num(av[2]) != 0 || atoi(av[2]) <= 0)
    {
        printf("%s", "Error: time_to_burnout must be a positive int");
        return (1);
    }
    if (is_num(av[3]) != 0 || atoi(av[3]) <= 0)
    {
        printf("%s", "Error: time_to_compile must be a positive int");
        return (1);
    }
    if (is_num(av[4]) != 0 || atoi(av[4]) <= 0)
    {
        printf("%s", "Error: time_to_debug must be a positive int");
        return (1);
    }
    if (is_num(av[5]) != 0 || atoi(av[5]) <= 0)
    {
        printf("%s", "Error: time_to_refactor must be a positive int");
        return (1);
    }
    if (is_num(av[6]) != 0 || atoi(av[6]) <= 0)
    {
        printf("%s", "Error: num_of_compiles must be a positive int");
        return (1);
    }
    if (is_num(av[7]) != 0 || atoi(av[7]) < 0)
    {
        printf("%s", "Error: dongle_cooldown must be a positive int");
        return (1);
    }
    if (strcmp(av[8], "fifo") != 0 && strcmp(av[8], "edf") != 0)
    {
        printf("%s", "Error: scheduler must be 'fifo' or 'edf'");
        return (1);
    }
    return (0);
}