/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:40 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 12:49:00 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_for_ready(t_sim *sim)
{
	while (!get_bool(&sim->sim_lock, &sim->all_ready))
		usleep(SLEEP_INTERVAL_USEC);
}

int	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_count)
{
	int	response;

	response = FALSE;
	handle_mutex(mutex, LOCK);
	if (*threads == philo_count)
		response = TRUE;
	handle_mutex(mutex, UNLOCK);
	return (response);
}

void	desync_philosophers(t_philosopher *philo)
{
	if (philo->sim->philo_count % 2 == 0)
	{
		if (philo->id % 2 == 0)
			sleep_philo(DESYNC_DELAY_USEC, philo->sim);
	}
	else
	{
		if (philo->id % 2)
			think(philo, TRUE);
	}
}
