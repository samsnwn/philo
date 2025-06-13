#include "../includes/philo.h"

static void assign_forks(t_philo *philo, t_fork *forks, int position)
{
  int nbr_philo;

  nbr_philo = philo->table->nbr_philo;
  if (philo->id % 2 == 0)
  {
    philo->first_fork = &forks[position];
    philo->second_fork = &forks[(position + 1) % nbr_philo];
  }
  else
  {
    philo->first_fork = &forks[(position + 1) % nbr_philo];
    philo->second_fork = &forks[position];
  }
}

static void philo_init(t_table *table)
{
  int i;
  t_philo *philo;

  i = -1;
  while (++i < table->nbr_philo)
  {
    philo = table->philos + i;
    philo->id = i + 1;
    philo->full = FALSE;
    philo->meals_count = 0;
    philo->table = table;
    safe_mutex_handle(&philo->philo_mutex, INIT);
    assign_forks(philo, table->forks, i);
  }
}

void data_init(t_table *table)
{
  int i;

  i = -1;
  table->end_simulation = FALSE;
  table->all_thread_ready = FALSE;
  table->threads_running = 0;
  table->philos = ft_malloc(sizeof(t_philo) * table->nbr_philo);
  safe_mutex_handle(&table->table_mutex, INIT);
  safe_mutex_handle(&table->write_lock, INIT);
  table->forks = ft_malloc(sizeof(t_fork) * table->nbr_philo);
  while (++i < table->nbr_philo)
  {
    safe_mutex_handle(&table->forks[i].fork, INIT);
    table->forks[i].fork_id = i;
  }
  philo_init(table);
}