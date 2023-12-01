/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:59:41 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/30 14:57:13 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum s_event
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_event;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	bool			initialized;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		thread;
	size_t			id;
	int				times_eaten;
	t_mutex			last_meal_mutex;
	struct timeval	time_last_meal;
	t_mutex			*left_fork;
	t_mutex			*right_fork;

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

	t_mutex			print_mutex;

	t_mutex			hungry_philos_mutex;
	int				hungry_philos;

	t_mutex			stop_program_mutex;
	bool			stop_program;
	struct timeval	start_time;

	t_mutex			*forks;
	t_philo			*philos;
}	t_data;

#endif
