/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:50:20 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/30 17:52:56 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "types.h"

void	join_philos(int philo_num, t_philo *philos);
bool	start_philos(t_data *data);
void	monitor_philos(t_data *data);

#endif
