/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:10:20 by krutten           #+#    #+#             */
/*   Updated: 2020/01/06 18:42:16 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sphere_inter2(t_rt *specs, t_ray *ray, t_var *v)
{
	(void) specs;
	
	if (v->t2 < v->t1 && v->t2 > NEAR)
		v->t1 = v->t2;
	if (v->t1 < ray->t && v->t1 > NEAR)
	{
		ray->t = v->t1;
		ray->surf = v->s->surf;
		intersection_vec3(ray);
		ray->hitnormal = normalise(vec3_add(ray->hitpoint,
		v->s->center, '-'));
		if (ray->surf->tex)
			ray->texcol = sphere_texturing(v->s, ray);
	}
}

int		sphere_intersect(t_rt *specs, t_ray *ray, void *ptr)
{
	t_var v;

	v.s = (t_sphere *)ptr;
	v.oc = vec3_add(ray->origin, v.s->center, '-');
	v.ext = vec3_add(ray->origin, ray->direct, '+');
	v.ext = vec3_add(v.ext, v.s->center, '-');
	v.b = 2 * vec3_dot(ray->direct, v.oc);
	v.c = vec3_dot(v.oc, v.oc) - (v.s->radius * v.s->radius);
	v.d = v.b * v.b - 4 * v.c;
	if (v.d < 0)
		return (0);
	v.t1 = (-v.b + sqrt(v.d)) / 2;
	v.t2 = (-v.b - sqrt(v.d)) / 2;
	sphere_inter2(specs, ray, &v);
	return (1);
}
