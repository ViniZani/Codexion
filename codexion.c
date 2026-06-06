#include "codexion.h"
void initialize_sim(t_sim *sim)
{
    int i;

    sim->coders = malloc(sizeof(t_coder) * sim->cfg.num_coders);
    if (!sim->coders)
        return ;
    sim->dongles = malloc(sizeof(t_dongle) * sim->cfg.num_coders);
    if (!sim->dongles)
        return ;
    i = 0;
    while (i < sim->cfg.num_coders)
    {

        sim->coders[i].id = i + 1;
        sim->coders[i].compiles_done = 0;
        sim->coders[i].last_compile_start = sim->start_time;
        sim->coders[i].cfg = &sim->cfg;

        sim->dongles[i].available = 1;
        sim->dongles[i].cooldown_until = 0;
        i++;
    }
}
int main(int ac, char **av)
{
    if (parser_input(ac, av) == 1)
        return (1);
    t_sim  *sim = malloc(sizeof(t_sim));
    if (!sim)
        return (1);
    sim->cfg.num_coders = atoi(av[1]);
    sim->cfg.time_to_burnout = atoi(av[2]);
    sim->cfg.time_to_compile = atoi(av[3]);
    sim->cfg.time_to_debug = atoi(av[4]);
    sim->cfg.time_to_refactor = atoi(av[5]);
    sim->cfg.num_compiles_req = atoi(av[6]);
    sim->cfg.dongle_cooldown = atoi(av[7]);
    sim->cfg.scheduler = av[8];
    sim->start_time = get_time_ms();
    initialize_sim(sim);
    // routine();
    long long elapsed = get_time_ms() - sim->start_time;
    printf("%lld %d is compiling\n", elapsed, sim->coders->id);
    printf("num_coders: %d\n", sim->cfg.num_coders);
    printf("time_to_burnout: %d ms\n", sim->cfg.time_to_burnout);
    printf("time_to_compile: %d ms\n", sim->cfg.time_to_compile);
    printf("time_to_debug: %d ms\n", sim->cfg.time_to_debug);
    printf("time_to_refactor: %d ms\n", sim->cfg.time_to_refactor);
    printf("num_compiles_req: %d\n", sim->cfg.num_compiles_req);
    printf("dongle_cooldown: %d ms\n", sim->cfg.dongle_cooldown);
    printf("scheduler: %s\n", (sim->cfg.scheduler));
    return (0);
}