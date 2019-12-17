/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_numbers2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:37:34 by rkamegne          #+#    #+#             */
/*   Updated: 2019/06/25 11:20:32 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t		ft_size_signed(t_conv *type, va_list arg)
{
	if (type->size == 'a' || type->size == 'j')
		return ((long long)va_arg(arg, intmax_t));
	else if (type->size == 'b')
		return ((char)va_arg(arg, intmax_t));
	else if (type->size == 'h')
		return ((short)va_arg(arg, intmax_t));
	else if (type->size == 'l')
		return ((long)va_arg(arg, intmax_t));
	else if (type->size == 'z')
		return (va_arg(arg, ssize_t));
	else
		return (va_arg(arg, int));
}

uintmax_t		ft_size_unsigned(t_conv *type, va_list arg)
{
	if (type->size == 'a')
		return ((unsigned long long)va_arg(arg, uintmax_t));
	else if (type->size == 'b')
		return ((unsigned char)va_arg(arg, uintmax_t));
	else if (type->size == 'h' && type->c != 'U')
		return ((unsigned short)va_arg(arg, uintmax_t));
	else if (type->size == 'l')
		return ((unsigned long)va_arg(arg, uintmax_t));
	else if (type->size == 'j')
		return (va_arg(arg, intmax_t));
	else if (type->size == 'z')
		return (va_arg(arg, size_t));
	else if ((type->c == 'U' && type->size == 'h') || type->c == 'U')
		return (va_arg(arg, unsigned long));
	else
		return (va_arg(arg, unsigned int));
}

long double		ft_size_float(t_conv *type, va_list arg)
{
	if (type->size == 'L')
		return ((long double)va_arg(arg, long double));
	else if (type->size == 'l')
		return ((double)va_arg(arg, double));
	else
		return ((double)va_arg(arg, double));
}

void			ft_fetch_arg3(t_conv *type, va_list arg)
{
	uintmax_t			val;
	long double			nbr;

	if (type->c == 'u' || type->c == 'U')
	{
		type->base = 10;
		val = ft_size_unsigned(type, arg);
		convert_unsigned(val, type);
	}
	else if (type->c == 'x' || type->c == 'X' || type->c == 'b')
	{
		type->base = (type->c == 'b') ? 2 : 16;
		val = ft_size_unsigned(type, arg);
		convert_unsigned(val, type);
	}
	else if (type->c == 'f')
	{
		nbr = ft_size_float(type, arg);
		ft_convert_float(nbr, type);
	}
}
