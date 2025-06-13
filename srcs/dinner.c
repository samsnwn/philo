#include "../includes/philo.h"

static void my_eat(t_philo *philo)
{
  safe_mutex_handle(&philo->first_fork->fork, LOCK);
  write_status(TAKE_FIRST_FORK, philo);
  safe_mutex_handle(&philo->second_fork->fork, LOCK);
  write_status(TAKE_SECOND_FORK, philo);
  set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECONDS));
  philo->meals_count++;
  write_status(EATING, philo);
  my_sleep(philo->table->time_to_eat, philo->table);
  if (philo->table->nbr_limit_meals > 0 && philo->meals_count == philo->table->nbr_limit_meals)
    set_bool(&philo->philo_mutex, &philo->full, TRUE);
  safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
  safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void my_think(t_philo *philo, int pre_sim)
{
  long t_eat;
  long t_sleep;
  long t_think;

  if (!pre_sim)
    write_status(THINKING, philo);
  if (philo->table->nbr_philo % 2 == 0)
    return ;
  t_eat = philo->table->time_to_eat;
  t_sleep = philo->table->time_to_sleep;
  t_think = t_eat * 2 - t_sleep;
  if (t_think < 0)
    t_think = 0;
  my_sleep(t_think * 0.42, philo->table);
}

void *dinner_sim(void *data)
{
  t_philo *philo;

  philo = (t_philo *)data;
  wait_all_threads(philo->table);
  set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECONDS));
  increase_long(&philo->table->table_mutex, &philo->table->threads_running);
  de_sync_philo(philo);
  while (!sim_finished(philo->table))
  {
    if (philo->full)
      break ;
    my_eat(philo);
    write_status(SLEEPING, philo);
    my_sleep(philo->table->time_to_sleep, philo->table);
    my_think(philo, FALSE);
  }
  return (NULL);
}

void *one_philo(void *data)
{
  t_philo *philo;

  philo = (t_philo *)data;
  wait_all_threads(philo->table);
  set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECONDS));
  increase_long(&philo->table->table_mutex, &philo->table->threads_running);
  write_status(TAKE_FIRST_FORK , philo);
  while (!sim_finished(philo->table))
    usleep(200);
  return (NULL);
}

void dinner_start(t_table *table)
{
  int i;

  i = -1;
  if (table->nbr_philo == 1)
    safe_thread_handle(&table->philos[0].thread_id, one_philo, &table->philos[0], CREATE);
  else
  {
    while (++i < table->nbr_philo)
      safe_thread_handle(&table->philos[i].thread_id, dinner_sim, &table->philos[i], CREATE);
  }
  safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
  table->start_simulation = get_time(MILISECONDS);
  set_bool(&table->table_mutex, &table->all_thread_ready, TRUE);
  i = -1;
  while (++i < table->nbr_philo)
    safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
  set_bool(&table->table_mutex, &table->end_simulation, TRUE);
  safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
