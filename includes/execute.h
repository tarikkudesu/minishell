/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:04:55 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/18 21:58:11 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/*-------------------execute_operations-----------------*/

void		signals(void);
void		execute(t_shell *data);
int			is_builtin(char *string);
void		single_cmd(t_shell *data);
char		**get_args(t_tokens *token);
void		dup_in_out(int input, int output);
char		*absolute_path(char	*cmd, char **env);
void		ft_execve(t_shell *data, char **cmd_arg);
void		exec_builtin(t_shell *data, char **cmd_argd);
void		process(t_shell *data, t_tokens *token, int input, int output);
int			red_process(t_shell *data, t_tokens *token, int input, int output);

/*-----------------end_execute_operations---------------*/

/*--------------------built_in_command------------------*/

void		ft_pwd(t_shell *data);
void		ft_cd(t_shell *data, char *path);
void		ft_env(t_shell *data, t_env *env);
void		ft_exit(t_shell *data, char **args);
void		ft_echo(t_shell *data, char **argument);
void		ft_unset(t_shell *data, t_env **env, char **vars);
void		add_export(t_shell *data, t_env **env, char **to_add);
void		ft_export(t_shell *data, t_env **env, char **to_add, int add);

/*------------------end_built_in_command----------------*/

#endif