# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 16:23:17 by kbrousse          #+#    #+#              #
#    Updated: 2023/06/27 13:36:05 by kbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ircserv

SRC =	main.cpp			\
		Server.cpp			\
		Client.cpp			\
		Channel.cpp			\
		run.cpp				\
		detectCommand.cpp

COMMANDS =	join.cpp			\
			nick.cpp			\
			user.cpp			\
			whois.cpp			\
			displayChannels.cpp	\
			disconnect.cpp

HEADERS =	headers/colours.hpp	\
			headers/Server.hpp	\
			headers/Client.hpp	\
			headers/Channel.hpp	\
			headers/ircserv.hpp

INCLUDE_FOLDER = -I headers/

OBJS_PATH = objects/

OBJS = $(SRCS:%.cpp=$(OBJS_PATH)%.o)

SRCS =	$(SRC)								\
		$(addprefix commands/, $(COMMANDS))

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
