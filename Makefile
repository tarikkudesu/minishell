SRC				=	srcs/main.c  \
					srcs/error.c  \
					pars/lexer.c   \
					pars/syntax.c   \
					pars/minifun.c   \
					pars/classify.c   \
					pars/env_lists.c   \
					pars/expansion.c    \
					pars/fill_token.c    \
					pars/token_lists.c    \
					pars/command_tree.c	   \
					pars/process_token.c    \
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
					signals/signals.c

GREEN			=	'\033[1;32m'
NONE			=	'\033[0m'
CC				=	cc
NAME			=	minishell
HEADERS			=	includes/minishell.h includes/struct.h includes/macros.h libft/libft.h
OBJ				=	$(SRC:.c=.o)
CFLAGS			=	-Wall -Wextra -Werror -g
READLINE		=	-lreadline

all: $(NAME) clean

$(NAME): $(OBJ) $(HEADERS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE) libft/libft.a  -L /Users/tamehri/.brew/opt/readline/lib

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@  -I /Users/tamehri/.brew/opt/readline/include

clean:
	@make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
