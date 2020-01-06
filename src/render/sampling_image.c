/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:21:28 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/06 16:41:24 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		fill_super_sampling(t_rt *specs, t_var *v)
{
	specs->img_s->data[v->coord[4]] = (((v->pix[0] & 0xff) + (v->pix[1] & 0xff)
							+ (v->pix[2] & 0xff) + (v->pix[3] & 0xff)) / 4);
	specs->img_s->data[v->coord[4] + 1] = ((((v->pix[0] >> 8) & 0xff) +
	((v->pix[1] >> 8) & 0xff) + ((v->pix[2] >> 8) & 0xff) + ((v->pix[3] >> 8) &
																0xff)) / 4);
	specs->img_s->data[v->coord[4] + 2] = ((((v->pix[0] >> 16) & 0xff)
					+ ((v->pix[1] >> 16) & 0xff) + ((v->pix[2] >> 16) & 0xff)
										+ ((v->pix[3] >> 16) & 0xff)) / 4);
}

void			super_sampling(t_rt *specs)
{
	int		i;
	int		j;
	t_var	v;

	i = 0;
	while (i < H_IMG)
	{
		j = 0;
		while (j < W_IMG)
		{
			v.coord[0] = (j * 8) + (i * 2) * specs->img->sizeline;
			v.coord[1] = (j * 8) + 4 + (i * 2) * specs->img->sizeline;
			v.coord[2] = (j * 8) + ((i * 2) + 1) * specs->img->sizeline;
			v.coord[3] = (j * 8) + 4 + ((i * 2) + 1) * specs->img->sizeline;
			ft_memcpy(&v.pix[0], specs->img->data + v.coord[0], 4);
			ft_memcpy(&v.pix[1], specs->img->data + v.coord[1], 4);
			ft_memcpy(&v.pix[2], specs->img->data + v.coord[2], 4);
			ft_memcpy(&v.pix[3], specs->img->data + v.coord[3], 4);
			v.coord[4] = i * specs->img_s->sizeline + (j * 4);
			fill_super_sampling(specs, &v);
			j++;
		}
		i++;
	}
}

static void		fill_sub_sampling(t_rt *specs, t_var *v)
{
	specs->img_s->data[v->coord[0]] = v->pix[0] & 0xff;
	specs->img_s->data[v->coord[0] + 1] = (v->pix[0] >> 8) & 0xff;
	specs->img_s->data[v->coord[0] + 2] = (v->pix[0] >> 16) & 0xff;
	specs->img_s->data[v->coord[1]] = v->pix[0] & 0xff;
	specs->img_s->data[v->coord[1] + 1] = (v->pix[0] >> 8) & 0xff;
	specs->img_s->data[v->coord[1] + 2] = (v->pix[0] >> 16) & 0xff;
	specs->img_s->data[v->coord[2]] = v->pix[0] & 0xff;
	specs->img_s->data[v->coord[2] + 1] = (v->pix[0] >> 8) & 0xff;
	specs->img_s->data[v->coord[2] + 2] = (v->pix[0] >> 16) & 0xff;
	specs->img_s->data[v->coord[3]] = v->pix[0] & 0xff;
	specs->img_s->data[v->coord[3] + 1] = (v->pix[0] >> 8) & 0xff;
	specs->img_s->data[v->coord[3] + 2] = (v->pix[0] >> 16) & 0xff;
}

void			sub_sampling(t_rt *specs)
{
	int		i;
	int		j;
	t_var	v;

	i = 0;
	while (i < specs->h_img)
	{
		j = 0;
		while (j < specs->w_img)
		{
			v.coord[4] = (j * 4) + i * specs->img->sizeline;
			ft_memcpy(&v.pix[0], specs->img->data + v.coord[4], 4);
			v.coord[0] = (j * 8) + i * 2 * specs->img_s->sizeline;
			v.coord[1] = v.coord[0] + 4;
			v.coord[2] = (j * 8) + ((i * 2) + 1) * specs->img_s->sizeline;
			v.coord[3] = v.coord[2] + 4;
			fill_sub_sampling(specs, &v);
			j++;
		}
		i++;
	}
}
