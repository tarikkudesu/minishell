/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:08:42 by tamehri           #+#    #+#             */
/*   Updated: 2023/11/03 23:10:20 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	sl;
	char	*res;

	if (!s)
		return (NULL);
	sl = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (sl + 1));
	if (!res)
		return (NULL);
	*(res + sl) = '\0';
	while (sl--)
		*(res + sl) = f((unsigned int)sl, *(s + sl));
	return (res);
}
