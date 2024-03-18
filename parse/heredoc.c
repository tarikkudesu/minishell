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

int	expansion_value_3(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (free(name), ft_strlen(env->value));
		env = env->next;
	}
	return (free(name), 0);
}

int	expansion_value_2(t_shell *data, char *str, int *i)
{
	int		len;
	char	*name;

	len = 0;
	while (*(str + len + 1) && ft_isalnum(*(str + len + 1)))
		len++;
	(*i) += len + 1;
	if (!len)
		return (1);
	name = ft_substr(str + 1, 0, len);
	if (!name)
		return (ft_putendl_fd(ERR_MAL, 2), 0);
	return (expansion_value_3(data->env_list, name));
}

int	expansion_value_1(t_shell *data, char *str, int *i)
{
	int		len;
	char	*nbr;

	len = 0;
	if (ft_isdigit(*(str + 1)))
	{
		(*i) += 2;
		return (0);
	}
	else if (*(str + 1) == '?')
	{
		nbr = ft_itoa(data->status);
		if (!nbr)
			return (0);
		len = ft_strlen(nbr);
		(*i) += 2;
		return (free(nbr), len);
	}
	return (expansion_value_2(data, str, i));
}

void	putline_fd(char *s, int fd)
{
	char	*env;
	int		i;
	int		j;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (*(s + i))
	{
		if (*(s + i) == '$')
		{
			env = meta_char_string(s, &i);
			// protect
			j = 0;
			while (*(env + j))
				write(fd, env + j++, 1);
			free(env);
		}
		else
		{
			write(fd, s + i, 1);
			i++;
		}
	}
	write(fd, "\n", 1);
}

static void	heredoc_fill(char *del, int fd, int exp)
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
		putline_fd(line, fd);
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
	data->doc_fd = open("/tmp/.mini_245", O_RDONLY);
	if (data->doc_fd < 0)
		return (perror(ERR_OPEN), 1);
	if (unlink("/tmp/.mini_245") < 0)
		return (perror(ERR_UNLINK), 1);
	heredoc_fill(del, fd, exp);
	close(fd);
	return (0);
}


int	del_len(char *str)
{
	int	c;
	int	i;

	i = 0;
	while (*str)
	{
		c = 0;
		if (meta_char(*str) && *str != '"' && *str != '\'' && *str != '$')
			break;
		if (*str == '\'' || *str == '"')
		{
			c = *str;
			str++;
			while (*str && *str != c)
			{
				str++;
				i++;
			}
		}
		else
			i++;
		str++;
	}
	return (i);
}

int	fill_del(char *str, char *del)
{
	int	i;
	int	c;
	int	exp;

	i = 0;
	exp = 0;
	while (*str)
	{
		c = 0;
		if (meta_char(*str) && *str != '"' && *str != '\'' && *str != '$')
			break ;
		if (*str == '\'' || *str == '"')
		{
			exp = 1;
			c = *str++;
			while (*str && *str != c)
				del[i++] = *str++;
		}
		else
			del[i++] = *str;
		str++;
	}
	del[i] = '\0';
	return (exp);
}

void	skip_space(char *str, int *index)
{
	while (*str && *str == ' ')
	{
		str++;
		(*index)++;
	}
}

int	here_doc(t_shell *data, int *index)
{
	t_tokens	*token;
	char		*del;
	int			exp;

	skip_space(data->line + *index, index);
	if (meta_char(data->line[*index]) && data->line[*index] != '"' && data->line[*index] != '\'' && data->line[*index] != '$')
		return (pars_error(data));
	del = malloc(sizeof(char) * (del_len(data->line + *index) + 1));
	if (!del)
		return (throw_error(ERR_MAL));
	exp = fill_del(data->line + *index, del);
	token = tokennew(del);
	if (!token)
		return (throw_error(ERR_MAL));
	tokenadd_back(&data->tokens, token);
	heredoc(data, del, exp);
	return (0);
}
