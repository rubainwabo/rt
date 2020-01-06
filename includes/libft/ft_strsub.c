/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 00:51:10 by rkamegne          #+#    #+#             */
/*   Updated: 2019/11/25 14:51:36 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = NULL;
	if (s != NULL)
	{
		if (!(str = (char*)malloc(sizeof(char) * len + 1)))
			return (NULL);
		if (ft_strlen(s) < start)
		{
			free(str);
			return (NULL);
		}
		while (i < len)
		{
			str[i] = s[i + start];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
