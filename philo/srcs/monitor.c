/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:22 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 12:52:08 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philosopher_died(t_philosopher *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->lock, &philo->is_full))
		return (FALSE);
	elapsed = get_current_time()
		- get_long(&philo->lock, &philo->last_meal);
	time_to_die = philo->sim->time_to_die;
	if (elapsed > time_to_die)
		return (TRUE);
	return (FALSE);
}

void	*watch_philosophers(void *data)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)data;
	while (!all_threads_running(&sim->sim_lock,
			&sim->running_threads, sim->philo_count))
		usleep(SLEEP_INTERVAL_USEC);
	while (!simulation_ended(sim))
	{
		i = -1;
		while (++i < sim->philo_count && !simulation_ended(sim))
		{
			if (philosopher_died(sim->philosophers + i))
			{
				set_bool(&sim->sim_lock, &sim->is_over, TRUE);
				print_state(DIED, sim->philosophers + i);
			}
		}
	}
	return (NULL);
}
