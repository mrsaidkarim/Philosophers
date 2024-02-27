CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = utils_bonus.c init_bonus.c philo_functions_bonus.c philo_bonus.c
OBJ = ${SRC:.c=.o}
HEADER = philo_bonus.h
NAME = philo_bonus

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