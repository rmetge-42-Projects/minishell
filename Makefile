NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs
RM = rm -rf

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

SRC = main.c\
	path.c\
	split_arg.c\
	structur.c

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: ${NAME}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -I$(INC_DIR) -c $< -o $@

${NAME}: $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) bonus

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

norminette:
	@-norminette | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)

re: fclean all

sources:
	./update_src

PHONY: all clean fclean re libft