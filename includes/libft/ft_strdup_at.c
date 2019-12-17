/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:08:55 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/26 21:13:06 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_at(char *str, char c)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str)
	{
		if (!ft_strchr(str, c))
			return (NULL);
		while (str[i] != c)
			i++;
		if (!(s = (char *)malloc(sizeof(*s) * (ft_strlen(str) - (i + 1)) + 1)))
			return (NULL);
		i++;
		while (str[i])
			s[j++] = str[i++];
		s[j] = '\0';
		return (s);
	}
	return (NULL);
}
