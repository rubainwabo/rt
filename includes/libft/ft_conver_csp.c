/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_csp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:36:54 by rkamegne          #+#    #+#             */
/*   Updated: 2019/06/25 11:20:01 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	convert_char(unsigned char c, t_conv *type)
{
	char	*str;
	char	add;

	if (type->padding)
	{
		add = (type->z != 0 && type->m == 0) ? '0' : ' ';
		type->padding--;
		str = ft_str_putchar(add, type->padding);
		ft_putrev_char(c, str, type);
	}
	else
	{
		type->count++;
		ft_putchar(c);
	}
}

void	convert_string(char *s, t_conv *type)
{
	char	*str;
	char	*strp;
	int		len;
	char	add;

	len = ft_strlen_err(s);
	if (type->precision > -1)
		str = ft_strccpy(s, type->precision);
	else
		str = ft_strccpy(s, len);
	len = (type->precision >= 0 &&
			type->precision <= len) ? type->precision : len;
	if (type->padding > len)
	{
		add = (type->z != 0 && type->m == 0) ? '0' : ' ';
		type->padding -= len;
		strp = ft_str_putchar(add, type->padding);
		ft_putrev_str(str, strp, type);
	}
	else
	{
		type->count += ft_strlen_err(str);
		ft_putstr(str);
		ft_strdel(&str);
	}
}

void	convert_pointer(unsigned long long ptr, t_conv *type)
{
	char	*str;
	char	*strp;
	char	add;
	int		len;
	char	*tmp;

	tmp = ft_utoa_base(ptr, 16, 0, ft_nb_len(ptr, 16));
	str = ft_strjoin("0x", tmp);
	len = ft_strlen_err(str);
	ft_strdel(&tmp);
	if (type->padding > len)
	{
		add = ' ';
		type->padding -= len;
		strp = ft_str_putchar(add, type->padding);
		ft_putrev_str(str, strp, type);
	}
	else
	{
		type->count += ft_strlen_err(str);
		ft_putstr(str);
		ft_strdel(&str);
	}
}

void	ft_fetch_arg(t_conv *type, va_list arg)
{
	unsigned int		val;
	char				*str;
	unsigned long long	ptr;

	if (type->c == 'c' || type->c == '%')
	{
		val = (type->c == '%') ? '%' : va_arg(arg, unsigned int);
		convert_char((unsigned char)val, type);
	}
	else if (type->c == 's')
	{
		if (!(str = va_arg(arg, char*)))
		{
			ft_putnull(type);
			return ;
		}
		convert_string(str, type);
	}
	else if (type->c == 'p')
	{
		ptr = va_arg(arg, unsigned long long);
		convert_pointer(ptr, type);
	}
	else
		ft_fetch_arg2(type, arg);
}
