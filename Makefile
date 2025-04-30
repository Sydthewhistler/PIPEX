# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 22:51:05 by scavalli          #+#    #+#              #
#    Updated: 2025/04/30 16:41:36 by scavalli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE =  main.c utils.c
FILE_BONUS = main_bonus.c utils_bonus.c utils2_bonus.c
NAME = pipex
BONUS_NAME = pipex_bonus
CC = clang
CFLAGS = -Wall -Wextra -Werror -g3
SRCS = $(FILE)
SRCS_BONUS = $(FILE_BONUS)
OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

.PHONY: all clean fclean re bonus

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BONUS_NAME): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS_NAME)

bonus: $(BONUS_NAME)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

rebonus : fclean bonus