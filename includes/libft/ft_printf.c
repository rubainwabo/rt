/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:36:15 by rkamegne          #+#    #+#             */
/*   Updated: 2019/06/25 11:20:56 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf(const char *restrict format, ...)
{
	va_list	arg;
	int		count;

	va_start(arg, format);
	count = ft_parse(format, arg);
	va_end(arg);
	return (count);
}
