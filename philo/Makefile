CC=cc
NAME = philo
SRC_DIR = src/
SRCS = $(SRC_DIR)simulation.c \
	$(SRC_DIR)parser.c \
	$(SRC_DIR)utils.c \
	$(SRC_DIR)philo.c

OBJ_DIR = objs/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CFLAGS = -g \
		-I include \

LDFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p objs/
	$(CC) $(CFLAGS) $< -c -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf $(OBJ_DIR)

run: all
	./$(NAME) $(ARGS)

run2: all
	valgrind --show-leak-kinds=all --leak-check=full ./$(NAME) $(ARGS)

re: fclean all

.PHONY: all fclean clean run run2 re bonus