/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:50 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/14 13:35:13 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "macros.h"
# include "../libft/libft.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

/*-----------------------parse-------------------------*/

char	    *meta_char_string(char *string, int *index);
void	    token_stat(t_shell *data, t_tokens *token);
void	    expand(t_shell *data, t_tokens *token);
int	        ft_strcmp(char *s1, char *s2);
void	    token_class(t_tokens *token);
void        token_class(t_tokens *token);
void	    command_tree(t_shell *data);
int	        check_syntax(t_shell *data);
int	        skip(t_tokens *token);
int	        keep(t_tokens *token);
int	        add(t_tokens *token);
int	        lexer(t_shell *data);
int         pars(t_shell *data);
int         meta_char(char c);

/*---------------------end_parse-----------------------*/

/*-------------------error_handling--------------------*/

void		ft_throw(char *strerr, int status);
void		free_2d_char(char **free2d);
void		free_2d_int(int **free2d);
int			throw_error(char *str);
void		my_free(char *ptr);

/*-------------------error_handling--------------------*/

/*----------------environement_operation---------------*/

void		env_add_back(t_env **linked, t_env *node);
void		get_env(t_shell *data, char **env);
t_env		*env_new(char *name, char *value);
void		env_clear(t_env **env);
int	        env_size(t_env *env);
void	    print(t_env *env);

/*--------------end_environement_operation--------------*/

/*--------------------token_operation-------------------*/

void		tokenadd_back(t_tokens **lst, t_tokens *new);
void		clear_command_tree(t_tokens **tree);
void		tokenclear(t_tokens **lst);
int			tokensize(t_tokens *lst);
t_tokens	*tokennew(char *content);

/*------------------end_token_operation-----------------*/

/*-------------------execute_operations-----------------*/
void		process(t_shell *data, t_tokens *token, int input, int output);
void		red_process(t_tokens *token, int input, int output, int *nbr);
void		exec_builtin(t_shell *data, char **cmd_argd);
char		*absolute_path(char	*cmd, char **env);
int			is_builtin(char *string);
void		execute(t_shell *data);
int			heredoc(char *del);
void		signals(void);

/*-----------------end_execute_operations---------------*/

/*--------------------built_in_command------------------*/

void	    ft_export(t_env **env, char **to_add, int add);
void	    ft_unset(t_env **env, char **vars);
void	    ft_echo(char **argument);
void	    ft_pwd(t_shell *data);
void		ft_exit(char **args);
void	    ft_env(t_env *env);
void	    ft_cd(char *path);

/*------------------end_built_in_command----------------*/


/* FUNCTIONS */
int	env_size(t_env *env);
char	**env_to_array(t_env *env_list);
int	class_operator(t_tokens *token);

#endif
