SRC				=	srcs/main.c srcs/token.c srcs/help.c
HEADERS			=	includes/minishell.h includes/struct.h includes/macros.h libft/libft.h
CFLAGS			=	-Wall -Wextra -Werror -g
READLINE		=	-lreadline
all: $(NAME) clean
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE) libft/libft.a
	@echo $(GREEN) "\n compilation done" $(NONE)
clean:
	@make -C libft clean
	@echo $(GREEN) "clean done\n" $(NONE)
fclean: clean
	@make -C libft fclean
	@echo $(GREEN) "fclean done\n" $(NONE)
re: fclean all
.PHONY: clean
