/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:41:33 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/22 20:45:19 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(char *str, char delim)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != delim)
		{
			count++;
			while (str[i] != delim && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}
