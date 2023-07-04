NAME =	ircserv

SRC =	main.cpp			\
		Server.cpp			\
		Client.cpp			\
		Channel.cpp			\
		detectCommand.cpp	\
		run.cpp

COMMANDS =	join.cpp					\
			nick.cpp					\
			user.cpp					\
			whois.cpp					\
			displayChannels.cpp			\
			privmsg.cpp					\
			pass.cpp					\
			part.cpp					\
			kick.cpp					\
			mode.cpp					\
			addOptionToChannel.cpp		\
			deleteOptionFromChannel.cpp

HEADERS =	headers/colours.hpp	\
			headers/Server.hpp	\
			headers/Client.hpp	\
			headers/Channel.hpp	\
			headers/ircserv.hpp	\

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
