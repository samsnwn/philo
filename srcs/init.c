#include "../includes/philo.h"

void data_init(t_table *table)
{
  int i;

  i = -1;
  table->end_simulation = FALSE;
  table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
  table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
  while (++i < table->philo_nbr)
  {
    safe_mutex_handle(&table->forks[i].fork, INIT);
  }

}