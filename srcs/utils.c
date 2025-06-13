#include "../includes/philo.h"

void  error_exit(char *error)
{
  printf("%s\n", error);
  exit(EXIT_FAILURE);
}

void *ft_malloc(size_t bytes)
{
  void *ptr;

  ptr = malloc(bytes);
  if (ptr == NULL)
    error_exit("Memory allocation failed");
  return (ptr);
}

long get_time(t_timecode timecode)
{
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    error_exit("Get time of day failed");
  if (timecode == SECONDS)
    return (tv.tv_sec + (tv.tv_usec / 1000000));
  else if (timecode == MILISECONDS)
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
  else if (timecode == MICROSECONDS)
    return ((tv.tv_sec * 1000000) + tv.tv_usec);
  else
    error_exit("Wrong input to get time");
  return (42);
}
void my_sleep(long usec, t_table *table)
{
  long start;
  long elapsed;
  long remaining;

  start = get_time(MICROSECONDS);
  while (get_time(MICROSECONDS) - start < usec)
  {
    if (sim_finished(table))
      break ;
    elapsed = get_time(MICROSECONDS) - start;
    remaining = usec - elapsed;
    if (remaining > 1000)
      usleep(remaining / 2);
    else
    {
      while (get_time(MICROSECONDS) - start < usec)
        ;
    }
  }
}

void free_destroy(t_table *table)
{
  int i;
  t_philo *philo;

  i = -1;
  while (++i < table->nbr_philo)
  {
    philo = table->philos + i;
    safe_mutex_handle(&philo->philo_mutex, DESTROY);
    safe_mutex_handle(&table->forks[i].fork, DESTROY);
  }
  safe_mutex_handle(&table->table_mutex, DESTROY);
  safe_mutex_handle(&table->write_lock, DESTROY);
  free(table->philos);
  free(table->forks);
}
