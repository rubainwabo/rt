/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:16:45 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/23 17:03:23 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ch;

	if (len == 0)
		return (b);
	ch = (unsigned char*)b;
	while (len--)
	{
		*ch = (unsigned char)c;
		if (len)
			ch++;
	}
	return (b);
}
