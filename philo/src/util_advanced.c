/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_advanced.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:44:41 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/30 16:19:09 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include "types.h"
#include "mutex.h"
#include "util.h"

/**
 * Converts a string to an int, very strictly
 * @param str The string to be converted
 * @param result_ptr A pointer to store the resulting int in
 * @returns A boolean indicating whether the conversion was succesful
 */
bool	ph_satoi(const char *str, int *result_ptr)
{
	int	i;
	int	sign;
	int	c;

	sign = -1;
	i = 0;
	if (str[i] == '-')
		sign = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ph_isdigit(str[i]))
		return (false);
	c = 0;
	while (ph_isdigit(str[i]))
	{
		if (c < INT_MIN / 10)
			return (false);
		if (c * 10 < INT_MIN + (str[i] - '0'))
			return (false);
		c = c * 10 - (str[i] - '0');
		i++;
	}
	*result_ptr = c * sign;
	return (str[i] == '\0' && !(sign == -1 && c == INT_MIN));
}

long	us_diff(struct timeval tv1, struct timeval tv2)
{
	return (1000000 * (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec));
}

void	msleep(t_data *data, long ms)
{
	struct timeval	tv_start;
	struct timeval	tv_current;
	long			us_left;

	us_left = ms * 1000;
	gettimeofday(&tv_start, NULL);
	while (us_left > 500)
	{
		mutex_lock(&data->stop_program_mutex);
		if (data->stop_program == true)
		{
			mutex_unlock(&data->stop_program_mutex);
			return ;
		}
		mutex_unlock(&data->stop_program_mutex);
		usleep(500);
		gettimeofday(&tv_current, NULL);
		us_left = ms * 1000 - us_diff(tv_start, tv_current);
	}
	if (us_left > 0)
		usleep(us_left);
}

void	print(t_philo *philo, t_event event)
{
	static bool		printing = true;
	static char		*messages[] = {
	[FORK] = "has taken a fork",
	[EAT] = "is eating",
	[SLEEP] = "is sleeping",
	[THINK] = "is thinking",
	[DIE] = "died"
	};
	struct timeval	tv;
	long			ms_since_start;

	mutex_lock(&philo->data->print_mutex);
	if (printing)
	{
		gettimeofday(&tv, NULL);
		ms_since_start = 1000 * (tv.tv_sec - philo->data->start_time.tv_sec) + \
			(tv.tv_usec - philo->data->start_time.tv_usec) / 1000;
		printf("%ld %zu %s\n", ms_since_start, philo->id, messages[event]);
		mutex_lock(&philo->data->hungry_philos_mutex);
		if (event == DIE || (event == EAT \
			&& (philo->data->hungry_philos == 0)))
			printing = false;
		mutex_unlock(&philo->data->hungry_philos_mutex);
	}
	mutex_unlock(&philo->data->print_mutex);
}
