/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 16:09:51 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/14 16:15:58 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "types.h"

bool	init_forks(t_data *data);
bool	init_mutex(t_data *data, int i);
bool	init_philos(t_data *data);

#endif
