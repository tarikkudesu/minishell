SRC				=	srcs/main.c \
					pars/lexer.c \
					pars/process_token.c \
					pars/classify.c \
					pars/expansion.c \
					pars/minifun.c \
					pars/token_lists.c \
					pars/syntax.c \
					srcs/error.c

GREEN			=	'\033[1;32m'
NONE			=	'\033[0m'
CC				=	cc
NAME			=	minishell
HEADERS			=	includes/minishell.h includes/struct.h includes/macros.h libft/libft.h
OBJ				=	$(SRC:.c=.o)
CFLAGS			=	-Wall -Wextra -Werror -g
READLINE		=	-lreadline

all: $(NAME) clean

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE) libft/libft.a
	@echo $(GREEN) "compilation done" $(NONE)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@echo $(GREEN) "clean done" $(NONE)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo $(GREEN) "fclean done" $(NONE)

re: fclean all
	@echo $(GREEN) "re done" $(NONE)

.PHONY: clean
