#include "../includes/philo.h"

void parse_input(t_table *table, char **argv)
{
  table->nbr_philo = ft_atol(argv[1]);
  table->time_to_die = ft_atol(argv[2]) * 1000;
  table->time_to_eat = ft_atol(argv[3]) * 1000;
  table->time_to_sleep = ft_atol(argv[4]) * 1000;
  if (table->time_to_die < 6e3
    || table->time_to_eat < 6e3
    || table->time_to_sleep < 6e3)
      error_exit("Use timestamps mayor than 60ms");
  if (argv[5])
    table->nbr_limit_meals = ft_atol(argv[5]);
  else
    table->nbr_limit_meals = -1;
}