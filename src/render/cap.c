/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:29:57 by krutten           #+#    #+#             */
/*   Updated: 2019/11/05 14:16:48 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	compute_oc(t_vec3 *oc, t_ray *ray, double t)
{
	oc->x = ray->origin.x + t * ray->direct.x;
	oc->y = ray->origin.y + t * ray->direct.y;
	oc->z = ray->origin.z + t * ray->direct.z;
}

int		cap_intersect_bot(t_ray *ray, t_cyl *specs)
{
	t_var	v;

	v.p.point = specs->center;
	v.p.normal = specs->axis;
	v.p.surf = specs->surf;
	v.oc = vec3_add(ray->origin, v.p.point, '-');
	if (vec3_dot(ray->direct, v.p.normal) == 0)
		return (0);
	v.t = (vec3_dot(v.oc, v.p.normal) * (-1))
		/ vec3_dot(ray->direct, v.p.normal);
	compute_oc(&v.oc, ray, v.t);
	v.dist = sqrt(pow(v.oc.x - v.p.point.x, 2) + pow(v.oc.y - v.p.point.y, 2) +
	pow(v.oc.z - v.p.point.z, 2));
	if (v.t < ray->t && v.t > NEAR && v.dist < specs->radius)
	{
		ray->t = v.t;
		ray->surf = v.p.surf;
		intersection_vec3(ray);
		ray->hitnormal = v.p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cap_intersect_top(t_ray *ray, t_cyl *specs)
{
	t_var	v;

	v.p.point = vec3_scale(specs->axis, specs->max, '*');
	v.p.point = vec3_add(specs->center, v.p.point, '+');
	v.p.normal = specs->axis;
	v.p.surf = specs->surf;
	v.oc = vec3_add(ray->origin, v.p.point, '-');
	if (vec3_dot(ray->direct, v.p.normal) == 0)
		return (0);
	v.t = (vec3_dot(v.oc, v.p.normal) * (-1))
		/ vec3_dot(ray->direct, v.p.normal);
	compute_oc(&v.oc, ray, v.t);
	v.dist = sqrt(pow(v.oc.x - v.p.point.x, 2) + pow(v.oc.y - v.p.point.y, 2) +
	pow(v.oc.z - v.p.point.z, 2));
	if (v.t < ray->t && v.t > NEAR && v.dist < specs->radius)
	{
		ray->t = v.t;
		ray->surf = v.p.surf;
		intersection_vec3(ray);
		ray->hitnormal = v.p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cone_cap_intersect_bot(t_ray *ray, t_cone *specs)
{
	t_var	v;

	v.p.point = vec3_scale(specs->axis, specs->min, '*');
	v.p.point = vec3_add(specs->center, v.p.point, '+');
	v.p.normal = specs->axis;
	v.p.surf = specs->surf;
	v.oc = vec3_add(ray->origin, v.p.point, '-');
	if (vec3_dot(ray->direct, v.p.normal) == 0)
		return (0);
	v.t = (vec3_dot(v.oc, v.p.normal) * (-1))
		/ vec3_dot(ray->direct, v.p.normal);
	compute_oc(&v.oc, ray, v.t);
	v.dist = sqrt(pow(v.oc.x - v.p.point.x, 2) + pow(v.oc.y - v.p.point.y, 2) +
	pow(v.oc.z - v.p.point.z, 2));
	v.rad = tan(specs->angle) * ft_abs(specs->min);
	if (v.t < ray->t && v.t > NEAR && v.dist < v.rad)
	{
		ray->t = v.t;
		ray->surf = v.p.surf;
		intersection_vec3(ray);
		ray->hitnormal = v.p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cone_cap_intersect_top(t_ray *ray, t_cone *specs)
{
	t_var	v;

	v.p.point = vec3_scale(specs->axis, specs->max, '*');
	v.p.point = vec3_add(specs->center, v.p.point, '+');
	v.p.normal = specs->axis;
	v.p.surf = specs->surf;
	v.oc = vec3_add(ray->origin, v.p.point, '-');
	if (vec3_dot(ray->direct, v.p.normal) == 0)
		return (0);
	v.t = (vec3_dot(v.oc, v.p.normal) * (-1))
	/ vec3_dot(ray->direct, v.p.normal);
	compute_oc(&v.oc, ray, v.t);
	v.dist = sqrt(pow(v.oc.x - v.p.point.x, 2) + pow(v.oc.y - v.p.point.y, 2) +
	pow(v.oc.z - v.p.point.z, 2));
	v.rad = tan(specs->angle) * ft_abs(specs->max);
	if (v.t < ray->t && v.t > NEAR && v.dist < v.rad)
	{
		ray->t = v.t;
		ray->surf = v.p.surf;
		intersection_vec3(ray);
		ray->hitnormal = v.p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}
