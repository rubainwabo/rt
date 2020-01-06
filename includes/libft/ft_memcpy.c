/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:56:44 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/23 17:04:12 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s1;
	char	*s2;

	if (n == 0 || dst == src)
		return (dst);
	s1 = (char*)dst;
	s2 = (char*)src;
	while (--n)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = *s2;
	return (dst);
}
