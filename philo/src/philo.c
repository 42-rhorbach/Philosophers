/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 17:07:56 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/12/01 15:11:47 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>

#include "types.h"
#include "mutex.h"
#include "util.h"

bool	philo_has_died(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	mutex_lock(&philo->last_meal_mutex);
	if (us_diff(philo->time_last_meal, current_time) \
												/ 1000 < philo->data->tt_die)
	{
		mutex_unlock(&philo->last_meal_mutex);
		return (false);
	}
	mutex_unlock(&philo->last_meal_mutex);
	print(philo, DIE);
	return (true);
}


static void	philo_routine(t_philo *philo)
{
	while (true)
	{
		// pick_fork(philo);
		if (philo->id % 2 == 0)
		{
			mutex_lock(philo->right_fork);
			print(philo, FORK);
			mutex_lock(philo->left_fork);
			print(philo, FORK);
		}
		else
		{
			mutex_lock(philo->left_fork);
			print(philo, FORK);
			mutex_lock(philo->right_fork);
			print(philo, FORK);
		}
		philo->times_eaten++;
		if (philo->times_eaten == philo->data->max_eat)
		{
			mutex_lock(&philo->data->hungry_philos_mutex);
			philo->data->hungry_philos--;
			mutex_unlock(&philo->data->hungry_philos_mutex);
		}
		print(philo, EAT);

		mutex_lock(&philo->last_meal_mutex);
		gettimeofday(&philo->time_last_meal, NULL);
		mutex_unlock(&philo->last_meal_mutex);

		msleep(philo->data, philo->data->tt_eat);
		mutex_unlock(philo->right_fork);
		mutex_unlock(philo->left_fork);

		print(philo, SLEEP);
		msleep(philo->data, philo->data->tt_sleep);
		print(philo, THINK);
		if (philo->data->philo_num % 2 == 1)
			msleep(philo->data, philo->data->stair_offset + \
			philo->data->tt_eat - philo->data->tt_sleep);
		mutex_lock(&philo->data->stop_program_mutex);
		if (philo->data->stop_program == true)
		{
			mutex_unlock(&philo->data->stop_program_mutex);
			return ;
		}
		mutex_unlock(&philo->data->stop_program_mutex);
	}
}

static void	single_philo_routine(t_philo *philo)
{
	mutex_lock(philo->left_fork);
	print(philo, FORK);
	msleep(philo->data, philo->data->tt_die + 1);
	mutex_unlock(philo->left_fork);
}

static void	*philo_start_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->data->philo_num == 1)
	{
		single_philo_routine(philo);
	}
	else
	{
		mutex_lock(&philo->data->stop_program_mutex);
		if (philo->data->stop_program == true)
		{
			mutex_unlock(&philo->data->stop_program_mutex);
			return (NULL);
		}
		mutex_unlock(&philo->data->stop_program_mutex);
		if (philo->id % 2 == 0)
			msleep(philo->data, philo->data->tt_eat / 2);
		if (philo->data->philo_num % 2 == 1)
			msleep(philo->data, philo->data->stair_offset * (philo->id / 2));
		philo_routine(philo);
	}
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

void	monitor_philos(t_data *data)
{
	int	i;

	while (true)
	{
		i = 0;
		while (i < data->philo_num)
		{
			if (philo_has_died(&data->philos[i]))
			{
				return ;
			}
			// if (data->max_eat > 0)
			// {
			// 	mutex_lock(&data->philos[i].times_eaten_mutex); //times eaten must be defined
			// 	if (((int)*(&data->philos[i].times_eaten)) > data->max_eat)
			// 	{
			// 		mutex_unlock(&data->philos[i].times_eaten_mutex);
			// 		mutex_lock(&data->stop_program_mutex);
			// 		data->stop_program = true;
			// 		mutex_unlock(&data->stop_program_mutex);
			// 		return ;
			// 	}
			// 	mutex_unlock(&data->philos[i].times_eaten_mutex);
			// }
			i++;
		}
		mutex_lock(&data->hungry_philos_mutex);
		if (data->hungry_philos == 0)
		{
			mutex_unlock(&data->hungry_philos_mutex);
			return ;
		}
		mutex_unlock(&data->hungry_philos_mutex);
		usleep(500);
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
