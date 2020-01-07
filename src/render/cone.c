/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:57:40 by krutten           #+#    #+#             */
/*   Updated: 2020/01/07 22:45:40 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cone_intersect_point(t_ray *ray, t_cone *specs, double height)
{
	t_vec3	tmp;
	t_vec3	tmp2;
	double	hplus;
	double	dist;

	intersection_vec3(ray);
	tmp = vec3_scale(specs->axis, height, '*');
	tmp2 = vec3_add(specs->center, tmp, '+');
	tmp = vec3_add(ray->hitpoint, tmp2, '-');
	dist = sqrt(vec3_dot(tmp, tmp));
	hplus = tan(specs->angle) * dist;
	if (height > 0)
		height += hplus;
	else
		height -= hplus;
	tmp = vec3_scale(specs->axis, height, '*');
	tmp2 = vec3_add(specs->center, tmp, '+');
	ray->hitnormal = vec3_add(ray->hitpoint, tmp2, '-');
	ray->hitnormal = normalise(ray->hitnormal);
	cone_cap_intersect_bot(ray, specs);
	cone_cap_intersect_top(ray, specs);
}

void	cut_cone_tops(t_cone *specs, t_ray *ray, double *t1, double *t2)
{
	double		hi[2];
	t_vec3		sect[4];

	sect[0] = vec3_add(ray->origin, vec3_scale(ray->direct, *t1, '*'), '+');
	sect[2] = vec3_add(sect[0], specs->center, '-');
	if ((hi[0] = vec3_dot(sect[2], specs->axis)) > specs->max ||
						hi[0] < specs->min)
		*t1 = FAR;
	sect[1] = vec3_add(ray->origin, vec3_scale(ray->direct, *t2, '*'), '+');
	sect[3] = vec3_add(sect[1], specs->center, '-');
	if ((hi[1] = vec3_dot(sect[3], specs->axis)) > specs->max ||
						hi[1] < specs->min)
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
		cone_intersect_point(ray, specs, hi[0]);
	}
}

int		cone_intersect(t_rt *spec, t_ray *ray, void *hit_object)
{
	double	abc[3];
	t_vec3	oc;
	double	t1;
	double	t2;
	t_cone	*specs;

	(void)spec;
	specs = (t_cone *)hit_object;
	oc = vec3_add(ray->origin, specs->center, '-');
	abc[0] = pow(vec3_dot(ray->direct, specs->axis), 2)
			- pow(cos(specs->angle), 2);
	abc[1] = 2 * ((vec3_dot(ray->direct, specs->axis)
			* vec3_dot(oc, specs->axis)) - (vec3_dot(ray->direct, oc)
				* pow(cos(specs->angle), 2)));
	abc[2] = pow(vec3_dot(oc, specs->axis), 2) - (vec3_dot(oc, oc)
			* pow(cos(specs->angle), 2));
	if (!solve_polynom_2(abc, &t1, &t2))
		return (0);
	if (t1 < NEAR && (t2 < NEAR))
		return (0);
	cut_cone_tops(specs, ray, &t1, &t2);
	return (1);
}
