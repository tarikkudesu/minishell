/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:50 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/11 10:26:43 by tamehri          ###   ########.fr       */
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

// int			expansion_value_1(t_shell *data, char *str, int *i);
// int			ft_strcmp(char *s1, char *s2);
// int			bunny_ears(char **s, char c);
// int 		    check_syntax(t_shell *data);
// void		    command_tree(t_shell *data);
// void		    assign(int *nbr, int add);
// int			lexer(t_shell *data);
// int			is_operator(int c);
// int			is_space(int c);

/*---------------------end_parse-----------------------*/

/*-------------------error_handling--------------------*/

int			throw_error(char *str);
void		ft_throw(char *strerr, int status);

/*-------------------error_handling--------------------*/

/*----------------environement_operation---------------*/

void		env_add_back(t_env **linked, t_env *node);
void		get_env(t_shell *data, char **env);
t_env		*env_new(char *name, char *value);
void		env_clear(t_env **env);

/*--------------end_environement_operation--------------*/

/*--------------------token_operation-------------------*/

// void		fill_token(t_shell *data, char **s, char *tmp, int i[3]);
// char		*init_token(char const *s, int *index, int lenght);
// int			process_token(t_shell *data, t_tokens *token);
void		tokenadd_back(t_tokens **lst, t_tokens *new);
void		clear_command_tree(t_tokens **tree);
// void		token_class(t_tokens *token);
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
void	    ft_env(t_env *env);
void		ft_exit(char **args);
void	    ft_cd(char *path);
void	    ft_pwd(void);

/*------------------end_built_in_command----------------*/

/* FUNCTIONS */
int	       init_leaf(t_shell *data, char *string, t_tokens *class, int split);
void	    command_tree(t_shell *data);
void	    expand(t_shell *data, t_tokens *token);
void        token_class(t_tokens *token);
int	        check_syntax(t_shell *data);
int	        ft_strcmp(char *s1, char *s2);
int         meta_char(char c);
int	        add(t_tokens *token);
int	        skip(t_tokens *token);
int	        keep(t_tokens *token);
int         pars(t_shell *data);
int	        lexer(t_shell *data);
void	    print(t_env *env);
void	    free_2d(char **free2d);

#endif
