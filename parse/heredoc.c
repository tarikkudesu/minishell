/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:56:24 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/04/05 13:49:00 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_sig;

int	get_env_value(t_shell *data, char *name, int fd)
{
	t_env	*env;
	char	*nbr;

	env = data->env_list;
	if (*(name + 1) == '?')
	{
		nbr = ft_itoa(data->status);
		if (!nbr)
			return (throw_error(data, ERR_MAL, 1));
		ft_putstr_fd(nbr, fd);
		return (free(nbr), 0);
	}
	while (env)
	{
		if (!ft_strcmp(env->name, name + 1))
		{
			ft_putstr_fd(env->value, fd);
			break ;
		}
		env = env->next;
	}
	return (0);
}

int	putline_fd(t_shell *data, char *s, int fd, int exp)
{
	char	*env;
	int		i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == '$' && exp == HEREDOC_E)
		{
			env = meta_char_string(s + i, &i);
			if (!env)
				return (ft_putendl_fd(ERR_MAL, 2), 1);
			if (get_env_value(data, env, fd))
				return (free(env), 1);
			free(env);
		}
		else
			write(fd, s + i++, 1);
	}
	write(fd, "\n", 1);
	return (0);
}

static int	heredoc_fill(t_shell *data, char *del, int fd, t_class exp)
{
	char	*line;
	int		zero;

	line = NULL;
	zero = dup(STDIN_FILENO);
	while (!g_sig && 1)
	{
		line = readline("> ");
		if (!del && !*line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (!line || !ft_strcmp(line, del))
			break ;
		if (putline_fd(data, line, fd, exp))
			return (free(line), dup2(zero, 0), close(zero), 1);
		(free(line), line = NULL);
	}
	if (line)
		free(line);
	if (g_sig)
		return (data->status = 1, dup2(zero, STDIN_FILENO), close(zero), 1);
	(dup2(zero, STDIN_FILENO), close(zero));
	return (0);
}

int	heredoc(t_shell *data, char *del, t_class exp)
{
	int		fd;
	char	*name;

	name = ft_itoa((int)data);
	if (!name)
		return (perror(ERR_MAL), 1);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
		return (free(name), perror(ERR_OPEN), 1);
	if (data->doc_fd != -1)
		close(data->doc_fd);
	data->doc_fd = open(name, O_RDONLY);
	if (data->doc_fd < 0)
		return (free(name), perror(ERR_OPEN), 1);
	if (unlink(name) < 0)
		return (free(name), perror(ERR_UNLINK), 1);
	if (heredoc_fill(data, del, fd, exp))
		return (free(name), close(fd), 1);
	return (free(name), close(fd), 0);
}
