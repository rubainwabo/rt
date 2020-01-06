/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 12:58:27 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/09 14:18:36 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ch;
	size_t			i;

	i = -1;
	ch = (unsigned char*)s;
	while (++i < n)
	{
		if (ch[i] == (unsigned char)c)
			return ((void*)&ch[i]);
	}
	return (NULL);
}
