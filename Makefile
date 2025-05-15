NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs
RM = rm -rf

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

SOURCES = ./built_in.c ./check_quote.c ./env.c ./export.c ./export_utils.c ./export_utils_two.c ./free.c ./free_utile.c ./header.c ./main.c ./path.c ./pipex.c ./pipex_utils.c ./structur_cmd.c ./structur_utile.c ./token_split.c ./token_utile.c 

OBJS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

MAKEFLAGS += --no-print-directory

all: message_comp $(NAME) message_done

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(LIBFT_PATH) -I$(INC_DIR) -c $< -o $@
	@echo -n "."

${NAME}: $(LIBFT)  $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) bonus
	@echo -n "."

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

message_comp:
	@echo -n "Compiling"

message_done:
	@printf "\n\033[0;32mSuccess\033[0m\n"

norminette:
	@-norminette | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

clean:
	@make -C $(LIBFT_PATH) clean
	@echo "Clean: \033[0;32mDone\033[0m"
	@$(RM) $(OBJ_DIR)

fclean:
	@make -C $(LIBFT_PATH) fclean
	@echo "Fclean: \033[0;32mDone\033[0m"
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)

re: fclean all

run: all
	@clear
	@./minishell

valgrind:
	valgrind --suppressions=valgrind.sup --show-leak-kinds=all --leak-check=full  ./minishell

sources:
	./update_src

PHONY: all clean fclean re libft