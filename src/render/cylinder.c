/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:57:36 by krutten           #+#    #+#             */
/*   Updated: 2019/12/14 14:55:43 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rtv1.h"

int		solve_polynom_2(double *abc, double *t1, double *t2)
{
	double	d;

	d = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (d < 0)
		return (0);
	*t1 = (-abc[1] + sqrt(d)) / (2 * abc[0]);
	*t2 = (-abc[1] - sqrt(d)) / (2 * abc[0]);
	return (1);
}

void	cut_cyl_tops(t_cyl *specs, t_ray *ray, double *t1, double *t2)
{
	double		hi[2];
	t_vec3		sect[4];

	sect[0] = vec3_add(ray->origin, vec3_scale(ray->direct, *t1, '*'), '+');
	sect[2] = vec3_add(sect[0], specs->center, '-');
	if ((hi[0] = vec3_dot(sect[2], specs->axis)) > specs->max || hi[0] < 0)
		*t1 = FAR;
	sect[1] = vec3_add(ray->origin, vec3_scale(ray->direct, *t2, '*'), '+');
	sect[3] = vec3_add(sect[1], specs->center, '-');
	if ((hi[1] = vec3_dot(sect[3], specs->axis)) > specs->max || hi[1] < 0)
		*t2 = FAR;
	if (*t2 < *t1 && *t2 > NEAR)
	{
		*t1 = *t2;
		sect[0] = sect[1];
		hi[0] = hi[1];
	}
	if (*t1 < ray->t && *t1 > NEAR)
	{
		ray->surf = specs->surf;
		ray->t = *t1;
		sect[2] = vec3_add(specs->center, vec3_scale(specs->axis, hi[0],
					'*'), '+');
		ray->hitnormal = normalise(vec3_add(sect[0], sect[2], '-'));
	}
}

int		cylinder_intersect(t_rt *spec, t_ray *ray, void *hit_object)
{
	double	abc[3];
	t_vec3	oc;
	double	t1;
	double	t2;
	t_cyl	*specs;

	(void) spec;
	specs = (t_cyl *)hit_object;
	oc = vec3_add(ray->origin, specs->center, '-');
	abc[0] = 1 - (vec3_dot(ray->direct, specs->axis) * vec3_dot(ray->direct,
			specs->axis));
	abc[1] = 2 * (vec3_dot(ray->direct, oc) - (vec3_dot(ray->direct,
			specs->axis) * vec3_dot(oc, specs->axis)));
	abc[2] = vec3_dot(oc, oc) - (vec3_dot(oc, specs->axis) *
			vec3_dot(oc, specs->axis)) - (specs->radius * specs->radius);
	if (!solve_polynom_2(abc, &t1, &t2))
		return (0);
	if (t1 < NEAR && t2 < NEAR)
		return (0);
	cut_cyl_tops(specs, ray, &t1, &t2);
	if (ray->t == t1)
		intersection_vec3(ray);
	cap_intersect_bot(ray, specs);
	cap_intersect_top(ray, specs);
	return (1);
}
