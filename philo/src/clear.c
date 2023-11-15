/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 16:03:48 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/14 16:27:34 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "types.h"

void	clear_forks(pthread_mutex_t	*forks, int initialized)
{
	int	i;

	if (forks != NULL)
	{
		i = 0;
		while (i < initialized)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
	}
	free(forks);
	return ;
}

void	destroy_meal_mutex(t_philo	*philos, int initialized)
{
	int	i;

	if (philos != NULL)
	{
		i = 0;
		while (i < initialized)
		{
			pthread_mutex_destroy(&philos[i].last_meal_mutex);
			i++;
		}
	}
	return ;
}

void	destroy_eaten_mutex(t_philo	*philos, int initialized)
{
	int	i;

	if (philos != NULL)
	{
		i = 0;
		while (i < initialized)
		{
			pthread_mutex_destroy(&philos[i].times_eaten_mutex);
			i++;
		}
	}
	return ;
}
