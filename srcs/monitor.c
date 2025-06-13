#include "../includes/philo.h"

int philo_died(t_philo *philo)
{
  long elapsed;
  long t_to_die;

  if (get_bool(&philo->philo_mutex, &philo->full))
    return FALSE;
  elapsed = get_time(MILISECONDS) - get_long(&philo->philo_mutex, &philo->last_meal_time);
  t_to_die = philo->table->time_to_die / 1000;
  if (elapsed > t_to_die)
    return TRUE;
  return FALSE;
}

void *monitor_dinner(void *data)
{
  t_table *table;
  int i;

  table = (t_table *)data;
  while (!all_threads_running(&table->table_mutex, &table->threads_running, table->nbr_philo))
    ;
    while (!sim_finished(table))
    {
      i = -1;
      while (++i < table->nbr_philo && !sim_finished(table))
      {
        if (philo_died(table->philos + i))
        {
          set_bool(&table->table_mutex, &table->end_simulation, TRUE);
          write_status(DIED, table->philos + i);
        }
      }
    }
  return (NULL);
}