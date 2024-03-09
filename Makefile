SRC				=	srcs/main.c\
					pars/lexer.c\
					srcs/error.c \
					pars/syntax.c \
					pars/minifun.c \
					pars/classify.c \
					pars/expansion.c \
					built_in/ft_cd.c  \
					execute/execute.c  \
					signals/signals.c	\
					built_in/ft_env.c    \
					built_in/ft_pwd.c     \
					pars/token_lists.c 	   \
					built_in/ft_exit.c	    \
					built_in/ft_echo.c		 \
					pars/command_tree.c	   	  \
					built_in/ft_unset.c	 	   \
					pars/process_token.c		\
					built_in/ft_export.c		 \
					execute/gold_process.c		  \
					execute/shell_environement.c   \
					built_in/double_linked_list.c   \

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
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE) libft/libft.a  -L /Users/ooulcaid/.brew/opt/readline/lib
	@echo $(GREEN) "compilation done" $(NONE)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@  -I /Users/ooulcaid/.brew/opt/readline/include

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
