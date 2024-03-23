/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:45:06 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/23 18:20:49 by tamehri          ###   ########.fr       */
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
		if (meta_char(*str) && *str != '"' && *str != '\'' && *str != '$')
			break ;
		c = 0;
		if (*str == '$' && (*(str + 1) == '\'' || *(str + 1) == '\"'))
			str += 2;
		else if (*str == '\'' || *str == '"')
		{
			c = *str++;
			while (*str && *str++ != c)
				i++;
			str++;
		}
		else if (*str)
		{
			str++;
			i++;
		}
	}
	return (i);
}

int	fill_delimeter(char *str, char *del, int *d, int exp)
{
	int	i;
	int	c;

	i = 0;
	while (*(str + *d))
	{
		if (meta_char(*(str + *d)) && *(str + *d) != '"' && \
			*(str + *d) != '\'' && *(str + *d) != '$')
			break ;
		c = 0;
		if (*(str + *d) == '$' && (*(str + *d + 1) == '\'' \
			|| *(str + *d + 1) == '"'))
			(*d) += 2;
		else if (*(str + *d) == '\'' || *(str + *d) == '"')
		{
			exp = 0;
			c = *(str + (*d)++);
			while (*(str + *d) && *(str + *d) != c)
				*(del + i++) = *(str + (*d)++);
			(*d)++;
		}
		else
			*(del + i++) = *(str + (*d)++);
	}
	return (*(del + i) = '\0', exp);
}

int	heredoc_init(t_shell *data, int *index)
{
	t_tokens	*token;
	char		*del;
	int			exp;

	while (data->line[*index] && ft_isspace(data->line[*index]))
		(*index)++;
	if (meta_char(data->line[*index]) && data->line[*index] != '"' \
		&& data->line[*index] != '\'' && data->line[*index] != '$')
		return (pars_error(data));
	del = malloc(sizeof(char) * (del_len(data->line + *index) + 1));
	if (!del)
		return (throw_error(data, ERR_MAL, 1));
	exp = fill_delimeter(data->line, del, index, 1);
	token = tokennew(del);
	if (!token)
		return (throw_error(data, ERR_MAL, 1));
	token->class = FILE_NAME;
	tokenadd_back(&data->tokens, token);
	if (!*del && exp)
		return (pars_error(data));
	if (exp)
		token->class = HEREDOC_E;
	else
		token->class = HEREDOC_O;
	return (0);
}
