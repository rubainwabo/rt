/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:04:22 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/22 20:20:30 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace(char *str, int c, int b)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	if (str == NULL)
		return (NULL);
	if (!(s = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			s[i] = b;
		else
			s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
