/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:44:16 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/30 17:59:19 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "philo.h"
#include "init.h"
#include "mutex.h"
#include "types.h"
#include "util.h"

static bool	parse_args(t_data *data, char **argv)
{
	data->max_eat = 0;
	if (ph_satoi(argv[1], &data->philo_num) == false \
	|| ph_satoi(argv[2], &data->tt_die) == false \
	|| ph_satoi(argv[3], &data->tt_eat) == false \
	|| ph_satoi(argv[4], &data->tt_sleep) == false \
	|| (argv[5] != NULL && ph_satoi(argv[5], &data->max_eat) == false) \
	|| data->philo_num < 1 || data->tt_die < 0 || data->tt_eat < 0 \
	|| data->tt_sleep < 0 || (argv[5] != NULL && data->max_eat < 1))
	{
		ph_putendl_fd("Error: unexpected arguments", STDERR_FILENO);
		return (false);
	}
	return (true);
}

static bool	init_mutexes(t_data *data)
{
	return (mutex_init(&data->print_mutex) \
			&& mutex_init(&data->hungry_philos_mutex) \
			&& mutex_init(&data->stop_program_mutex));
}

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

//TODO: CREATE DESTROY_FORKS && DESTROY_PHILOS
static void	destroy(t_data *data)
{
	mutex_destroy(&data->print_mutex);
	mutex_destroy(&data->hungry_philos_mutex);
	mutex_destroy(&data->stop_program_mutex);
	destroy_forks(data);
	free(data->forks);
	destroy_philosophers(data);
	free(data->philos);
}

static bool	init(t_data *data, char **argv)
{
	if (!init_mutexes(data))
	{
		ph_putendl_fd("Error: mutex init failed", STDERR_FILENO);
		return (false);
	}
	if (!parse_args(data, argv))
		return (false);
	data->hungry_philos = data->philo_num;
	if (!init_forks(data) || !init_philos(data))
		return (false);
	if (!start_philos(data))
		return (false);
	data->stair_offset = 0;
	if (data->philo_num >= 3)
		data->stair_offset = data->tt_eat / ((data->philo_num - 1) / 2);
	return (true);
}

// Printf is thread-safe, but helgrind can't detect it
// Search for "POSIX requires that implementations of standard" on:
// https://web.archive.org/web/20221216131501/https://cs.swan.ac.uk/~csoliver
// /ok-sat-library/internet_html/doc/doc/Valgrind/3.8.1/html/hg-manual.html
int	main(int argc, char **argv)
{
	static t_data	data;

	if (argc < 5 || argc > 6)
	{
		ph_putendl_fd("Error: too many/few arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!init(&data, argv))
	{
		destroy(&data);
		return (EXIT_FAILURE);
	}
	monitor_philos(&data);
	mutex_lock(&data.stop_program_mutex);
	data.stop_program = true;
	mutex_unlock(&data.stop_program_mutex);
	join_philos(data.philo_num, data.philos);

	destroy(&data);
	return (EXIT_SUCCESS);
}
