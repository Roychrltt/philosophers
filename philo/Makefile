NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c 

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Program$(RESET) $(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)creating...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Program$(RESET) $(CYAN)$(BOLD)$(BLINK)$(NAME)$(RESET) $(GREEN)created!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "$(GREEN)Clean finished!$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN)Fclean finished!$(RESET)"

re: fclean all

.PHONY: $(NAME) all clean fclean re

# COLORS
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
BLINK = \033[5m
RESET = \033[0m
