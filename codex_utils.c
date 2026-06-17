/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzani-st <vzani-st@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:55:44 by vzani-st          #+#    #+#             */
/*   Updated: 2026/06/09 12:01:26 by vzani-st         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	take_dongle(t_dongle *dongle, t_sim *sim)
{
	pthread_mutex_lock(&dongle->mutex);
	while (!dongle->available)
	{
		if (!sim->simulation_running)
		{
			pthread_mutex_unlock(&dongle->mutex);
			return ;
		}
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	dongle->available = 0;
	pthread_mutex_unlock(&dongle->mutex);
}

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->available = 1;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

void	log_state(t_coder *coder, char *msg)
{
	long long	elapsed;

	elapsed = get_time_ms() - coder->sim->start_time;
	pthread_mutex_lock(&coder->sim->log_mutex);
	printf("%lld %d %s\n", elapsed, coder->id, msg);
	pthread_mutex_unlock(&coder->sim->log_mutex);
}
int	sleep_checking(t_sim *sim, int ms)
{
	int	slept;

	slept = 0;
	while (slept < ms && sim->simulation_running)
	{
		usleep(1000);
		slept++;
	}
	if (sim->simulation_running == 0)
		return (1);
	return(0);
}
