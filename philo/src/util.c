/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:44:41 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/19 16:52:52 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "types.h"

/**
 * Checks whether the arg is a digit
 * @param arg Char to be evaluated
 * @returns 1 if character was a digit, 0 if not
 */
int	ph_isdigit(int arg)
{
	return (arg >= '0' && arg <= '9');
}

/**
 * Converts a string to an int, very strictly
 * @param str The string to be converted
 * @param result_ptr A pointer to store the resulting int in
 * @returns A boolean indicating whether the conversion was succesful
 */
bool	ph_satoi(const char *str, int *result_ptr)
{
	int		i;
	int		sign;
	long	c;

	sign = -1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	if (!ph_isdigit(str[i]))
		return (false);
	c = 0;
	while (ph_isdigit(str[i]))
	{
		c = ((c * 10) - (str[i] - '0'));
		if (c * sign < -2147483648 || c * sign > 2147483647)
			return (false);
		i++;
	}
	*result_ptr = c * sign;
	return (str[i] == '\0');
}

long	us_diff(struct timeval tv1, struct timeval tv2)
{
	return (1000000 * (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec));
}

void	msleep(long ms)
{
	struct timeval	tv_start;
	struct timeval	tv_current;
	long			us_left;

	us_left = ms * 1000;
	gettimeofday(&tv_start, NULL);
	while (us_left > 500)
	{
		usleep(500); // 500μs = 0.5ms
		gettimeofday(&tv_current, NULL);
		us_left = ms * 1000 - us_diff(tv_start, tv_current);
	}
	if (us_left > 0)
		usleep(us_left);
}

void	print(t_philo *philo, char const *msg)
{
	struct timeval tv;
	long ms_since_start;

	gettimeofday(&tv, NULL);
	ms_since_start = 1000 * (tv.tv_sec - philo->data->start_time.tv_sec) +
		(tv.tv_usec - philo->data->start_time.tv_usec) / 1000;
	// printf("[%ld] %zu %s\n", ms_since_start, philo->id, msg);
	printf("%ld %zu %s\n", ms_since_start, philo->id, msg);
	fflush(NULL);
}
