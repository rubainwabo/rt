/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:28:55 by rkamegne          #+#    #+#             */
/*   Updated: 2019/05/03 21:29:18 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		i;

	i = -1;
	str = NULL;
	if (!s1 || !s2)
		return ((s1) ? s1 : s2);
	if (!(str = (char*)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	str = ft_strcat_free(str, s2);
	ft_strdel(&s1);
	return (str);
}
