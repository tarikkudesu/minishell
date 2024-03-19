/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:45:06 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/19 16:58:06 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	del_len(char *str)
{
	int	c;
	int	i;

	i = 0;
	while (*str)
	{
		c = 0;
		if (meta_char(*str) && *str != '"' && *str != '\'' && *str != '$')
			break ;
		if (*str == '\'' || *str == '"')
		{
			c = *str++;
			while (*str && *str++ != c)
				i++;
		}
		else
			i++;
		str++;
	}
	return (i);
}

int	fill_delimeter(char *str, char *del, int *index)
{
	int	i;
	int	c;
	int	exp;

	i = 0;
	exp = 1;
	while (*(str + *index))
	{
		c = 0;
		if (meta_char(*(str + *index)) && *(str + *index) != '"' \
			&& *(str + *index) != '\'' && *(str + *index) != '$')
			break ;
		if (*(str + *index) == '\'' || *(str + *index) == '"')
		{
			exp = 0;
			c = *(str + (*index)++);
			while (*(str + *index) && *(str + *index) != c)
				del[i++] = *(str + (*index)++);
		}
		else
			del[i++] = *(str + *index);
		(*index)++;
	}
	del[i] = '\0';
	return (exp);
}

int	heredoc_init(t_shell *data, int *index)
{
	t_tokens	*token;
	char		*del;
	int			exp;

	while (data->line[*index] && isspace(data->line[*index]))
		(*index)++;
	if (meta_char(data->line[*index]) && data->line[*index] != '"' \
		&& data->line[*index] != '\'' && data->line[*index] != '$')
		return (1);
	del = malloc(sizeof(char) * (del_len(data->line + *index) + 1));
	if (!del)
		return (throw_error(ERR_MAL));
	exp = fill_delimeter(data->line, del, index);
	token = tokennew(del);
	if (!token)
		return (throw_error(ERR_MAL));
	token->class = FILE_NAME;
	tokenadd_back(&data->tokens, token);
	if (!*del && exp)
		return (pars_error(data));
	if (heredoc(data, del, exp))
		return (1);
	return (0);
}
