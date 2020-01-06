/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 13:31:56 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/22 17:23:28 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			nb_len(unsigned int n)
{
	int				i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int			is_negative(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char				*ft_itoa(int n)
{
	unsigned int	nbr;
	char			*str;
	int				len;

	len = 0;
	nbr = is_negative(n);
	len = nb_len(nbr);
	if (n < 0)
		len++;
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = '\0';
	while (--len > 0)
	{
		str[len] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		str[0] = '-';
	else
		str[0] = nbr + '0';
	return (str);
}
