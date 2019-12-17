/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:29 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/23 17:33:47 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	i1;
	size_t	i2;

	i = 0;
	i1 = ft_strlen(dst);
	i2 = ft_strlen(src);
	if (size == 0)
		return (i2);
	if (size - 1 < i1)
		return (i2 + size);
	while (i1 + i < size - 1 && src[i] != '\0')
	{
		dst[i1 + i] = src[i];
		i++;
	}
	dst[i1 + i] = '\0';
	return (i1 + i2);
}
