/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:26:05 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/02 09:56:49 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nl;

	nl = ft_strlen(needle);
	if (!haystack && !len)
		return (0);
	if (*needle == '\0' || needle == haystack)
		return ((char *)haystack);
	i = 0;
	while (*(haystack + i))
	{
		j = 0;
		while (j + i < len && *(haystack + i + j) == *(needle + j))
		{
			if (!*(haystack + i + j) && !*(needle + j))
				return ((char *)(haystack + i));
			j++;
		}
		if (*(needle + j) == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
