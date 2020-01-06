/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_putchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:30:43 by rkamegne          #+#    #+#             */
/*   Updated: 2019/04/16 13:39:33 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_putchar(int c, int len)
{
	int		i;
	char	*s;

	i = -1;
	if (!(s = ft_strnew(len)))
		return (NULL);
	while (++i < len)
		s[i] = c;
	s[i] = '\0';
	return (s);
}
