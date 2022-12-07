NAME = cub3D
SRC = src
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Imlx -c -g

NONE := '\033[0m'
GREEN := '\033[92m'
GRAY := '\033[90m'
RED := '\033[91m'
CURSIVE := '\033[3m'

SRCS =	$(wildcard $(SRC)/*.c)

OBJ=$(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	@echo $(CURSIVE)$(GREEN)"-- Making $(NAME) --"$(NONE)
	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo $(GREEN)$ "--$(NAME) was created --"$(NONE)
all:
	$(MAKE) $(NAME)

clean:
	@echo $(CURSIVE)$()" -- Deleting objects --"$(NONE)
	rm -f $(OBJ)
	@echo $(RED)"--objects was deleted -- "$(NONE)

fclean: clean
	@echo $(CURSIVE)$(RED)"-- Deleting $(NAME) --"$(NONE)
	rm -f $(NAME)
	@echo $(RED)"-- $(NAME) was deleted -- "$(NONE)

re: fclean all
