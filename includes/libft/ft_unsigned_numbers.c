/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_numbers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:37:13 by rkamegne          #+#    #+#             */
/*   Updated: 2019/06/25 11:20:23 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_prefix(uintmax_t val, t_conv *type)
{
	char	*pre;

	type->h = (val == 0 && type->precision != 0) ? 0 : type->h;
	pre = (type->h && type->base == 8) ? ft_str_putchar('0', 1) : NULL;
	if (type->h && type->base == 16 && val != 0)
	{
		pre = ft_strnew(2);
		if (type->c == 'x')
			pre = ft_strcpy(pre, "0x");
		else
			pre = ft_strcpy(pre, "0X");
	}
	return (pre);
}

void	ft_padding_no_preu(uintmax_t val, t_conv *type, char *str,
															int len)
{
	char	*strp;
	int		add;
	char	*pre;

	pre = ft_prefix(val, type);
	if (type->padding > len)
	{
		add = (type->precision == -1 && type->z != 0 && type->m == 0) ? 48 : 32;
		type->padding -= len;
		type->padding -= (type->h && type->base == 8) ? 1 : 0;
		type->padding -= (type->h && type->base == 16 && str != NULL) ? 2 : 0;
		strp = ft_str_putchar(add, type->padding);
		strp = (add == 48) ? ft_strjoin_free(pre, strp) : strp;
		str = (add == 32) ? ft_strjoin_free(pre, str) : str;
		ft_putrev_str(str, strp, type);
	}
	else
	{
		str = ft_strjoin_free(pre, str);
		type->count += ft_strlen_err(str);
		ft_putstr(str);
		ft_strdel(&str);
	}
}

void	ft_padding_preu(t_conv *type, char *str)
{
	char	*strp;

	if (type->padding > type->precision)
	{
		type->padding -= type->precision;
		type->padding -= (type->h && type->base == 8) ? 1 : 0;
		type->padding -= (type->h && type->base == 16) ? 2 : 0;
		strp = ft_str_putchar(' ', type->padding);
		ft_putrev_str(str, strp, type);
	}
	else
	{
		type->count += ft_strlen_err(str);
		ft_putstr(str);
		ft_strdel(&str);
	}
}

void	convert_unsigned(uintmax_t val, t_conv *type)
{
	char	*str;
	char	*tmp;
	char	*pre;
	int		len;

	len = ft_nb_len(val, type->base);
	str = ft_utoa_base(val, type->base, (type->c == 'X') ? 1 : 0, len);
	if (type->precision > len)
	{
		pre = ft_prefix(val, type);
		str = ((type->h && type->base == 8) || (type->precision == -1 &&
		type->padding == 0 && type->base == 16)) ?
		ft_strjoin_free(pre, str) : str;
		type->precision -= (type->h && type->base == 8) ? 1 : 0;
		tmp = ft_str_putchar('0', (type->precision - len));
		str = ft_strjoin_free(tmp, str);
		str = (type->h && type->base == 16) ? ft_strjoin_free(pre, str) : str;
		ft_padding_preu(type, str);
	}
	else
	{
		(type->precision == 0 && val == 0) ? ft_padding_no_preu(val,
		type, NULL, 0) : ft_padding_no_preu(val, type, str, len);
		(type->precision == 0 && val == 0) ? ft_strdel(&str) : 0;
	}
}
