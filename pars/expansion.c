/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:48:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/04 17:50:29 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expansion_value(char *str, int *i) //changed
{
	int		len;
	char	*var;
	char	*val;

	len = 0;
	while (*(str + len) && ft_isalnum(*(str + len)))
		len++;
	(*i) += len + 1;
	if (!len)
		return (1);
	var = ft_substr(str, 0, len);
	if (!var)
		return (0);
	val = getenv(var);
	if (!val)
		return (0);
	return (free(var), ft_strlen(val));
}

void	expand(char **s, char *tmp, int i[3]) // changed
{
	int		x;
	int		len;
	char	*var;
	char	*val;

	x = 0;
	len = 0;
	while (*(tmp + i[0] + len + 1) && ft_isalnum(*(tmp + i[0] + len + 1)))
		len++;
	((!len) && (*(*s + i[1]) = *(tmp + i[0])) && (i[0] += 1) && (i[1] += 1));
	if (!len)
		return ;
	var = ft_substr(tmp, i[0] + 1, len);
	if (!var)
		return ;
	i[0] += len + 1;
	val = getenv(var);
	if (!val)
		return ;
	while (*(val + x))
	{
		*(*s + i[1]) = *(val + x);
		i[1] += 1;
		x++;
	}
}
