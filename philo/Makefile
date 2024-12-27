NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g3

SRC = 	philosophers.c \
		parse.c \
		utils.c \

OBJ = $(SRC:.c=.o)

HEADER = philo.h

GREEN = \033[32m
RESET = \033[0m

all: header $(LIBFT) $(NAME)

header:
	@echo "$(GREEN)"
	@echo "----------------------------------------------------------------"
	@echo "|     _     ___       __                _       _            __|"
	@echo "|    (_)___/ (_)___  / /_   ____  _____(_)___ _(_)___  ___  / /|"
	@echo "|   / / __  / / __ \/ __/  / __ \/ ___/ / __ \`/ / __ \/ _ \/ /|"
	@echo "|  / / /_/ / / /_/ / /_   / /_/ / /  / / /_/ / / / / /  __/ /  |"
	@echo "| /_/\__,_/_/\____/\__/   \____/_/  /_/\__, /_/_/ /_/\___/_/   |"
	@echo "|                                     /____/                   |"
	@echo "----------------------------------------------------------------"
	@echo "$(RESET)"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all