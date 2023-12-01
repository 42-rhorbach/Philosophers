/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 15:28:11 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/12/01 15:34:21 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "mutex.h"

static void	destroy_forks(t_data *data)
{
	int	i;

	if (data->forks == NULL)
		return ;
	i = 0;
	while (i < data->philo_num)
	{
		mutex_destroy(&data->forks[i]);
		i++;
	}
}

static void	destroy_philosophers(t_data *data)
{
	int	i;

	if (data->philos == NULL)
		return ;
	i = 0;
	while (i < data->philo_num)
	{
		mutex_destroy(&data->philos->last_meal_mutex);
		i++;
	}
}

void	destroy(t_data *data)
{
	mutex_destroy(&data->print_mutex);
	mutex_destroy(&data->hungry_philos_mutex);
	mutex_destroy(&data->stop_program_mutex);
	destroy_forks(data);
	free(data->forks);
	destroy_philosophers(data);
	free(data->philos);
}
