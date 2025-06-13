#include "../includes/philo.h"

static void handle_mutex_error(int status, t_action action)
{
  if (status == 0)
    return ;
  if (status == EINVAL && (action == LOCK || action == UNLOCK))
    error_exit("The value specified by mutex is invalid.");
  else if (status == EINVAL && action == INIT)
    error_exit(" The value specified by attr is invalid.");
  else if (status == EDEADLK)
    error_exit("A deadlock would occur if the thread blocked waiting for mutex");
  else if (status == EBUSY)
    error_exit("Mutex is locked.");
  else if (status == ENOMEM)
    error_exit("The process cannot allocate enough memory to create another mutex.");
  else if (status == EPERM)
    error_exit("The current thread does not hold a lock on mutex.");
}

void  safe_mutex_handle(pthread_mutex_t *mutex, t_action action)
{
  if (action == LOCK)
    handle_mutex_error(pthread_mutex_lock(mutex), action);
  else if (action == UNLOCK)
    handle_mutex_error(pthread_mutex_unlock(mutex), action);
  else if (action == INIT)
    handle_mutex_error(pthread_mutex_init(mutex, NULL), action);
  else if (action == DESTROY)
    handle_mutex_error(pthread_mutex_destroy(mutex), action);
  else
    error_exit("Invalid action");
}

static void handle_thread_error(int status, t_action action)
{
  if (status == 0)
    return ;
  if (status == EINVAL && action == CREATE)
    error_exit("The value specified by attr is invalid.");
  else if (status == EINVAL && (action == JOIN || action == DETACH))
    error_exit("The value specified by thread is not joinable");
  else if (status == EDEADLK)
    error_exit("A deadlock was detected or the value of thread specifies the calling thread");
  else if (status == ESRCH)
    error_exit("No thread could be found corresponding to that specified by the given thread ID, thread.");
  else if (status == EAGAIN)
    error_exit("No resources to create another thread.");
  else if (status == EPERM)
    error_exit("The caller does not have appropriate permission\n");
}

void  safe_thread_handle(pthread_t *thread, void *(*func)(void *), void *data, t_action action)
{
  if (action == CREATE)
    handle_thread_error(pthread_create(thread, NULL, func, data), action);
  else if (action == JOIN)
    handle_thread_error(pthread_join(*thread, NULL), action);
  else if (action == DETACH)
    handle_thread_error(pthread_detach(*thread), action);
  else
    error_exit("Invalid action");
}