/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:49:06 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/19 16:51:18 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdbool.h>
# include <sys/time.h>

# include "types.h"

int		ph_isdigit(int arg);
bool	ph_satoi(const char *str, int *result_ptr);
long	us_diff(struct timeval tv1, struct timeval tv2);
void	msleep(long ms);
void	print(t_philo *philo, char const *msg);

#endif
