#include "../includes/philo.h"

void set_bool(pthread_mutex_t *mutex, int *dest, int value)
{
  safe_mutex_handle(mutex, LOCK);
  *dest = value;
  safe_mutex_handle(mutex, UNLOCK);
}

int get_bool(pthread_mutex_t *mutex, int *value)
{
  int ret;

  safe_mutex_handle(mutex, LOCK);
  ret = *value;
  safe_mutex_handle(mutex, UNLOCK);
  return ret;
}

void set_long(pthread_mutex_t *mutex, long *dest, long value)
{
  safe_mutex_handle(mutex, LOCK);
  *dest = value;
  safe_mutex_handle(mutex, UNLOCK);
}

long get_long(pthread_mutex_t *mutex, long *value)
{
  long ret;

  safe_mutex_handle(mutex, LOCK);
  ret = *value;
  safe_mutex_handle(mutex, UNLOCK);
  return ret;
}

int sim_finished(t_table *table)
{
  return (get_bool(&table->table_mutex, &table->end_simulation));
}