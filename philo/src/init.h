/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 16:09:51 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/30 17:47:19 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "types.h"

void	*ft_calloc(size_t count, size_t size);
bool	init_forks(t_data *data);
bool	init_philos(t_data *data);

#endif
