/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 15:56:58 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/18 21:16:11 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		found;

	found = 0;
	i = 0;
	if (!*needle)
		return ((char*)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		if (needle[j] == haystack[i])
			found = i;
		while (found < len && needle[j] == haystack[found] && needle[j] != '\0')
		{
			j++;
			found++;
			if (needle[j] == '\0')
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
