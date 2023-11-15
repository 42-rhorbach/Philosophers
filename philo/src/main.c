/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:44:16 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 17:16:57 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "philo.h"
#include "init.h"
#include "clear.h"
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

static bool	init(t_data *data, char **argv)
{
	if (!parse_args(data, argv))
		return (false);
	if (!init_forks(data))
		return (false);
	if (!init_philos(data))
	{
		clear_forks(data->forks, data->philo_num);
		return (false);
	}
	if (pthread_mutex_init(&data->someone_died_mutex, NULL) != 0)
	{
		destroy_meal_mutex(data->philos, data->philo_num);
		destroy_eaten_mutex(data->philos, data->philo_num);
		free(data->philos);
		clear_forks(data->forks, data->philo_num);
		ph_putendl_fd("Error: mutex init failed", STDERR_FILENO);
		return (false);
	}
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
		return (EXIT_FAILURE);
	}
	start_philos(&data);
	destroy_meal_mutex(data.philos, data.philo_num);
	destroy_eaten_mutex(data.philos, data.philo_num);
	free(data.philos);
	clear_forks(data.forks, data.philo_num);
	return (EXIT_SUCCESS);
}
