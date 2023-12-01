/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 17:07:56 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/12/01 15:47:22 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>

#include "types.h"
#include "mutex.h"
#include "util.h"
#include "philo.h"

void	join_philos(int philo_num, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

bool	start_philos(t_data *data)
{
	int	i;

	i = 0;
	mutex_lock(&data->stop_program_mutex);
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, \
		&philo_start_routine, &data->philos[i]) != 0)
		{
			data->stop_program = true;
			mutex_unlock(&data->stop_program_mutex);
			join_philos(i, data->philos);
			ph_putendl_fd("Error: instantiating threads failed", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	gettimeofday(&data->start_time, NULL);
	while (i > 0)
	{
		i--;
		data->philos[i].time_last_meal = data->start_time;
	}
	mutex_unlock(&data->stop_program_mutex);
	return (true);
}
