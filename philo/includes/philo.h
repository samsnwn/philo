/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:31:46 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 13:09:48 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define TRUE 1
# define FALSE 0
# define DESYNC_DELAY_USEC 30000
# define THINKING_SCALE_FACTOR 0.42
# define MIN_TIME_THRESHOLD_USEC 60000
# define SLEEP_INTERVAL_USEC 100
# define USLEEP_THRESHOLD_USEC 1000

typedef struct s_sim	t_sim;

typedef enum e_op
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
}	t_op;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DIED
}	t_state;

typedef struct s_utensil
{
	pthread_mutex_t		lock;
	int					id;
}	t_utensil;

typedef struct s_philosopher
{
	int				id;
	long			meals_eaten;
	int				is_full;
	long			last_meal;
	pthread_mutex_t	lock;
	pthread_t		thread;
	t_utensil		*first_utensil;
	t_utensil		*second_utensil;
	t_sim			*sim;
}		t_philosopher;

typedef struct s_sim
{
	long			philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_limit;
	long			start_time;
	int				is_over;
	int				all_ready;
	long			running_threads;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	output_lock;
	pthread_t		watcher;
	t_utensil		*utensils;
	t_philosopher	*philosophers;
}		t_sim;

// Core functions
void	parse_args(t_sim *sim, char **argv);
void	init_sim(t_sim *sim);
void	run_sim(t_sim *sim);
void	cleanup_sim(t_sim *sim);

// Philosopher actions
void	eat_meal(t_philosopher *philo);
void	think(t_philosopher *philo, int pre_sim);
void	sleep_philo(long usec, t_sim *sim);

// Thread and mutex handlers
void	handle_thread(pthread_t *thread, void *(*func)(void *),
			void *data, t_op op);
void	handle_mutex(pthread_mutex_t *mutex, t_op op);

// Utility functions
void	exit_error(char *error);
void	*Malloc(size_t bytes);
long	parse_long(char *str);
long	get_current_time(void);
void	print_state(t_state state, t_philosopher *philo);
void	cleanup_sim(t_sim *sim);

// Data access functions
void	set_bool(pthread_mutex_t *mutex, int *dest, int value);
int		get_bool(pthread_mutex_t *mutex, int *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	increment_long(pthread_mutex_t *mutex, long *value);

// Synchronization utilities
void	*watch_philosophers(void *data);
void	wait_for_ready(t_sim *sim);
int		all_threads_running(pthread_mutex_t *mutex,
			long *threads, long philo_count);
void	desync_philosophers(t_philosopher *philo);
int		simulation_ended(t_sim *sim);

#endif
