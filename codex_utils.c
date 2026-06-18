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

struct timespec ms_to_timespec(long ms_from_now)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	struct timespec ts;
	ts.tv_sec = tv.tv_sec + ms_from_now / 1000;
	ts.tv_nsec = (tv.tv_usec * 1000) + (ms_from_now % 1000) * 1000000;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec += 1;
		ts.tv_nsec -= 1000000000;
	}
	return ts;
}
long long	get_time_ms(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	take_dongle(t_dongle *dongle, t_sim *sim)
{
	pthread_mutex_lock(&dongle->mutex);
	struct timespec ts;
	while (!dongle->available || get_time_ms() < dongle->cooldown_until)
	{
		if (!sim->simulation_running)
		{
			pthread_mutex_unlock(&dongle->mutex);
			return ;
		}
		if (get_time_ms() < dongle->cooldown_until)
		{
			ts = ms_to_timespec(dongle->cooldown_until - get_time_ms());
			pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
		}
		else{
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
		}
	}
	dongle->available = 0;
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
	return(1);
}