/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:14:37 by rkamegne          #+#    #+#             */
/*   Updated: 2019/04/08 15:27:09 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_isalpha_spec(int c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'o' || c == 'u' ||
		c == 'x' || c == 'X' || c == '%' || c == 'f' || c == 'p' || c == 'b' ||
		c == 'U')
		return (1);
	return (0);
}

char			*ft_strchr_alpha(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char*)&s[i]);
		if (ft_isalpha_spec(s[i]))
			break ;
		i++;
	}
	if (c == 0)
		return ((char*)&s[i]);
	return (NULL);
}
