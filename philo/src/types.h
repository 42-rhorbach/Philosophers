/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:59:41 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 17:20:41 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	bool			initialized;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		thread;
	size_t			id;
	pthread_mutex_t	times_eaten_mutex;
	int				times_eaten;
	pthread_mutex_t	last_meal_mutex;
	struct timeval	time_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_num;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_eat;

	unsigned int	stair_offset;

	pthread_mutex_t	print_mutex;

	pthread_mutex_t	someone_died_mutex;
	bool			someone_died;
	struct timeval	start_time;

	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

#endif
