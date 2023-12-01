/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 16:09:51 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/12/01 15:33:09 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "types.h"

void	*ph_calloc(size_t count, size_t size);
bool	init_mutexes(t_data *data);
bool	init_forks(t_data *data);
bool	init_philos(t_data *data);

#endif
