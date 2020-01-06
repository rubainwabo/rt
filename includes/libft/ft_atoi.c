/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:45:34 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/12 20:50:12 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int		i;
	int		is_negative;
	int		nbr;

	i = 0;
	is_negative = 0;
	nbr = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
			str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		is_negative = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	if (is_negative)
		nbr = -nbr;
	return (nbr);
}
