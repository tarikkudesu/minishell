/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:05:47 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/14 14:02:33 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_shell		t_shell;
typedef struct s_tokens		t_tokens;
typedef enum e_class		t_class;
typedef enum e_stat			t_stat;
typedef struct s_env		t_env;

enum	e_stat
{
	GENERAL = 'G',
	INQUOTE = 'S',
	INDQUOTE = 'D',
};

enum	e_class
{
	DEFAULT = 'D',
	WORD = 'W',
	WHITESPACE = 'S',
	DQUOTE = '"',
	QUOTE = '\'',
	PIPE = '|',
	IN_RED = '<',
	OUT_RED = '>',
	HEREDOC = 'H',
	APPEND = 'A',
	ENV = '$',
	FILE_NAME = 'F',
};

struct s_env
{
	char			*value;
	char			*name;
	struct s_env	*next;
	struct s_env	*prev;
};

struct	s_tokens
{
	char		*string;
	t_class		class;
	t_stat		stat;
	t_tokens	*left;
	t_tokens	*right;
};

struct	s_shell
{
	char		**env;
	t_env		*env_list;
	char		*line;
	t_tokens	*tokens;
	t_tokens	*tree;
	int			**pipes;
	int			*pids;
	int			number_of_commands;
	int			status;
	t_stat		stat;
};

#endif
