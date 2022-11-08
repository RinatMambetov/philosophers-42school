# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: greita <greita@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/07 16:10:35 by greita            #+#    #+#              #
#    Updated: 2022/05/14 12:38:19 by greita           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRCS 			= control.c \
				  init_args.c \
				  init_vars.c \
				  live_like_philo.c \
				  utils.c \
				  utils2.c \
				  philo.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
FLAGS			= -Wall -Wextra -Werror

%.o:			%.c philo.h Makefile
				$(CC) $(FLAGS) -c $< -o $@

all:			$(NAME)

${NAME}:		$(OBJS)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY: 		all clean fclean re
