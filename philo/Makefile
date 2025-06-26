CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs
OBJ_DIR = obj
NAME = philo

SRCS = srcs/main.c \
			srcs/lib.c \
			srcs/parse.c \
			srcs/init.c \
			srcs/sim.c \
			srcs/handlers.c \
			srcs/protected.c \
			srcs/print.c \
			srcs/sync.c \
			srcs/monitor.c \
			srcs/utils.c \
			srcs/actions.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -Iincludes

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
