#include "../includes/philo.h"

void write_status(t_status status, t_philo *philo)
{
  long elapsed;

  elapsed = get_time(MILISECONDS) - philo->table->start_simulation;
  if (philo->full)
    return ;
  safe_mutex_handle(&philo->table->write_lock, LOCK);
  if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !sim_finished(philo->table))
    printf(" %ld   %d has taken a fork\n", elapsed, philo->id);
  else if (status == EATING && !sim_finished(philo->table))
    printf(" %ld   %d is eating\n", elapsed, philo->id);
  else if (status == SLEEPING && !sim_finished(philo->table))
    printf(" %ld   %d is sleeping\n", elapsed, philo->id);
  else if (status == THINKING && !sim_finished(philo->table))
    printf(" %ld   %d is thinking\n", elapsed, philo->id);
  else if (status == DIED)
    printf(" %ld   %d died\n", elapsed, philo->id);
  safe_mutex_handle(&philo->table->write_lock, UNLOCK);
}