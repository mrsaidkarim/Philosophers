CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = utils.c init.c start.c philo_functions.c mutex_helper.c philo.c
OBJ = ${SRC:.c=.o}
HEADER = philo.h
NAME = philo

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean