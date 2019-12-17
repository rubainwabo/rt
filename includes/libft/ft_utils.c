/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:15:55 by rkamegne          #+#    #+#             */
/*   Updated: 2019/06/25 11:20:42 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnull(t_conv *type)
{
	type->count += 6;
	ft_putstr("(null)");
}

int		ft_patoi(char *str, int *offset)
{
	int		nbr;

	nbr = 0;
	if (!str)
		return (0);
	while (ft_isdigit(str[*offset]))
	{
		nbr *= 10;
		nbr += str[(*offset)++] - '0';
	}
	(*offset)--;
	return (nbr);
}

void	ft_putrev_char(unsigned char c, char *strp, t_conv *type)
{
	type->count += ft_strlen_err(strp) + 1;
	if (!type->m)
	{
		ft_putstr(strp);
		ft_putchar(c);
	}
	else
	{
		ft_putchar(c);
		ft_putstr(strp);
	}
	ft_strdel(&strp);
}

void	ft_putrev_str(char *str, char *strp, t_conv *type)
{
	type->count += ft_strlen_err(strp) + ft_strlen_err(str);
	if (type->m)
	{
		ft_putstr(str);
		ft_putstr(strp);
	}
	else
	{
		ft_putstr(strp);
		ft_putstr(str);
	}
	ft_strdel(&strp);
	ft_strdel(&str);
}

int		ft_init(t_conv *type)
{
	type->c = '0';
	type->precision = -1;
	type->padding = 0;
	type->size = '0';
	type->s = 0;
	type->m = 0;
	type->z = 0;
	type->h = 0;
	type->p = 0;
	type->count = 0;
	type->base = 0;
	type->take = 0;
	return (0);
}
