SRC				=	srcs/main.c  \
					srcs/error.c  \
					parse/lexer.c \
					parse/parse.c \
					parse/minifun.c \
					parse/syntax.c \
					parse/env_lists.c \
					parse/token_lists.c \
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
