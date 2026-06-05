#ifndef CODEXION_H
# define CODEXION_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <sys/time.h>
# include <pthread.h>

int is_num(char *av);
int parser_input(int ac, char **av);
long long get_time_ms(void);

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

typedef struct s_dongle
{
    // pthread_mutex_t mutex;
    // pthread_cond_t  cond;
    int             available;
    long long       cooldown_until;
} t_dongle;

typedef struct s_coder
{
    int id;
    int compiles_done;
    long long last_compile_start;
    t_config *cfg;
    // t_dongle *left_dongle;
    // t_dongle *right_dongle;
} t_coder;

typedef struct s_sim
{
    t_config cfg;
    t_coder *coders;
    t_dongle *dongles;
    //pthread_t *coder_threads;
    //pthread_t monitor_thread;
    //pthread_mutex_t log_mutex;
    int simulation_running;
    long long start_time;
    // Talvez um mutex para simulation_running
    // Estruturas para o scheduler global? 
    // Mas como cada dongle tem sua fila, não precisa de scheduler global.
} t_sim;

#endif