/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:19 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 11:32:20 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_sim	sim;

	if (argc == 5 || argc == 6)
	{
		parse_args(&sim, argv);
		init_sim(&sim);
		run_sim(&sim);
		cleanup_sim(&sim);
	}
	else
		exit_error("Invalid number of arguments");
	return (0);
}
