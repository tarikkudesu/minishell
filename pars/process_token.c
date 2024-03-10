/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:09:38 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/10 12:08:58 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	this function will find the lenght of a token after removing quotes and
	expanding envirement variables
	var[0] is for iterating str
*/
static int	token_len(t_shell *data, char *str)
{
	int	var[3];

	(assign(var, 0), assign(var + 1, 0));
	while (*(str + var[0]))
	{
		if (*(str + var[0]) == '\"' || *(str + var[0]) == '\'')
		{
			(assign(var + 2, *(str + var[0])), assign(var, var[0] + 1));
			while (*(str + var[0]) && *(str + var[0]) != var[2])
			{
				if (*(str + var[0]) == '$')
					var[1] += expansion_value_1(data, str + var[0], var);
				else
					(assign(var, var[0] + 1), assign(var + 1, var[1] + 1));
			}
			var[0]++;
		}
		else if (*(str + var[0]) == '$')
			var[1] += expansion_value_1(data, str + var[0], var);
		else
			(assign(var, var[0] + 1), assign(var + 1, var[1] + 1));
	}
	return (var[1]);
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
	s = malloc(sizeof(char) * (token_len(data, token->string) + 1));
	if (!s)
		return (throw_error(ERR_MAL));
	token_class(token);
	tmp = token->string;
	while (*(tmp + i[0]))
	{
		i[2] = 0;
		fill_token(data, &s, tmp, i);
	}
	*(s + i[1]) = '\0';
	free(token->string);
	token->string = s;
	return (0);
}
