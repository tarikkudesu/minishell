SRC				=	srcs/main.c  \
					srcs/error.c  \
					parse/lexer.c \
					parse/parse.c \
					parse/expand.c \
					parse/syntax.c \
					parse/minifun.c \
					parse/classify.c \
					parse/env_lists.c \
					parse/token_lists.c \
					parse/command_tree.c \
					signals/signals.c \
					built_in/ft_cd.c         \
					built_in/ft_env.c         \
					built_in/ft_pwd.c          \
					built_in/ft_exit.c	        \
					built_in/ft_echo.c		     \
					built_in/ft_unset.c	 	      \
					built_in/ft_export.c		   \
					execute/builtin.c         	     \
					execute/execute.c                 \
					execute/heredoc.c 				   \
					execute/redirection.c               \
					execute/gold_process.c		         \
					execute/path_processing.c             \
					args.c

GREEN			=	'\033[1;32m'
NONE			=	'\033[0m'
CC				=	cc
NAME			=	minishell
HEADERS			=	includes/minishell.h includes/struct.h includes/macros.h libft/libft.h
OBJ				=	$(SRC:.c=.o)
CFLAGS			=	-Wall -Wextra -Werror -g
READLINE		=	-lreadline

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE) libft/libft.a  -L /Users/$(USER)/.brew/opt/readline/lib

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@  -I /Users/$(USER)/.brew/opt/readline/include

clean:
	@make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
