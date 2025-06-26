/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:33 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 12:50:15 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*single_philosopher(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	wait_for_ready(philo->sim);
	set_long(&philo->lock, &philo->last_meal, get_current_time());
	increment_long(&philo->sim->sim_lock, &philo->sim->running_threads);
	print_state(TAKE_LEFT_FORK, philo);
	while (!simulation_ended(philo->sim))
		usleep(200);
	return (NULL);
}

void	*philosopher_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	wait_for_ready(philo->sim);
	set_long(&philo->lock, &philo->last_meal, get_current_time());
	increment_long(&philo->sim->sim_lock, &philo->sim->running_threads);
	desync_philosophers(philo);
	while (!simulation_ended(philo->sim))
	{
		if (get_bool(&philo->lock, &philo->is_full))
			break ;
		eat_meal(philo);
		print_state(SLEEPING, philo);
		sleep_philo(philo->sim->time_to_sleep, philo->sim);
		think(philo, FALSE);
	}
	return (NULL);
}

void	run_sim(t_sim *sim)
{
	int	i;

	i = -1;
	if (sim->philo_count == 0)
		return ;
	else if (sim->philo_count == 1)
		handle_thread(&sim->philosophers[0].thread, single_philosopher,
			&sim->philosophers[0], CREATE);
	else
	{
		while (++i < sim->philo_count)
			handle_thread(&sim->philosophers[i].thread,
				philosopher_routine, &sim->philosophers[i], CREATE);
	}
	handle_thread(&sim->watcher, watch_philosophers, sim, CREATE);
	sim->start_time = get_current_time();
	set_bool(&sim->sim_lock, &sim->all_ready, TRUE);
	i = -1;
	while (++i < sim->philo_count)
		handle_thread(&sim->philosophers[i].thread, NULL, NULL, JOIN);
	set_bool(&sim->sim_lock, &sim->is_over, TRUE);
	handle_thread(&sim->watcher, NULL, NULL, JOIN);
}
