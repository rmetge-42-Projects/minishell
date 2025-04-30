NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs
RM = rm -rf

SOURCES = ./main.c ./path.c ./split_arg.c ./structur.c
OBJ_DIR = obj
OBJS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: ${NAME}

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -I/usr/include -I$(LIBFT_PATH) -I ./inc -c $< -o $@

${NAME}: $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

norminette:
	@-norminette | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

sources:
	./update_src

PHONY: all clean fclean re libft