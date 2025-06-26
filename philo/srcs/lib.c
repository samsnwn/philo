/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:14 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 13:09:26 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static long	convert_number(char *str)
{
	long	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
			exit_error("Value too large");
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

long	parse_long(char *str)
{
	int		len;
	char	*start;

	len = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		exit_error("Only positive numbers allowed");
	if (*str < '0' || *str > '9')
		exit_error("Not a digit");
	start = str;
	while (*str >= '0' && *str <= '9')
	{
		len++;
		str++;
	}
	if (len > 10)
		exit_error("Value too large");
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str)
		exit_error("Invalid characters after number");
	return (convert_number(start));
}
