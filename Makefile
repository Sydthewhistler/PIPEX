# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 22:51:05 by scavalli          #+#    #+#              #
#    Updated: 2025/03/13 15:20:49 by scavalli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE =  main.c utils.c
FILE_BONUS = main_bonus.c utils_bonus.c utils2_bonus.c
NAME = pipex
CC = clang
CFLAGS = -Wall -Wextra -Werror
SRCS = $(FILE)
SRCS_BONUS = $(FILE_BONUS)
OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

.PHONY: all clean fclean re bonus

all : $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus : $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)

clean :
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -f $(NAME)

re : fclean all

rebonus : fclean bonus