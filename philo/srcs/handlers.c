/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:32:06 by samcasti          #+#    #+#             */
/*   Updated: 2025/06/19 12:45:42 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	handle_mutex_error(int status, t_op op)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (op == LOCK || op == UNLOCK))
		exit_error("Invalid mutex value");
	else if (status == EINVAL && op == INIT)
		exit_error("Invalid mutex attributes");
	else if (status == EDEADLK)
		exit_error("Deadlock detected");
	else if (status == EBUSY)
		exit_error("Mutex is locked");
	else if (status == ENOMEM)
		exit_error("Insufficient memory for mutex");
	else if (status == EPERM)
		exit_error("Thread does not hold mutex lock");
}

void	handle_mutex(pthread_mutex_t *mutex, t_op op)
{
	if (op == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), op);
	else if (op == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), op);
	else if (op == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), op);
	else if (op == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), op);
	else
		exit_error("Invalid mutex operation");
}

static void	handle_thread_error(int status, t_op op)
{
	if (status == 0)
		return ;
	if (status == EINVAL && op == CREATE)
		exit_error("Invalid thread attributes");
	else if (status == EINVAL && op == JOIN)
		exit_error("Thread is not joinable");
	else if (status == EDEADLK)
		exit_error("Deadlock detected or self-join");
	else if (status == ESRCH)
		exit_error("Thread not found");
	else if (status == EAGAIN)
		exit_error("Insufficient resources for thread");
	else if (status == EPERM)
		exit_error("Insufficient permissions");
}

void	handle_thread(pthread_t *thread, void *(*func)(void *), 
		void *data, t_op op)
{
	if (op == CREATE)
		handle_thread_error(pthread_create(thread, NULL, func, data), op);
	else if (op == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), op);
	else
		exit_error("Invalid thread operation");
}
