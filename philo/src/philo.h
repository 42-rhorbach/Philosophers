/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:50:20 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/12/01 15:58:43 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "types.h"

//src/philo.c
void	join_philos(int philo_num, t_philo *philos);
bool	start_philos(t_data *data);

//src/philo_routine.c
void	*philo_start_routine(void *arg);

#endif
