/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:53:07 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/02 09:57:17 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ds;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	ds = ft_strlen(dst);
	if (dstsize <= ds)
		return (dstsize + ft_strlen(src));
	i = 0;
	while (i + ds + 1 < dstsize && *(src + i))
	{
		*(dst + ds + i) = *(src + i);
		i++;
	}
	*(dst + ds + i) = '\0';
	return (ds + ft_strlen(src));
}
