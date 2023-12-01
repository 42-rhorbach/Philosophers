/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 16:06:42 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/30 17:48:22 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "init.h"
#include "philo.h"
#include "mutex.h"
#include "types.h"
#include "util.h"

bool	init_forks(t_data *data)
{
	int				i;

	data->forks = ft_calloc(data->philo_num, sizeof(*data->forks));
	if (data->forks == NULL)
	{
		ph_putendl_fd("Error: forks: memory allocation failed", STDERR_FILENO);
		return (false);
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (mutex_init(&data->forks[i]) == false)
		{
			ph_putendl_fd("Error: forks: mutex init failed", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_philos(t_data *data)
{
	int	i;

	data->philos = ft_calloc(data->philo_num, sizeof(*data->philos));
	if (data->philos == NULL)
	{
		ph_putendl_fd("Error: memory allocation failed", STDERR_FILENO);
		return (false);
	}
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		if (mutex_init(&data->philos[i].last_meal_mutex) == false)
		{
			ph_putendl_fd("Error: philos: mutex init failed", STDERR_FILENO);
			return (false);
		}
		data->philos[i].times_eaten = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_num];
		data->philos[i].data = data;
		i++;
	}
	return (true);
}
