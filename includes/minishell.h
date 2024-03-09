/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:50 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/07 19:26:39 by ooulcaid         ###   ########.fr       */
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

/*-----------------------parse-------------------------*/

void		check_syntax(t_shell *data);
int			ft_strcmp(char *s1, char *s2);
int			expansion_value(char *str, int *i);
void		expand(char **s, char *tmp, int i[3]);
int			is_operator(int c);
int			is_space(int c);
int			bunny_ears(char **s, char c);
int			get_number_of_tokens(char *line);
int			lexer(t_shell *data);
void    	command_tree(t_shell *data);

/*---------------------end_parse-----------------------*/

/*-------------------error_handling--------------------*/

int			throw_error(char *str);
void		ft_throw(char *strerr);

/*-------------------error_handling--------------------*/

/*----------------environement_operation---------------*/

t_env		*get_env(char **env);
t_env	    *env_new(char *name, char *value);
void		env_add_back(t_env **linked, t_env *node);
void		print(t_env **env);
void		env_clear(t_env **env);

/*--------------end_environement_operation--------------*/

/*--------------------token_operation-------------------*/

char		*init_token(char const *s, int *index, int lenght);
int			process_token(t_shell *data, t_tokens *token);
int			tokensize(t_tokens *lst);
void		token_class(t_tokens *token);
void		tokenadd_back(t_tokens **lst, t_tokens *new);
void		tokenclear(t_tokens **lst);
t_tokens	*tokennew(char *content);

/*------------------end_token_operation-----------------*/

/*-------------------execute_operations-----------------*/
void		process(t_shell *data, t_tokens *token, int input, int output);
void		execute(t_shell *data);
void		signals(void);

/*-----------------end_execute_operations---------------*/

/*--------------------built_in_command------------------*/

void		ft_exit(void);
void		ft_cd(char *path, int ac);
void		ft_echo(t_tokens	*echo, char **av);
void		ft_env(t_env	*env);
void		ft_exit(void);
void		ft_export(t_env **env, char *to_add, int add);
void		ft_pwd(void);
void		unset(t_env **env, char *variable);

/*------------------end_built_in_command----------------*/


/* FUNCTIONS */
void	assign(int *nbr, int add);

#endif
