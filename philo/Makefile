
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = aktion.c init.c utils.c philo.c monitor.c thread.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean c:
	$(RM) $(OBJS)

fclean f: clean
	$(RM) $(NAME)

v: $(NAME)
	valgrind --tool=helgrind ./philo 5 800 200 200 7

re: fclean all

.PHONY: all clean fclean re c f
