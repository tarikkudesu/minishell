/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:04:55 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/16 14:13:46 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/*-------------------execute_operations-----------------*/

void		dup_in_out(int input, int output);
void		process(t_shell *data, t_tokens *token, int input, int output);
void		exec_builtin(t_shell *data, char **cmd_argd);
char		*absolute_path(char	*cmd, char **env);
void		execute(t_shell *data);
void		signals(void);
int			heredoc(char *del);
int			is_builtin(char *string);
int			red_process(t_tokens *token, int input, int output);

/*-----------------end_execute_operations---------------*/

/*--------------------built_in_command------------------*/

void		ft_exit(t_shell *data, char **args);
void		ft_pwd(t_shell *data);
void		ft_cd(t_shell *data, char *path);
void		ft_env(t_shell *data, t_env *env);
void		ft_echo(t_shell *data, char **argument);
void		ft_unset(t_shell *data, t_env **env, char **vars);
void		ft_export(t_shell *data, t_env **env, char **to_add, int add);
void		add_export(t_shell *data, t_env **env, char **to_add);

/*------------------end_built_in_command----------------*/

/*----------------environement_operation---------------*/

void		env_add_back(t_env **linked, t_env *node);
void		get_env(t_shell *data, char **env);
t_env		*env_new(char *name, char *value);
void		env_clear(t_env **env);

/*--------------end_environement_operation--------------*/

#endif