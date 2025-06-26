/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:48 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 12:48:18 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(t_state state, t_philosopher *philo)
{
	long	elapsed;

	elapsed = (get_current_time() - philo->sim->start_time) / 1000;
	if (get_bool(&philo->lock, &philo->is_full))
		return ;
	handle_mutex(&philo->sim->output_lock, LOCK);
	if ((state == TAKE_LEFT_FORK || state == TAKE_RIGHT_FORK)
		&& !simulation_ended(philo->sim))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (state == EATING && !simulation_ended(philo->sim))
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if (state == SLEEPING && !simulation_ended(philo->sim))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (state == THINKING && !simulation_ended(philo->sim))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (state == DIED)
		printf("%ld %d died\n", elapsed, philo->id);
	handle_mutex(&philo->sim->output_lock, UNLOCK);
}
