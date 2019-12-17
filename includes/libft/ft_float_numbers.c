/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:37:24 by rkamegne          #+#    #+#             */
/*   Updated: 2019/06/25 11:22:35 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_float_sign(double nbr, t_conv *type)
{
	char	*sign;
	int64_t	*pointer;

	pointer = (int64_t *)&nbr;
	if (*pointer >> 63)
	{
		sign = ft_str_putchar('-', 1);
		type->s = 0;
	}
	else
		sign = (type->p) ? ft_str_putchar('+', 1) : NULL;
	type->s = (type->p) ? 0 : type->s;
	type->count += (type->s) ? 1 : 0;
	return (sign);
}

double			ft_roundf(long double nbr, int precision)
{
	long double		diviseur;

	diviseur = 5;
	if (precision == 0)
		return (nbr + (nbr > 0.0 ? 0.5 : -0.5));
	while (precision-- >= 0)
		diviseur /= 10;
	return (nbr + (nbr > 0.0 ? diviseur : -diviseur));
}

char			*ft_ftoa(long double nbr, t_conv *type)
{
	char				*str;
	int					i;
	long double			dec;

	i = 0;
	nbr = (nbr < 0) ? -nbr : nbr;
	if (!(str = ft_strnew(type->precision + 1)))
		return (NULL);
	if (type->h == 0 && type->precision == 0)
	{
		ft_strdel(&str);
		return (ft_utoa((unsigned long long)nbr));
	}
	str[i] = '.';
	if (type->h && type->precision == 0)
		return (ft_strjoin_free(ft_utoa((unsigned long long)nbr), str));
	str[type->precision + 1] = '\0';
	dec = nbr - (long long)nbr;
	while (++i < type->precision + 1)
	{
		dec *= 10;
		str[i] = (long long)dec + '0';
		dec -= (long long)dec;
	}
	return (ft_strjoin_free(ft_utoa((unsigned long long)nbr), str));
}

void			ft_convert_float(long double nbr, t_conv *type)
{
	char	*sign;
	char	*str;
	int		tmp;

	sign = ft_float_sign(nbr, type);
	tmp = type->precision;
	if (type->precision == -1)
		type->precision = 6;
	nbr = ft_roundf(nbr, type->precision);
	if (!(str = ft_ftoa(nbr, type)))
	{
		ft_strdel(&sign);
		return ;
	}
	type->precision = tmp;
	type->take = 1;
	ft_padding_no_pre(sign, type, str);
}
