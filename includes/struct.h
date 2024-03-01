/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:05:47 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/01 23:29:49 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

typedef	struct	s_cmds
{
	int		is_last;
	int		pid;
	int		nb_operator; // for multiple redirection in one cmd ... | > a > b > ... | > ...
	t_list	*op; // list of operators > or >> in case we have multiple
	char	*abs_path; // absolute path of cmd
	char	**cmd; // splited argument "ls -l" => "ls" "-l"
}	t_cmds;

typedef	struct	s_shell
{
	t_cmds	**cmds;
	char	**env;
}	t_shell;

#endif
