/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:49:06 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/16 13:43:16 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

# include "types.h"

//src/utils.c
bool	ph_satoi(const char *str, int *result_ptr);
long	us_diff(struct timeval tv1, struct timeval tv2);
void	msleep(t_data *data, long ms);
void	print(t_philo *philo, t_event event);

//src/util_basic.c
int		ph_isdigit(int arg);
ssize_t	ph_putendl_fd(char *s, int fd);

#endif
