/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:09:38 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/07 00:22:16 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	quoted_word(char **s, char *tmp, int i[3])
// {
// 	while (i[2] && *(tmp + i[0]) && *(tmp + i[0]) != i[2])
// 	{
// 		if (i[2] == '\"')
// 		{
// 			if (*(tmp + i[0]) == '$')
// 				expand(s, tmp, i);
// 			else if (*(tmp + i[0]) != '$' && *(tmp + i[0]) != '\"')
// 			{
// 				*(*s + i[1]) = *(tmp + i[0]);
// 				i[0] += 1;
// 				i[1] += 1;
// 			}
// 		}
// 		if (i[2] == '\'' && *(tmp + i[0]) != '\'')
// 		{
// 			*(*s + i[1]) = *(tmp + i[0]);
// 			i[0] += 1;
// 			i[1] += 1;
// 		}
// 	}
// }

// void	operat_word(char **s, char *tmp, int i[3])
// {
// 	if (*(tmp + i[0]))
// 	{
// 		while (*(tmp + i[0]) && is_operator(*(tmp + i[0])))
// 		{
// 			*(*s + i[1]) = *(tmp + i[0]);
// 			i[0] += 1;
// 			i[1] += 1;
// 		}
// 		if (*(tmp + i[0]) == '\"' || *(tmp + i[0]) == '\'')
// 		{
// 			i[2] = *(tmp + i[0]);
// 			i[0] += 1;
// 		}
// 	}
// 	quoted_word(s, tmp, i);
// }

// void	simple_word(char **s, char *tmp, int i[3])
// {
// 	while (*(tmp + i[0]) && !is_operator(*(tmp + i[0])) 
// 	&& *(tmp + i[0]) != '\"' && *(tmp + i[0]) != '\'')
// 	{
// 		if (*(tmp + i[0]) == '$')
// 			expand(s, tmp, i);
// 		else
// 		{
// 			*(*s + i[1]) = *(tmp + i[0]);
// 			i[0] += 1;
// 			i[1] += 1;
// 		}
// 	}
// 	operat_word(s, tmp, i);
// }

/*
	this function will find the lenght of a token after removing quotes and
	expanding envirement variables
*/
static int	token_len(char *str)
{
	int		i;
	char	c;
	int		len;

	i = 0;
	len = 0;
	while (*(str + i))
	{
		c = 0;
		(*(str + i) == '$' && (len += expansion_value(str + i + 1, &i)));
		(*(str + i) != '$' && (++len) && (++i));
		if (*(str + i) && (*(str + i) == '\'' || *(str + i) == '\"'))
			c = *(str + i++);
		while (c && *(str + i) && *(str + i) != c)
		{
			(c == '\"' && *(str + i) == '$'
				&& (len += expansion_value(str + i + 1, &i)));
			((c != '\"' || *(str + i) != '$') && (++len) && (++i));
		}
		if (*(str + i) && (*(str + i) == '\'' || *(str + i) == '\"'))
			i++;
	}
	return (len);
}

/*
	this function will remove quotes and expand envirement variables and
	set token class
	i[0] for iterating tmp, i[1] for iterating s, i[3] for storing \" and \' :)
*/
int	process_token(t_shell *data, t_tokens *token)
{
	char	*tmp;
	char	*s;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	s = malloc(sizeof(char) * (token_len(token->string) + 1));
	if (!s)
		return (throw_error(ERR_MAL));
	token_class(token);
	tmp = token->string;
	while (*(tmp + i[0]))
	{
		i[2] = 0;
		fill_token(&s, tmp, i);
	}
	*(s + i[1]) = '\0';
	free(token->string);
	token->string = s;
	// check_syntax(data);
	// command_tree(data);
	return (0);
}
