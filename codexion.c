/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzani-st <vzani-st@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:55:57 by vzani-st          #+#    #+#             */
/*   Updated: 2026/06/09 11:55:59 by vzani-st         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
void	launch_simulation(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->cfg.num_coders)
	{
		pthread_create(&sim->coder_threads[i], NULL,
			coder_routine, &sim->coders[i]);
		i++;
	}
	i = 0;
	while (i < sim->cfg.num_coders)
	{
		pthread_join(sim->coder_threads[i], NULL);
		i++;
	}
}

void	take_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	while (!dongle->available)
	{
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	dongle->available = 0;
	pthread_mutex_unlock(&dongle->mutex);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (coder->sim->simulation_running)
	{
		// 1. pegar dongles
		take_dongle(&coder->sim->dongles[coder->id]);
		take_dongle(&coder->sim->dongles[(coder->id + 1)
			% coder->cfg->num_coders]);
		// 2. compilar (usleep)
		// 3. soltar dongles
		// 4. debugar (usleep)
		// 5. refatorar (usleep)
		// 6. incrementar compiles_done
	}
	return (NULL);
}

void	initialize_sim(t_sim *sim)
{
	int	i;

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
		sim->coders[i].sim = sim;
		pthread_mutex_init(&sim->dongles[i].mutex, NULL);
		pthread_cond_init(&sim->dongles[i].cond, NULL);
		i++;
	}
	sim->coder_threads = malloc(sizeof(pthread_t) * sim->cfg.num_coders);
	pthread_mutex_init(&sim->log_mutex, NULL);
	sim->simulation_running = 1;
}

int	main(int ac, char **av)
{
	t_sim		*sim;
	long long	elapsed;

	if (parser_input(ac, av) == 1)
		return (1);
	sim = malloc(sizeof(t_sim));
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
	elapsed = get_time_ms() - sim->start_time;
	coder_routine(sim);
	launch_simulation(sim);
	return (0);
}
/*
printf("%lld %d is compiling\n", elapsed, sim->coders->id);
printf("num_coders: %d\n", sim->cfg.num_coders);
printf("time_to_burnout: %d ms\n", sim->cfg.time_to_burnout);
printf("time_to_compile: %d ms\n", sim->cfg.time_to_compile);
printf("time_to_debug: %d ms\n", sim->cfg.time_to_debug);
printf("time_to_refactor: %d ms\n", sim->cfg.time_to_refactor);
printf("num_compiles_req: %d\n", sim->cfg.num_compiles_req);
printf("dongle_cooldown: %d ms\n", sim->cfg.dongle_cooldown);
printf("scheduler: %s\n", (sim->cfg.scheduler));*/