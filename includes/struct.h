/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:05:47 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/23 17:38:23 by tamehri          ###   ########.fr       */
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
	HEREDOC_E = 'E',
	HEREDOC_O = 'O',
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
	t_tokens	*tokens;
	char		*line;
	t_tokens	*tree;
	int			**pipes;
	int			cmd_nbr;
	int			status;
	int			doc_fd;
	char		*pwd;
	t_stat		stat;
	char		exp;
};

#endif
