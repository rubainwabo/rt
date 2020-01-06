/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:32:15 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/09 15:53:46 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		after_point(long double nb, const char *str)
{
	int		i;
	double	base;

	i = 0;
	base = 0.1;
	if (str[i++] == '.')
	{
		while (ft_isdigit(str[i]))
		{
			nb += ((str[i] - '0') * base);
			base /= 10;
			i++;
		}
	}
	return ((double)nb);
}

double		ft_atof(const char *str)
{
	long double		nb;
	int				i;
	int				signe;

	i = 0;
	nb = 0.0;
	signe = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10;
		nb = nb + (str[i] - '0');
		i++;
	}
	return ((after_point(nb, &str[i]) * signe));
}
