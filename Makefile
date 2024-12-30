# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 10:55:21 by mmuhaise          #+#    #+#              #
#    Updated: 2024/12/30 03:10:55 by mmuhaise         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main utils init routine monitor validation

SRC = $(addsuffix .c, $(addprefix src/, $(SRCS)))

OBJS = $(addsuffix .o, $(addprefix objs/, $(SRCS)))

all: $(NAME)

$(NAME): $(OBJS)
	gcc  -g -Wall -Wextra -Werror $(OBJS) -o $(NAME)

objs/%.o:	src/%.c
	@mkdir -p $(dir $@)
	@gcc -g -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf ./objs

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re