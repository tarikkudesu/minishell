/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:50 by tamehri           #+#    #+#             */
/*   Updated: 2024/06/01 18:54:34 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "macros.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>

/*-------------------execute_operations-----------------*/

void		signals(void);
void		ctl_c(int signal);
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
void		add_export(t_shell *data, char **to_add);
void		ft_unset(t_shell *data, t_env **env, char **vars);
void		ft_export(t_shell *data, t_env **env, char **to_add, int add);

/*------------------end_built_in_command----------------*/

/*-----------------------parse-------------------------*/

t_tokens	*init_token(t_shell *data, char *line, int *index, int t);
int			heredoc(t_shell *data, char *del, t_class exp);
char		*meta_char_string(char *string, int *index);
void		token_stat(t_shell *data, t_tokens *token);
int			heredoc_init(t_shell *data, int *index);
char		*token_string(char *string, int *index);
int			expand(t_shell *data, t_tokens *token);
int			class_operator(t_tokens *token);
int			ft_strcmp(char *s1, char *s2);
void		token_class(t_tokens *token);
void		token_class(t_tokens *token);
void		command_tree(t_shell *data);
int			check_quoting(char *str);
void		read_line(t_shell *data);
int			exclude(t_tokens *token);
int			syntax(t_shell *data);
int			skip(t_tokens *token);
int			lexer(t_shell *data);
int			pars(t_shell *data);
int			ft_isspace(char c);
int			meta_char(char c);

/*---------------------end_parse-----------------------*/

/*--------------------utils_functions-------------------*/

char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
int			ft_atoi(const char *str);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
char		*ft_itoa(int n);

/*------------------utils_functions_end------------------*/

/*-------------------error_handling--------------------*/

int			throw_error(t_shell *data, char *str, int status);
void		free_2d_int(int **free2d, int nb_pipe);
void		ft_throw(char *strerr, int status);
void		free_2d_char(char **free2d);
int			pars_error(t_shell *data);
void		my_free(char *ptr);

/*-------------------error_handling--------------------*/

/*----------------environement_operation---------------*/

void		get_env(t_shell *data, char **env, char **def_env, char *name);
void		env_add_back(t_env **linked, t_env *node);
char		*env_join(char const *s1, char const *s2);
t_env		*env_new(char *name, char *value);
char		**env_to_array(t_env *env_list);
void		env_clear(t_env **env);
int			env_size(t_env *env);
void		print(t_env *env);

/*--------------end_environement_operation--------------*/

/*--------------------token_operation-------------------*/

void		tokenadd_back(t_tokens **lst, t_tokens *new);
void		clear_command_tree(t_tokens **tree);
void		tokenclear(t_tokens **lst);
int			tokensize(t_tokens *lst);
t_tokens	*tokennew(char *content);

/*------------------end_token_operation-----------------*/


/* FUNCTIONS */
void	exit_if(int processes, int status);

#endif
