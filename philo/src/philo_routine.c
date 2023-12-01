/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 15:45:35 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/12/01 16:11:43 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "types.h"
#include "mutex.h"
#include "util.h"

static bool	should_philo_continue(t_philo *philo)
{
	if (philo->data->philo_num % 2 == 1)
		msleep(philo->data, philo->data->stair_offset + \
		philo->data->tt_eat - philo->data->tt_sleep);
	mutex_lock(&philo->data->stop_program_mutex);
	if (philo->data->stop_program == true)
	{
		mutex_unlock(&philo->data->stop_program_mutex);
		return (false);
	}
	mutex_unlock(&philo->data->stop_program_mutex);
	return (true);
}

static void	pick_fork(t_philo *philo)
{
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
}

static void	philo_routine(t_philo *philo)
{
	while (true)
	{
		pick_fork(philo);
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
		if (should_philo_continue(philo) == false)
			return ;
	}
}

static void	single_philo_routine(t_philo *philo)
{
	mutex_lock(philo->left_fork);
	print(philo, FORK);
	msleep(philo->data, philo->data->tt_die + 1);
	mutex_unlock(philo->left_fork);
}

void	*philo_start_routine(void *arg)
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
