/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:45 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 11:32:45 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	exit_error(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	*Malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		exit_error("Memory allocation failed");
	return (ptr);
}

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_error("Failed to get time");
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

int	simulation_ended(t_sim *sim)
{
	return (get_bool(&sim->sim_lock, &sim->is_over));
}

void	cleanup_sim(t_sim *sim)
{
	int				i;
	t_philosopher	*philo;

	i = -1;
	while (++i < sim->philo_count)
	{
		philo = sim->philosophers + i;
		handle_mutex(&philo->lock, DESTROY);
		handle_mutex(&sim->utensils[i].lock, DESTROY);
	}
	handle_mutex(&sim->sim_lock, DESTROY);
	handle_mutex(&sim->output_lock, DESTROY);
	free(sim->philosophers);
	free(sim->utensils);
}
