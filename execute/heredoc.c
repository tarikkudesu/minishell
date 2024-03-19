/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:56:24 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/17 15:17:55 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	heredoc(char *del)
// {
// 	int		fd;
// 	int		fd2;
// 	char	*line;

// 	fd2 = open(".tmp", O_WRONLY | O_CREAT, 0644);
// 	if (fd2 < 0)
// 		ft_throw("ERROR_OPEN_HERDOC", 1);
// 	fd = open(".tmp", O_RDONLY);
// 	if (fd < 0)
// 		ft_throw("ERROR_OPEN_HERDOC", 1);
// 	if (unlink(".tmp") < 0)
// 		ft_throw("ERRON_UNLINK_HERDOC", 1);
// 	while (1)
// 	{
// 		ft_putstr_fd("> ", 1);
// 		line = readline("");
// 		if (!line || (!ft_strcmp(line, del)))
// 			break ;
// 		(write(fd2, line, ft_strlen(line)), write(fd2, "\n", 1));
// 		(free(line), line = NULL);
// 	}
// 	if (line)
// 		free(line);
// 	close(fd2);
// 	return (fd);
// }
