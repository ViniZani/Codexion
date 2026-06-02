#include "codexion.h"

int main(int ac, char **av)
{
    if (ac != 9)
    {
        printf("%s", "Error: parameter must be exaclty 8");
        return (1);
    }
    if (atoi(av[1]) <= 0)
    {
        printf("%s", "Error: num_coders must be a positive int");
        return (1);
    }
        if (atoi(av[6]) <= 0)
    {
        printf("%s", "Error: num_of_compiles must be a positive int");
        return (1);
    }
    int number_of_coders = atoi(av[1]);
    //time_to_burnout = av[2];
    //time_to_compile = av[3];
    //time_to_debug = av[4];
    //time_to_refactor = av[5];
    int number_of_compiles_req = atoi(av[6]);
    //dongle_cd = av[7];
    //scheduler = av[8];
    printf("deu certo o num_coders: %i", number_of_coders);
    return number_of_coders;
}