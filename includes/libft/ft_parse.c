/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:08:56 by rkamegne          #+#    #+#             */
/*   Updated: 2019/06/25 11:24:24 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_get_size(t_conv *type, char *format, int i)
{
	int			count;

	count = 0;
	if (type->c == 'f' && format[i] == 'L' && (type->size = 'L'))
		return ;
	else if (format[i] == 'j')
		type->size = 'j';
	else if (format[i] == 'z' && type->size != 'j')
		type->size = 'z';
	else if (format[i] == 'l' && type->size != 'a' && type->size != 'z'
	&& type->size != 'j' && type->size != 'l' &&
	(count = ft_count_words(format + i, 'l')))
		type->size = (count % 2) ? 'l' : 'a';
	else if (format[i] == 'h' && type->size != 'z' && type->size != 'j' &&
		type->size != 'a' && type->size != 'l' &&
		type->size != 'b' && type->size != 'h' &&
		(count = ft_count_words(format + i, 'h')))
		type->size = (count % 2) ? 'h' : 'b';
}

static	void	ft_get_prec_padd(t_conv *type, char *format, int *i)
{
	if (format[*i] == '.')
	{
		*i += 1;
		type->precision = ft_patoi(format, i);
	}
	else if (ft_isdigit(format[*i]) && (format[*i] - '0') > 0)
		type->padding = ft_patoi(format, i);
	else
		ft_get_size(type, format, *i);
}

static	void	ft_get_options(char *format, t_conv *type, int offset)
{
	int			i;

	i = -1;
	while (++i < offset)
	{
		if (format[i] == '+')
			type->p = 1;
		else if (format[i] == '-')
			type->m = 1;
		else if (format[i] == '#')
			type->h = 1;
		else if (format[i] == ' ')
			type->s = 1;
		else if (format[i] == '0')
			type->z = 1;
		else
			ft_get_prec_padd(type, format, &i);
	}
}

static	char	*ft_parse_conv(char *format, va_list arg, t_conv *type)
{
	unsigned int		offset;
	char				*o;
	unsigned int		i;

	o = NULL;
	i = -1;
	offset = 0;
	while (TYPES[++i])
	{
		if ((o = ft_strchr_alpha(format, TYPES[i])))
		{
			offset = o - format;
			break ;
		}
	}
	if (o != NULL)
	{
		type->c = *o;
		ft_get_options(format, type, offset);
		ft_fetch_arg(type, arg);
		format += offset;
	}
	else
		format--;
	return (format);
}

int				ft_parse(const char *restrict format, va_list arg)
{
	t_conv				type;
	int					count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if (ft_init(&type) == -1)
				return (-1);
			if (!(format = ft_parse_conv((char*)(format + 1), arg, &type)))
				return (-1);
			count += type.count;
		}
		else
		{
			ft_putchar(*format);
			count++;
		}
		format++;
	}
	return (count);
}
