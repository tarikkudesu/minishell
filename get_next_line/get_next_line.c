/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:52:05 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/09 19:23:34 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_to_nl(char *stat, int fd)
{
	char	*buff;
	int		bytes;

	buff = malloc(sizeof(char) * 256);
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!gn_strchr(stat) && bytes)
	{
		bytes = read(fd, buff, 256);
		if (bytes == -1)
		{
			free(buff);
			buff = NULL;
			return (NULL);
		}
		*(buff + bytes) = '\0';
		stat = gn_strjoin(stat, buff);
	}
	free(buff);
	buff = NULL;
	return (stat);
}

char	*ft_before_nl(char *stat)
{
	char	*line;
	int		i;

	if (!*stat)
		return (NULL);
	i = 0;
	while (*(stat + i) && *(stat + i) != '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (*(stat + i) && *(stat + i) != '\n')
	{
		*(line + i) = *(stat + i);
		i++;
	}
	if (*(stat + i) == '\n')
		*(line + i++) = '\n';
	*(line + i) = '\0';
	return (line);
}

char	*ft_after_nl(char *stat)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (*(stat + i) && *(stat + i) != '\n')
		i++;
	if (!*(stat + i))
	{
		free(stat);
		return (stat = NULL, NULL);
	}
	line = malloc(sizeof(char) * (gn_strlen(stat + i) + 1));
	if (!line)
	{
		free(stat);
		return (stat = NULL, NULL);
	}
	i++;
	j = 0;
	while (*(stat + i))
		*(line + j++) = *(stat + i++);
	*(line + j) = '\0';
	free(stat);
	return (stat = NULL, line);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*line;

	if (fd < 0)
	{
		if (stat)
		{
			free(stat);
			stat = NULL;
		}
		return (NULL);
	}
	stat = read_to_nl(stat, fd);
	if (!stat)
		return (NULL);
	line = ft_before_nl(stat);
	stat = ft_after_nl(stat);
	return (line);
}
