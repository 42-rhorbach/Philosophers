/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:59:41 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/19 16:49:32 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	size_t			id;
	size_t			times_eaten;
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

	struct timeval	start_time;

	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

#endif
