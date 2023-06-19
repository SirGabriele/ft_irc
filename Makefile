# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 16:23:17 by kbrousse          #+#    #+#              #
#    Updated: 2023/06/19 15:02:35 by kbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ircserv

SRCS =	main.cpp			\
		Server.cpp			\
		Client.cpp			\
		launchProgram.cpp

HEADERS =	headers/colours.hpp	\
			headers/Server.hpp	\
			headers/Client.hpp	\
			headers/ircserv.hpp

INCLUDE_FOLDER = -I headers/

OBJS_PATH = objects/

OBJS = $(SRCS:%.cpp=$(OBJS_PATH)%.o)

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
