/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:16:27 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/07 20:37:09 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** simple trick converting char to unsigned char to fix overflows
*/

void		apply_sepia(t_rt *specs)
{
	t_var	v;
	int		i;
	int		comp;

	i = 0;
	comp = H_IMG * W_IMG * 4;
	while (i < comp)
	{
		v.red = ft_min(255.0, (((unsigned char)specs->img_s->data[i + 2] * .393)
							+ ((unsigned char)specs->img_s->data[i + 1] * .769)
							+ ((unsigned char)specs->img_s->data[i] * .189)));
		v.green = ft_min(255.0, (((unsigned char)specs->img_s->data[i + 2]
					* .349) + ((unsigned char)specs->img_s->data[i + 1] * .686)
					+ ((unsigned char)specs->img_s->data[i] * .168)));
		v.blue = ft_min(255.0, (((unsigned char)specs->img_s->data[i + 2]
					* .272) + ((unsigned char)specs->img_s->data[i + 1] * .534)
							+ ((unsigned char)specs->img_s->data[i] * .131)));
		specs->img_s->data[i + 2] = v.red;
		specs->img_s->data[i + 1] = v.green;
		specs->img_s->data[i] = v.blue;
		i += 4;
	}
}

void		apply_grayscale(t_rt *specs)
{
	int comp;
	int	i;
	int	gray;

	i = 0;
	comp = H_IMG * W_IMG * 4;
	while (i < comp)
	{
		gray = (int)(((unsigned char)specs->img_s->data[i + 2] * 0.3) +
		((unsigned char)specs->img_s->data[i + 1] * 0.59) +
		((unsigned char)specs->img_s->data[i] * 0.11));
		specs->img_s->data[i + 2] = gray;
		specs->img_s->data[i + 1] = gray;
		specs->img_s->data[i] = gray;
		i += 4;
	}
}

void		apply_blue(t_rt *specs)
{
	int comp;
	int	i;
	int	gray;

	i = 0;
	comp = H_IMG * W_IMG * 4;
	while (i < comp)
	{
		gray = (int)(((unsigned char)specs->img_s->data[i + 2] * 0.3) +
		((unsigned char)specs->img_s->data[i + 1] * 0.59) +
		((unsigned char)specs->img_s->data[i] * 0.11));
		specs->img_s->data[i + 2] = 0;
		specs->img_s->data[i + 1] = 0;
		specs->img_s->data[i] = gray;
		i += 4;
	}
}

void		apply_red(t_rt *specs)
{
	int comp;
	int	i;
	int	gray;

	i = 0;
	comp = H_IMG * W_IMG * 4;
	while (i < comp)
	{
		gray = (int)(((unsigned char)specs->img_s->data[i + 2] * 0.3) +
		((unsigned char)specs->img_s->data[i + 1] * 0.59) +
		((unsigned char)specs->img_s->data[i] * 0.11));
		specs->img_s->data[i + 2] = gray;
		specs->img_s->data[i + 1] = 0;
		specs->img_s->data[i] = 0;
		i += 4;
	}
}

void		reverse_chan(t_rt *specs)
{
	int comp;
	int	i;

	i = 0;
	comp = H_IMG * W_IMG * 4;
	while (i < comp)
	{
		specs->img_s->data[i + 2] = (unsigned char)
		(255 - specs->img_s->data[i + 2]);
		specs->img_s->data[i + 1] = (unsigned char)
		(255 - specs->img_s->data[i + 1]);
		specs->img_s->data[i] = (unsigned char)
		(255 - specs->img_s->data[i]);
		i += 4;
	}
}
