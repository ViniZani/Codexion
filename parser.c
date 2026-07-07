/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzani-st <vzani-st@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:54:20 by vzani-st          #+#    #+#             */
/*   Updated: 2026/06/09 11:54:23 by vzani-st         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_num(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] < '0' || av[i] > '9')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	parser_input(int ac, char **av)
{
	int			i;
	const char	*params[] = {"num_coders", "time_to_burnout", "time_to_compile",
		"time_to_debug", "time_to_refactor", "num_of_compiles"};

	if (ac != 9)
		return (printf("Error: parameter must be exactly 8\n"), 1);
	i = 1;
	while (i <= 6)
	{
		if (is_num(av[i]) || atoi(av[i]) <= 0)
			return (printf("Error: %s must be a positive int\n", params[i - 1]),
				1);
		i++;
	}
	if (is_num(av[7]) || atoi(av[7]) < 0)
		return (printf("Error: dongle_cooldown must be a positive int\n"), 1);
	if (strcmp(av[8], "fifo") && strcmp(av[8], "edf"))
		return (printf("Error: scheduler must be 'fifo' or 'edf'\n"), 1);
	return (0);
}

void	cleanup_sim(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->cfg.num_coders)
	{
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
		i++;
	}
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_cond_destroy(&sim->coders[i].wait_cond);
	free(sim->coders);
	free(sim->dongles);
	free(sim->coder_threads);
}
