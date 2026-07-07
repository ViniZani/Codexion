/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzani-st <vzani-st@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:51:37 by vzani-st          #+#    #+#             */
/*   Updated: 2026/06/09 11:51:48 by vzani-st         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

int						is_num(char *av);
int						parser_input(int ac, char **av);
long long				get_time_ms(void);
typedef struct s_coder	t_coder;

typedef struct s_sim	t_sim;
typedef struct s_config
{
	int					num_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					num_compiles_req;
	int					dongle_cooldown;
	int					scheduler;
}						t_config;

typedef struct s_dongle
{
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
	int					available;
	long long			cooldown_until;
	t_coder				*queue[64];
	int					queue_size;
}						t_dongle;

typedef struct s_coder
{
	int					id;
	int					compiles_done;
	long long			last_compile_start;
	t_config			*cfg;
	t_sim				*sim;
	t_dongle			*dongle;
	pthread_cond_t		wait_cond;
}						t_coder;

typedef struct s_sim
{
	t_config			cfg;
	t_coder				*coders;
	t_dongle			*dongles;
	pthread_t			*coder_threads;
	pthread_t			monitor_thread;
	pthread_mutex_t		log_mutex;
	int					simulation_running;
	long long			start_time;
}						t_sim;
void					*coder_routine(void *arg);
void					take_dongle(t_dongle *dongle, t_sim *sim,
							t_coder *coder);
void					release_dongle(t_dongle *dongle, t_config *cfg);
void					log_state(t_coder *coder, char *msg);
int						sleep_checking(t_sim *sim, int ms);
struct timespec			ms_to_timespec(long ms_from_now);
void					cleanup_sim(t_sim *sim);
void					fifo_enqueue(t_dongle *dongle, t_coder *coder);
t_coder					*fifo_dequeue(t_dongle *dongle);
void					edf_enqueue(t_dongle *dongle, t_coder *coder);
t_coder					*edf_dequeue(t_dongle *dongle);
void					dequeue(t_dongle *dongle, int scheduler);
void					enqueue(t_dongle *dongle, t_coder *coder,
							int scheduler);
#endif
