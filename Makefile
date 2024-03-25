SRC				=	srcs/main.c    \
					srcs/error.c    \
					srcs/minishell.c \
					parse/lexer.c     \
					parse/parse.c      \
					parse/expand.c      \
					parse/syntax.c       \
					parse/minifun.c       \
					parse/classify.c       \
					parse/env_lists.c       \
					parse/token_lists.c      \
					parse/command_tree.c      \
					parse/heredoc_parse.c      \
					signals/signals.c           \
					built_in/ft_cd.c             \
					built_in/ft_env.c             \
					built_in/ft_pwd.c              \
					built_in/ft_exit.c	            \
					built_in/ft_echo.c		         \
					built_in/ft_unset.c	 	          \
					built_in/ft_export.c		       \
					built_in/export2.c                  \
					execute/single_cmd.c                 \
					execute/env_processing.c              \
					execute/builtin.c         	           \
					execute/execute.c                       \
					parse/heredoc.c 			        	 \
					execute/redirection.c                     \
					execute/gold_process.c		               \
					execute/path_processing.c                   \
					utils/ft_atoi.c                              \
					utils/ft_isalnum.c                            \
					utils/ft_isalpha.c                             \
					utils/ft_itoa.c                                 \
					utils/ft_putendl_fd.c                            \
					utils/ft_putstr_fd.c                              \
					utils/ft_split.c                                   \
					utils/ft_strchr.c                                   \
					utils/ft_strdup.c                                    \
					utils/ft_strjoin.c                                    \
					utils/ft_strlen.c                                      \
					utils/ft_strncmp.c                                      \
					utils/ft_substr.c

CC				=	cc
NAME			=	minishell
HEADERS			=	includes/struct.h includes/macros.h includes/minishell.h
OBJ				=	$(SRC:.c=.o)
CFLAGS			=	-Wall -Wextra -Werror
READLINE		=	-lreadline

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE) -L /Users/$(USER)/.brew/opt/readline/lib

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I /Users/$(USER)/.brew/opt/readline/include

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
