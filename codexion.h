#ifndef CODEXION_H
# define CODEXION_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>

int is_num(char *av);
int parser_input(int ac, char **av);

typedef struct s_config
{
    int num_coders;
    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;
    int num_compiles_req;
    int dongle_cooldown;
    char *scheduler;
} t_config;

typedef struct s_sim
{
    t_config cfg;
    //t_coder *coders;
    //t_dongle *dongles;
    //pthread_t *coder_threads;
    //pthread_t monitor_thread;
    //pthread_mutex_t log_mutex;
    int simulation_running;
    // Talvez um mutex para simulation_running (ou use atomics)
    // Estruturas para o scheduler global? 
    // Mas como cada dongle tem sua fila, não precisa de scheduler global.
} t_sim;

#endif