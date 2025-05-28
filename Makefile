NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs
RM = rm -rf

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

SOURCES = src/builtin/built_in.c src/builtin/builtin_redirection.c src/builtin/built_in_utils.c src/builtin/cd.c src/builtin/env.c src/builtin/export.c src/builtin/export_utils.c src/builtin/export_utils_two.c src/execution/execution.c src/execution/heredoc.c src/execution/pipex.c src/execution/pipex_utils.c src/execution/signal.c src/free/free.c src/free/free_utile.c src/header.c src/main.c src/parsing/check_quote.c src/parsing/cmd_utils.c src/parsing/dollar.c src/parsing/path.c src/parsing/structur_cmd.c src/parsing/structur_utile.c src/parsing/token_split.c src/parsing/token_utile.c

OBJS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

MAKEFLAGS += --no-print-directory

all: message_comp $(NAME) message_done

DIRS = $(sort $(dir $(OBJS)))

$(DIRS):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
	@$(CC) $(CFLAGS) -I$(LIBFT_PATH) -I$(INC_DIR) -c $< -o $@
	@echo -n "."

${NAME}: $(LIBFT) $(OBJS)
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
	valgrind --suppressions=valgrind.sup --show-leak-kinds=all --leak-check=full --track-fds=yes ./minishell

sources:
	./update_src

PHONY: all clean fclean re libft