/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 17:18:59 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 17:20:52 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	mutex_lock(t_mutex *mutex_ptr)
{
	pthread_mutex_lock(&mutex_ptr->mutex);
}

void	mutex_unlock(t_mutex *mutex_ptr)
{
	pthread_mutex_unlock(&mutex_ptr->mutex);
}

void	mutex_destroy(t_mutex *mutex_ptr)
{
	if (mutex_ptr->initialized)
		pthread_mutex_destroy(&mutex_ptr->mutex);
}

bool	mutex_init(t_mutex *mutex_ptr)
{
	if (pthread_mutex_init(&mutex_ptr->mutex, NULL) != 0)
		return (false);
	mutex_ptr->initialized = true;
	return (true);
}
