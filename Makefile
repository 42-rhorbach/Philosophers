# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rhorbach <rhorbach@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/28 14:49:09 by rhorbach      #+#    #+#                  #
#    Updated: 2023/10/10 17:05:00 by rhorbach      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

all:
	$(MAKE) -C philo all

%:
	$(MAKE) -C philo