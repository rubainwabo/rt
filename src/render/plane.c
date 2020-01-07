/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:29:57 by krutten           #+#    #+#             */
/*   Updated: 2020/01/07 23:44:54 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		bump_map(t_ray *ray, t_plane *spec, double bumpwidth,
																t_vec3 parallel)
{
	double	dist;
	t_vec3	temp;
	t_vec3	temp2;
	t_mat3	rot;

	temp = vec3_add(ray->hitpoint, spec->point, '-');
	temp2 = vec3_scale(parallel, vec3_dot(temp, parallel), '*');
	temp = vec3_add(temp, temp2, '-');
	dist = pow(vec3_dot(temp, temp), 0.5);
	rot = mat3_unit();
	rot_from_base2((cos(fmod(dist / bumpwidth, 1.0) * 2 * 3.1415)) *
												(3.1415 / 6), &parallel, &rot);
	ray->hitnormal = vector_matrix_multiply(ray->hitnormal, rot);
}

void			normal_towards_cam(t_ray *ray)
{
	double	len1;
	double	len2;
	t_vec3	tmp;

	tmp = vec3_add(ray->origin, ray->hitpoint, '-');
	len1 = sqrt(vec3_dot(tmp, tmp));
	tmp = vec3_scale(ray->hitnormal, 0.05, '*');
	tmp = vec3_add(ray->hitpoint, tmp, '+');
	tmp = vec3_add(ray->origin, tmp, '-');
	len2 = sqrt(vec3_dot(tmp, tmp));
	if (len2 > len1)
		ray->hitnormal = vec3_scale(ray->hitnormal, -1.0, '*');
}

static void		plane_intersect2(t_rt *spec, t_ray *ray, t_plane *p, t_vec3 oc)
{
	if (spec->bump == 1)
		bump_map(ray, p, 2, oc);
	if (ray->surf->text)
		ray->texcol = plane_texturing(p, ray, spec);
}

int				plane_intersect(t_rt *spec, t_ray *ray, void *hit_object)
{
	t_vec3	oc;
	double	t;
	t_plane	*p;

	(void)spec;
	p = (t_plane *)hit_object;
	oc = vec3_add(ray->origin, p->point, '-');
	if (vec3_dot(ray->direct, p->normal) == 0)
		return (0);
	t = (vec3_dot(oc, p->normal) * (-1))
		/ vec3_dot(ray->direct, p->normal);
	if (t < ray->t && t > NEAR)
	{
		ray->t = t;
		ray->surf = p->surf;
		intersection_vec3(ray);
		ray->hitnormal = p->normal;
		oc = vec3_init(0, -ray->hitnormal.z, ray->hitnormal.y);
		if (vec3_dot(ray->hitnormal, vec3_init(1, 0, 0)) > 0.999)
			oc = vec3_init(-ray->hitnormal.y, ray->hitnormal.x, 0);
		plane_intersect2(spec, ray, p, oc);
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}
