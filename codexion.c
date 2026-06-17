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

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	int		i;
	int		all_done;
	long long	elapsed;

	sim = (t_sim *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->cfg.num_coders)
		{
			elapsed = get_time_ms() - sim->coders[i].last_compile_start;
			if (elapsed > sim->cfg.time_to_burnout)
			{
				pthread_mutex_lock(&sim->log_mutex);
				printf("%lld %d burned out\n",
					get_time_ms() - sim->start_time, sim->coders[i].id);
				pthread_mutex_unlock(&sim->log_mutex);
				sim->simulation_running = 0;
				return (NULL);
			}
			i++;
		}
		all_done = 1;
		i = 0;
		while (i < sim->cfg.num_coders)
		{
			if (sim->coders[i].compiles_done < sim->cfg.num_compiles_req)
			{
				all_done = 0;
				break ;
			}
			i++;
		}
		if (all_done)
		{
			sim->simulation_running = 0;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
void	launch_simulation(t_sim *sim)
{
	int	i;

	pthread_create(&sim->monitor_thread, NULL, monitor_routine, sim);
	i = 0;
	while (i < sim->cfg.num_coders)
	{
		pthread_create(&sim->coder_threads[i], NULL, coder_routine,
			&sim->coders[i]);
		i++;
	}
	i = 0;
	while (i < sim->cfg.num_coders)
	{
		pthread_join(sim->coder_threads[i], NULL);
		i++;
	}
	pthread_join(sim->monitor_thread, NULL);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	t_sim *sim;

	coder = (t_coder *)arg;
	sim = (t_sim *)arg;
	while (coder->sim->simulation_running)
	{
		take_dongle(&coder->sim->dongles[coder->id - 1], sim);
		log_state(coder, "has taken a dongle");
		take_dongle(&coder->sim->dongles[(coder->id) % coder->cfg->num_coders], sim);
		log_state(coder, "has taken a dongle");
		coder->last_compile_start = get_time_ms();
		log_state(coder, "is compiling");
		if (!sleep_checking(coder->sim, coder->cfg->time_to_compile))
    		break;
		release_dongle(&coder->sim->dongles[coder->id - 1]);
		release_dongle(&coder->sim->dongles[(coder->id)
			% coder->cfg->num_coders]);
		log_state(coder, "is debugging");
		if (!sleep_checking(coder->sim, coder->cfg->time_to_compile))
    		break;
		log_state(coder, "is refactoring");
		if (!sleep_checking(coder->sim, coder->cfg->time_to_compile))
    		break;
		coder->compiles_done++;
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
	t_sim	*sim;

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
	launch_simulation(sim);
	return (0);
}
