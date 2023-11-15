/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 16:06:42 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/14 16:28:43 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "philo.h"
#include "types.h"
#include "util.h"
#include "clear.h"

bool	init_forks(t_data *data)
{
	int				i;

	data->forks = malloc(data->philo_num * sizeof(*data->forks));
	if (data->forks == NULL)
	{
		ph_putendl_fd("Error: forks: memory allocation failed", STDERR_FILENO);
		return (false);
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			clear_forks(data->forks, i);
			ph_putendl_fd("Error: forks: mutex init failed", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	init_mutex(t_data *data, int i)
{
	if (pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL) != 0)
	{
		destroy_meal_mutex(data->philos, i);
		destroy_eaten_mutex(data->philos, i);
		free(data->philos);
		ph_putendl_fd("Error: philos: mutex init failed", STDERR_FILENO);
		return (false);
	}
	if (pthread_mutex_init(&data->philos[i].times_eaten_mutex, NULL) != 0)
	{
		destroy_meal_mutex(data->philos, i + 1);
		destroy_eaten_mutex(data->philos, i);
		free(data->philos);
		ph_putendl_fd("Error: philos: mutex init failed", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(data->philo_num * sizeof(*data->philos));
	if (data->philos == NULL)
	{
		ph_putendl_fd("Error: memory allocation failed", STDERR_FILENO);
		return (false);
	}
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		if (init_mutex(data, i) == false)
			return (false);
		data->philos[i].times_eaten = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_num];
		data->philos[i].data = data;
		i++;
	}
	return (true);
}
