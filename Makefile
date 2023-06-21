# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 16:23:17 by kbrousse          #+#    #+#              #
#    Updated: 2023/06/21 13:37:31 by kbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ircserv

SRC =	main.cpp			\
		Server.cpp			\
		Client.cpp			\
		run.cpp				\
		parse.cpp

UTILS =	isInputFull.cpp

HEADERS =	headers/colours.hpp	\
			headers/Server.hpp	\
			headers/Client.hpp	\
			headers/ircserv.hpp

INCLUDE_FOLDER = -I headers/

OBJS_PATH = objects/

OBJS = $(SRCS:%.cpp=$(OBJS_PATH)%.o)

SRCS =	$(SRC)							\
		$(addprefix utils/, $(UTILS))	\

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

$(OBJS_PATH)%.o: %.cpp $(HEADERS)
		mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INCLUDE_FOLDER) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJS_PATH)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
