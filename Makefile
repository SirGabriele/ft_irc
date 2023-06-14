NAME =

SRCS =

HEADERS =

OBJS_PATH = objects/

OBJS = $(SRCS:%.cpp=$(OBJS_PATH)%.o)

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

$(OBJS_PATH)%.o: %.cpp $(HEADERS)
		mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJS_PATH)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
