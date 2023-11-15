/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 16:09:37 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/14 16:12:04 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAR_H
# define CLEAR_H

# include "types.h"

void	clear_forks(pthread_mutex_t	*forks, int initialized);
void	destroy_meal_mutex(t_philo	*philos, int initialized);
void	destroy_eaten_mutex(t_philo	*philos, int initialized);

#endif
