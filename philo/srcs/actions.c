/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:31:57 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/24 13:06:22 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_meal(t_philosopher *philo)
{
	handle_mutex(&philo->first_utensil->lock, LOCK);
	print_state(TAKE_LEFT_FORK, philo);
	handle_mutex(&philo->second_utensil->lock, LOCK);
	print_state(TAKE_RIGHT_FORK, philo);
	set_long(&philo->lock, &philo->last_meal, get_current_time());
	increment_long(&philo->lock, &philo->meals_eaten);
	print_state(EATING, philo);
	sleep_philo(philo->sim->time_to_eat, philo->sim);
	if (philo->sim->meal_limit > 0
		&& get_long(&philo->lock, &philo->meals_eaten)
		== philo->sim->meal_limit)
		set_bool(&philo->lock, &philo->is_full, TRUE);
	handle_mutex(&philo->second_utensil->lock, UNLOCK);
	handle_mutex(&philo->first_utensil->lock, UNLOCK);
}

void	sleep_philo(long usec, t_sim *sim)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_current_time();
	while (get_current_time() - start < usec)
	{
		if (simulation_ended(sim))
			break ;
		elapsed = get_current_time() - start;
		remaining = usec - elapsed;
		if (remaining > USLEEP_THRESHOLD_USEC)
			usleep(remaining / 2);
		else
		{
			while (get_current_time() - start < usec)
				usleep(SLEEP_INTERVAL_USEC);
		}
	}
}

void	think(t_philosopher *philo, int pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		print_state(THINKING, philo);
	if (philo->sim->philo_count % 2 == 0)
		return ;
	t_eat = philo->sim->time_to_eat;
	t_sleep = philo->sim->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	sleep_philo(t_think * THINKING_SCALE_FACTOR, philo->sim);
}
