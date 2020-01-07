/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:54:16 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/07 22:39:16 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		uv_plane_compute(t_plane *p, t_vec3 coord, t_ray *ray,
		double stretch)
{
	t_vec3	u_base;
	t_vec3	v_base;
	double	u;
	double	v;

	if (p->normal.x || p->normal.y)
		u_base = vec3_init(-p->normal.y, p->normal.x, 0);
	else
		u_base = vec3_init(1, 0, 0);
	u_base = normalise(u_base);
	v_base = vec3_cross(p->normal, u_base);
	v_base = normalise(v_base);
	u = vec3_dot(u_base, coord);
	u = fabs(u);
	u = (u / 10) * stretch;
	u = fmod(u, 1.0);
	v = vec3_dot(v_base, coord);
	v = fabs(v);
	v = (v / 10) * stretch;
	v = fmod(v, 1.0);
	return ((int)(u * ray->surf->texture->width) + (int)(v *
			ray->surf->texture->height) * ray->surf->texture->width);
}

t_vec3	plane_texturing(t_plane *p, t_ray *ray, t_rt *specs)
{
	int		offset;
	int		color;
	t_vec3	output;

	offset = uv_plane_compute(p, vec3_add(ray->hitpoint, p->point, '-'),
			ray, specs->texstretch);
	ft_memcpy(&color, &ray->surf->texture->data[4 * offset], 4);
	output.x = ((color >> 16) & 0xff) / 255.0;
	output.y = ((color >> 8) & 0xff) / 255.0;
	output.z = (color & 0xff) / 255.0;
	return (output);
}

int		uv_sphere_compute(t_vec3 coord, t_ray *ray, double umove, double vmove)
{
	double	theta;
	double	phi;
	double	u;
	double	v;

	theta = atan(coord.x / coord.z);
	phi = asin(-coord.y);
	u = (theta + M_PI) / (2 * M_PI);
	u = fmod(u + (umove / 20), 1.0);
	v = (phi + M_PI / 2.0) / (M_PI);
	v = fmod(v + (vmove / 20), 1.0);
	printf("u %f, v %f, umove %f, vmove %f\n", u, v, umove, vmove);
	u = fabs(u);
	v = fabs(v);
	if (v > 0.9999)
		return (0);
	return ((int)(u * ray->surf->texture->width) + (int)(v *
			ray->surf->texture->height) * ray->surf->texture->width);
}

t_vec3	sphere_texturing(t_sphere *s, t_ray *ray, t_rt *specs)
{
	int		offset;
	int		color;
	t_vec3	output;

	offset = uv_sphere_compute(normalise(vec3_add(ray->hitpoint, s->center,
			'-')), ray, specs->texmove[0], specs->texmove[1]);
	ft_memcpy(&color, &ray->surf->texture->data[4 * offset], 4);
	output.x = ((color >> 16) & 0xff) / 255.0;
	output.y = ((color >> 8) & 0xff) / 255.0;
	output.z = (color & 0xff) / 255.0;
	return (output);
}
