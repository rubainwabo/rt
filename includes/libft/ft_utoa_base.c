/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:47:45 by rkamegne          #+#    #+#             */
/*   Updated: 2019/09/23 16:32:38 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long n, int base, int maj, int len)
{
	char				*str;
	char				*temp;
	unsigned long long	nbr;

	nbr = n;
	temp = (base == 10) ? ft_utoa_base(ft_abs(n), base, maj, len) :
	ft_utoa_base(nbr, base, maj, len);
	if (n < 0 && base == 10)
	{
		str = ft_strjoin("-", temp);
		ft_strdel(&temp);
		return (str);
	}
	return (temp);
}

char	*ft_utoa_base(unsigned long long n, int base, int maj, int len)
{
	char	*str;
	int		i;
	char	c;

	c = (maj) ? 'A' : 'a';
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = '\0';
	while (--len > 0)
	{
		i = n % base;
		str[len] = (i >= 10) ? c + (i - 10) : i + '0';
		n /= base;
	}
	str[0] = (n >= 10) ? c + (n - 10) : n + '0';
	return (str);
}
