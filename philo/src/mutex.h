/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 17:21:11 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 17:22:16 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include "types.h"

void	mutex_lock(t_mutex *mutex_ptr);
void	mutex_unlock(t_mutex *mutex_ptr);
void	mutex_destroy(t_mutex *mutex_ptr);
bool	mutex_init(t_mutex *mutex_ptr);

#endif
