/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 00:13:31 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/22 17:05:00 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if ((s1 == NULL && s2) || (s2 == NULL && s1))
		return (0);
	if (s1 == NULL && s2 == NULL)
		return (1);
	n--;
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] - s2[i] == 0)
		return (1);
	else
		return (0);
}
