/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:56:24 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/17 19:51:50 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_fill(char *del, int fd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = readline("");
		if (!del && !*line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (!line || !ft_strcmp(line, del))
			break ;
		ft_putendl_fd(line, fd);
		(free(line), line = NULL);
	}
	if (line)
		free(line);
}

int	heredoc(t_shell *data, char *del)
{
	int		fd;

	fd = open("/tmp/.mini_245", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->doc_fd < 0)
		return (perror(ERR_OPEN), 1);
	data->doc_fd = open("/tmp/.mini_245", O_RDONLY);
	if (fd < 0)
		return (perror(ERR_OPEN), 1);
	// if (unlink(".tmp") < 0)
	// 	return (perror(ERR_UNLINK), 1);
	heredoc_fill(del, fd);
	close(fd);
	return (0);
}
