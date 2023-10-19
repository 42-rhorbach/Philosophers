/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:44:16 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/19 16:51:11 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "philo.h"
#include "types.h"
#include "util.h"

static bool	parse_args(t_data *data, char **argv)
{
	data->max_eat = 0;
	if (ph_satoi(argv[1], &data->philo_num) == false \
	|| ph_satoi(argv[2], &data->tt_die) == false \
	|| ph_satoi(argv[3], &data->tt_eat) == false \
	|| ph_satoi(argv[4], &data->tt_sleep) == false \
	|| (argv[5] != NULL && ph_satoi(argv[5], &data->max_eat) == false))
	{
		// error
		return (false);
	}
	if (data->philo_num < 1 || data->tt_die < 0 || data->tt_eat < 0 \
	|| data->tt_sleep < 0 || (argv[5] != NULL && data->max_eat < 1))
	{
		// error
		return (false);
	}
	return (true);
}

static bool	init_forks(t_data *data)
{
	int				i;

	data->forks = malloc(data->philo_num * sizeof(*data->forks));
	if (data->forks == NULL)
		return (false); //error
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			//error and free
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(data->philo_num * sizeof(*data->philos));
	if (data->philos == NULL)
		return (false); //error
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].times_eaten = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_num];
		data->philos[i].data = data;
		i++;
	}
	return (true);
}

static bool	init(t_data *data, char **argv)
{
	if (!parse_args(data, argv) \
	|| !init_forks(data) \
	|| !init_philos(data))
		return (false);
	gettimeofday(&data->start_time, NULL); // TODO: move, ask Marius
	return (true);
}

// Printf is thread-safe, but helgrind can't detect it
// Search for "POSIX requires that implementations of standard" on:
// https://web.archive.org/web/20221216131501/https://cs.swan.ac.uk/~csoliver/ok-sat-library/internet_html/doc/doc/Valgrind/3.8.1/html/hg-manual.html
int main(int argc, char **argv)
{
	static t_data	data;

	if (argc < 5 || argc > 6)
	{
		// error
		return (EXIT_FAILURE);
	}
	if (!init(&data, argv))
	{
		// error
		return (EXIT_FAILURE);
	}

	//prepare everything before this
	start_philos(&data);
	return (EXIT_SUCCESS);
}
