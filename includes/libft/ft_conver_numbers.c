/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:37:00 by rkamegne          #+#    #+#             */
/*   Updated: 2019/06/25 11:21:43 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_padding_no_pre(char *sign, t_conv *type, char *str)
{
	char	*strp;
	int		add;
	int		len;

	len = (sign) ? ft_strlen_err(str) + 1 : ft_strlen_err(str);
	if (type->padding > len)
	{
		add = (type->take && type->z != 0 && type->m == 0) ? 48 : 32;
		type->padding -= (type->s) ? len + 1 : len;
		strp = ft_str_putchar(add, type->padding);
		if (sign && type->m == 0)
			strp = (add == 48) ? ft_strjoin_free(sign, strp) :
			ft_strjoin_free(strp, sign);
		else if (sign && type->m)
			str = ft_strjoin_free(sign, str);
		(type->s) ? ft_putchar(' ') : 0;
		ft_putrev_str(str, strp, type);
	}
	else
	{
		str = (sign) ? ft_strjoin_free(sign, str) : str;
		(type->s) ? ft_putchar(' ') : 0;
		ft_putrev_str(str, NULL, type);
	}
}

void			ft_padding_pre(char *sign, t_conv *type, char *str)
{
	char	*strp;

	type->precision += (sign) ? 1 : 0;
	if (type->padding > type->precision)
	{
		type->padding -= (type->s) ? type->precision + 1 : type->precision;
		strp = ft_str_putchar(' ', type->padding);
		str = (sign) ? ft_strjoin_free(sign, str)
		: str;
		(type->s) ? ft_putchar(' ') : 0;
		ft_putrev_str(str, strp, type);
	}
	else
	{
		str = (sign) ? ft_strjoin_free(sign, str) : str;
		(type->s) ? ft_putchar(' ') : 0;
		type->count += ft_strlen_err(str);
		ft_putstr(str);
		ft_strdel(&str);
	}
}

static	char	*ft_check_sign(intmax_t nbr, t_conv *type)
{
	char	*sign;

	if (nbr < 0)
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

void			convert_int(intmax_t nbr, t_conv *type)
{
	char	*str;
	char	*tmp;
	char	*sign;
	int		len;

	type->take = (type->precision == -1) ? 1 : 0;
	sign = ft_check_sign(nbr, type);
	len = ft_nb_len(ft_abs(nbr), 10);
	str = ft_utoa_base(ft_abs(nbr), 10, 0, len);
	if (type->precision > len)
	{
		tmp = ft_str_putchar('0', (type->precision - len));
		str = ft_strjoin_free(tmp, str);
		ft_padding_pre(sign, type, str);
	}
	else
	{
		(type->precision == 0 && nbr == 0) ?
		ft_padding_no_pre(sign, type, NULL)
		: ft_padding_no_pre(sign, type, str);
		(type->precision == 0 && nbr == 0) ? ft_strdel(&str) : 0;
	}
}

void			ft_fetch_arg2(t_conv *type, va_list arg)
{
	uintmax_t		val;
	intmax_t		nbr;

	if (type->c == 'd')
	{
		nbr = ft_size_signed(type, arg);
		convert_int(nbr, type);
	}
	else if (type->c == 'i')
	{
		nbr = ft_size_signed(type, arg);
		convert_int(nbr, type);
	}
	else if (type->c == 'o')
	{
		type->base = 8;
		val = ft_size_unsigned(type, arg);
		convert_unsigned(val, type);
	}
	else
		ft_fetch_arg3(type, arg);
}
