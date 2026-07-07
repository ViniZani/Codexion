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

void	take_dongle(t_dongle *dongle, t_sim *sim, t_coder *coder)
{
	struct timespec	ts;

	pthread_mutex_lock(&dongle->mutex);
	enqueue(dongle, coder, sim->cfg.scheduler);
	while (!dongle->available || get_time_ms() < dongle->cooldown_until
		|| dongle->queue[0] != coder)
	{
		if (!sim->simulation_running)
		{
			pthread_mutex_unlock(&dongle->mutex);
			return ;
		}
		if (get_time_ms() < dongle->cooldown_until)
		{
			ts = ms_to_timespec(dongle->cooldown_until - get_time_ms());
			pthread_cond_timedwait(&coder->wait_cond, &dongle->mutex, &ts);
		}
		else
			pthread_cond_wait(&coder->wait_cond, &dongle->mutex);
	}
	if (!sim->simulation_running)
	{
		pthread_mutex_unlock(&dongle->mutex);
		return ;
	}
	dequeue(dongle, sim->cfg.scheduler);
	pthread_mutex_unlock(&dongle->mutex);
}

void	release_dongle(t_dongle *dongle, t_config *cfg)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->cooldown_until = get_time_ms() + cfg->dongle_cooldown;
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
		return (0);
	return (1);
}
