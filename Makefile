NAME =	ircserv

NAME_BOT = passBot

SRC =	main.cpp			\
		Server.cpp			\
		Client.cpp			\
		Channel.cpp			\
		detectCommand.cpp	\
		run.cpp				\

SRC_BOT =	bot.cpp	\

COMMANDS =	join.cpp					\
			nick.cpp					\
			user.cpp					\
			whois.cpp					\
			displayChannels.cpp			\
			privmsg.cpp					\
			pass.cpp					\
			part.cpp					\
			quit.cpp					\
			kick.cpp					\
			mode.cpp					\
			invite.cpp					\
			addOptionToChannel.cpp		\
			topic.cpp					\
			deleteOptionFromChannel.cpp	\

HEADERS =	headers/Server.hpp	\
			headers/Client.hpp	\
			headers/Channel.hpp	\

INCLUDE_FOLDER = -I headers/

OBJS_PATH = objects/

OBJS = $(SRCS:%.cpp=$(OBJS_PATH)%.o)

OBJ_BOT = $(SRC_BOT:%.cpp=$(OBJS_PATH)%.o)

SRCS =	$(SRC)								\
		$(addprefix commands/, $(COMMANDS))	\

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

$(OBJS_PATH)%.o: %.cpp $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDER) -c $< -o $@

all: $(NAME)

bonus: $(NAME) $(NAME_BOT)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(NAME_BOT): $(OBJ_BOT)
	$(CC) $(OBJ_BOT) -o $(NAME_BOT)

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BOT)

re: fclean all

.PHONY: all clean fclean re bonus
