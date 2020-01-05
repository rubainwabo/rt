/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colouring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:18:25 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/18 12:49:29 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		shading_far(t_rt *specs, int x, int y)
{
	specs->img->data[(y * specs->w_img + x) * 4] = specs->far_col & 0xff;
	specs->img->data[(y * specs->w_img + x) * 4 + 1] =
			(specs->far_col >> 8) & 0xff;
	specs->img->data[(y * specs->w_img + x) * 4 + 2] =
			(specs->far_col >> 16) & 0xff;
}

void		shading(t_ray *ray, t_rt *specs, int x, int y)
{
	int				r;
	int				g;
	int				b;
	float			exposure;

	exposure = -0.66f;
	r = (1.0f - expf(ray->colour.x * exposure)) * 255.0;
	g = (1.0f - expf(ray->colour.y * exposure)) * 255.0;
	b = (1.0f - expf(ray->colour.z * exposure)) * 255.0;
	specs->img->data[(y * specs->w_img + x) * 4] = b;
	specs->img->data[(y * specs->w_img + x) * 4 + 1] = g;
	specs->img->data[(y * specs->w_img + x) * 4 + 2] = r;
}

int			diffuse_prot(t_ray *ray, t_rt *specs, t_ray *original)
{
	ray->origin = original->origin;
	ray->direct = original->direct;
	lighting(ray, specs);
	return (0);
}

int			colour_mask(float att, t_vec3 col, t_ray *ray)
{
	ray->colour.x *= att * col.x;
	ray->colour.y *= att * col.y;
	ray->colour.z *= att * col.z;
	return (0);
}
