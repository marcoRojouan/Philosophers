# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/30 by mrojouan              #+#    #+#                  #
#    Updated: 2026/03/30 by mrojouan             ###   ########.fr            #
#                                                                              #
# **************************************************************************** #

# ============================= VARIABLES ============================== #

NAME			= philosophers
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -pthread -I. -g
CFLAGS_DEBUG	= $(CFLAGS) -g3 -O0
RM				= rm -f

# ============================= SOURCES =============================== #

SRCS			= philosophers.c \
				  initialisation/table_init.c \
				  parsing_utils/utils.c \
				  parsing_utils/verif_args.c \
				  simulation/sim_check.c \
				  simulation/sim_utils.c \
				  simulation/simulation.c \
				  simulation/routines_utils.c \
				  error_clean/clean_up.c

OBJS			= $(SRCS:.c=.o)

# ============================= RULES ================================ #

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "✓ $(NAME) compiled successfully!"

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS = $(CFLAGS_DEBUG)
debug: clean $(NAME)
	@echo "✓ Debug build completed!"

clean:
	$(RM) $(OBJS)
	@echo "✓ Object files cleaned!"

fclean: clean
	$(RM) $(NAME)
	@echo "✓ All cleaned!"

re: fclean all

# ============================= PHONY TARGETS ======================== #

.PHONY: all clean fclean re debug
