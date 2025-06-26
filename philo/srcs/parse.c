/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:26 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 12:51:04 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	parse_args(t_sim *sim, char **argv)
{
	sim->philo_count = parse_long(argv[1]);
	sim->time_to_die = parse_long(argv[2]) * 1000;
	sim->time_to_eat = parse_long(argv[3]) * 1000;
	sim->time_to_sleep = parse_long(argv[4]) * 1000;
	if (sim->time_to_die < MIN_TIME_THRESHOLD_USEC
		|| sim->time_to_eat < MIN_TIME_THRESHOLD_USEC
		|| sim->time_to_sleep < MIN_TIME_THRESHOLD_USEC)
		exit_error("Use timestamps greater than 60ms");
	if (argv[5])
		sim->meal_limit = parse_long(argv[5]);
	else
		sim->meal_limit = -1;
}
