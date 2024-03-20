/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:56:24 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/20 11:59:45 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env_value(t_shell *data, char *name, int fd)
{
	t_env	*env;
	char	*nbr;

	env = data->env_list;
	if (*(name + 1) == '?')
	{
		nbr = ft_itoa(data->status);
		if (!nbr)
			return (throw_error(ERR_MAL));
		ft_putstr_fd(nbr, fd);
		return (free(nbr), 0);
	}
	while (env)
	{
		if (!ft_strcmp(env->name, name + 1))
			ft_putstr_fd(env->value, fd);
		env = env->next;
	}
	return (0);
}

int	putline_fd(t_shell *data, char *s, int fd)
{
	char	*env;
	int		i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == '$')
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

static void	heredoc_fill(t_shell *data, char *del, int fd, int exp)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!del && !*line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (!line || !ft_strcmp(line, del))
			break ;
		if (exp && putline_fd(data, line, fd))
			return (free(line));
		(free(line), line = NULL);
	}
	if (line)
		free(line);
}

int	heredoc(t_shell *data, char *del, int exp)
{
	int		fd;

	fd = open("/tmp/.mini_245", O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
		return (perror(ERR_OPEN), 1);
	if (data->doc_fd != -1)
		close(data->doc_fd);
	data->doc_fd = open("/tmp/.mini_245", O_RDONLY);
	if (data->doc_fd < 0)
		return (perror(ERR_OPEN), 1);
	if (unlink("/tmp/.mini_245") < 0)
		return (perror(ERR_UNLINK), 1);
	heredoc_fill(data, del, fd, exp);
	close(fd);
	return (0);
}
