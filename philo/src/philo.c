/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 17:07:56 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 16:37:56 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>

#include "types.h"
#include "util.h"

//error handling
//norminette
//error with 1 philo, stuck in mutex lock, write special case - DONE
//leaks checken
//fflush weghalen en alternative vinden - DONE
//SNELHEID - LOOKS GOOD?
//let them die - done?
//check in monitoring if they have eaten enough times - done?

bool	philo_has_died(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (us_diff(philo->time_last_meal, current_time) \
												/ 1000 < philo->data->tt_die)
	{
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	print(philo, "died");
	return (true);
}

// void	pick_fork(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->right_fork);
// 		print(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->left_fork);
// 		print(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		print(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->right_fork);
// 		print(philo, "has taken a fork");
// 	}
// }

static void	philo_routine(t_philo *philo)
{
	while (true)
	{
		// pick_fork(philo);
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
		if (philo->data->max_eat > 0)
		{
			pthread_mutex_lock(&philo->times_eaten_mutex);
			philo->times_eaten++;
			pthread_mutex_unlock(&philo->times_eaten_mutex);
		}
		pthread_mutex_lock(&philo->last_meal_mutex);
		gettimeofday(&philo->time_last_meal, NULL);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		msleep(philo->data, philo->data->tt_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		print(philo, "is sleeping");
		msleep(philo->data, philo->data->tt_sleep);
		print(philo, "is thinking");
		if (philo->data->philo_num % 2 == 1)
			msleep(philo->data, philo->data->stair_offset + \
			philo->data->tt_eat - philo->data->tt_sleep);
		pthread_mutex_lock(&philo->data->someone_died_mutex);
		if (philo->data->someone_died == true)
		{
			pthread_mutex_unlock(&philo->data->someone_died_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->someone_died_mutex);
	}
}

static void	single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
	msleep(philo->data, philo->data->tt_die + 1);
	pthread_mutex_unlock(philo->left_fork);
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
		pthread_mutex_lock(&philo->data->someone_died_mutex);
		if (philo->data->someone_died == true)
		{
			pthread_mutex_unlock(&philo->data->someone_died_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->someone_died_mutex);
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
				pthread_mutex_lock(&data->someone_died_mutex);
				data->someone_died = true;
				pthread_mutex_unlock(&data->someone_died_mutex);
				return ;
			}
			if (data->max_eat > 0)
			{
				pthread_mutex_lock(&data->philos[i].times_eaten_mutex); //times eaten must be defined
				if (((int)*(&data->philos[i].times_eaten)) > data->max_eat)
				{
					pthread_mutex_unlock(&data->philos[i].times_eaten_mutex);
					pthread_mutex_lock(&data->someone_died_mutex);
					data->someone_died = true;
					pthread_mutex_unlock(&data->someone_died_mutex);
					return ;
				}
				pthread_mutex_unlock(&data->philos[i].times_eaten_mutex);
			}
			i++;
		}
		usleep(500);
	}
}

void	start_philos(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->someone_died_mutex);
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_start_routine, &data->philos[i]) != 0)
		{
			data->someone_died = true;
			pthread_mutex_unlock(&data->someone_died_mutex);
			join_philos(i, data->philos);
			ph_putendl_fd("Error: instantiating threads failed", STDERR_FILENO);
			return ;
		}
		i++;
	}
	gettimeofday(&data->start_time, NULL);
	while (i > 0)
	{
		i--;
		data->philos[i].time_last_meal = data->start_time;
	}
	pthread_mutex_unlock(&data->someone_died_mutex);
	monitor_philos(data);
	join_philos(data->philo_num, data->philos);
}
