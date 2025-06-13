#include "../includes/philo.h"

void wait_all_threads(t_table *table)
{
  while (!get_bool(&table->table_mutex, &table->all_thread_ready))
  ;
}

int all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
  int ret;

  ret = FALSE;
  safe_mutex_handle(mutex, LOCK);
  if (*threads == philo_nbr)
    ret = TRUE;
  safe_mutex_handle(mutex, UNLOCK);
  return ret;
}

void increase_long(pthread_mutex_t *mutex, long *value)
{
  safe_mutex_handle(mutex, LOCK);
  (*value)++;
  safe_mutex_handle(mutex, UNLOCK);
}

void de_sync_philo(t_philo *philo)
{
  if (philo->table->nbr_philo % 2 == 0)
  {
    if (philo->id % 2 == 0)
      my_sleep(30000, philo->table);
  }
  else
  {
    if (philo->id % 2)
      my_think(philo, TRUE);
  }
}