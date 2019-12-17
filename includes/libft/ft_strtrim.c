/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 01:22:39 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/23 17:02:34 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		space_start(char const *s)
{
	int		i;

	i = 0;
	while (*s != '\0')
	{
		if (*s != ' ' && *s != '\t' && *s != '\n')
			return (i);
		s++;
		i++;
	}
	return (i);
}

static int		space_end(char const *s)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s);
	while (j-- >= 0)
	{
		if (s[j] != ' ' && s[j] != '\t' && s[j] != '\n')
			return (i);
		i++;
	}
	return (i);
}

char			*ft_strtrim(char const *s)
{
	int		start;
	int		end;
	int		i;
	int		var;
	char	*str;

	if (s == NULL)
		return (NULL);
	i = 0;
	start = space_start(s);
	end = space_end(s);
	var = ft_strlen(s) - end - start;
	if (var < 0)
		var = 0;
	str = (char*)malloc(sizeof(char) * var + 1);
	if (str == NULL)
		return (NULL);
	while (i < var)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
