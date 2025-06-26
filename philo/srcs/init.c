/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:10 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 12:55:06 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	assign_utensils(t_philosopher *philo,
		t_utensil *utensils, int position)
{
	int	nbr_philo;
	int	left_id;
	int	right_id;

	nbr_philo = philo->sim->philo_count;
	left_id = position;
	right_id = (position + 1) % nbr_philo;
	if (left_id < right_id)
	{
		philo->first_utensil = &utensils[left_id];
		philo->second_utensil = &utensils[right_id];
	}
	else
	{
		philo->first_utensil = &utensils[right_id];
		philo->second_utensil = &utensils[left_id];
	}
}

static void	init_philosophers(t_sim *sim)
{
	int				i;
	t_philosopher	*philo;

	i = -1;
	while (++i < sim->philo_count)
	{
		philo = sim->philosophers + i;
		philo->id = i + 1;
		philo->sim = sim;
		handle_mutex(&philo->lock, INIT);
		set_long(&philo->lock, &philo->meals_eaten, 0);
		set_bool(&philo->lock, &philo->is_full, FALSE);
		assign_utensils(philo, sim->utensils, i);
	}
}

void	init_sim(t_sim *sim)
{
	int	i;

	i = -1;
	sim->is_over = FALSE;
	sim->all_ready = FALSE;
	sim->running_threads = 0;
	sim->philosophers = Malloc(sizeof(t_philosopher) * sim->philo_count);
	handle_mutex(&sim->sim_lock, INIT);
	handle_mutex(&sim->output_lock, INIT);
	sim->utensils = Malloc(sizeof(t_utensil) * sim->philo_count);
	while (++i < sim->philo_count)
	{
		handle_mutex(&sim->utensils[i].lock, INIT);
		sim->utensils[i].id = i;
	}
	init_philosophers(sim);
}
