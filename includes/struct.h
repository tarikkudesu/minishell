/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:05:47 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/08 15:06:13 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_shell		t_shell;
typedef struct s_tokens		t_tokens;
typedef enum e_class		t_class;
typedef struct s_env		t_env;

enum	e_class
{
	WORD = 1,
	OUTPUT_RED,
	INPUT_RED,
	HEREDOC,
	APPEND,
	PIPE,
};

struct s_env
{
	char			*environ;
	struct s_env	*next;
	struct s_env	*prev;
};

struct	s_tokens
{
	char		*string;
	int			index;
	t_class		class;
	t_tokens	*right;
	t_tokens	*left;
};

struct	s_shell
{
	t_env		*env;
	char		*line;
	t_tokens	*token;
	int			**pipes;
	int			*pids;
	int			number_of_tokens;
	int			number_of_commands;
	int			status;
};

#endif
