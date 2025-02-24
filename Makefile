NAME = philo
SRC = srcs/understand.c
SRC_BONUS = 
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

bonus: $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME)

clean:
	/bin/rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
