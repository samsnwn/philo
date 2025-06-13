#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

#define TRUE 1
#define FALSE 0

typedef struct s_table t_table;

typedef enum e_action
{
  LOCK,
  UNLOCK,
  INIT,
  DESTROY,
  CREATE,
  JOIN,
  DETACH,

}           t_action;

typedef enum e_timecode
{
  SECONDS,
  MILISECONDS,
  MICROSECONDS,
}           t_timecode;

typedef enum e_status
{
  EATING,
  SLEEPING,
  THINKING,
  TAKE_FIRST_FORK,
  TAKE_SECOND_FORK,
  DIED,
}           t_status;

typedef struct s_fork
{
  pthread_mutex_t fork;
  int             fork_id;
}             t_fork;

typedef struct s_philo
{
  int     id;
  long    meals_count;
  int     full;
  long    last_meal_time;
  pthread_mutex_t philo_mutex;
  pthread_t         thread_id;
  t_fork  *first_fork;
  t_fork  *second_fork;
  t_table *table;
}               t_philo;

typedef struct s_table
{
  long nbr_philo;
  long time_to_die;
  long time_to_eat;
  long time_to_sleep;
  long nbr_limit_meals;
  long start_simulation;
  int end_simulation;
  int   all_thread_ready;
  long threads_running;
  pthread_mutex_t table_mutex;
  pthread_mutex_t write_lock;
  pthread_t monitor;
  t_fork  *forks;
  t_philo *philos;
}     t_table;

void parse_input(t_table *table, char **argv);
void data_init(t_table *table);
void dinner_start(t_table *table);
void *dinner_sim(void *data);
void my_think(t_philo *philo, int pre_sim);

// SAFE HANDLERS
void  safe_thread_handle(pthread_t *thread, void *(*func)(void *), void *data, t_action action);
void  safe_mutex_handle(pthread_mutex_t *mutex, t_action action);

// LIB & UTILS
void  error_exit(char *error);
void *ft_malloc(size_t bytes);
long	ft_atol(const char *str);
long get_time(t_timecode timecode);
void my_sleep(long usec, t_table *table);
void write_status(t_status status, t_philo *philo);
void free_destroy(t_table *table);

// GETTERS & SETTERS
void set_bool(pthread_mutex_t *mutex, int *dest, int value);
int get_bool(pthread_mutex_t *mutex, int *value);
void set_long(pthread_mutex_t *mutex, long *dest, long value);
long get_long(pthread_mutex_t *mutex, long *value);
int sim_finished(t_table *table);

// SYNC UTILS
void *monitor_dinner(void *data);
void wait_all_threads(t_table *table);
int all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void de_sync_philo(t_philo *philo);

void increase_long(pthread_mutex_t *mutex, long *value);

#endif
