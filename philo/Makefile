
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = aktion.c init.c utils.c main.c monitor.c thread.c
OBJS = $(SRCS:.c=.o)
INCLUDES = -I./include
RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean c:
	$(RM) $(OBJS)

fclean f: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re c f