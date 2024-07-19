NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -I.

SRC = main.c init.c life.c utils.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	printf "$(ERASE)$(GREEN)Program$(RESET) $(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)created!$(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(ERASE)$(BLUE) > Compilation: $(RESET) $<"

clean:
	printf "$(ERASE)$(GREEN)Cleaning up...$(RESET)"
	rm -rf ${OBJS}
	printf "$(ERASE)$(GREEN)Clean finished!\n$(RESET)"

fclean: clean
	printf "$(GREEN)Fcleaning up...$(RESET)"
	rm -rf ${NAME}
	printf "$(ERASE)$(GREEN)Fclean finished!\n$(RESET)"

re: fclean all

.PHONY: $(NAME) all clean fclean re
.SILENT:

# COLORS
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
BLINK = \033[5m
ERASE = \033[2K\r
RESET = \033[0m
