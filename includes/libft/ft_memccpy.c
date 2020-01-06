/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:37:44 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/23 17:03:58 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	if (dst == src || n == 0)
		return (NULL);
	i = 0;
	c1 = (unsigned char*)dst;
	c2 = (unsigned char*)src;
	while (i < n)
	{
		c1[i] = c2[i];
		if (c1[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
