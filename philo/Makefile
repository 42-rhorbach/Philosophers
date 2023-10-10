# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rhorbach <rhorbach@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/10 17:07:20 by rhorbach      #+#    #+#                  #
#    Updated: 2023/10/10 17:14:22 by rhorbach      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJDIR = obj

CFLAGS = -Wall -Wextra -Werror
CFLAGS += $(if $(DEBUG),-g)
# -fsanitize=address)
CFLAGS += -I $(HEADERDIR)
CFLAGS += -Wfatal-errors

GREEN := \033[1;32m
RED := \033[1;31m
BLUE := \033[1;34m
PINK := \033[1;38;5;206m
NC := \033[0m

#########################

FILES = \
	src/philo.c

HEADERS = \
	# src/cmd_lst/cmd_lst.h						\
	# src/env/env.h 								\
	# src/redirect_lst/redir_lst.h				\
	# src/tokens/tokens.h							\
	# src/error.h 								\
	# src/types.h

#########################

OBJFILES = $(addprefix $(OBJDIR)/,$(FILES:c=o))
CFLAGS += $(addprefix -I,$(sort $(dir $(HEADERS))))

#########################

LFLAGS += -l pthread

#########################

#clear_line = \e[K
#move_up = \e[A
#define prettycomp
#printf "$(1)$(clear_line)\n"
#$(1)
#printf "$(move_up)"
#endef

#########################

all: $(NAME)
	@echo "$(GREEN)[Completed $(NAME)]$(NC)"

$(NAME): $(OBJFILES)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJFILES) $(LFLAGS) -o $(NAME)

DEPENDS := $(patsubst %.o,%.d,$(OBJFILES))
-include $(DEPENDS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)[Compiling $<]$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@printf "\033[1A\033[K"


# @$(call prettycomp,$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@)

clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)[Deleted $(NAME) objects]$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[Deleted $(NAME)]$(NC)"

re: fclean all

#########################

.PHONY: all clean fclean re
