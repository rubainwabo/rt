/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling_image2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:33:07 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/06 16:44:26 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		fill(t_rt *specs, int coord, int pix)
{
	specs->img_s->data[coord] = pix & 0xff;
	specs->img_s->data[coord + 1] = (pix >> 8) & 0xff;
	specs->img_s->data[coord + 2] = (pix >> 16) & 0xff;
}

static void		fill_sub2_sampling(t_rt *specs, t_var *v)
{
	fill(specs, v->coord[0], v->pix[0]);
	fill(specs, v->coord[1], v->pix[0]);
	fill(specs, v->coord[2], v->pix[0]);
	fill(specs, v->coord[3], v->pix[0]);
	fill(specs, v->coord[4], v->pix[0]);
	fill(specs, v->coord[5], v->pix[0]);
	fill(specs, v->coord[6], v->pix[0]);
	fill(specs, v->coord[7], v->pix[0]);
	fill(specs, v->coord[8], v->pix[0]);
	fill(specs, v->coord[9], v->pix[0]);
	fill(specs, v->coord[10], v->pix[0]);
	fill(specs, v->coord[11], v->pix[0]);
	fill(specs, v->coord[12], v->pix[0]);
	fill(specs, v->coord[13], v->pix[0]);
	fill(specs, v->coord[14], v->pix[0]);
	fill(specs, v->coord[15], v->pix[0]);
}

static void		compute_coord(t_rt *specs, t_var *v, int i, int j)
{
	v->coord[16] = (j * 4) + i * specs->img->sizeline;
	ft_memcpy(&v->pix[0], specs->img->data + v->coord[16], 4);
	v->coord[0] = (j * 16) + i * 4 * specs->img_s->sizeline;
	v->coord[1] = v->coord[0] + 4;
	v->coord[2] = v->coord[0] + 8;
	v->coord[3] = v->coord[0] + 12;
	v->coord[4] = (j * 16) + ((i * 4) + 1) * specs->img_s->sizeline;
	v->coord[5] = v->coord[4] + 4;
	v->coord[6] = v->coord[4] + 8;
	v->coord[7] = v->coord[4] + 12;
	v->coord[8] = (j * 16) + ((i * 4) + 2) * specs->img_s->sizeline;
	v->coord[9] = v->coord[8] + 4;
	v->coord[10] = v->coord[8] + 8;
	v->coord[11] = v->coord[8] + 12;
	v->coord[12] = (j * 16) + ((i * 4) + 3) * specs->img_s->sizeline;
	v->coord[13] = v->coord[12] + 4;
	v->coord[14] = v->coord[12] + 8;
	v->coord[15] = v->coord[12] + 12;
}

void			sub2_sampling(t_rt *specs)
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
			compute_coord(specs, &v, i, j);
			fill_sub2_sampling(specs, &v);
			j++;
		}
		i++;
	}
}
