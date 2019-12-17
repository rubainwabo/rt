/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:29:57 by krutten           #+#    #+#             */
/*   Updated: 2019/12/14 14:56:06 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_towards_cam(t_ray *ray)
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

int		plane_intersect(t_rt *spec, t_ray *ray, void *hit_object)
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
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}
