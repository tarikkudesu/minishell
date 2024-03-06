/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:50 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/06 10:53:37 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "macros.h"
# include "../libft/libft.h"

# include <fcntl.h>             //open
# include <stdio.h>             //printf, perror
# include <stdlib.h>            //malloc, free, exit, getenv
# include <unistd.h>            //write, read, access, close, fork, unlink, execve, dup, dup2, pipe, chdir, getcwd, isatty, ttyname, ttyslot
# include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line, rl_replace_line. rl_redisplay, add_history
# include <readline/history.h>  // readline, rl_clear_history, rl_on_new_line, rl_replace_line. rl_redisplay, add_history
# include <signal.h>            //signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/wait.h>          //wait, waitpid, wait3, wait4
# include <sys/stat.h>          //stat, lstat, fstat
# include <dirent.h>            //opendir, closedir
# include <string.h>            //strerror
# include <errno.h>             //errno

/* FUNCTIONS */
int			throw_error(char *str);
void		check_syntax(t_shell *data);
void		token_class(t_tokens *token);
int			ft_strcmp(char *s1, char *s2);
void		token_class(t_tokens *token);
int			expansion_value(char *str, int *i);
void		expand(char **s, char *tmp, int i[3]);
int			is_operator(int c);
int			is_space(int c);
int			bunny_ears(char **s, char c);
int			process_token(t_shell *data, t_tokens *token);
int			tokensize(t_tokens *lst);
void		tokenclear(t_tokens **lst);
void		tokenadd_back(t_tokens **lst, t_tokens *new);
t_tokens	*tokennew(char *content);
char		*init_token(char const *s, int *index, int lenght);
int			get_number_of_tokens(char *line);
int			lexer(t_shell *data);

#endif
