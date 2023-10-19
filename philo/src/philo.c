/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 17:07:56 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/19 16:54:46 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>

#include "types.h"
#include "util.h"

static void	philo_routine(t_philo *philo)
{
	while (true)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			print(philo, "has taken a fork");
			pthread_mutex_lock(philo->left_fork);
			print(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			print(philo, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			print(philo, "has taken a fork");
		}
		print(philo, "is eating");
		msleep(philo->data->tt_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print(philo, "is sleeping");
		msleep(philo->data->tt_sleep);
		print(philo, "is thinking");
	}
}

static void	*philo_start_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		msleep(philo->data->tt_eat / 2);
	if (philo->data->philo_num % 2 == 1)
		msleep(philo->data->tt_eat
			* ((philo->id - 1) / 2) / ((philo->data->philo_num - 1) / 2));
	philo_routine(philo);
	return (NULL);
}

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

void	start_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_start_routine, &data->philos[i]) != 0)
		{
			// error and free threads
			// make sure all data->philos stop
			join_philos(i, data->philos);
			return ;
		}
		i++;
	}
	join_philos(data->philo_num, data->philos);
}
