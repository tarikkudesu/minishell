/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:50 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/09 19:19:37 by tamehri          ###   ########.fr       */
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
int	        expansion_value_1(t_shell *data, char *str, int *i);
int			is_operator(int c);
int			is_space(int c);
void		assign(int *nbr, int add);
int			bunny_ears(char **s, char c);\
int			lexer(t_shell *data);
void    	command_tree(t_shell *data);

/*---------------------end_parse-----------------------*/

/*-------------------error_handling--------------------*/

int			throw_error(char *str);
void		ft_throw(char *strerr);

/*-------------------error_handling--------------------*/

/*----------------environement_operation---------------*/

void        get_env(t_shell *data, char **env);
t_env	    *env_new(char *name, char *value);
void		env_add_back(t_env **linked, t_env *node);
void		env_clear(t_env **env);

/*--------------end_environement_operation--------------*/

/*--------------------token_operation-------------------*/

void        fill_token(t_shell *data, char **s, char *tmp, int i[3]);
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
void		red_process(t_tokens *token, int input, int output, int *nbr);
char		*absolute_path(char	*cmd, char **env);
void		process(t_shell *data, t_tokens *token, int input, int output);
int			heredoc(char *del);
void		execute(t_shell *data);
int			is_builtin(char *string);
void		exec_builtin(t_shell *data, char **cmd_argd);

/*-----------------end_execute_operations---------------*/

/*--------------------built_in_command------------------*/

void		ft_unset(t_env **env, char **vars);
void		ft_pwd(void);
void		ft_export(t_env **env, char **to_add, int add);
void		ft_exit(void);
void		ft_env(t_env *env);
void		ft_echo(char **argument);
void		ft_cd(char *path);

/*------------------end_built_in_command----------------*/


/* FUNCTIONS */
char	*get_next_line(int fd);
size_t	gn_strlen(const char *s);
char	*gn_strchr(const char *s);
char	*gn_strjoin(char *s1, char *s2);
void	print(t_env *env);

#endif
