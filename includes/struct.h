/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:05:47 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/03 14:51:36 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_shell 	t_shell;
typedef	struct	s_tokens	t_tokens;
typedef	enum	e_class		t_class;

enum	e_class
{
	WORD = 1,
	HERDOC,
	APPEND,
	TRUNC,
	INFILE,
	PIPE,
};

struct	s_tokens
{
	char		*token;
	t_class		class;
	t_tokens	*next;
};

// struct	s_cmds
// {
// 	t_class	op;
// 	char	*str_op;
	
// };


struct	s_shell
{
	char		*line;
	t_tokens	*token;
	// t_cmds	**cmds;
	// char	**env;
};


#endif
